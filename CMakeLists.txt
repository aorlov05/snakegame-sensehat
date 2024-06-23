cmake_minimum_required(VERSION 3.25.1)
project(snakegamesensehat C)

set(LIBRARY_DIR $ENV{HOME}/lib/sensehat)
set(INCLUDE_DIR $ENV{HOME}/include/sensehat)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES_LIST src/apple.c src/display.c src/input.c src/main.c src/snake.c)

add_executable(snakegamesensehat ${SOURCE_FILES_LIST})

# Find installed libsensehat library
find_library(SENSE_HAT_LIBRARY NAMES sensehat PATHS ${LIBRARY_DIR} NO_DEFAULT_PATH)

# Include both project and library headers
target_include_directories(snakegamesensehat PRIVATE
        ${INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include)

# Link static library
target_link_libraries(snakegamesensehat ${SENSE_HAT_LIBRARY})

if (SENSE_HAT_LIBRARY)
    message(STATUS "Found libsensehat in ${SENSE_HAT_LIBRARY}")
else ()
    message(FATAL_ERROR "Dependency libsensehat not installed")
endif ()
