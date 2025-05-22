cmake_minimum_required(VERSION 3.10)
project(guess_the_number)

set(CMAKE_CXX_STANDARD 17)

# Явно указываем выходной каталог
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(guess-the-number src/main.cpp)

# Для Windows добавляем расширение .exe
if(WIN32)
    set_target_properties(guess-the-number PROPERTIES SUFFIX ".exe")
endif()