#include "customInteractorStyle.h"

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCellPicker.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkUnsignedCharArray.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkLine.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

vtkStandardNewMacro(CustomInteractorStyle);

void CustomInteractorStyle::OnLeftButtonDown(){
    auto picker = vSP<vtkCellPicker>::New();
    int eventPosition[2] {0, 0};

    this->GetInteractor()->GetEventPosition(eventPosition);
    picker->Pick(eventPosition[0], eventPosition[1], 0, this->GetDefaultRenderer());
    auto cellID = picker->GetCellId();

    if(cellID != -1){
      vSP<vtkUnsignedCharArray> cellData = vSP<vtkUnsignedCharArray>::New();
      double tupleData[4] = {0, 0, 0, 0};
      auto pickedActorMapper = picker->GetActor()->GetMapper();
      m_pickedPolyData = vtkPolyData::SafeDownCast(pickedActorMapper->GetInput());
      m_polyDataOriginalScalars = m_pickedPolyData->GetCellData()->GetScalars();
      auto numberOfCells = m_pickedPolyData->GetNumberOfCells();

      MarkCellEdges(pickedActorMapper->GetInput()->GetCell(cellID));

      cellData->SetNumberOfComponents(3);
      cellData->SetNumberOfTuples(numberOfCells);

      auto lut = vtkLookupTable::SafeDownCast(pickedActorMapper->GetLookupTable());
      lut->SetHueRange(.0, .667);
      lut->SetSaturationRange(.0, .0);

      for (int i = 0; i < numberOfCells; i++)
      {
        if(i != cellID){
          lut->GetColor(i, tupleData);
          tupleData[0] *= 255;
          tupleData[1] *= 255;
          tupleData[2] *= 255;
          tupleData[3] = 255;
        }
        else{
          tupleData[0] = 0;
          tupleData[1] = 255;
          tupleData[2] = 0;
          tupleData[3] = 128;
        }

        cellData->InsertTuple(i, tupleData);
      }

      m_pickedPolyData->GetCellData()->SetScalars(cellData);
      this->GetDefaultRenderer()->GetRenderWindow()->Render();
    }

    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void CustomInteractorStyle::OnLeftButtonUp(){
    if(m_pickedPolyData){
      m_pickedPolyData->GetCellData()->SetScalars(m_polyDataOriginalScalars);
      this->GetDefaultRenderer()->RemoveActor(m_edgesActor);

      m_pickedPolyData = nullptr;
      m_edgesActor->Delete();
    }

    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void CustomInteractorStyle::MarkCellEdges(vtkCell* _pickedCell){
  vSP<vtkNamedColors> colorGenerator = vSP<vtkNamedColors>::New();
  vSP<vtkPolyData> edgesPolyData = vSP<vtkPolyData>::New();
  vSP<vtkCellArray> edgeLines = vSP<vtkCellArray>::New();
  vSP<vtkPolyDataMapper> mapper = vSP<vtkPolyDataMapper>::New();
  vSP<vtkVertexGlyphFilter> vertexGlyphFilter = vSP<vtkVertexGlyphFilter>::New();
  m_edgesActor = vtkActor::New();
    auto points = _pickedCell->GetNumberOfPoints();

  edgesPolyData->SetPoints(_pickedCell->GetPoints());
  vertexGlyphFilter->AddInputData(edgesPolyData);
  vertexGlyphFilter->Update();

  for(int i = 0; i < points; i++){
        vSP<vtkLine> line = vSP<vtkLine>::New();
        line->GetPointIds()->SetId(0,i);
        if((i+1) < points){
          line->GetPointIds()->SetId(1,i+1);
        }
        else{
          line->GetPointIds()->SetId(1,0);
        }

        edgeLines->InsertNextCell(line);
  }

  vertexGlyphFilter->GetOutput()->SetLines(edgeLines);
  mapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
  m_edgesActor->SetMapper(mapper);
  auto actorProperties = m_edgesActor->GetProperty();
  actorProperties->SetPointSize(10);
  actorProperties->SetLineWidth(2);
  actorProperties->SetColor(colorGenerator->GetColor3d("HotPink").GetData());

  this->GetDefaultRenderer()->AddActor(m_edgesActor);
}