cmake_minimum_required(VERSION 3.16)
project(CPU6502 LANGUAGES CXX)

# Usa C++17 o superior
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activa símbolos de depuración (como el flag -g)
set(CMAKE_BUILD_TYPE Debug)

# Agrega los headers en "include/"
include_directories(include)

# Agrega el ejecutable principal
add_executable(cpu6502
    src/main.cpp
    src/cpu.cpp
    src/memory.cpp
)

# Agrega un ejecutable para tests si existe
add_executable(tests
    tests/test_runner.cpp
    src/cpu.cpp
    src/memory.cpp
)

# Si usás una librería externa como doctest o catch2, podés agregarla también
