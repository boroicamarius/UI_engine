cmake_minimum_required(VERSION 3.26)

project(UI_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SDL2IMAGE_INSTALL OFF)
set(SDL2TTF_INSTALL OFF)
set(SDL2MIXER_INSTALL OFF)
set(INSTALL_MANPAGES OFF)

set(SDL2_MAIN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL)

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_mixer EXCLUDE_FROM_ALL)

add_library(UI_engine STATIC)
target_include_directories(UI_engine PUBLIC "include/")
target_sources(UI_engine 
PRIVATE 
	src/Globals.cpp
	src/UI_collection.cpp
	src/UI_engine.cpp
	src/UI_frame.cpp
	src/UI_image.cpp
	src/UI_text.cpp
	src/UI_window.cpp
	src/UI.cpp
)

target_link_libraries(SDL2_ttf PRIVATE $<BUILD_INTERFACE:SDL2::SDL2>)
target_link_libraries(SDL2_image PRIVATE $<BUILD_INTERFACE:SDL2::SDL2>)
target_link_libraries(SDL2_mixer PRIVATE $<BUILD_INTERFACE:SDL2::SDL2>)

target_link_libraries(UI_engine
PUBLIC
	SDL2::SDL2main
	SDL2::SDL2
	SDL2_image::SDL2_image
	SDL2_ttf::SDL2_ttf
	SDL2_mixer::SDL2_mixer
)

include(CMakePrintHelpers)

cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)
cmake_print_variables(CMAKE_BINARY_DIR)

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL/SDL2.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_image/SDL2_image.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_ttf/SDL2_ttf.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_mixer/SDL2_mixer.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_mixer/external/libmodplug/modplug.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_mixer/external/flac/src/libFLAC/FLAC.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_mixer/external/opusfile/opusfile.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_mixer/external/opus/opus.dll
DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/external/SDL_mixer/external/ogg/ogg.dll
DESTINATION ${CMAKE_BINARY_DIR})