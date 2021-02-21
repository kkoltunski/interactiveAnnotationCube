#include "scene3d.h"
#include "customInteractorStyle.h"
#include "actorsPool.h"

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

Scene3D::Scene3D(int* _sceneDimension)  :   
    m_renderWindow{vSP<vtkRenderWindow>::New()},
    m_windowInteractor{vSP<vtkRenderWindowInteractor>::New()}
{
    m_sceneDimension[0] = _sceneDimension[0];
    m_sceneDimension[1] = _sceneDimension[1];
}

Scene3D::Scene3D(int _dimensionX, int _dimensionY)  :
    m_renderWindow{vSP<vtkRenderWindow>::New()},
    m_windowInteractor{vSP<vtkRenderWindowInteractor>::New()}
{
    m_sceneDimension[0] = _dimensionX;
    m_sceneDimension[1] = _dimensionY;
}

void Scene3D::initialize(){
    auto renderer = m_actorsPool.getRenderer();
    m_renderWindow->SetSize(m_sceneDimension[0], m_sceneDimension[1]);
    m_renderWindow->AddRenderer(renderer);
    m_renderWindow->SetWindowName("Interactive Annotation Cube");

    vSP<CustomInteractorStyle> interactorStyle = vSP<CustomInteractorStyle>::New();
    interactorStyle->SetDefaultRenderer(renderer);

    m_windowInteractor->SetRenderWindow(m_renderWindow);
    m_windowInteractor->SetInteractorStyle(interactorStyle);
    m_windowInteractor->Initialize();
}

void Scene3D::start(){
    m_renderWindow->Render();
    m_windowInteractor->Start();
}

vtkRenderWindowInteractor* Scene3D::getInteractor(){
    return m_windowInteractor;
}
