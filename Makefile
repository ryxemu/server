NAME := ryxemu-server

DOCKER_ARGS := --rm -v ${PWD}:/src -w /src ${NAME}

.PHONY: build
build:
	cd build && make

.PHONY: cmake
cmake:
	mkdir -p build
	cd build && cmake -DEQEMU_BUILD_LOGIN=ON \
			-DEQEMU_BUILD_TESTS=ON \
			-DCMAKE_CXX_COMPILER_LAUNCHER=ccache ..

docker-cmake: docker-image-check
	docker run ${DOCKER_ARGS} make cmake

docker-build: docker-image-check
	docker run ${DOCKER_ARGS} make build

docker-image-check:
ifeq ($(shell docker images -q ${NAME} 2> /dev/null),)
	@echo "Docker image not found. Building..."
	make docker-image-build
endif

docker-image-build:
	cd .devcontainer && docker build -t ${NAME} .