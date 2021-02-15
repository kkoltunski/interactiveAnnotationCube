#include <iostream>
#include <vtkAutoInit.h>
#include "scene3d.h"

VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingOpenGL2)

int main(int, char**) {
    Scene3D scene(700, 700);
    scene.initialize();

    return 0;
}
