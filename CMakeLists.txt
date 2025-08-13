cmake_minimum_required(VERSION 3.1)
project(ddbclient)

include_directories(
    thirdparty/linenoise-ng/include
    thirdparty/api-cpp/include
    thirdparty/libuuid
)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

set(ORIGINAL_C_FLAGS "${CMAKE_C_FLAGS}")
set(ORIGINAL_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|ARM|aarch64|AARCH64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsigned-char")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char")
endif()

add_subdirectory(thirdparty/api-cpp)

set(CMAKE_C_FLAGS "${ORIGINAL_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${ORIGINAL_CXX_FLAGS}")


add_subdirectory(src bin)
add_subdirectory(thirdparty/linenoise-ng)
add_subdirectory(thirdparty/libuuid)


set(CMAKE_INSTALL_PREFIX "/usr/local/")

set(CPACK_PACKAGE_NAME ${project})
set(CPACK_SET_DESTDIR ON)
set(CPACK_INSTALL_PREFIX "/usr/local/")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_RPM_PACKAGE_GROUP "ddb")
set(CPACK_PACKAGE_VENDOR "peeyee")
set(CPACK_RPM_PACKAGE_LICENSE "Apache 2.0 + Common Clause 1.0")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|ARM|aarch64|AARCH64")
    message(STATUS "Building for ARM64 (aarch64)")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "arm64")  
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "aarch64")   
else()
    message(STATUS "Building for x86_64 (amd64)")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64") 
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
endif()

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "yeyoung0909@163.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "peeyee")

include(CPack)
