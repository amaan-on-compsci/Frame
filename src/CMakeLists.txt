cmake_minimum_required(VERSION 3.5)
project(imageRenderer)

add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_HOME_DIRECTORY}/include
        ${CMAKE_HOME_DIRECTORY}/vendor/SDL/include
        ${CMAKE_HOME_DIRECTORY}/vendor/AudioFile
        ${CMAKE_HOME_DIRECTORY}/vendor/wxWidgets
)
target_sources(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_HOME_DIRECTORY}/src/main.cpp
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        SDL3::SDL3
        wx::net
        wx::core
        wx::base
)

