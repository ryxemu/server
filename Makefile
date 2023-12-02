.PHONY: build
build:
	cd build && make

.PHONY: cmake
cmake:
	mkdir -p build
	cd build && cmake -DEQEMU_BUILD_LOGIN=ON \
			-DEQEMU_BUILD_TESTS=ON \
			-DCMAKE_CXX_COMPILER_LAUNCHER=ccache ..