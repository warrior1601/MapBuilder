//-----MainWindow.h--------------//
// Map_Builder
// Created by Jedidiah Paterson on 05/28/2020.
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.

/** @file mainwindow.h This file contains the function that allow a model to be loaded and manipulated.
 * Currently suppoorting .MOD/.TXT/.STL files only.
 * @author Jedidiah Paterson
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// Header files from QT
#include <QColorDialog>
#include <QCursor>
#include <QDebug>           // TROUBLESHOOTING ONLY //
#include <QEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
// Header files from vtk
#include <vtkActorCollection.h>

#include <vtkAppendPolyData.h>

#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCubeAxesActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPolyData.h>
#include <vtkProp.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkTransform.h>

#include <vtkVRMLExporter.h>
#include <vtkVRMLImporter.h>
// C++ Header files
// Projct Header files
#include "grid.h"
#include "mouse_interactor.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:  
    explicit MainWindow(QWidget *parent = nullptr);   
    ~MainWindow();

private slots:
    void on_Add_Column_released();
    void on_Add_Row_released();
    void on_Rows_valueChanged(int arg1);
    void on_Columns_valueChanged(int arg1);
    void on_Generate_Map_released();
    void on_Row_Selector_valueChanged(int arg1);
    void on_Column_Selector_valueChanged(int arg1);
    void on_Select_Square_released();
    void on_Elevation_valueChanged(double arg1);
    void on_Clear_released(); //This deletes the map. So a new map can be generated
    void on_Dimensions_released();
    void on_Load_STL_released(); //will be removed
    void on_Terrain_Type_Selector_currentIndexChanged(const QString &arg1);
    void on_Texture_Type_Selector_currentIndexChanged(const QString &arg1);

    void on_X_STL_Shift_valueChanged(double arg1); //For adjusting STL loaded files position
    void on_Y_STL_Shift_valueChanged(double arg1); //For adjusting STL loaded files position
    void on_Z_STL_Shift_valueChanged(double arg1); //For adjusting STL loaded files position

    void on_X_STL_Scale_valueChanged(double arg1); //For adjusting STL loaded files scale
    void on_Y_STL_Scale_valueChanged(double arg1); //For adjusting STL loaded files scale
    void on_Z_STL_Scale_valueChanged(double arg1); //For adjusting STL loaded files scale

    void on_X_Camera_Position_valueChanged(int value); //Camera Controls
    void on_Y_Camera_Position_valueChanged(int value); //Camera Controls
    void on_Z_Camera_Position_valueChanged(int value); //Camera Controls

    void on_X_STL_Actor_Rotate_valueChanged(int value); //Rotate the STLloaded fileon the cell
    void on_Y_STL_Actor_Rotate_valueChanged(int value); //Rotate the STLloaded fileon the cell
    void on_Z_STL_Actor_Rotate_valueChanged(int value); //Rotate the STLloaded fileon the cell

    void on_Create_Hill_stateChanged(int arg1);
    void on_Hill_Radius_valueChanged(int arg1);
    void on_Hill_Gradient_valueChanged(int value);

    void on_Elevation_Filter_stateChanged(int arg1);
    void on_Camera_Interactor_stateChanged(int arg1);
    void on_Mouse_Interactor_stateChanged(int arg1);

    void on_Save_released();
    void on_Load_released();

    void on_X_Texture_Scale_valueChanged(double arg1);
    void on_Y_Texture_Scale_valueChanged(double arg1);
    void on_Z_Texture_Scale_valueChanged(double arg1);

    void on_X_Texture_Rotation_valueChanged(int value);
    void on_Y_Texture_Rotation_valueChanged(int value);
    void on_Z_Texture_Rotation_valueChanged(int value);

    void on_X_Texture_Translation_valueChanged(double arg1);
    void on_Y_Texture_Translation_valueChanged(double arg1);
    void on_Z_Texture_Translation_valueChanged(double arg1);

    void on_Terrain_Color_Change_clicked();

private:
//-------Private Functions--------//
    void HandleInteractors();
    void RenderFunction();
    void OrientationWidgetInIt();
    void UpdateSpinBoxes();
    void mousePressEvent(QMouseEvent *event);

//-------Private Members---------//
    Ui::MainWindow *ui;
    grid FirstMap;
    int SelectedRow = 0;
    int SelectedColumn = 0;

    vtkSmartPointer<vtkSTLReader> readerSTL = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkCubeAxesActor> AxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();

    vtkSmartPointer<cellSelectionInteractor> cellInteractor = vtkSmartPointer<cellSelectionInteractor>::New();
    vtkSmartPointer<vtkVRMLExporter> SceneWriter = vtkSmartPointer<vtkVRMLExporter>::New();
    vtkSmartPointer<vtkVRMLImporter> SceneReader = vtkSmartPointer<vtkVRMLImporter>::New();

    std::vector <std::string> ListOfLoadedTerrainTypes;
    std::vector <vtkSmartPointer<vtkSTLReader> > ListOfLoadedSTLs;

    vtkSmartPointer<vtkTransform> TransformTexture = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkAppendPolyData> AppendedPolyData = vtkSmartPointer<vtkAppendPolyData>::New();

};
#endif // MAINWINDOW_H
