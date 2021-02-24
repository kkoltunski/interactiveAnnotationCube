cmake_minimum_required(VERSION 3.0.0)
project(interactiveAnnotationCubeTests VERSION 0.1.0)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/mainTests.cpp
)

find_package(VTK REQUIRED) 

add_subdirectory(googletest)
include_directories(googletest/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    SceneLibrary
    ${VTK_LIBRARIES}
    gtest 
    gtest_main
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_HOME_DIRECTORY}
)