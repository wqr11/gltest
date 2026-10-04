run:
	./build/GLTEST.exe

build:
	ninja -C build
	make run

all:
	cmake -B build -G "Ninja" .
	ninja -C build
	make default
