f:
	cmake -B build -G "Ninja" .
	ninja -C build

default:
	ninja -C build
