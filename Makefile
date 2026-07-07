default:
	mkdir -p ./build && cd build && cmake ../ && make -j20 && mv GLTEST ../$(date +%s)
winf:
	powershell -Command "Remove-Item -Recurse -Force ./build -ErrorAction SilentlyContinue; New-Item -ItemType Directory -Path ./build -Force; cd build; cmake ..; cmake --build ."
win:
	powershell -Command "cd build; cmake --build ."