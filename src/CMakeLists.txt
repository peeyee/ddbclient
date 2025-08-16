set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SOURCES "*.cpp")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release") 
else()
	set(CMAKE_BUILD_TYPE "Debug")  
endif()

option(CROSS_COMPILE_ARM "Enable cross-compilation for ARM" OFF)

if(UNIX)
	add_definitions(-DLINUX -D_GLIBCXX_USE_CXX11_ABI=0)
	set(CLIENT_LIBS)
	# dependence order matters, typically from left to right, but some how it reverses here
    list(APPEND CLIENT_LIBS DolphinDBAPI uuid ssl crypto)
	include_directories(include)

    if(CROSS_COMPILE_ARM)		
		SET(CMAKE_SYSTEM_NAME Linux)
		SET(CMAKE_SYSTEM_PROCESSOR arm)
		SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
		SET(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)	
		link_directories(${PROJECT_SOURCE_DIR}/lib/arm)
		message("cross compile for ARM.")
		message("libs  ${CLIENT_LIBS}")
	elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|ARM|aarch64|AARCH64")
		message(STATUS "ARM: ${CMAKE_SYSTEM_PROCESSOR}")
		link_directories(${PROJECT_SOURCE_DIR}/lib/arm)
    else()
		link_directories(${PROJECT_SOURCE_DIR}/lib)
    endif()
	add_executable(ddbclient ${SOURCES})
	target_link_libraries(ddbclient ${CLIENT_LIBS} 
		fmt
		pthread 
		rt 
		dl 
		linenoise
	) 
    install(TARGETS ddbclient DESTINATION bin)
endif()
