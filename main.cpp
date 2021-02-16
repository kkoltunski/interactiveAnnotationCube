#include <iostream>
#include <vtkAutoInit.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAnnotatedCubeActor.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include "SceneModule/scene3d.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2)

int main(int, char**) {
  Scene3D scene(700, 700);
  scene.initialize();
  scene.start();
  return 0;
}
