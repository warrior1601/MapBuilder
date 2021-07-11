//--------------------mainwindow.cpp--------------------//

// MainWindow.cpp
// Map_Builder
// Created By Jedidiah Paterson on 05/28/2020.
// Copyright @ 2020 Jedidiah Paterson. All right reserved.

#include "ui_mainwindow.h" // in orer to click "Go To Slot on mainwindow.ui this need to be before the header file"
#include "mainwindow.h"
//-------------Constructor------------//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display_Window->SetRenderWindow( renderWindow );
    ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
    HandleInteractors();

    renderer->ResetCameraClippingRange();
    renderer->SetBackground( colors->GetColor3d("Black").GetData() );
    renderer->GetActiveCamera()->SetPosition(50.0, 50.0, 50.0);
    renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);

    ui->Elevation->setEnabled(false);
    ui->X_STL_Scale->setEnabled(false);
    ui->Y_STL_Scale->setEnabled(false);
    ui->Z_STL_Scale->setEnabled(false);
    ui->X_STL_Shift->setEnabled(false);
    ui->Y_STL_Shift->setEnabled(false);
    ui->Z_STL_Shift->setEnabled(false);
    ui->X_STL_Actor_Rotate->setEnabled(false);
    ui->Y_STL_Actor_Rotate->setEnabled(false);
    ui->Z_STL_Actor_Rotate->setEnabled(false);
    ui->Terrain_Type_Selector->setEnabled(false);
    ui->Texture_Type_Selector->setEnabled(false);

}
//--------------Destructor-------------//
MainWindow::~MainWindow()
{
    delete ui;
}
//-------Special Member Functions------//
void MainWindow::RenderFunction()
{
    for(size_t i=0; i<FirstMap.GetNumberOfRows(); i++)
    {
        for(size_t j=0; j<FirstMap.GetNumberOfColumns(); j++)
            renderer->AddActor(FirstMap.GetMap()[i][j].GetActor() );
    }
    orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    OrientationWidgetInIt();
    renderer->ResetCamera();
    renderWindow->Render();
    ui->X_Map_Size->display(int (FirstMap.GetMap().size() ) );
    ui->Y_Map_Size->display(int (FirstMap.GetMap()[0].size() ) );
}

void MainWindow::on_Add_Column_released()
{
    FirstMap.SetNumberOfColumns( (FirstMap.GetNumberOfColumns() + 1 ) );
    FirstMap.AddColumn();
    RenderFunction();
    ui->Column_Selector->setMaximum(FirstMap.GetNumberOfColumns() );
}

void MainWindow::on_Add_Row_released()
{
    FirstMap.SetNumberOfRows( (FirstMap.GetNumberOfRows() + 1 ) );
    if (FirstMap.GetNumberOfColumns() == 0)
        FirstMap.SetNumberOfColumns(1);

    FirstMap.AddRow();
    RenderFunction();
    ui->Row_Selector->setMaximum(FirstMap.GetNumberOfRows() );
}

void MainWindow::OrientationWidgetInIt()
{
    //This adds the X-Y-Z axis markers and moves them as the view point changes
    orientationWidget->SetOrientationMarker( axes );
    orientationWidget->SetInteractor(ui->Display_Window->GetRenderWindow()->GetInteractor());
    orientationWidget->SetEnabled(1);
    orientationWidget->InteractiveOff();
}

void MainWindow::on_Rows_valueChanged(int arg1) { FirstMap.SetNumberOfRows(arg1); }

void MainWindow::on_Columns_valueChanged(int arg1) { FirstMap.SetNumberOfColumns(arg1); }

void MainWindow::on_Generate_Map_released()
{
    this->setCursor(Qt::WaitCursor);
    on_Rows_valueChanged(ui->Rows->value() );
    on_Columns_valueChanged(ui->Columns->value() );
    FirstMap.GenerateMap();
    RenderFunction();
    ui->Row_Selector->setMaximum(FirstMap.GetNumberOfRows() );
    ui->Column_Selector->setMaximum(FirstMap.GetNumberOfColumns() );
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_Row_Selector_valueChanged(int arg1)
{
    SelectedRow = arg1;

    if (arg1 == 0)
    {
        ui->Elevation->setEnabled(false);
        ui->X_STL_Scale->setEnabled(false);
        ui->Y_STL_Scale->setEnabled(false);
        ui->Z_STL_Scale->setEnabled(false);
        ui->X_STL_Shift->setEnabled(false);
        ui->Y_STL_Shift->setEnabled(false);
        ui->Z_STL_Shift->setEnabled(false);
        ui->X_STL_Actor_Rotate->setEnabled(false);
        ui->Y_STL_Actor_Rotate->setEnabled(false);
        ui->Z_STL_Actor_Rotate->setEnabled(false);
        ui->Terrain_Type_Selector->setEnabled(false);
        ui->Texture_Type_Selector->setEnabled(false);
        return;
    }
    if(SelectedColumn>0)
    {
        ui->Elevation->setEnabled(true);
        ui->X_STL_Scale->setEnabled(true);
        ui->Y_STL_Scale->setEnabled(true);
        ui->Z_STL_Scale->setEnabled(true);
        ui->X_STL_Shift->setEnabled(true);
        ui->Y_STL_Shift->setEnabled(true);
        ui->Z_STL_Shift->setEnabled(true);
        ui->X_STL_Actor_Rotate->setEnabled(true);
        ui->Y_STL_Actor_Rotate->setEnabled(true);
        ui->Z_STL_Actor_Rotate->setEnabled(true);
        ui->Terrain_Type_Selector->setEnabled(true);
        ui->Texture_Type_Selector->setEnabled(true);
        UpdateSpinBoxes();
        FirstMap.HighlightTerrainSquare((SelectedRow - 1), (SelectedColumn - 1) );
        renderWindow->Render();
    }
}

void MainWindow::on_Column_Selector_valueChanged(int arg1)
{
    SelectedColumn = arg1;

    if (arg1 == 0)
    {
        ui->Elevation->setEnabled(false);
        ui->X_STL_Scale->setEnabled(false);
        ui->Y_STL_Scale->setEnabled(false);
        ui->Z_STL_Scale->setEnabled(false);
        ui->X_STL_Shift->setEnabled(false);
        ui->Y_STL_Shift->setEnabled(false);
        ui->Z_STL_Shift->setEnabled(false);
        ui->X_STL_Actor_Rotate->setEnabled(false);
        ui->Y_STL_Actor_Rotate->setEnabled(false);
        ui->Z_STL_Actor_Rotate->setEnabled(false);
        ui->Terrain_Type_Selector->setEnabled(false);
        ui->Texture_Type_Selector->setEnabled(false);
        return;
    }
    if(SelectedRow>0)
    {
        ui->Elevation->setEnabled(true);
        ui->X_STL_Scale->setEnabled(true);
        ui->Y_STL_Scale->setEnabled(true);
        ui->Z_STL_Scale->setEnabled(true);
        ui->X_STL_Shift->setEnabled(true);
        ui->Y_STL_Shift->setEnabled(true);
        ui->Z_STL_Shift->setEnabled(true);
        ui->X_STL_Actor_Rotate->setEnabled(true);
        ui->Y_STL_Actor_Rotate->setEnabled(true);
        ui->Z_STL_Actor_Rotate->setEnabled(true);
        ui->Terrain_Type_Selector->setEnabled(true);
        ui->Texture_Type_Selector->setEnabled(true);
        UpdateSpinBoxes();
        FirstMap.HighlightTerrainSquare((SelectedRow - 1), (SelectedColumn - 1) );
        renderWindow->Render();
    }
}

void MainWindow::on_Select_Square_released() //This will change. Just added for testing
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Model Colour");
    //checks to ensure that the selector color is valid
    if(Color.isValid())
    {   //converts the QColor to RGB values ranging from 0.0 through 1.0 to be used by SetColor function
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
        FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetActor()->GetProperty()->SetColor( red,green,blue );
        FirstMap.SetColour(red, green, blue);
    }
    renderWindow->Render();
}

void MainWindow::on_Elevation_valueChanged(double arg1)
{
    if(FirstMap.GetCreateHillStatus() == Qt::Unchecked)
    {
        ui->Hill_Radius->setValue(0);
        FirstMap.CreateHill(arg1, SelectedRow, SelectedColumn);
        on_Terrain_Type_Selector_currentIndexChanged(ui->Terrain_Type_Selector->currentText() );
    }
    else
    {
        FirstMap.CreateHill(arg1, SelectedRow, SelectedColumn);
        //need a way to update the actor for the stl image for all cells in the hill.
    }
    renderWindow->Render();
}

void MainWindow::on_Clear_released()
{
    ui->Display_Window->GetRenderWindow()->RemoveRenderer( renderer );
    FirstMap.Clear();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
    renderer->ResetCamera();
    renderWindow->Render();

    FirstMap.SetNumberOfRows(0);
    FirstMap.SetNumberOfColumns(0);

    ui->Column_Selector->setValue(0);
    ui->Row_Selector->setValue(0);
    ui->Column_Selector->setMaximum(0);
    ui->Row_Selector->setMaximum(0);
}

void MainWindow::on_Dimensions_released()
{
    static bool checked = true;
    checked = !checked;
    if(checked == true)
    {
        AxesActor->SetBounds(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetActor()->GetBounds());
        AxesActor->SetCamera(renderer->GetActiveCamera());
        //Shows the grid
        AxesActor->DrawXGridlinesOn();
        AxesActor->DrawYGridlinesOn();
        AxesActor->DrawZGridlinesOn();
        //Sets the axes colour as white.Future upgrade should allow the user to change this colour
        AxesActor->GetXAxesGridlinesProperty()->SetColor(0.5,0.5,0.5);
        AxesActor->GetYAxesGridlinesProperty()->SetColor(0.5,0.5,0.5);
        AxesActor->GetZAxesGridlinesProperty()->SetColor(0.5,0.5,0.5);
        AxesActor->XAxisMinorTickVisibilityOff();
        AxesActor->YAxisMinorTickVisibilityOff();
        AxesActor->ZAxisMinorTickVisibilityOff();
        //Sets the grid line location
        AxesActor->SetGridLineLocation(2);
        renderer->AddActor(AxesActor);
    }
    else
    {
        renderer->RemoveActor(AxesActor);
    }
    renderWindow->Render();
}

void MainWindow::on_Load_STL_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "../../terrain_types",
                                                    tr("Model Files(*.stl)"));
    std::string FilePath = fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    if (myFile.is_open())
    {
        ui->Display_Window->GetRenderWindow()->RemoveRenderer( renderer );
        readerSTL->SetFileName(FilePath.data());

        vtkSmartPointer<vtkUnstructuredGrid> Ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
        vtkSmartPointer<vtkDataSetMapper> Mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();

        Mapper->SetInputConnection( readerSTL->GetOutputPort() );
        readerSTL->Update();
        Actor->SetMapper(Mapper);
        Actor->GetProperty()->EdgeVisibilityOff();
        //Actor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() );
        renderer->AddActor(Actor);

        std::cout << Actor->GetMapper()->GetInput()->GetNumberOfCells() <<std::endl;

        ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
    }
    renderWindow->Render();
}

void MainWindow::on_Terrain_Type_Selector_currentIndexChanged(const QString &arg1)
{
    if (!FirstMap.GetMap().empty() )
    {
        std::string Terrain = arg1.toUtf8().constData();
        renderer->RemoveActor(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor() );

        if(Terrain.compare("No Terrain Type") == 0)
        {
            on_X_STL_Actor_Rotate_valueChanged(0);
            on_Y_STL_Actor_Rotate_valueChanged(0);
            on_Z_STL_Actor_Rotate_valueChanged(0);

            renderWindow->Render();
            return;
        }

        if(!ListOfLoadedTerrainTypes.empty() )
        {
            for(size_t i=0; i<ListOfLoadedTerrainTypes.size(); i++)
            {
                if(Terrain.compare(ListOfLoadedTerrainTypes[i]) == 0 )
                {
                    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().ChangeTerrainTypeActor(ListOfLoadedSTLs[i]);
                    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetName(Terrain);
                    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );
                    renderer->AddActor(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor() );
                    renderWindow->Render();
                    return;
                }
            }
            FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].SetTerrainType(Terrain); //This loads the Terrain for the first time
            renderer->AddActor(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor() );

            ListOfLoadedTerrainTypes.push_back(Terrain);
            ListOfLoadedSTLs.push_back(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetSTL() );
        }
        else
        {
            on_X_STL_Actor_Rotate_valueChanged(0);
            on_Y_STL_Actor_Rotate_valueChanged(0);
            on_Z_STL_Actor_Rotate_valueChanged(0);

            FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].SetTerrainType(Terrain); //This loads the terrain for the first time when the List is empty
            renderer->AddActor(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor() );

            ListOfLoadedTerrainTypes.push_back(Terrain);
            ListOfLoadedSTLs.push_back(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetSTL() );
        }
        UpdateSpinBoxes();
        renderWindow->Render();
    }
}

void MainWindow::on_Texture_Type_Selector_currentIndexChanged(const QString &arg1)
{

    std::string inputFilename = arg1.toUtf8().constData();

    if(inputFilename.compare("No Texture") == 0)
    {
        FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].RemoveTexure();
        renderWindow->Render();
        return;
    }
    std::string Image = "../../terrain_types/" + inputFilename + ".jpeg";
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].SetTextureName(Image);
    renderWindow->Render();
}

void MainWindow::UpdateSpinBoxes()
{
    ui->X_STL_Shift->setValue(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[0]);
    ui->Y_STL_Shift->setValue(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[1]);
    ui->Z_STL_Shift->setValue(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[2]);

    ui->X_STL_Scale->setValue(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[0]);
    ui->Y_STL_Scale->setValue(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[1]);
    ui->Z_STL_Scale->setValue(FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[2]);
}

void MainWindow::on_X_STL_Shift_valueChanged(double arg1)
{
    double Offset[] = {arg1, FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[1], FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[2]};
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorOffset(Offset);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );
    renderWindow->Render();
}

void MainWindow::on_Y_STL_Shift_valueChanged(double arg1)
{
    double Offset[] = {FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[0], arg1, FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[2]};
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorOffset(Offset);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );
    renderWindow->Render();
}

void MainWindow::on_Z_STL_Shift_valueChanged(double arg1)
{
    double Offset[] = {FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[0], FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorOffset()[1], arg1};
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorOffset(Offset);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );
    renderWindow->Render();
}

void MainWindow::on_X_STL_Scale_valueChanged(double arg1)
{
    double Scale[] = {arg1, FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[1], FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[2]};
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorScale(Scale);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );

    renderWindow->Render();
}

void MainWindow::on_Y_STL_Scale_valueChanged(double arg1)
{
    double Scale[] = {FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[0], arg1, FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[2]};
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorScale(Scale);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );
    renderWindow->Render();
}

void MainWindow::on_Z_STL_Scale_valueChanged(double arg1)
{
    double Scale[] = {FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[0], FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActorScale()[1], arg1};
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorScale(Scale);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().UpdateTerrainTypeActor( FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainSquarePosition() );
    renderWindow->Render();
}

void MainWindow::on_X_Camera_Position_valueChanged(int value)
{
    static int Last_Value_Azimuth = 0.0;
    int Temp = value;
    value = value-Last_Value_Azimuth;
    renderer->GetActiveCamera()->Azimuth(double (value));
    Last_Value_Azimuth = Temp;
    renderWindow->Render();
}

void MainWindow::on_Y_Camera_Position_valueChanged(int value)
{
    static double Last_Value_Roll = 0.0;
    int Temp = value;
    value = value-Last_Value_Roll;
    renderer->GetActiveCamera()->Roll(double (value));
    Last_Value_Roll = Temp;
    renderWindow->Render();
}

void MainWindow::on_Z_Camera_Position_valueChanged(int value)
{
    static double Last_Value_Elevation= 0.0;
    int Temp = value;
    value = value-Last_Value_Elevation;
    renderer->GetActiveCamera()->Elevation(double (value));
    Last_Value_Elevation = Temp;
    renderWindow->Render();
}

void MainWindow::on_X_STL_Actor_Rotate_valueChanged(int value)
{
    static double X_Rotation= 0.0;
    int Temp = value;
    value = value-X_Rotation;
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->RotateWXYZ(double (value), 1, 0, 0);
    double *Ornt = FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->GetOrientation();
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorOrientation(Ornt);
    X_Rotation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Y_STL_Actor_Rotate_valueChanged(int value)
{
    static double Y_Rotation= 0.0;
    int Temp = double (value);
    value = value-Y_Rotation;


    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->RotateWXYZ(double (value), 0, 1, 0 );
    double *Ornt = FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->GetOrientation();
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorOrientation(Ornt);
    Y_Rotation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Z_STL_Actor_Rotate_valueChanged(int value)
{
    static double Z_Rotation= 0.0;
    int Temp = double (value);
    value = value-Z_Rotation;

    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->RotateWXYZ(double (value), 0, 0, 1 );
    double *Ornt = FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->GetOrientation();
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().SetActorOrientation(Ornt);

    Z_Rotation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Create_Hill_stateChanged(int arg1) { FirstMap.SetCreateHill(arg1); }

void MainWindow::on_Hill_Radius_valueChanged(int arg1) { FirstMap.SetHillRadius(arg1); }

void MainWindow::on_Hill_Gradient_valueChanged(int value) { FirstMap.SetHillGradient(double (value/100.00) ); }

void MainWindow::on_Elevation_Filter_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        FirstMap.ElevationTopography();
    }

    if(arg1 == Qt::Unchecked)
    {
        FirstMap.RemoveElevationTopography();
    }
    renderWindow->Render();
}

void MainWindow::HandleInteractors()
{
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();

    cellInteractor = vtkSmartPointer<cellSelectionInteractor>::New();
    cellInteractor->SetDefaultRenderer(renderer);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> defaultStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

    if (ui->Camera_Interactor->checkState() == Qt::Checked)
        renderWindowInteractor->SetInteractorStyle(defaultStyle);

    if (ui->Mouse_Interactor->checkState() == Qt::Checked)
        renderWindowInteractor->SetInteractorStyle(cellInteractor);

    OrientationWidgetInIt();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (ui->Mouse_Interactor->checkState() == Qt::Checked)
    {
        cellInteractor->OnLeftButtonDown();
        ui->Row_Selector->setValue(int(cellInteractor->GetSelectedCell()[0]) + 1);
        ui->Column_Selector->setValue( int(cellInteractor->GetSelectedCell()[1]) + 1 );
    }
}

void MainWindow::on_Camera_Interactor_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
        ui->Mouse_Interactor->setCheckState(Qt::Unchecked);
    HandleInteractors();
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_Mouse_Interactor_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
        ui->Camera_Interactor->setCheckState(Qt::Unchecked);
    HandleInteractors();
    this->setCursor(Qt::PointingHandCursor);
}

void MainWindow::on_Save_released()
{
    QString NewSTLFilePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                          "",tr("VRML (*.vrml)"));
    std::string STLFilePath = NewSTLFilePath.toUtf8().constData();
    SceneWriter->SetFileName(STLFilePath.c_str());
    //Established data input for the writer
    SceneWriter->SetInput (renderWindow);
    SceneWriter->Write();
}

void MainWindow::on_Load_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model File"), "",
                                                    tr("VRML(*.vrml)"));
    std::string FilePath = fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        SceneReader->SetFileName(FilePath.data());
        SceneReader->SetRenderWindow(ui->Display_Window->GetRenderWindow() );
        SceneReader->Update();

        renderWindow->Render();
    }
}

void MainWindow::on_X_Texture_Scale_valueChanged(double arg1)
{
    double *Scale = TransformTexture->GetScale();
    Scale[0] = arg1;
    TransformTexture->Scale(Scale);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    renderWindow->Render();
}

void MainWindow::on_Y_Texture_Scale_valueChanged(double arg1)
{
    double *Scale = TransformTexture->GetScale();
    Scale[1] = arg1;
    TransformTexture->Scale(Scale);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    renderWindow->Render();
}

void MainWindow::on_Z_Texture_Scale_valueChanged(double arg1)
{
    double *Scale = TransformTexture->GetScale();
    Scale[2] = arg1;
    TransformTexture->Scale(Scale);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    renderWindow->Render();
}

void MainWindow::on_X_Texture_Rotation_valueChanged(int value)
{
    static double XTextureRotation = 0.0;
    int Temp = double (value);
    value = value-XTextureRotation;
    TransformTexture->RotateWXYZ(double (value), 1.0, 0.0, 0.0);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    XTextureRotation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Y_Texture_Rotation_valueChanged(int value)
{
    static double YTextureRotation = 0.0;
    int Temp = double (value);
    value = value-YTextureRotation;
    TransformTexture->RotateWXYZ(double (value), 0.0, 1.0, 0.0);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    YTextureRotation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Z_Texture_Rotation_valueChanged(int value)
{
    static double ZTextureRotation = 0.0;
    int Temp = double (value);
    value = value-ZTextureRotation;
    TransformTexture->RotateWXYZ(double (value), 0.0, 0.0, 1.0);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    ZTextureRotation = Temp;
    renderWindow->Render();
}

void MainWindow::on_X_Texture_Translation_valueChanged(double arg1)
{
    TransformTexture->Translate(arg1, 0.0, 0.0);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    renderWindow->Render();
}

void MainWindow::on_Y_Texture_Translation_valueChanged(double arg1)
{
    TransformTexture->Translate(0.0, arg1, 0.0);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    renderWindow->Render();
}

void MainWindow::on_Z_Texture_Translation_valueChanged(double arg1)
{
    TransformTexture->Translate(0.0, 0.0, arg1);
    FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTexture()->SetTransform(TransformTexture);
    renderWindow->Render();
}

void MainWindow::on_Terrain_Color_Change_clicked()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Model Colour");
    //checks to ensure that the selector color is valid
    if(Color.isValid())
    {   //converts the QColor to RGB values ranging from 0.0 through 1.0 to be used by SetColor function
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
        FirstMap.GetMap()[SelectedRow - 1][SelectedColumn - 1].GetTerrainType().GetActor()->GetProperty()->SetColor( red,green,blue );
        FirstMap.SetColour(red, green, blue);
    }
    renderWindow->Render();
}
