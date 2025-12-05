cmake_minimum_required(VERSION 3.16)
project(PasswordManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 QUIET COMPONENTS Widgets)
qt_standard_project_setup()

include(FetchContent)

find_library(SQLITE3_LIBRARY sqlite3 PATHS /usr/lib /usr/local/lib /opt/homebrew/lib)
find_path(SQLITE3_INCLUDE_DIR sqlite3.h PATHS /usr/include /usr/local/include /opt/homebrew/include)

if(SQLITE3_LIBRARY AND SQLITE3_INCLUDE_DIR)
    message(STATUS "Found SQLite3: ${SQLITE3_LIBRARY}")
    add_library(SQLite3::SQLite3 UNKNOWN IMPORTED)
    set_target_properties(SQLite3::SQLite3 PROPERTIES
        IMPORTED_LOCATION "${SQLITE3_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SQLITE3_INCLUDE_DIR}"
    )
else()
    FetchContent_Declare(
        sqlite3
        URL https://www.sqlite.org/2024/sqlite-amalgamation-3490100.zip
    )
    FetchContent_MakeAvailable(sqlite3)
    
    add_library(SQLite3::SQLite3 STATIC
        ${sqlite3_SOURCE_DIR}/sqlite3.c
    )
    target_include_directories(SQLite3::SQLite3 PUBLIC
        ${sqlite3_SOURCE_DIR}
    )
endif()

file(GLOB SRC_FILES
    src/*.cpp
    src/*.h
)

qt_add_executable(PasswordManager
    ${SRC_FILES}
)

target_link_libraries(PasswordManager PRIVATE Qt6::Widgets SQLite3::SQLite3)
