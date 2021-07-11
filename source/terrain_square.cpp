#include "terrain_square.h"
//-----Constructor-----//
terrain_square::terrain_square(double X, double Y)
{
    TextureName = "No Texture";
    X--;
    Points->Initialize();
    Points->InsertNextPoint(  X,         Y,        0.0);
    Points->InsertNextPoint( (X + 1.0),  Y,        0.0);
    Points->InsertNextPoint( (X + 1.0), (Y + 1.0), 0.0);
    Points->InsertNextPoint(  X,        (Y + 1.0), 0.0);

    SetTriangles();

    polydata->SetPolys(TriangleArray);
    polydata->SetPoints(Points);

    planeMapper->SetInputData(polydata);
    Actor->SetMapper(planeMapper);
    Actor->GetProperty()->EdgeVisibilityOn();
    Actor->GetProperty()->SetColor(0.0, 0.7, 0.0);

   terrain_type Terrain;
   TerrainSquarePosition[0] = Actor->GetCenter()[0];
   TerrainSquarePosition[1] = Actor->GetCenter()[1];
   TerrainSquarePosition[2] = Actor->GetCenter()[2];

}
//-----Destructor-----//
terrain_square::~terrain_square(){}
//-----Get Functions-----//
vtkSmartPointer<vtkActor> terrain_square::GetActor() { return (Actor); }

vtkSmartPointer<vtkPolyDataMapper> terrain_square::GetMapper() { return (planeMapper); }

vtkSmartPointer<vtkPolyData> terrain_square::GetPolyData() { return (polydata); }

vtkSmartPointer<vtkTexture> terrain_square::GetTexture() { return (texture); }

double* terrain_square::GetTerrainSquarePosition() { return (TerrainSquarePosition); }

terrain_type& terrain_square::GetTerrainType() { return (TerrainType); }
//-----Set Functions-----//
void terrain_square::SetTerrainType(const std::string &aTerrain)
{
    TerrainType.LoadTerrainImage(aTerrain);
    TerrainType.UpdateTerrainTypeActor(TerrainSquarePosition);
}

void terrain_square::SetTriangles()
{
    vtkSmartPointer<vtkTriangle> triangle_Hex_8 = vtkSmartPointer<vtkTriangle>::New();
    triangle_Hex_8->GetPointIds()->SetId ( 0, vtkIdType (0) );
    triangle_Hex_8->GetPointIds()->SetId ( 1, vtkIdType (1) );
    triangle_Hex_8->GetPointIds()->SetId ( 2, vtkIdType (2) );
    TriangleArray->InsertNextCell(triangle_Hex_8);

    vtkSmartPointer<vtkTriangle> triangle_Hex_9 = vtkSmartPointer<vtkTriangle>::New();
    triangle_Hex_9->GetPointIds()->SetId ( 0, vtkIdType (0) );
    triangle_Hex_9->GetPointIds()->SetId ( 1, vtkIdType (3) );
    triangle_Hex_9->GetPointIds()->SetId ( 2, vtkIdType (2) );
    TriangleArray->InsertNextCell(triangle_Hex_9);
}

void terrain_square::SetTextureName(const std::string &aTexture)
{
    TextureName = aTexture;
    SetTexture();
}

void terrain_square::SetTexture()
{
    if(TextureName.compare("No Texture") == 0)
        return;

    vtkSmartPointer<vtkJPEGReader> jPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
    jPEGReader->SetFileName ( TextureName.c_str() );

    texture->SetInputConnection(jPEGReader->GetOutputPort() );

    vtkSmartPointer<vtkTextureMapToPlane> texturePlane = vtkSmartPointer<vtkTextureMapToPlane>::New();
    texturePlane->SetInputData(polydata);

    planeMapper->SetInputConnection(texturePlane->GetOutputPort() );
    texture->Update();
    Actor->SetTexture(texture);
}

//------Special Member Functions-----//
void terrain_square::UpdateHex(double aElevation, double* aCenter, double HillGradient)
{
    std::vector< std::vector<double> > Data;
    for(vtkIdType i=0; i<4; i++)
    {
        std::vector<double> oldPoints;
        Data.push_back(oldPoints);

        double *Point = {Points->GetPoint(i)};
        Point[2] = (aElevation * pow(HillGradient, (sqrt( pow( (Point[0] - aCenter[0]) , 2) + pow( (Point[1] - aCenter[1]), 2) ) ) ) );
        Data[i].push_back(Point[0]);
        Data[i].push_back(Point[1]);
        Data[i].push_back(Point[2]);
    }

    Points->Initialize();
    Points->InsertNextPoint(Data[0][0], Data[0][1], Data[0][2]);
    Points->InsertNextPoint(Data[1][0], Data[1][1], Data[1][2]);
    Points->InsertNextPoint(Data[2][0], Data[2][1], Data[2][2]);
    Points->InsertNextPoint(Data[3][0], Data[3][1], Data[3][2]);

    SetTriangles();

    polydata->SetPolys(TriangleArray);
    polydata->SetPoints(Points);

    TerrainSquarePosition[2] = Actor->GetCenter()[2];
    TerrainType.UpdateTerrainTypeActor(TerrainSquarePosition);
}

void terrain_square::ReEstablishPipeline()
{
    planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    polydata->SetPolys(TriangleArray);
    polydata->SetPoints(Points);
    planeMapper->SetInputData(polydata);
    SetTexture();
    Actor->SetMapper(planeMapper);
}

void terrain_square::RemoveTexure()
{
    Actor->SetTexture(nullptr);
    Actor->GetProperty()->SetColor( Actor->GetProperty()->GetColor() );
    texture = vtkSmartPointer<vtkTexture>::New();
}


