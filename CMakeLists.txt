cmake_minimum_required(VERSION 3.24)
project(ddbclient)
add_subdirectory(src bin)

install(TARGETS ddbclient DESTINATION bin)
