cmake_minimum_required(VERSION 3.10.0)

project(libbw64_utils VERSION 1.0.0 LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS ON)
add_subdirectory(thrid_party)

add_subdirectory(axml_utils)

message(${CMAKE_SYSTEM_NAME})
