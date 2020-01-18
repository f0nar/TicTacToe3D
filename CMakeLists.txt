cmake_minimum_required(VERSION 3.10)

project(tictactoe3d)

set(CMAKE_CXX_STANDARD 14)

file(GLOB 
	CPP_SOURCES "*.cpp"
	CPP_HEADERS "*.h")

add_executable(  ${PROJECT_NAME} ${CPP_SOURCES} ${CPP_HEADERS} ) 
