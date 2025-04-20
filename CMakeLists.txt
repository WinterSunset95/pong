cmake_minimum_required(VERSION 3.14)
project(Pong VERSION 1.0 DESCRIPTION "Pong game in C++ and SDL" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# SDL
if (WIN32)
	set(SDL_DIR "./SDL3-3.2.10/x86_64-w64-mingw32")
	set(IMG_DIR "./SDL3_image-3.2.4/x86_64-w64-mingw32")
	set(TTF_DIR "./SDL3_ttf-3.2.2/x86_64-w64-mingw32")
else ()
	set(SDL_DIR "/usr")
	set(IMG_DIR "/usr")
	set(TTF_DIR "/usr")
endif()

# Include SDL Headers
include_directories(${SDL_DIR}/include ${IMG_DIR}/include ${TTF_DIR}/include src/headers)

# Source files
file(GLOB SOURCES "src/*.cpp")

if (WIN32)
	message(STATUS "Building for Windows")
	link_directories(${SDL_DIR}/lib ${IMG_DIR}/lib ${TTF_DIR}/lib)
	add_executable(pong ${SOURCES})
	target_link_libraries(pong -static libSDL3.dll.a libSDL3_image.dll.a libSDL3_ttf.dll.a)
else()
	message(STATUS "Building for Linux")
	add_executable(pong ${SOURCES})
	find_package(SDL3 REQUIRED CONFIG)
	target_link_libraries(pong SDL3 SDL3_image SDL3_ttf)
endif()
