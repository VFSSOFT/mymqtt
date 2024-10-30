cmake_minimum_required(VERSION 3.23)
project(mymqtt C)

set(CMAKE_C_STANDARD 99)

find_package(OpenSSL REQUIRED)

add_library(mymqtt SHARED mymqtt.c)

target_link_libraries(mymqtt OpenSSL::SSL OpenSSL::Crypto)
