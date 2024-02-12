cmake_minimum_required(VERSION 3.1)
project(ddbclient)
add_subdirectory(src bin)

set(CMAKE_INSTALL_PREFIX "/usr/local/")

set(CPACK_PACKAGE_NAME ${project})
set(CPACK_SET_DESTDIR ON)
set(CPACK_INSTALL_PREFIX "/usr/local/")
set(CPACK_PACKAGE_VERSION "0.2.0")
set(CPACK_RPM_PACKAGE_GROUP "ddb")
set(CPACK_PACKAGE_VENDOR "peeyee")
set(CPACK_RPM_PACKAGE_LICENSE "Apache 2.0 + Common Clause 1.0")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_CONTACT "yeyoung0909@163.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "peeyee")

include(CPack)
