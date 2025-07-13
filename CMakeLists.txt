cmake_minimum_required(VERSION 3.12)
project(tone-driver-sdl2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include directories
include_directories(
    
    /include
)

# Library target
add_library(tone-driver-sdl2 STATIC
    src/ToneDriverSDL2.cpp
)

target_include_directories(tone-driver-sdl2 PUBLIC include)
target_link_libraries(tone-driver-sdl2 ${SDL2_LIBRARIES})

# test-tone
add_executable(test-tone examples/test-tone.cpp)
target_link_libraries(test-tone tone-driver-sdl2 ${SDL2_LIBRARIES})

# major-scale
add_executable(major-scale examples/major-scale.cpp)
target_link_libraries(major-scale tone-driver-sdl2 ${SDL2_LIBRARIES})

# test-frequencies
add_executable(test-frequencies examples/test-frequencies.cpp)
target_link_libraries(test-frequencies tone-driver-sdl2 ${SDL2_LIBRARIES})

# precomputed-frequencies
add_executable(precomputed-frequencies examples/precomputed-frequencies.cpp)
target_link_libraries(precomputed-frequencies tone-driver-sdl2 ${SDL2_LIBRARIES})

# Install (optional, for later)
# install(TARGETS tone-driver-sdl2 DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)

