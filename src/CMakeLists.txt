set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SOURCES "*.cpp")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release") 
else()
	set(CMAKE_BUILD_TYPE "Debug")  
endif()

if(UNIX)
	add_definitions(-DLINUX -D_GLIBCXX_USE_CXX11_ABI=0)

	set(DDBAPI libDDBAPI.a) 
	include_directories(include)
	include_directories(include/dolphindb)
	link_directories(${PROJECT_SOURCE_DIR}/lib)
	link_libraries(${DDBAPI} readline history ncurses)

	add_executable(ddbclient ${SOURCES})
	target_link_libraries(ddbclient pthread rt dl) 

    install(TARGETS ddbclient DESTINATION bin)
endif()
