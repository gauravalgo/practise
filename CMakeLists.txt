cmake_minimum_required(VERSION 3.0)

project(practisce)

add_executable(practisce main.cpp)

install(TARGETS practisce RUNTIME DESTINATION bin)
