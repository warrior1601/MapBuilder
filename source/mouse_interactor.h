#ifndef MOUSE_INTERACTOR_H
#define MOUSE_INTERACTOR_H
// VTK Header Header Files
#include <vtkActorCollection.h>
#include <vtkCellPicker.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnstructuredGrid.h>


class cellSelectionInteractor : public vtkInteractorStyleTrackballCamera
{

public:
    static cellSelectionInteractor *New();

    vtkTypeMacro(cellSelectionInteractor,vtkInteractorStyleTrackballCamera);
//-----Constructor-----//
    cellSelectionInteractor();
//-----Destructor-----//
    ~cellSelectionInteractor();
//-----Special Member Functions-----//
    virtual void OnLeftButtonDown();
    double* GetSelectedCell();
    bool CheckInit();

private:
    double SelectedCellInGrid[2];
    bool initBool;
};

#endif // MOUSE_INTERACTOR_H
