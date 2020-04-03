cmake_minimum_required(VERSION 3.15)
project(Adidas C)

set(CMAKE_C_STANDARD 99)

set(DCMAKE_SH="CMAKE_SH-NOTFOUND")


add_executable(encode encode.c)
add_executable(decode decode.c)
add_executable(channel channel.c)