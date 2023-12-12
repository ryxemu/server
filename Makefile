NAME := ryxemu-server
VERSION ?= 0.0.1

DOCKER_ARGS := --rm  --name ${NAME} -v ${PWD}:/src -w /src ${NAME}

# Run 'ninja' in build directory
.PHONY: build
build:
	@if [ ! -d "build$$BUILD_SUFFIX" ]; then \
		make cmake; \
	fi

	@cd build$$BUILD_SUFFIX && cmake --build . --config Release --target all --

# Run 'cmake' in build directory
.PHONY: cmake
cmake:
	mkdir -p build$$BUILD_SUFFIX
	@cd build$$BUILD_SUFFIX && cmake -DEQEMU_BUILD_LOGIN=ON \
			-DEQEMU_BUILD_TESTS=OFF \
			-DCMAKE_CXX_COMPILER_LAUNCHER=ccache -G Ninja ..

clean:
	rm -rf build
# Run 'cmake' in ubuntu docker container
docker-cmake: docker-image-build
	docker run ${DOCKER_ARGS} make cmake

# Run 'ninja' in ubuntu docker container
docker-build: docker-image-build
	docker run ${DOCKER_ARGS} make build

# Build image if it doesn't exist
docker-image-build:
ifeq ($(shell docker images -q ${NAME} 2> /dev/null),)
	@echo "Docker image not found. Building..."
	cd .devcontainer && docker build -f Dockerfile.ubuntu.dev -t ${NAME} .
endif

# Run 'cmake' in passed docker container
docker-cmake-%: docker-image-build-%
	docker run ${DOCKER_ARGS}-$* make cmake BUILD_SUFFIX=-$*

# Run 'ninja' in passed docker container
docker-build-%: docker-image-build-%
	docker run ${DOCKER_ARGS}-$* make build BUILD_SUFFIX=-$*

docker-clean: clean

# Build image if it doesn't exist
docker-image-build-%:
ifeq ($(shell docker images -q ${NAME}-$* 2> /dev/null),)
	@echo "Docker image ${NAME}-$* not found. Building..."
	cd .devcontainer && docker build -f Dockerfile.$*.dev -t ${NAME}-$* .
endif

# CICD triggers this
set-version:
	sed -i 's/#define VERSION ".*/#define VERSION "$(VERSION)-$(shell git show --format=%h -s)"/g' common/version.h
	@echo "VERSION=${VERSION}-$(shell git show --format=%h -s)" >> $$GITHUB_ENV


MARIADB_VERSION := 11.2.2
MARIADB_FOLDER := mariadb-${MARIADB_VERSION}-linux-systemd-x86_64
OS := $(shell uname -s)

.PHONY: prep
prep:
	@echo "Preparing build/bin for usage..."
	@-cd build/bin && unlink assets
	@cd build/bin && ln -s ../../base/assets assets
	@cp -R -u -p base/login.ini build/bin/login.ini
	@cp -R -u -p base/config.yaml build/bin/config.yaml
	@mkdir -p build/bin/logs
	@mkdir -p build/bin/shared
	@echo "RyXEmu is prepared"

# Runs loginserver binary
.PHONY: loginserver
loginserver:
	cd build/bin && ./loginserver

# Runs shared_memory binary
.PHONY: shared
shared:
	cd build/bin && ./shared_memory

# Runs zone binary
.PHONY: zone
zone:
	@-rm build/bin/logs/zone/zone*.log
	cd build/bin && ./zone

# Runs world binary
.PHONY: world
world:
	@-rm build/bin/logs/world*.log
	cd build/bin && ./world

# Runs ucs binary
.PHONY: ucs
ucs:
	@-rm build/bin/logs/ucs*.log
	cd build/bin && ./ucs

# Runs queryserv binary
.PHONY: queryserv
queryserv:
	@-rm build/bin/logs/query_server*.log
	cd build/bin && ./queryserv

# Start mariaDB standalone
.PHONY: mariadb
mariadb:
	@-killall mariadbd
	cd build/bin/db/${MARIADB_FOLDER}/bin && ./mysqld_safe --defaults-file=${PWD}/build/bin/db/my.cnf &

# Backs up the database
.PHONY: backup-db
backup-db:
	@echo "Backing up the database and zipping it..."
	@-rm -rf build/bin/db/backup
	@-mkdir -p build/bin/db/backup
	cd build/bin/db/${MARIADB_FOLDER}/bin && ./mariabackup --defaults-file=${PWD}/build/bin/db/my.cnf --backup --user=${USER} --socket=${PWD}//var/run/mysqld/mysqld.sock --target-dir=${PWD}/build/bin/db/backup
	cd build/bin/db && tar -czvf backup.tar.gz backup
	@-rm -rf build/bin/db/backup
	@echo "Backup complete. The file is located at build/bin/db/backup.tar.gz"

# Restores the database
.PHONY: restore-db
restore-db:
	@echo "Restoring the database from backup..."
	@-mkdir -p build/bin/db/backup
	cd build/bin/db && tar -xf backup.tar.gz
	cd build/bin/db/${MARIADB_FOLDER}/bin && ./mariabackup --defaults-file=${PWD}/build/bin/db/my.cnf --prepare --user=${USER} --socket=${PWD}//var/run/mysqld/mysqld.sock --target-dir=${PWD}/build/bin/db/backup
	cd build/bin/db && rm -rf backup.tar.gz
	@echo "Restore complete."

# Initializes a standalone copy of mariadb-server
.PHONY: init-db
init-mariadb:
	@echo "Initializing a standalone copy of mariadb-server..."
	@-mkdir -p build/bin/db
	@-sudo service mariadb start
	@# old way, kept for history reasons for portable edition
	@#cd build/bin/db && wget -nc https://mirrors.xtom.com/mariadb//mariadb-${MARIADB_VERSION}/bintar-linux-systemd-x86_64/${MARIADB_FOLDER}.tar.gz
	@#cd build/bin/db && pv ${MARIADB_FOLDER}.tar.gz | tar -xz
	@#cp -R -u -p base/my.cnf build/bin/db/my.cnf
	@#cd build/bin/db/${MARIADB_FOLDER}/scripts && ./mariadb-install-db --defaults-file=${PWD}/build/bin/db/my.cnf --datadir=${PWD}/build/bin/db/data --basedir=${PWD}/build/bin/db/${MARIADB_FOLDER}
	@#cd build/bin/db/${MARIADB_FOLDER}/bin && ./mysqld_safe --initialize-insecure --datadir=${PWD}/build/bin/db/data --defaults-file=${PWD}/build/bin/db/my.cnf
	@#echo "MariaDB is now initialized. Use 'make mariadb' to run it."
	@echo "MariaDB is now initialized."


.PHONY: inject-mariadb
inject-mariadb:
	-mysql -u root -S /var/run/mysqld/mysqld.sock -e 'CREATE DATABASE ryx;'
	-mysql -u root -S /var/run/mysqld/mysqld.sock -e "CREATE USER 'ryx'@'127.0.0.1' IDENTIFIED BY 'ryxpass';"
	-mysql -u root -S /var/run/mysqld/mysqld.sock -e "GRANT ALL PRIVILEGES ON *.* TO 'ryx'@'127.0.0.1';"
	-unzip -p base/db.sql.zip | mysql -u root -S /var/run/mysqld/mysqld.sock --database ryx
	@echo "MariaDB is now injected."