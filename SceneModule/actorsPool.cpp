#include "actorsPool.h"

#include <vtkRenderer.h>
#include <vtkNamedColors.h>

#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>

ActorsPool::ActorsPool() : m_renderer{vSP<vtkRenderer>::New()}
{
    vSP<vtkNamedColors> colorGenerator = vSP<vtkNamedColors>::New();
    m_renderer->SetBackground(colorGenerator->GetColor3d("LightSteelBlue").GetData());
    m_renderer->SetUseFXAA(true);

vSP<vtkCylinderSource> cylinder = vSP<vtkCylinderSource>::New();
cylinder->SetResolution(8);

vSP<vtkPolyDataMapper> cylinderMapper = vSP<vtkPolyDataMapper>::New();
cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

vSP<vtkActor> cylinderActor = vSP<vtkActor>::New();
cylinderActor->SetMapper(cylinderMapper);
m_renderer->AddActor(cylinderActor);
m_renderer->ResetCamera();
}

vSP<vtkRenderer> ActorsPool::getRenderer(){
    return m_renderer;
}