cmake_minimum_required(VERSION 3.1)
project(ddbclient)

include_directories(
    thirdparty/linenoise-ng/include
    thirdparty/api-cpp/include
)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")

add_subdirectory(src bin)
add_subdirectory(thirdparty/linenoise-ng)
add_subdirectory(thirdparty/api-cpp)
add_subdirectory(thirdparty/libuuid)


set(CMAKE_INSTALL_PREFIX "/usr/local/")

set(CPACK_PACKAGE_NAME ${project})
set(CPACK_SET_DESTDIR ON)
set(CPACK_INSTALL_PREFIX "/usr/local/")
set(CPACK_PACKAGE_VERSION "0.4.0")
set(CPACK_RPM_PACKAGE_GROUP "ddb")
set(CPACK_PACKAGE_VENDOR "peeyee")
set(CPACK_RPM_PACKAGE_LICENSE "Apache 2.0 + Common Clause 1.0")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_CONTACT "yeyoung0909@163.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "peeyee")

include(CPack)
