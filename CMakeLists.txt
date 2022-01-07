cmake_minimum_required(VERSION 3.7)
project(untitled5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(untitled5 Hadik.cpp main.cpp Client.cpp Client.h Server.cpp Server.h Hadik.h Logika.cpp Logika.h Ovocie.h)