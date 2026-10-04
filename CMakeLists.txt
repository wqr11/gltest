cmake_minimum_required(VERSION 3.16)

if(WIN32)
  set(VCPKG_ROOT "C:/Users/wqr/vcpkg" CACHE PATH "")

  set(
    CMAKE_TOOLCHAIN_FILE
    "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE FILEPATH "VCPKG toolchain"
  )

  set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic")
  set(CMAKE_C_COMPILER "C:/msys64/clang64/bin/clang.exe")
  set(CMAKE_CXX_COMPILER "C:/msys64/clang64/bin/clang++.exe")
  set(CMAKE_PREFIX_PATH "C:/Qt/6.12.0/llvm-mingw_64" ${CMAKE_PREFIX_PATH})
else()
  set(VCPKG_ROOT "/home/wqr/vcpkg" CACHE PATH "")

  set(
    CMAKE_TOOLCHAIN_FILE
    "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE FILEPATH "VCPKG toolchain"
  )

  set(VCPKG_TARGET_TRIPLET "x64-linux")
endif()

project(GLTEST VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c*)

qt_standard_project_setup()
qt_add_executable(${TARGET}
  ${SOURCES})

qt_add_resources(${TARGET} "resources"
  PREFIX "/"
  FILES
    textures/4po4mak.png
)

target_link_libraries(${TARGET}
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    glm::glm
)
