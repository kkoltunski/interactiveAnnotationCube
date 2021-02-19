FIND_PACKAGE(VTK REQUIRED) 
      
set(SOURCES
    scene3d.cpp
    customInteractorStyle.cpp
)

set(HEADERS
    scene3d.h
    customInteractorStyle.h
)

ADD_LIBRARY(SceneLibrary STATIC ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES(SceneLibrary ${VTK_LIBRARIES})