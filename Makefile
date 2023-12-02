NAME := ryxemu-server

.PHONY: build
build:
	cd build && make

.PHONY: cmake
cmake:
	mkdir -p build
	cd build && cmake -DEQEMU_BUILD_LOGIN=ON \
			-DEQEMU_BUILD_TESTS=ON \
			-DCMAKE_CXX_COMPILER_LAUNCHER=ccache ..

docker-image-build:
	cd .devcontainer && docker build -t ${NAME} .