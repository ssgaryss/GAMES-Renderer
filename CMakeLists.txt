cmake_minimum_required(VERSION 3.0) #cmake最低版本

project(GAMES-Renderer) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(${PROJECT_NAME} main.cpp)
