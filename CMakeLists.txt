cmake_minimum_required(VERSION 3.15)
project(json_deserializer)

set(CMAKE_CXX_STANDARD 17)

#find_package(nlohmann_json 3.7.3 REQUIRED)

add_subdirectory(json)

add_executable(json_deserializer src/main.cpp src/request_loader.cpp include/request_loader.h)