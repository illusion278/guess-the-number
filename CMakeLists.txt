cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(MyCppProject)                 # Название проекта

set(CMAKE_CXX_STANDARD 17)            # Используем C++17

# Создаём исполняемый файл из main.cpp
add_executable(my_program main.cpp)