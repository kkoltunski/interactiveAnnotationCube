cmake_minimum_required(VERSION 3.0.0)
project(interactiveAnnotatedCube VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

if(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release mode!")
    set(VTK_DIR "/home/kdoz/Libraries/VTK/build/release")
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug mode!")
    set(VTK_DIR "/home/kdoz/Libraries/VTK/build/debug")
endif()

find_package(VTK REQUIRED)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
                
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)