cmake_minimum_required(VERSION 3.22)

project(
	tic-tac-toe
	VERSION 1.0.0
	LANGUAGES C CXX)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} game)