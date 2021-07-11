#ifndef GRID_H
#define GRID_H
//VTK Header files
#include <vtkElevationFilter.h>
//C++ Header files
#include <vector>
//Project Files
#include "terrain_square.h"

class grid
{
public:
//-----Constructor-----//
    grid();
//-----Destructor-----//
    ~grid();
//-----Get Functions-----//
    int GetCreateHillStatus();
    double GetHillGradient();
    int GetHillRaduis();
    int GetNumberOfRows();
    int GetNumberOfColumns();
    std::vector< std::vector<terrain_square> >& GetMap(void);
//-----Set Functions-----//
    void SetCreateHill(int aQTCheckedStatus);
    void SetHillGradient(double aGradient);
    void SetHillRadius(int aRadius);
    void SetNumberOfRows(int aNumber);
    void SetNumberOfColumns(int aNumber);
    void SetColour(double red, double green, double blue );
//-----Special Member Functions-----//
    void AddRow();
    void AddColumn();
    void GenerateMap();
    void DeleteRow(int aNumber);
    void DeleteColumn(int aNumber);
    void Clear();
    void CreateHill(double aElevation, int Row, int Column);
    void ElevationTopography();
    void HighlightTerrainSquare(int Row, int Column);
    void RemoveElevationTopography();
    void SaveMap();
    void LoadMap();

private:
    int NumberOfRows = 0;
    int NumberOfColumns = 0;
    int HillRadius = 0;
    double HillGradient = 0.95;
    int CreateHillStatus = 0;
    int LastRow = 0;
    int LastColumn = 0;
    double HighlightedTerrainSquareColour[3] = {0.0, 0.0, 0.0};
    bool StartUpHighlighter = false;

    std::vector< std::vector<terrain_square> > Map;
};

#endif // GRID_H
