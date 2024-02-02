set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB SOURCES "*.cpp")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release") 
else()
	set(CMAKE_BUILD_TYPE "Debug")  
endif()

if(UNIX)
	add_definitions(-DLINUX -D_GLIBCXX_USE_CXX11_ABI=1)

	set(DDBAPI libDDBAPI.a) 
	include_directories(include)
	include_directories(include/dolphindb)
	link_directories(${PROJECT_SOURCE_DIR}/lib)
	link_libraries(${DDBAPI})

	add_executable(ddbclient ${SOURCES})
	target_link_libraries(ddbclient pthread rt dl) 
endif()
