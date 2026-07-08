cmake_minimum_required(VERSION 3.16)

project(GLTEST)

set(TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_CXX_COMPILER "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe")
    add_compile_options("/Zc:__cplusplus")
    add_compile_options("/permissive-")
    set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/msvc2022_64" ${CMAKE_PREFIX_PATH})
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Network Gui Qml Widgets OpenGLWidgets)

if (WIN32)
    set(LIB_ROOT_PATH ${PROJECT_SOURCE_DIR}/lib/msvc)
else ()
    set(LIB_ROOT_PATH ${PROJECT_SOURCE_DIR}/lib/gcc)
endif()

find_library(GLM glm.lib PATHS ${LIB_ROOT_PATH} REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c*)
file(GLOB GLOBAL_INCLUDE_DIRS LIST_DIRECTORIES true ${PROJECT_SOURCE_DIR}/src/*)

qt_standard_project_setup()

qt_add_executable(${TARGET} ${SOURCES})

if (WIN32)
    set_target_properties(${TARGET} PROPERTIES WIN32_EXECUTABLE ON)
endif()

target_include_directories(${TARGET}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${GLOBAL_INCLUDE_DIRS}
)

target_link_libraries(${TARGET}
    PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Gui
    Qt6::Qml
    Qt6::Widgets
    Qt6::OpenGLWidgets
    ${GLM}
)