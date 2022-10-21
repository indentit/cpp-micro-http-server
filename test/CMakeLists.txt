cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(cpp-micro-http-server LANGUAGES CXX)

add_executable(${PROJECT_NAME} http_server_example.cpp)

file(GLOB_RECURSE SERVER ${PROJECT_SOURCE_DIR}/../server/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE
	${SERVER}
	)

find_path(ASIO_PATH asio.hpp REQUIRED)
target_include_directories(${PROJECT_NAME} INTERFACE ${ASIO_PATH})
find_library(PTHREAD pthread REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PTHREAD})


