cmake_minimum_required(VERSION 3.0)
project(ddbclient)
add_subdirectory(src bin)

set(CMAKE_INSTALL_PREFIX "/usr/local/")
install(FILES lib/libDolphinDBAPI.so DESTINATION lib)
install(TARGETS ddbclient DESTINATION bin)
