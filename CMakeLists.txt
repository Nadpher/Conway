cmake_minimum_required(VERSION 3.17)
project(Conway)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")
endif()

# finds linux distro
find_program(LSB_RELEASE_EXEC lsb_release)
execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
    OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# sets program sources
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# linking sdl2 is hard <.<
find_package(SDL2 REQUIRED sdl2)
if (SDL2_FOUND)
    if(LSB_RELEASE_ID_SHORT MATCHES Arch)
        target_link_libraries(${PROJECT_NAME} SDL2::SDL2) 
    else()
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
    endif()
else()
    message(FATAL_ERROR "Package sdl2 not found. Cmake will now exit.")
endif()
