cmake_minimum_required(VERSION 3.5)
project(imageRenderer)

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