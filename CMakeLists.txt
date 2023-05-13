cmake_minimum_required(VERSION 2.8)
project(SdlCppGame)

set(CMAKE_CXX_STANDARD 14)

# Linux target requires the SDL2 and SDL2_image development libraries.
include_directories(${SDL2}/include/SDL2)
link_directories(${SDL2}/lib)

set(SOURCE_FILES
	source/logger/logger.cpp
    source/game.cpp
	source/main.cpp
	)

add_executable(sdlcppgame ${SOURCE_FILES})



target_link_libraries(sdlcppgame SDL2 SDL2_image)
