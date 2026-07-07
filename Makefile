default:
	mkdir -p ./build && cd build && cmake ../ && make -j20 && mv GLTEST ../$(date +%s)