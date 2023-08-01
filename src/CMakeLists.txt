set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB SOURCES "*.cpp")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug") 
else()
	set(CMAKE_BUILD_TYPE "Release")  
endif()

if(UNIX)
	add_definitions(-DLINUX -D_GLIBCXX_USE_CXX11_ABI=1)


	set(PROGRAM_OPTIONS libboost_program_options.a) 
	set(DDBAPI libDolphinDBAPI.a) 

	if(OPENSSL_INCLUDE_DIR)
    		include_directories(${OPENSSL_INCLUDE_DIR})
	else()
		include_directories(include)
	endif()    
	include_directories(include/dolphindb)
	link_directories(${PROJECT_SOURCE_DIR}/lib)
        link_libraries(${PROGRAM_OPTIONS})
	add_executable(ddbclient ${SOURCES})
	target_link_libraries(ddbclient DolphinDBAPI rt) 
endif()
