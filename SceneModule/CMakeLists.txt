FIND_PACKAGE(VTK REQUIRED) 
      
set(SOURCES
    scene3d.cpp
    customInteractorStyle.cpp
    actorsPool.cpp
)

set(HEADERS
    scene3d.h
    customInteractorStyle.h
    actorsPool.h
)

ADD_LIBRARY(SceneLibrary STATIC ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES(SceneLibrary ${VTK_LIBRARIES})