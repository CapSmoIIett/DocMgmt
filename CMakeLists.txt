cmake_minimum_required(VERSION 3.16)

project(DocMgmt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(Client/)
add_subdirectory(Server/)
