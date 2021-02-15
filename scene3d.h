#ifndef SCENE3D_H
#define SCENE3D_H

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

template<typename T>
using vSP = vtkSmartPointer<T>;

class Scene3D{
public:
    Scene3D() = delete;
    Scene3D(int* _sceneDimension);
    Scene3D(int _dimensionX, int _dimensionY);

    void initialize();

private:
    int m_sceneDimension[2];

    vSP<vtkRenderer> m_renderer;
    vSP<vtkRenderWindow> m_renderWindow;
    vSP<vtkRenderWindowInteractor> m_windowInteractor;
};

#endif // SCENE3D_H