#ifndef TERRAIN_SQUARE_H
#define TERRAIN_SQUARE_H
// Header files from vtk
#include <vtkImageData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkTriangle.h>
//C++ Header Files
#include <cmath>
// Project Header files
#include "terrain_type.h"
class terrain_square
{
public:
//-----Consturctor-----//
    terrain_square(double X, double Y);
//-----Destructor-----//
    ~terrain_square();
//-----Get Functions-----//
    vtkSmartPointer<vtkActor> GetActor();
    vtkSmartPointer<vtkPolyDataMapper> GetMapper();
    vtkSmartPointer<vtkPolyData> GetPolyData();
    vtkSmartPointer<vtkTexture> GetTexture();
    double* GetTerrainSquarePosition();
    terrain_type& GetTerrainType();
//-----Set Functions-----//
    void SetTerrainType(const std::string &aTerrain);
    void SetTexture();
    void SetTextureName(const std::string &aTexture);
//------Special Member Functions-----//
    void ReEstablishPipeline();
    void RemoveTexure();
    void UpdateHex(double aElevation, double* aCenter, double HillGradient);

private:
    void SetTriangles();
    double TerrainSquarePosition[3];

    vtkSmartPointer<vtkPolyDataMapper> planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> Points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkCellArray> TriangleArray = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();

    terrain_type TerrainType; //Will limit to only one type of Terrain for now
    std::string Features; //This may be come a list of features
    std::string TextureName;
};

#endif // TERRAIN_SQUARE_H
