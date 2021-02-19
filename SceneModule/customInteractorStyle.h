#ifndef CUSTOMINTERACTORSTYLE_H
#define CUSTOMINTERACTORSTYLE_H

#include "../typedefs.h"

#include <vtkObjectFactory.h>
#include <vtkInteractorStyleTrackballCamera.h>

class vtkActor;
class vtkCell;
class vtkPolyData;
class vtkDataArray;
class vtkInteractorStyleTrackballCamera;

class CustomInteractorStyle : public vtkInteractorStyleTrackballCamera{
public:
	static CustomInteractorStyle *New();

	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();

protected:
	void MarkCellEdges(vtkCell* _pickedCell);

	CustomInteractorStyle() = default;
	virtual ~CustomInteractorStyle() = default;

private:
	vtkTypeMacro(CustomInteractorStyle,
    			vtkInteractorStyleTrackballCamera);

	CustomInteractorStyle(const CustomInteractorStyle&);
	void operator=(const CustomInteractorStyle&);

	vtkPolyData* m_pickedPolyData;
	vtkDataArray* m_polyDataOriginalScalars;
	vtkActor* m_edgesActor;
};

#endif // CUSTOMINTERACTORSTYLE_H