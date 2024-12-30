cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (SDLTest
	VERSION 0.1
	DESCRIPTION "SDLTest Project")

# Set the C++ standard (e.g., 17 or 20)
set(CMAKE_CXX_STANDARD 20)           # Use 17 for C++17, or 20 for C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure the standard is strictly enforced
set(CMAKE_CXX_EXTENSIONS OFF)        # Disable compiler-specific extensions (optional)

# Find SDL2 library
find_package(SDL2 REQUIRED)
#find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} wrapperlibrary/)

# This project will output an executable file
add_executable(${PROJECT_NAME} SDLTest.cpp)

# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

# Link SDL2
target_link_libraries(SDLTest ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)


#target_include_directories(SDLOpenFontExample PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
#target_link_libraries(SDLOpenFontExample PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
