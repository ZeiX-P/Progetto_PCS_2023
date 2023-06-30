#include "empty_class.hpp"

namespace ProjectLibrary
{

void Mesh::ImportCell0Ds(TriangularMesh& mesh)
{

  ifstream file;
  //file.open("./Cell0Ds.csv");
  file.open(file1);


  list<string> listLines;
  string line;

  while (getline(file, line))

        listLines.push_back(line);


  listLines.pop_front();
  file.close();



  mesh.NumberCell0D = listLines.size();



  mesh.Cell0DId.reserve(mesh.NumberCell0D);
  mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

  for (const string& line : listLines)
  {
    istringstream converter(line);

    unsigned int id;
    unsigned int marker;
    Vector2d coord;

    converter >>  id >> marker >> coord(0) >> coord(1);

    mesh.Cell0DId.push_back(id);
    mesh.Cell0DCoordinates.push_back(coord);

    if( marker != 0)
    {
      if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
        mesh.Cell0DMarkers.insert({marker, {id}});
      else
        mesh.Cell0DMarkers[marker].push_back(id);
    }

  }
  file.close();

}
// ***************************************************************************
void Mesh::ImportCell1Ds(TriangularMesh& mesh)
{

  ifstream file;
  //file.open("./Cell1Ds.csv");
  file.open(file2);



  list<string> listLines;
  string line;

  while (getline(file, line))

    listLines.push_back(line);

  listLines.pop_front();



  mesh.NumberCell1D = listLines.size();

  mesh.Cell1DId.reserve(mesh.NumberCell1D);
  mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

  for (const string& line : listLines)
  {
    istringstream converter(line);

    unsigned int id;
    unsigned int marker;
    Vector2i vertices;

    converter >>  id >> marker >> vertices(0) >> vertices(1);

    mesh.Cell1DId.push_back(id);
    mesh.Cell1DVertices.push_back(vertices);

    if( marker != 0)
    {
      if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
        mesh.Cell1DMarkers.insert({marker, {id}});
      else
        mesh.Cell1DMarkers[marker].push_back(id);
    }
  }

  file.close();
}
// ***************************************************************************
void Mesh::ImportCell2Ds(TriangularMesh& mesh){


    ifstream file;
    //file.open("./Cell2Ds.csv");
    file.open(file3);


    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();


    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        array<unsigned int, 3> vertices;
        array<unsigned int, 3> edges;

        converter >>  id;
        for(unsigned int i = 0; i < 3; i++)
            converter >> vertices[i];
        for(unsigned int i = 0; i < 3; i++)
            converter >> edges[i];

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);

        array<unsigned int,6> result;
        for(int j=0;j<3;j++){

            result[j] = vertices[j];
        }
        for(int z=3;z<6;z++){
            result[z] = edges[z-3];
        }

        mesh.Triangles.push_back(result);
        file.close();

        }
    }
 bool Algorithm::check_point_in(TriangularMesh &mesh, double x, double y){
    bool bool1 = false;
    for(int i=0;i<mesh.Cell0DCoordinates.size();i++){
        Vector2d coord = mesh.Cell0DCoordinates[i];
        double X = coord(0);
        double Y = coord(1);
        if(X==x && Y==y){
            bool1 = true;
            return true;
        }

    }
    if(bool1 == false){
        return false;
    }
}
int Algorithm::add_mid_point_mesh(int v1, int v2){

    double x1 = data.Cell0DCoordinates[v1][0];
    double y1 = data.Cell0DCoordinates[v1][1];

    double x2 = data.Cell0DCoordinates[v2][0];
    double y2 = data.Cell0DCoordinates[v2][1];

    double x = abs(x1+x2)/2;
    double y = abs(y1+y2)/2;
    if(Algorithm::check_point_in(data, x, y)==true){
        for(int i=0;i<=data.Cell0DId.size();i++){
            int id = data.Cell0DId[i];
            double X = data.Cell0DCoordinates[id][0];
            double Y = data.Cell0DCoordinates[id][1];
            //cout << id << " " << X << " " << Y << endl;
            if(x==X && y==Y){

                return id;
            }
        }

    }
    else if(Algorithm::check_point_in(data, x, y)==false){

        Vector2d coord;
        coord(0) = x;
        coord(1) = y;

        int id = data.Cell0DId[data.Cell0DId.size()-1]+1;
        data.Cell0DId.push_back(id);
        data.Cell0DCoordinates.push_back(coord);

        return id;
        }

}
bool Algorithm::check_edge_in(int v1, int v2){
    for(int i = 0;i<data.Cell1DVertices.size();i++){
        int V1 = data.Cell1DVertices[i][0];
        int V2 = data.Cell1DVertices[i][1];
        if((V1==v1 && V2==v2) || (V2==v1 && V1==v2)){
            return true;
        }

    }

}
bool Algorithm::Add_Edges(int v1, int v2){
    if(check_edge_in(v1,v2)==false){
        int id1 = data.Cell1DId.size()+1;
        data.Cell1DId.push_back(id1);
        //cout <<data.Cell1DId[id1-1] <<endl;
        Vector2i vertices;
        vertices[0] = v1;
        vertices[1] = v2;
        data.Cell1DVertices.push_back(vertices);
        return true;
    }
    else
        return false;


}
int Algorithm::AddTriangle_0(vector <int> h){

    int v1 = h[0];
    int v2 = h[1];
    int opposite_vertex = h[2];

    int mid_point_index = Algorithm::add_mid_point_mesh(v1, v2);


    int id2 = data.Cell2DVertices.size()+1;
    data.Cell2DId.push_back(id2);

    array<unsigned int, 3> vertices;

    vertices[0] = v1;
    vertices[1] = opposite_vertex;
    vertices[2] = mid_point_index;

    array<unsigned int, 3> edges;

    bool bool1 = Algorithm::Add_Edges(v1, mid_point_index);

    //controlla se il lato è gia sttap aggiunto
    if(bool1==true){
        int y = data.Cell1DId.size();

        edges[0] = data.Cell1DId[y-1];
    }
    else{
        //else se edge è gia nel database
        for(int i = 0;i<data.Cell1DVertices.size();i++){
            int V1 = data.Cell1DVertices[i][0];
            int V2 = data.Cell1DVertices[i][1];
            if((V1==v1 && V2==mid_point_index) || (V1==mid_point_index && V2==v1)){
                edges[0] = data.Cell1DId[i];
            }
        }
    }

    bool bool2 = Algorithm::Add_Edges(opposite_vertex, mid_point_index);
    if(bool2==true){
        int y = data.Cell1DId.size();
        edges[1] = data.Cell1DId[y-1];
    }
    else{
        for(int i = 0;i<data.Cell1DVertices.size();i++){
            int V1 = data.Cell1DVertices[i][0];
            int V2 = data.Cell1DVertices[i][1];
            if((V1==opposite_vertex && V2==mid_point_index) || (V1==mid_point_index && V2==opposite_vertex)){
                edges[1] = data.Cell1DId[i];
            }
        }
    }

    bool bool3 = Algorithm::Add_Edges(v1, opposite_vertex);
    if(bool3==true){
        int y = data.Cell1DId.size();
        edges[2] = data.Cell1DId[y-1];
    }
    else{
        for(int i = 0;i<data.Cell1DVertices.size();i++){
            int V1 = data.Cell1DVertices[i][0];
            int V2 = data.Cell1DVertices[i][1];
            if((V1==v1 && V2==opposite_vertex) || (V1==opposite_vertex && V2==v1)){
                edges[2] = data.Cell1DId[i];
            }
        }
    }


    data.Cell2DVertices.push_back(vertices);
    data.Cell2DEdges.push_back(edges);


    return mid_point_index;


}
void Algorithm::AddTriangle_1(vector <int> h){

    int v1 = h[0];
    int v2 = h[1];

    int mid_point_index = Algorithm::add_mid_point_mesh(v1, v2);
    int opposite_vertex = h[2];

    int id2 = data.Cell2DVertices.size()+1;
    data.Cell2DId.push_back(id2);

    array<unsigned int, 3> vertices;

    vertices[0] = v2;
    vertices[1] = opposite_vertex;
    vertices[2] = mid_point_index;

    array<unsigned int, 3> edges;

    bool bool1 = Algorithm::Add_Edges(v2, mid_point_index);
    if(bool1==true){
        edges[0] = data.Cell1DId[data.Cell1DId.size()-1];
    }
    else{
        for(int i = 0;i<data.Cell1DVertices.size();i++){
            int V1 = data.Cell1DVertices[i][0];
            int V2 = data.Cell1DVertices[i][1];
            if((V1==v2 && V2==mid_point_index) || (V1==mid_point_index && V2==v2)){
                edges[0] = data.Cell1DId[i];
            }
        }
    }
    bool bool2 = Algorithm::Add_Edges(opposite_vertex, mid_point_index);
    if(bool2==true){
        edges[1] = data.Cell1DId[data.Cell1DId.size()-1];
    }
    else{
        for(int i = 0;i<data.Cell1DVertices.size();i++){
            int V1 = data.Cell1DVertices[i][0];
            int V2 = data.Cell1DVertices[i][1];
            if((V1==opposite_vertex && V2==mid_point_index) || (V1==mid_point_index && V2==opposite_vertex)){
                edges[1] = data.Cell1DId[i];
            }
        }
    }
    bool bool3 = Algorithm::Add_Edges(v2, opposite_vertex);
    if(bool3==true){
        edges[2] = data.Cell1DId[data.Cell1DId.size()-1];
    }
    else{
        for(int i = 0;i<data.Cell1DVertices.size();i++){
            int V1 = data.Cell1DVertices[i][0];
            int V2 = data.Cell1DVertices[i][1];
            if((V1==v2 && V2==opposite_vertex) || (V1==opposite_vertex && V2==v2)){
                edges[2] = data.Cell1DId[i];
            }
        }
    }

    data.Cell2DVertices.push_back(vertices);
    data.Cell2DEdges.push_back(edges);
    }



//traingle_index è  indice del vecchio trinagolo, v1 e v2 sono i vertici del lato, restituisce l indice
int Algorithm::find_triangle_sharing_late_to_new_triangle(int triangle_index, int v1, int v2){

    for(int c=0; c<data.Cell2DVertices.size(); c++){
        if(c==triangle_index){
            continue;
        }
        array<unsigned int, 3> vertices = data.Cell2DVertices[c];
        if(v1==vertices[0] && v2==vertices[1]){
               return c;
        }
        if(v1==vertices[1] && v2==vertices[2]){
               return c;
        }
        if(v1==vertices[1] && v2==vertices[0]){
               return c;
        }
        if(v1==vertices[2] && v2==vertices[1]){
               return c;
        }
        if(v1==vertices[0] && v2==vertices[2]){
               return c;
        }
        if(v1==vertices[2] && v2==vertices[0]){
               return c;
        }
    }


}

bool Algorithm::check_triangle_ammissibility(int mid_point_index){

    //int mid_point = v[2];
    Vector2d coord = data.Cell0DCoordinates[mid_point_index];
    double x = coord(0);
    double y = coord(1);
    if(x==0 && y!=0){
        return true;
    }
    else if(x==1 && y!=0){
        return true;
    }
    else if(x!=0 && y==0){
        return true;
    }
    else if(x!=0 && y==1){
        return true;
    }
    else{
        return false;
    }


}

}
