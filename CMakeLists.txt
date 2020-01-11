cmake_minimum_required(VERSION 3.10)

project(tictactoe3d)

set(CMAKE_CXX_STANDARD 11)

include_directories( "${CMAKE_SOURCE_DIR}/." )
file(GLOB 
	CPP_SOURCES "*.cpp"
	CPP_HEADERS "*.h")
add_executable(  ${PROJECT_NAME} ${CPP_SOURCES} ${CPP_HEADERS} ) 
#add_executable( ${PROJECT_NAME} main.cpp field.h field.cpp game.cpp game.h player.h )          
