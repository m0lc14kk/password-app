cmake_minimum_required(VERSION 3.16)
project(PasswordManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
    src/*.cpp
    src/*.h
)

add_executable(PasswordManager
    ${SRC_FILES}
)