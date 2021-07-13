#ifndef TERRAIN_TYPE_H
#define TERRAIN_TYPE_H
//VTK header files
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkJPEGReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>
//C++ header files
#include <string>
class terrain_type
{
public:
//-----Constructor-----//
    terrain_type();
    terrain_type(std::string aName);
//-----Destructor-----//
    ~terrain_type();
//-----Set Functions-----//
    void SetName(std::string aName);
    void SetActorOffset(double *aOffset);
    void SetActorOrientation(double *aOrientation);
    void SetActorScale(double *aScale);
//-----Get Functions-----//
    std::string GetName();
    vtkSmartPointer<vtkActor> GetActor();
    vtkSmartPointer<vtkSTLReader> GetSTL();
    double* GetActorOffset();
    double* GetActorOrientation();
    double* GetActorScale();
//------Special Member Functions-----//
    void ChangeTerrainTypeActor(vtkSmartPointer<vtkSTLReader> aSTLReader);
    void LoadTerrainImage(std::string aName); //This is called only the first time and stl it loaded
    void UpdateTerrainTypeActor(double *aTerrainSquarePosition);
private:
    std::string Name;

    double ActorOrientation[3];
    double ActorOffset[3];
    double ActorScale[3];

    vtkSmartPointer<vtkDataSetMapper> Mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> TerrainActor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkSTLReader> TerrainSTLReader = vtkSmartPointer<vtkSTLReader>::New();
};

#endif // TERRAIN_TYPE_H
