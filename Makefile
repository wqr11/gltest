default:
	mkdir -p ./build && cd build && cmake ../ && make -j20 && mv GLTEST ../$(date +%s)
winforce:
	powershell -Command "Remove-Item -Recurse -Force ./build -ErrorAction SilentlyContinue; New-Item -ItemType Directory -Path ./build -Force; cd build; cmake ..; cmake --build ."
win:
	powershell -Command "cd build; cmake --build ."
run:
	bash -c "TWGL_VERTEX_SHADER=C:/Users/wqr/Desktop/gltest/shaders/vertex.glsl TWGL_FRAGMENT_SHADER=C:/Users/wqr/Desktop/gltest/shaders/fragment.glsl ./build/Debug/GLTEST.exe"