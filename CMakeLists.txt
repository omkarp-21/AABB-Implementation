# Generate compile_commands.json for clangd / LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.10)
project(hello VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 2.x
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics network audio)

# Gather sources
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Executable
add_executable(hello
    main.cpp
    ${SRC_FILES}
)

# Include directories
target_include_directories(hello PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against SFML
target_link_libraries(hello PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
)
