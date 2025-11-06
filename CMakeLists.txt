cmake_minimum_required(VERSION 3.10)
project(raylib_project LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose Debug or Release" FORCE)
endif()

add_subdirectory(external/raylib)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories(${PROJECT_NAME} PRIVATE src)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/W3 /Zi /Od>
        $<$<CONFIG:Release>:/O2 /DNDEBUG>
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
    )
endif()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(${PROJECT_NAME}
        ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY}
    )
elseif(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} m pthread dl)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
)
