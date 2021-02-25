FIND_PACKAGE(VTK REQUIRED) 
      
set(SOURCES
    scene3d.cpp
    customInteractorStyle.cpp
    actorsPool.cpp
)

add_library(SceneLibrary STATIC ${SOURCES} ${HEADERS})
target_link_libraries(SceneLibrary ${VTK_LIBRARIES})

target_link_directories(SceneLibrary PUBLIC ${CMAKE_HOME_DIRECTORY}/SceneModule)