cmake_minimum_required(VERSION 3.16)

project(GLTEST)

set(TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c*)

find_package(Qt6 REQUIRED COMPONENTS Core Network Gui Qml Widgets)

qt_standard_project_setup()

qt_add_executable(${TARGET} ${SOURCES})

if (WIN32)
    set_target_properties(${TARGET} PROPERTIES WIN32_EXECUTABLE ON)
endif()

target_link_libraries(${TARGET}
    PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Gui
    Qt6::Qml
    Qt6::Widgets
)