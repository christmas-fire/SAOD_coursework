cmake_minimum_required(VERSION 3.10)

# Название проекта
project(coursework)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите путь к исходным файлам
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Соберите все файлы в папке src
file(GLOB SOURCES "${SRC_DIR}/*.cpp")
file(GLOB HEADERS "${SRC_DIR}/*.hpp")

# Создайте исполняемый файл
add_executable(coursework ${SOURCES} ${HEADERS})