cmake_minimum_required(VERSION 3.12)
project(tone-driver-sdl2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# === ToneDriver interface ===
add_library(tone-driver INTERFACE)
target_include_directories(tone-driver INTERFACE include)

# === music-components ===
#add_library(music-components STATIC
    # Add music-component cpp files
#)
#target_include_directories(music-components PUBLIC include)
#target_link_libraries(music-components PUBLIC tone-driver)

# === music-driver ===
#add_library(music-driver STATIC
    # Add music-driver cpp files
#)
#target_include_directories(music-driver PUBLIC include)
#target_link_libraries(music-driver PUBLIC music-components)

# === tone-driver-sdl2 ===
# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(tone-driver-sdl2 STATIC
    src/tone-driver-sdl2/ToneDriverSDL2.cpp
)
target_include_directories(tone-driver-sdl2 PUBLIC include)
target_link_libraries(tone-driver-sdl2 PUBLIC tone-driver ${SDL2_LIBRARIES})

# === Examples ===

# Example: tone-driver-sdl2/major-scale
add_executable(major-scale examples/tone-driver-sdl2/major-scale.cpp)
target_link_libraries(major-scale PRIVATE tone-driver-sdl2)

# Example: tone-driver-sdl2/test-tone
add_executable(test-tone examples/tone-driver-sdl2/test-tone.cpp)
target_link_libraries(test-tone PRIVATE tone-driver-sdl2)

# Example: tone-driver-sdl2/test-frequencies
add_executable(test-frequencies examples/tone-driver-sdl2/test-frequencies.cpp)
target_link_libraries(test-frequencies PRIVATE tone-driver-sdl2)

# Example: tone-driver-sdl2/precomputed-frequencies
add_executable(precomputed-frequencies examples/tone-driver-sdl2/precomputed-frequencies.cpp)
target_link_libraries(precomputed-frequencies PRIVATE tone-driver-sdl2)

# Example: music-driver/note-test
add_executable(note-test
    examples/music-driver/note-test.cpp
    src/music-driver/MusicDriver.cpp
    src/music-components/Note.cpp
)
target_link_libraries(note-test PRIVATE tone-driver-sdl2)

# Install (optional, for later)
# install(TARGETS tone-driver-sdl2 DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)

