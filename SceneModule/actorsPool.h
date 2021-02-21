#ifndef ACTORSPOOL_H
#define ACTORSPOOL_H

#include "../typedefs.h"

class vtkRenderer;

class ActorsPool{
public:
    ActorsPool();
    vSP<vtkRenderer> getRenderer();
    
protected:

private:
    vSP<vtkRenderer> m_renderer;

};

#endif // ACTORSPOOL_H