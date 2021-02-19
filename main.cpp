#include <vtkAutoInit.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAnnotatedCubeActor.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "SceneModule/scene3d.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2)

int main(int, char**) {
  Scene3D scene(700, 700);
  scene.initialize();

vSP<vtkNamedColors> colors = vSP<vtkNamedColors>::New();

vSP<vtkCylinderSource> cylinder = vSP<vtkCylinderSource>::New();
cylinder->SetResolution(8);

vSP<vtkPolyDataMapper> cylinderMapper = vSP<vtkPolyDataMapper>::New();
cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

vSP<vtkActor> cylinderActor = vSP<vtkActor>::New();
cylinderActor->SetMapper(cylinderMapper);
scene.getRenderer()->AddActor(cylinderActor);
scene.getRenderer()->ResetCamera();
scene.getRenderer()->GetRenderWindow()->Render();

  // A cube with labeled faces.
  vtkSmartPointer<vtkAnnotatedCubeActor> cube =
    vtkSmartPointer<vtkAnnotatedCubeActor>::New();
  cube->SetXPlusFaceText("R"); // Right
  cube->SetXMinusFaceText("L"); // Left
  cube->SetYPlusFaceText("A"); // Anterior
  cube->SetYMinusFaceText("P"); // Posterior
  cube->SetZPlusFaceText("S"); // Superior/Cranial
  cube->SetZMinusFaceText("I"); // Inferior/Caudal
  cube->SetFaceTextScale(0.5);
  cube->GetCubeProperty()->SetColor(colors->GetColor3d("Black").GetData());

  cube->GetTextEdgesProperty()->SetColor(
    colors->GetColor3d("Black").GetData());

  // Change the vector text colors.
  cube->GetXPlusFaceProperty()->SetColor(
    colors->GetColor3d("Tomato").GetData());
  cube->GetXMinusFaceProperty()->SetColor(
    colors->GetColor3d("Tomato").GetData());
  cube->GetYPlusFaceProperty()->SetColor(
    colors->GetColor3d("DeepSkyBlue").GetData());
  cube->GetYMinusFaceProperty()->SetColor(
    colors->GetColor3d("DeepSkyBlue").GetData());
  cube->GetZPlusFaceProperty()->SetColor(
    colors->GetColor3d("SeaGreen").GetData());
  cube->GetZMinusFaceProperty()->SetColor(
    colors->GetColor3d("SeaGreen").GetData());

    vtkSmartPointer<vtkOrientationMarkerWidget> om =
        vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    om->SetOrientationMarker(cube);
    om->SetViewport(0.0, 0.8, 0.2, 1.0);
    om->SetInteractor(scene.getInteractor());
    om->EnabledOn();
    om->InteractiveOff();

  scene.start();
  return 0;
}