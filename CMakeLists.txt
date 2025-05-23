cmake_minimum_required(VERSION 3.15)
project(guess-the-number)


# Указываем, что исходники находятся в папке src
file(GLOB SOURCES "src/*.cpp")

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Для Visual Studio устанавливаем C++ стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)