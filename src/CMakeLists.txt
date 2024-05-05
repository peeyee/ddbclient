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

	include_directories(include)
	include_directories(include/dolphindb)
    if(CROSS_COMPILE_ARM)		
	SET(CMAKE_SYSTEM_NAME Linux)
	SET(CMAKE_SYSTEM_PROCESSOR arm)
	SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
	SET(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)	
	link_directories(${PROJECT_SOURCE_DIR}/lib/arm)
	# dependence order matters, typically from left to right, but some how it reverses here
        list(APPEND CLIENT_LIBS DolphinDBAPI uuid ssl crypto history readline ncurses)
	message("cross compile for ARM.")
	message("libs  ${CLIENT_LIBS}")
    else()
	set(DDBAPI libDDBAPI.a) 
	link_directories(${PROJECT_SOURCE_DIR}/lib)
	list(APPEND CLIENT_LIBS ${DDBAPI} readline history ncurses)
    endif()
	add_executable(ddbclient ${SOURCES})
	target_link_libraries(ddbclient ${CLIENT_LIBS} pthread rt dl) 

    install(TARGETS ddbclient DESTINATION bin)
endif()
