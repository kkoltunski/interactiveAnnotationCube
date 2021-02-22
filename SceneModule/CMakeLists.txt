FIND_PACKAGE(VTK REQUIRED) 
      
set(SOURCES
    scene3d.cpp
    customInteractorStyle.cpp
)

ADD_LIBRARY(SceneLibrary STATIC ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES(SceneLibrary ${VTK_LIBRARIES})

target_link_directories(SceneLibrary PUBLIC ${CMAKE_HOME_DIRECTORY}/SceneModule)