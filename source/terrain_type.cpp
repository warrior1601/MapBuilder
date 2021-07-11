#include "terrain_type.h"
#include <vtkDataObject.h>
#include <vtkDataReader.h>

//-----Constructor-----//
terrain_type::terrain_type()
{
    Name = "No Terrain Type";

    ActorOrientation[0] = 0.0;
    ActorOrientation[1] = 0.0;
    ActorOrientation[2] = 0.0;

    ActorOffset[0] = 0.0;
    ActorOffset[1] = 0.0;
    ActorOffset[2] = 0.0;

    ActorScale[0] = 0.0;
    ActorScale[1] = 0.0;
    ActorScale[2] = 0.0;
}

terrain_type::terrain_type(std::string aName)
{
    Name = "No Terrain Type";

    ActorOrientation[0] = 0.0;
    ActorOrientation[1] = 0.0;
    ActorOrientation[2] = 0.0;

    ActorOffset[0] = 0.0;
    ActorOffset[1] = 0.0;
    ActorOffset[2] = 0.0;

    ActorScale[0] = 0.0;
    ActorScale[1] = 0.0;
    ActorScale[2] = 0.0;
}
//-----Destructor-----//
terrain_type::~terrain_type() {}
//-----Set Functions-----//
void terrain_type::SetName(std::string aName)
{
    Name = aName;
    //Sets default values for offset and Scaling
    if(Name.compare("Grass") == 0)
    {
        ActorOffset[0] = 0.017;
        ActorOffset[1] = 0.007;
        ActorOffset[2] = 0.090;

        ActorScale[0] = 0.042;
        ActorScale[1] = 0.042;
        ActorScale[2] = 0.042;
        return;
    }

    if(Name.compare("Vine Tree") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.174;
        ActorScale[1] = 0.216;
        ActorScale[2] = 0.300;
        return;
    }
    if(Name.compare("Corner Wall") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
    if(Name.compare("Wall Straight") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
    if(Name.compare("Stone Floor") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
    if(Name.compare("Pillar Square") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
    if(Name.compare("Wall Arch") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
    if(Name.compare("Wall Curved") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
    if(Name.compare("Well on Tile") == 0)
    {
        ActorOffset[0] = 0.0;
        ActorOffset[1] = 0.0;
        ActorOffset[2] = 0.0;

        ActorScale[0] = 0.02;
        ActorScale[1] = 0.02;
        ActorScale[2] = 0.02;
        return;
    }
}

void terrain_type::SetActorOffset(double *aOffset)
{
    ActorOffset[0] = aOffset[0];
    ActorOffset[1] = aOffset[1];
    ActorOffset[2] = aOffset[2];
}

void terrain_type::SetActorOrientation(double *aOrientation)
{
    ActorOrientation[0] = aOrientation[0];
    ActorOrientation[1] = aOrientation[1];
    ActorOrientation[2] = aOrientation[2];
}

void terrain_type::SetActorScale(double *aScale)
{
    ActorScale[0] = aScale[0];
    ActorScale[1] = aScale[1];
    ActorScale[2] = aScale[2];
}

//-----Get Functions-----//
std::string terrain_type::GetName(){ return (Name); }

vtkSmartPointer<vtkActor> terrain_type::GetActor() { return (TerrainActor); }

vtkSmartPointer<vtkSTLReader> terrain_type::GetSTL() { return (TerrainSTLReader); }

double* terrain_type::GetActorOffset() { return (ActorOffset); }

double* terrain_type::GetActorOrientation() { return (ActorOrientation); }

double* terrain_type::GetActorScale() { return (ActorScale); }
//------Special Member Functions-----//
void terrain_type::ChangeTerrainTypeActor(vtkSmartPointer<vtkSTLReader> aSTLReader)
{
    vtkSmartPointer<vtkActor> NewActor = vtkSmartPointer<vtkActor>::New();

    Mapper->SetInputConnection(aSTLReader->GetOutputPort() );
    aSTLReader->Update();
    NewActor->SetMapper(Mapper);
    NewActor->GetProperty()->EdgeVisibilityOff();
    NewActor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() );
    NewActor->SetOrientation(ActorOrientation);

    TerrainActor = NewActor;
}

void terrain_type::LoadTerrainImage(std::string aName)
{
    if(aName.compare("No Terrain Type") != 0 ) //Should never reach this point if No Terrian Type is selected
    {
        std::string FilePath = "../../terrain_types/" + aName + ".stl";
        std::ifstream myFile(FilePath);
        SetName(aName);
        if(myFile.is_open() )
        {
            TerrainSTLReader = vtkSmartPointer<vtkSTLReader>::New();
            TerrainSTLReader->SetFileName(FilePath.data() );
            Mapper->SetInputConnection(TerrainSTLReader->GetOutputPort() );
            TerrainSTLReader->Update();
            TerrainActor->SetMapper(Mapper);
            TerrainActor->GetProperty()->EdgeVisibilityOff();
            TerrainActor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() );
        }
    }
}

void terrain_type::UpdateTerrainTypeActor(double *aTerrainSquarePosition)
{
    if(Name.compare("No Terrain Type") == 0)
        return;
    else
    {
        double TerrianOffset[] = { (aTerrainSquarePosition[0] + ActorOffset[0]), (aTerrainSquarePosition[1] + ActorOffset[1]), ((aTerrainSquarePosition[2]) - ActorOffset[2]) };
        TerrainActor->SetPosition(TerrianOffset[0], TerrianOffset[1], TerrianOffset[2]);
        TerrainActor->SetScale(ActorScale[0], ActorScale[1], ActorScale[2]);
    }
}


