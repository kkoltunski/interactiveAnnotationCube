#include "scene3d.h"
#include "customInteractorStyle.h"

#include <vtkNamedColors.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkPolyDataMapper.h>
#include <vtkCylinderSource.h>
#include <vtkProperty.h>
#include <vtkCellData.h>


Scene3D::Scene3D(int* _sceneDimension)  :   
    m_renderer{vSP<vtkRenderer>::New()},
    m_renderWindow{vSP<vtkRenderWindow>::New()},
    m_windowInteractor{vSP<vtkRenderWindowInteractor>::New()}
{
    m_sceneDimension[0] = _sceneDimension[0];
    m_sceneDimension[1] = _sceneDimension[1];
}

Scene3D::Scene3D(int _dimensionX, int _dimensionY)  :
    m_renderer{vSP<vtkRenderer>::New()},
    m_renderWindow{vSP<vtkRenderWindow>::New()},
    m_windowInteractor{vSP<vtkRenderWindowInteractor>::New()}
{
    m_sceneDimension[0] = _dimensionX;
    m_sceneDimension[1] = _dimensionY;
}

void Scene3D::initialize(){
    vSP<vtkNamedColors> colorGenerator = vSP<vtkNamedColors>::New();

vSP<vtkCylinderSource> cylinder = vSP<vtkCylinderSource>::New();
cylinder->SetResolution(8);

vSP<vtkPolyDataMapper> cylinderMapper = vSP<vtkPolyDataMapper>::New();
cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

vSP<vtkActor> cylinderActor = vSP<vtkActor>::New();
cylinderActor->SetMapper(cylinderMapper);

    m_renderer->SetBackground(colorGenerator->GetColor3d("LightSteelBlue").GetData());
    m_renderer->SetUseFXAA(true);
    m_renderer->AddActor(cylinderActor);
    m_renderer->ResetCamera();

    m_renderWindow->SetSize(m_sceneDimension[0], m_sceneDimension[1]);
    m_renderWindow->AddRenderer(m_renderer);
    m_renderWindow->SetWindowName("Interactive Annotation Cube");

    vSP<CustomInteractorStyle> interactorStyle = vSP<CustomInteractorStyle>::New();
    interactorStyle->SetDefaultRenderer(m_renderer);

    m_windowInteractor->SetRenderWindow(m_renderWindow);
    m_windowInteractor->SetInteractorStyle(interactorStyle);
    m_windowInteractor->Initialize();
}

void Scene3D::start(){
    m_renderWindow->Render();
    m_windowInteractor->Start();
}

vSP<vtkRenderWindowInteractor> Scene3D::getInteractor(){
    return m_windowInteractor;
}