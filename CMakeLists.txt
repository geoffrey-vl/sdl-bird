cmake_minimum_required(VERSION 2.8)
project(SdlCppGame)

set(CMAKE_CXX_STANDARD 14)

# Linux target requires the SDL2 and SDL2_image development libraries.
include_directories(${SDL2}/include/SDL2)
link_directories(${SDL2}/lib)

set(SOURCE_FILES
	source/logger/logger.cpp
    source/texture.cpp
	source/game.cpp
	source/main.cpp
	)

add_executable(sdlcppgame ${SOURCE_FILES})
target_link_libraries(sdlcppgame SDL2 SDL2_image)

# copy assets
set(SOURCE_DATA_DIR ${CMAKE_SOURCE_DIR}/data)
set(TARGET_DATA_DIR ${CMAKE_BINARY_DIR}/data)
message(AUTHOR_WARNING "Copy from ${SOURCE_DATA_DIR} to ${TARGET_DATA_DIR}")
add_custom_command(TARGET sdlcppgame POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${SOURCE_DATA_DIR} ${TARGET_DATA_DIR})