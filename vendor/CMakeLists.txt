cmake_minimum_required(VERSION 3.5)
project(imageRenderer)

# SDL3 Flags
set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(SDL)

#wxWidgets flags
set(wxBUILD_SHARED OFF)
add_subdirectory(wxWidgets)

add_library(vendor INTERFACE)

 target_link_libraries(vendor 
    INTERFACE 
        SDL3::SDL3
        wx::net 
        wx::core
        wx::base
    )