cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(micro_http_server LANGUAGES CXX)

add_library(${PROJECT_NAME} 
	server/server.cpp
	server/router.cpp
	server/request.cpp
	server/response.cpp
	server/header.cpp
	)


# sources
file(GLOB_RECURSE SERVER ${PROJECT_SOURCE_DIR}/server/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE
	${SERVER}
	)

# headers
find_path(ASIO_PATH asio.hpp REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${ASIO_PATH}
	${PROJECT_SOURCE_DIR}/server
	)

# libs
find_library(PTHREAD pthread REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PTHREAD})

# test executable
add_executable(http_server_example test/http_server_example.cpp)
target_link_libraries(http_server_example PRIVATE micro_http_server)
