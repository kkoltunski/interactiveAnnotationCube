cmake_minimum_required(VERSION 3.0.0)
project(interactiveAnnotationCube VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
)

if(CMAKE_BUILD_TYPE MATCHES Release)
    set(VTK_DIR "/home/kdoz/Libraries/VTK/build/release")
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
    set(VTK_DIR "/home/kdoz/Libraries/VTK/build/debug")
endif()

find_package(VTK REQUIRED)

add_subdirectory(SceneModule)
add_subdirectory(uTests)
add_executable(${PROJECT_NAME} ${SOURCES})
                
target_link_libraries(${PROJECT_NAME} 
    SceneLibrary
    ${VTK_LIBRARIES}
)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_HOME_DIRECTORY})