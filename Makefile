NAME := ryxemu-server
VERSION ?= 0.0.1

DOCKER_ARGS := --rm -v ${PWD}:/src -w /src ${NAME}

# Run 'ninja' in build directory
.PHONY: build
build:
	@if [ ! -d "build$$BUILD_SUFFIX" ]; then \
		make cmake; \
	fi

	@cd build$$BUILD_SUFFIX && ninja

# Run 'cmake' in build directory
.PHONY: cmake
cmake:
	mkdir -p build$$BUILD_SUFFIX
	@cd build$$BUILD_SUFFIX && cmake -DEQEMU_BUILD_LOGIN=ON \
			-DEQEMU_BUILD_TESTS=OFF \
			-DCMAKE_CXX_COMPILER_LAUNCHER=ccache -G Ninja ..

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

# Build image if it doesn't exist
docker-image-build-%:
ifeq ($(shell docker images -q ${NAME}-$* 2> /dev/null),)
	@echo "Docker image ${NAME}-$* not found. Building..."
	cd .devcontainer && docker build -f Dockerfile.$*.dev -t ${NAME}-$* .
endif

# CICD triggers this
.PHONY: update-version
update-version:
	sed -i 's/#define VERSION ".*/#define VERSION "$(VERSION)"/g' common/version.h

# CICD triggers this
.PHONY: set-version
set-version: update-version
	sed -i 's/#define VERSION ".*/#define VERSION "$(VERSION)"/g' common/version.h
	@echo "VERSION=${VERSION}" >> $$GITHUB_ENV