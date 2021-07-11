#include "mouse_interactor.h"

vtkStandardNewMacro(cellSelectionInteractor);

cellSelectionInteractor::cellSelectionInteractor() { initBool = false; }

cellSelectionInteractor::~cellSelectionInteractor(){}

void cellSelectionInteractor::OnLeftButtonDown()
{
    initBool = true;
    int* pos = this->GetInteractor()->GetEventPosition();

  vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
  picker->SetTolerance(0.0005);

  picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer());

  if(picker->GetCellId() != -1)
  {
      double * Bounds = picker->GetActors()->GetLastActor()->GetBounds();

      SelectedCellInGrid[0] = Bounds[0];
      SelectedCellInGrid[1] = Bounds[2];
  }
  else
      initBool = false;
}

bool cellSelectionInteractor::CheckInit() { return initBool; }

double* cellSelectionInteractor::GetSelectedCell() { return SelectedCellInGrid; }
