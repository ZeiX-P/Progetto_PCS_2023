#include "empty_class.hpp"
#define MAX 10000
int main()
{

  ProjectLibrary::Mesh m("./Cell0Ds.csv", "./Cell1Ds.csv","./Cell2Ds.csv");

  ProjectLibrary::TriangularMesh mesh = m.mesh;

  m.ImportCell0Ds(mesh);
  m.ImportCell1Ds(mesh);
  m.ImportCell2Ds(mesh);

  ProjectLibrary::Sort_Area_Triangles s(mesh);
  ProjectLibrary::Algorithm algo(mesh);

  int k = 100;

  algo.raff(s, k);

  m.export_data_coord("coordinate.csv", mesh);
  m.export_data_vertices("vertices.csv", mesh);

  return 0;
}
