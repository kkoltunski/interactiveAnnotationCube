#include "scene3d.h"
#include <vtkNamedColors.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkPolyDataMapper.h>
#include <vtkCylinderSource.h>

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

    m_renderer->SetBackground(colorGenerator->GetColor3d("LightSteelBlue").GetData());
    m_renderer->SetUseFXAA(true);

    m_renderWindow->SetSize(m_sceneDimension[0], m_sceneDimension[1]);
    m_renderWindow->AddRenderer(m_renderer);
    m_renderWindow->SetWindowName("Interactive Annotation Cube");

    m_windowInteractor->SetRenderWindow(m_renderWindow);
    m_windowInteractor->SetInteractorStyle(vSP<vtkInteractorStyleTrackballCamera>::New());
    m_windowInteractor->Initialize();
}

void Scene3D::start(){
    m_renderWindow->Render();
    m_windowInteractor->Start();
}

vSP<vtkRenderWindowInteractor> Scene3D::getInteractor(){
    return m_windowInteractor;
}