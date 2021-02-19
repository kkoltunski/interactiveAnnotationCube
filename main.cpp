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

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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

// #include <vtkVersion.h>
// #include <vtkSmartPointer.h>
// #include <vtkRendererCollection.h>
// #include <vtkDataSetMapper.h>
// #include <vtkUnstructuredGrid.h>
// #include <vtkIdTypeArray.h>
// #include <vtkTriangleFilter.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkActor.h>
// #include <vtkCommand.h>
// #include <vtkRenderWindow.h>
// #include <vtkRenderer.h>
// #include <vtkRenderWindowInteractor.h>
// #include <vtkPolyData.h>
// #include <vtkPoints.h>
// #include <vtkCellArray.h>
// #include <vtkPlaneSource.h>
// #include <vtkCellPicker.h>
// #include <vtkInteractorStyleTrackballCamera.h>
// #include <vtkProperty.h>
// #include <vtkSelectionNode.h>
// #include <vtkSelection.h>
// #include <vtkExtractSelection.h>
// #include <vtkObjectFactory.h>
// #include <vtkAutoInit.h>

// VTK_MODULE_INIT(vtkRenderingOpenGL2)

// // Catch mouse events
// class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera
// {
//   public:
//   static MouseInteractorStyle* New();

//   MouseInteractorStyle()
//   {
//     selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
//     selectedActor = vtkSmartPointer<vtkActor>::New();
//   }

//     virtual void OnLeftButtonDown()
//     {
//       // Get the location of the click (in window coordinates)
//       int* pos = this->GetInteractor()->GetEventPosition();

//       vtkSmartPointer<vtkCellPicker> picker =
//         vtkSmartPointer<vtkCellPicker>::New();
//       picker->SetTolerance(0.0005);
  
//       // Pick from this location.
//       picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());

//       double* worldPosition = picker->GetPickPosition();
//       std::cout << "Cell id is: " << picker->GetCellId() << std::endl;

//       if(picker->GetCellId() != -1)
//         {
      
//         std::cout << "Pick position is: " << worldPosition[0] << " " << worldPosition[1]
//                   << " " << worldPosition[2] << endl;
                  
//         vtkSmartPointer<vtkIdTypeArray> ids =
//           vtkSmartPointer<vtkIdTypeArray>::New();
//         ids->SetNumberOfComponents(1);
//         ids->InsertNextValue(picker->GetCellId());

//         vtkSmartPointer<vtkSelectionNode> selectionNode =
//           vtkSmartPointer<vtkSelectionNode>::New();
//         selectionNode->SetFieldType(vtkSelectionNode::CELL);
//         selectionNode->SetContentType(vtkSelectionNode::INDICES);
//         selectionNode->SetSelectionList(ids);

//         vtkSmartPointer<vtkSelection> selection =
//           vtkSmartPointer<vtkSelection>::New();
//         selection->AddNode(selectionNode);

//         vtkSmartPointer<vtkExtractSelection> extractSelection =
//           vtkSmartPointer<vtkExtractSelection>::New();
// #if VTK_MAJOR_VERSION <= 5
//         extractSelection->SetInput(0, this->Data);
//         extractSelection->SetInput(1, selection);
// #else
//         extractSelection->SetInputData(0, this->Data);
//         extractSelection->SetInputData(1, selection);
// #endif
//         extractSelection->Update();

//         // In selection
//         vtkSmartPointer<vtkUnstructuredGrid> selected =
//           vtkSmartPointer<vtkUnstructuredGrid>::New();
//         selected->ShallowCopy(extractSelection->GetOutput());

//         std::cout << "There are " << selected->GetNumberOfPoints()
//                   << " points in the selection." << std::endl;
//         std::cout << "There are " << selected->GetNumberOfCells()
//                   << " cells in the selection." << std::endl;


// #if VTK_MAJOR_VERSION <= 5
//         selectedMapper->SetInputConnection(
//           selected->GetProducerPort());
// #else
//         selectedMapper->SetInputData(selected);
// #endif
     
//         selectedActor->SetMapper(selectedMapper);
//         selectedActor->GetProperty()->EdgeVisibilityOn();
//         selectedActor->GetProperty()->SetEdgeColor(1,0,0);
//         selectedActor->GetProperty()->SetLineWidth(3);
        
//         this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(selectedActor);
        
//         }
//       // Forward events
//       vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
//     }

//     vtkSmartPointer<vtkPolyData> Data;
//     vtkSmartPointer<vtkDataSetMapper> selectedMapper;
//     vtkSmartPointer<vtkActor> selectedActor;

// };

// vtkStandardNewMacro(MouseInteractorStyle);

// int main (int, char *[])
// {
//   vtkSmartPointer<vtkPlaneSource> planeSource =
//     vtkSmartPointer<vtkPlaneSource>::New();
//   planeSource->Update();

//   vtkSmartPointer<vtkTriangleFilter> triangleFilter =
//     vtkSmartPointer<vtkTriangleFilter>::New();
//   triangleFilter->SetInputConnection(planeSource->GetOutputPort());
//   triangleFilter->Update();
  
//   vtkSmartPointer<vtkPolyDataMapper> mapper =
//     vtkSmartPointer<vtkPolyDataMapper>::New();
//   mapper->SetInputConnection(triangleFilter->GetOutputPort());

//   vtkSmartPointer<vtkActor> actor =
//     vtkSmartPointer<vtkActor>::New();
//   actor->GetProperty()->SetColor(0,1,0); //green
//   actor->SetMapper(mapper);

//   vtkSmartPointer<vtkRenderer> renderer =
//     vtkSmartPointer<vtkRenderer>::New();
//   vtkSmartPointer<vtkRenderWindow> renderWindow =
//     vtkSmartPointer<vtkRenderWindow>::New();
//   renderWindow->AddRenderer(renderer);

//   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//     vtkSmartPointer<vtkRenderWindowInteractor>::New();
//   renderWindowInteractor->SetRenderWindow(renderWindow);
//   renderWindowInteractor->Initialize();

//   // Set the custom stype to use for interaction.
//   vtkSmartPointer<MouseInteractorStyle> style =
//     vtkSmartPointer<MouseInteractorStyle>::New();
//   style->SetDefaultRenderer(renderer);
//   style->Data = triangleFilter->GetOutput();

//   renderWindowInteractor->SetInteractorStyle(style);

//   renderer->AddActor(actor);
//   renderer->ResetCamera();

//   renderer->SetBackground(0,0,1); // Blue

//   renderWindow->Render();
//   renderWindowInteractor->Start();

//   return EXIT_SUCCESS;
// }