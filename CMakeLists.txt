cmake_minimum_required(VERSION 3.16)
project(PasswordManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

file(GLOB SRC_FILES
    src/*.cpp
    src/*.h
)

qt_add_executable(PasswordManager
    ${SRC_FILES}
)

target_link_libraries(PasswordManager PRIVATE Qt6::Widgets)
