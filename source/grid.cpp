#include "grid.h"
//-----Constructor-----//
grid::grid() {}
//-----Destructor-----//
grid::~grid() {}
//-----Get Functions-----//
int grid::GetCreateHillStatus() { return (CreateHillStatus); }

double grid::GetHillGradient() { return (HillGradient); }

int grid::GetHillRaduis() {return (HillRadius); }

int grid::GetNumberOfRows() { return NumberOfRows; }

int grid::GetNumberOfColumns() { return NumberOfColumns; }

std::vector< std::vector<terrain_square> >& grid::GetMap(void) { return Map; }
//-----Set Functions-----//
void grid::SetCreateHill(int aQTCheckedStatus) { CreateHillStatus = aQTCheckedStatus; }

void grid::SetHillGradient(double aGradient) { HillGradient = aGradient; }

void grid::SetHillRadius(int aRadius) { HillRadius = aRadius; }

void grid::SetNumberOfRows( int aNumber) { NumberOfRows = aNumber; }

void grid::SetNumberOfColumns( int aNumber) { NumberOfColumns = aNumber; }

void grid::SetColour(double red, double green, double blue )
{
    HighlightedTerrainSquareColour[0] = red;
    HighlightedTerrainSquareColour[1] = green;
    HighlightedTerrainSquareColour[2] = blue;
}
//-----Special Member Functions-----//
void grid::AddRow()
{
    std::vector<terrain_square> Row;
    Map.push_back(Row);

    Map.back().push_back(terrain_square(double (Map.size() ), 0.0 ) );
    if (Map.back().size() != Map[0].size() )
    {
        for(size_t i=0; i< Map[0].size(); i++ )
            Map.back().push_back(terrain_square( double (Map.size() ), (i+1) ) );
    }
}

void grid::AddColumn()
{
    for(size_t i=0; i < Map.size() ; i++)
        Map[i].push_back(terrain_square(double (i+1), double(Map[i].size() ) ) );
}

void grid::GenerateMap()
{
    int RowsAlreadyBuilt = 0;
    int ColumnsAlreadyBuilt = 0;
    int Offset = 1;

    if (!Map.empty() )
    {
        RowsAlreadyBuilt = int (Map.size() );
        ColumnsAlreadyBuilt = int (Map[0].size() );
        Offset = 0;
    }

    for(int i=RowsAlreadyBuilt; i < (NumberOfRows); i++)
        AddRow();


    for(int i=ColumnsAlreadyBuilt; i < (NumberOfColumns - Offset ); i++)
        AddColumn();
}

void grid::DeleteRow(int aNumber) {}

void grid::DeleteColumn(int aNumber) {}

void grid::SaveMap()
{
    //Thoughts: get grid size then loop through each cell and get Elevation and Actor (Print self maybe) check out save light and load light function
    //While looping through will need to get terrain type and actor information --- get information and set information might work but also need name of terrain
}

void grid::LoadMap()
{//this will be really fun to write but once it is written i can use this with a different ui that allows for
                      //the placing of figures on the map
}

void grid::Clear() { Map.clear(); }

void grid::CreateHill(double aElevation, int Row, int Column)
{
    double *Center = Map[Row - 1][Column - 1].GetActor()->GetCenter();

    for(int x = -HillRadius; x<=HillRadius; x++)
    {
        for(int y = -HillRadius; y<=HillRadius; y++)
        {
            if(((Row + x ) <= 0) || ( (Row + x) > int( Map.size() ) )|| ( (Column + y) <= 0)|| ( (Column + y) > int( Map[0].size() ) ) )
            {}
            else
            {
               Map[(Row + x) - 1][(Column + y) - 1].UpdateHex(aElevation, Center, HillGradient);
            }
        }
    }
}

void grid::ElevationTopography()
{
    std::vector<vtkSmartPointer<vtkElevationFilter>> ListOfElevationFilters;
    int ElevationRulerPosistion[2] = {0, 0};
    double HighPoint[3] = {0.0, 0.0, 0.0};
    double LowPoint[3] = {0.0, 0.0, 0.0 };

    for(int i=0; i < Map.size(); i++)
    {
        for(int j=0; j<Map[0].size(); j++)
        {
            if( Map[i][j].GetTerrainSquarePosition()[2] > HighPoint[2])
            {
                ElevationRulerPosistion[0] = i;
                ElevationRulerPosistion[1] = j;
                HighPoint[2] = Map[i][j].GetTerrainSquarePosition()[2];
            }
            if((i == 0)&&(j == 0))
            {
                LowPoint[2] = HighPoint[2];
            }

            if( Map[i][j].GetTerrainSquarePosition()[2] < LowPoint[2])
            {
                LowPoint[2] = Map[i][j].GetTerrainSquarePosition()[2];
            }
        }
    }

    for(int i=0; i < Map.size(); i++)
    {
        for(int j=0; j<Map[0].size(); j++)
        {
            vtkSmartPointer<vtkElevationFilter> ElevationFilter = vtkSmartPointer<vtkElevationFilter>::New();
            ElevationFilter->SetLowPoint(ElevationRulerPosistion[0], ElevationRulerPosistion[1], (LowPoint[2]) );
            ElevationFilter->SetHighPoint(ElevationRulerPosistion[0], ElevationRulerPosistion[1], (HighPoint[2]) );
            ElevationFilter->SetInputData( Map[i][j].GetActor()->GetMapper()->GetInput() );
            ElevationFilter->Update();
            Map[i][j].GetActor()->GetMapper()->SetInputConnection( ElevationFilter->GetOutputPort() );
            ListOfElevationFilters.push_back(ElevationFilter);
        }
    }
}

void grid::RemoveElevationTopography()
{
    for(int i=0; i < Map.size(); i++)
    {
        for(int j=0; j<Map[0].size(); j++)
        {
           Map[i][j].ReEstablishPipeline();
        }
    }
}

void grid::HighlightTerrainSquare(int Row, int Column)
{
    if(StartUpHighlighter == true)
    {
        Map[LastRow][LastColumn].GetActor()->GetProperty()->EdgeVisibilityOff();
        Map[LastRow][LastColumn].GetActor()->GetProperty()->SetColor(HighlightedTerrainSquareColour[0], HighlightedTerrainSquareColour[1], HighlightedTerrainSquareColour[2]);
    }

    Map[Row][Column].GetActor()->GetProperty()->EdgeVisibilityOn();
    Map[Row][Column].GetActor()->GetProperty()->SetEdgeColor(1.0, 0.0, 0.0);
    Map[Row][Column].GetActor()->GetProperty()->GetColor(HighlightedTerrainSquareColour);
    Map[Row][Column].GetActor()->GetProperty()->SetColor(1.0, 1.0, 0.0);
    StartUpHighlighter = true;
    LastRow = Row;
    LastColumn = Column;
}
