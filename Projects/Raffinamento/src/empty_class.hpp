#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "map"
#include <cstdlib>
#include <vector>
#include<cmath>
#include <cstdlib>
#define MAX 10000
#include <fstream>

//using namespace ofstream;
using namespace std;
using namespace Eigen;

namespace ProjectLibrary
{
struct index_value{

    double value;
    int i;
};
struct TriangularMesh
{
    unsigned int NumberCell0D = 0; ///< number of Cell0D
    std::vector<unsigned int> Cell0DId = {}; ///< Cell0D id, size 1 x NumberCell0D
    std::vector<Vector2d> Cell0DCoordinates = {}; ///< Cell0D coordinates, size 2 x NumberCell0D (x,y)
    std::map<unsigned int, list<unsigned int>> Cell0DMarkers = {}; ///< Cell0D markers, size 1 x NumberCell0D (marker)

    unsigned int NumberCell1D = 0; ///< number of Cell1D
    std::vector<unsigned int> Cell1DId = {}; ///< Cell1D id, size 1 x NumberCell1D
    std::vector<Vector2i> Cell1DVertices = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
    std::map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; ///< Cell1D propertoes, size 1 x NumberCell1D (marker)

    unsigned int NumberCell2D = 0; ///< number of Cell2D
    std::vector<unsigned int> Cell2DId = {}; ///< Cell2D id, size 1 x NumberCell2D
    std::vector<array<unsigned int, 3>> Cell2DVertices = {}; ///< Cell2D Vertices indices, size 1 x NumberCell2DVertices[NumberCell2D]
    std::vector<array<unsigned int, 3>> Cell2DEdges = {}; ///< Cell2D Cell1D indices, size 1 x NumberCell2DEdges[NumberCell2D]


    std::vector<array<unsigned int,6>> Triangles = {};
    struct index_value tuple[MAX];
};


class Mesh{
private:


public:
    string file1;
    string file2;
    string file3;

    TriangularMesh mesh;

    Mesh(string f1, string f2, string f3){
        file1 = f1;
        file2 = f2;
        file3 = f3;
    }

    void ImportCell0Ds(TriangularMesh &mesh);
    void ImportCell1Ds(TriangularMesh &mesh);
    void ImportCell2Ds(TriangularMesh &mesh);

    void export_data_coord(string file, TriangularMesh &mesh){

        ofstream outdata; // outdata is like cin
         // loop index
        //string outputFileName = "./result.txt";

        outdata.open(file); // opens the file
            if( !outdata ){
                // file couldn't be opened
                cerr << "Error: file could not be opened" << endl;
                exit(1);
            }

        outdata << "Id Marker X Y" << "\n";

        for(int i=0; i<mesh.Cell0DCoordinates.size(); i++){
            outdata << i  <<" "<< mesh.Cell0DCoordinates[i][0] <<" "<< mesh.Cell0DCoordinates[i][1] << "\n";

        }
        outdata.close();


        }


    void export_data_vertices(string file, TriangularMesh &mesh){

        ofstream outdata; // outdata is like cin
         // loop index
        //string outputFileName = "./result.txt";

        outdata.open(file); // opens the file
            if( !outdata ){
                // file couldn't be opened
                cerr << "Error: file could not be opened" << endl;
                exit(1);
            }

        outdata << "Id Vertices" << "\n";

        for(int i=0; i<mesh.Cell2DVertices.size(); i++){
            outdata << i  <<" "<< mesh.Cell2DVertices[i][0] <<" "<< mesh.Cell2DVertices[i][1] <<" " << mesh.Cell2DVertices[i][2] << "\n";

        }
        outdata.close();


        }

};


class Sort_Area_Triangles{
private:

    double calculate_area(int j){

        double area;

        int v1 = data.Cell2DVertices[j][0];
        int v2 = data.Cell2DVertices[j][1];
        int v3 = data.Cell2DVertices[j][2];


        area = abs((data.Cell0DCoordinates[v1][0]*data.Cell0DCoordinates[v2][1]+data.Cell0DCoordinates[v2][0]*data.Cell0DCoordinates[v3][1]
                +data.Cell0DCoordinates[v1][0]*data.Cell0DCoordinates[v2][1]-data.Cell0DCoordinates[v1][0]*data.Cell0DCoordinates[v2][1]
                -data.Cell0DCoordinates[v1][0]*data.Cell0DCoordinates[v2][1]-data.Cell0DCoordinates[v1][0]*data.Cell0DCoordinates[v2][1]))/2;


        return area;

    }
    // Print the array
    void printArray(int arr[], int size) {
      for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
      cout << endl;
    }

public:
    TriangularMesh  &data;

    Sort_Area_Triangles(TriangularMesh & data_)
         :    data(data_) {}


    vector<double> calculateAreaTriangles(){
        vector<double> area;

        for(int j=0;j<data.Cell2DVertices.size(); j++){
                double a = calculate_area(j);
                area.push_back(a);
        }
    return area;
    }


    void array_pointers_area(double * i[], vector<double>& a){

        for(int j=0;j<a.size();j++){

           i[j] = &a[j];

        }
    }   

    void print_index_area(double *i[],vector<double>& a){
        size_t sizeOfArray = sizeof(i)/sizeof(i[0]);
        for(int j=0;j<a.size();j++){
            cout << "Indice triangolo: " << j << "  " << "Area triangolo: " << *i[j]<< endl;
        }
    }

    void MergeSortedIntervals(vector<double>& v, int s, int m, int e) {

        // temp is used to temporary store the vector obtained by merging
        // elements from [s to m] and [m+1 to e] in v
        vector<double> temp;

        int i, j;
        i = s;
        j = m + 1;

        while (i <= m && j <= e) {

            if (v[i] <= v[j]) {
                temp.push_back(v[i]);
                ++i;
            }
            else {
                temp.push_back(v[j]);
                ++j;
            }

        }

        while (i <= m) {
            temp.push_back(v[i]);
            ++i;
        }

        while (j <= e) {
            temp.push_back(v[j]);
            ++j;
        }

        for (int i = s; i <= e; ++i)
            v[i] = temp[i - s];

    }

    // the MergeSort function
    // Sorts the array in the range [s to e] in v using
    // merge sort algorithm
    void MergeSort(vector<double>& v, int s, int e) {
        if (s < e) {
            int m = (s + e) / 2;
            MergeSort(v, s, m);
            MergeSort(v, m + 1, e);
            MergeSortedIntervals(v, s, m, e);
        }
    }

    int array_of_tuples_area(index_value area[]){

        int n = data.Cell2DVertices.size();
        int i = 0;
        for(int j=0;j<n;j++){

            struct index_value a;
            a.i = j;

            a.value = Sort_Area_Triangles::calculate_area(j);

            area[j] = a;
            i = i+1;
        }
        return i;

    }

    void merge(struct index_value s[], int const left, int const mid,
                                    int const right){

        auto const subArrayOne = mid - left + 1;
        auto const subArrayTwo = right - mid;

        // Create temp arrays
        auto *leftArray = new struct index_value[subArrayOne];
        auto *rightArray = new struct index_value[subArrayTwo];

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (int i = 0; i < subArrayOne; i++)
            leftArray[i] = s[left + i];
            //leftArray[i].i = s[left + i].i;
        for (int j = 0; j < subArrayTwo; j++)
            rightArray[j]= s[mid + 1 + j];
            //rightArray[j].i = s[mid + 1 + j].i;

        auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
        int indexOfMergedArray = left; // Initial index of merged array

        // Merge the temp arrays back into array[left..right]
        while (indexOfSubArrayOne < subArrayOne
               && indexOfSubArrayTwo < subArrayTwo) {


            if (leftArray[indexOfSubArrayOne].value
                <= rightArray[indexOfSubArrayTwo].value) {
                s[indexOfMergedArray] = leftArray[indexOfSubArrayOne];

                indexOfSubArrayOne++;
            }
            else {
                s[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
        // Copy the remaining elements of
        // left[], if there are any
        while (indexOfSubArrayOne < subArrayOne) {
            s[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
        // Copy the remaining elements of
        // right[], if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            s[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }
    void MergeSortAlgorithm(struct index_value s[], int const begin, int const end){

        if (begin < end){
                 // Returns recursively
            auto mid = begin + (end - begin) / 2;
            MergeSortAlgorithm(s, begin, mid);
            MergeSortAlgorithm(s, mid + 1, end);
            merge(s, begin, mid, end);
        }


    }

    void print_array_tuples(struct index_value a[]){
        int n = data.Cell0DId.size();
        cout << n;
        for(int j=0;j<n;j++){

            cout << "Index: " << a[j].i << "::: Area: "<< a[j].value << endl;
        }

    }



};

class Algorithm{

private:

    double length_side(int v1, int v2){
        //array<unsigned, 3> vertices = data.Cell2DVertices[c];

        double x1 = data.Cell0DCoordinates[v1][0];
        double y1 = data.Cell0DCoordinates[v1][1];
        double x2 = data.Cell0DCoordinates[v2][0];
        double y2 = data.Cell0DCoordinates[v2][1];

        float x = x1-x2;
        float y = y1-y2;

        float a = pow(x,2);
        float b =  pow(y,2);

        double lenght = sqrt(a + b);

        return lenght;

    }

    //trova lato triangolo con lato piu lungo e vertice opposto, return vettore={v,v2, v_opposto}
    vector<int> longer_side_and_opposite_vertex(int c){

        array<unsigned int, 3> vertices = data.Cell2DVertices[c];
        double longer_side = 0;
        vector<int> a = {0, 0, 0};

        int v0 = vertices[0];
        int v1 = vertices[1];
        int v2 = vertices[2];

        double l1  = Algorithm::length_side(v0, v1);
        double l2  = Algorithm::length_side(v1, v2);
        double l3  = Algorithm::length_side(v0, v2);

        if (l1 >= l2 && l1 >= l3){

            //longer_side = l1;
            a.at(0) = v0;
            a.at(1) = v1;
        }
        if(l2 >= l1 && l2 >= l3){

            //longer_side = l2;
            a.at(0) = v1;
            a.at(1) = v2;
        }
        if(l3 >= l1 && l3 >= l2){
            //longer_side = l3;
            a.at(0) = v0;
            a.at(1) = v2;
        }

        for(int i=0;i<3;i++){
            int v = vertices[i];
            if(a[0] != v && a[1] != v){
                a.at(2) = v;
                return a;
            }
        }
    }

    void print_points(TriangularMesh &mesh){

        for(int j=0; j<mesh.Cell2DVertices.size();j++){
            cout << j <<"Indice Triangolo: "<< mesh.Cell2DVertices[j][0]<<"-" << mesh.Cell2DVertices[j][1]<< "-"  << mesh.Cell2DVertices[j][2] << endl;
        }
    }

public:

    TriangularMesh  &data;

    Algorithm(TriangularMesh & data_)
        :    data(data_) {}

    int add_mid_point_mesh(int v1, int v2);
    bool Add_Edges(int v1, int v2);
    int AddTriangle_0(vector <int> h);
    void AddTriangle_1(vector <int> h);
    bool check_triangle_ammissibility(int mid_point_index);
    int find_triangle_sharing_late_to_new_triangle(int index, int v1, int v2);
    bool check_point_in(TriangularMesh &mesh, double x, double y);
    bool check_edge_in(int v1, int v2);

    int find_opposite_vertex(int index_triangle, int v1, int v2){

        array<unsigned int, 3> vertices= data.Cell2DVertices[index_triangle];

        for(int z=0;z<3;z++){
            int opposite_vertex2 = vertices[z];

            if(opposite_vertex2!=v1 && opposite_vertex2!=v2){

                return opposite_vertex2;
            }
        }

    }


    void raff(Sort_Area_Triangles s, int k){

        ProjectLibrary::index_value a[MAX];
        int n = s.array_of_tuples_area(a);
        s.MergeSortAlgorithm(a, 0, data.Cell2DVertices.size()-1);

        for(int j=n-1;j>n-k;--j){

            int index_triangle = a[j].i;
            vector<int> h = longer_side_and_opposite_vertex(index_triangle);
            int v1 = h[0];
            int v2 = h[1];
            int index = find_triangle_sharing_late_to_new_triangle(index_triangle, v1, v2);
            int opposite_vertex1 = h[2];
                if(index!=0){
                int mid_point_index = AddTriangle_0(h);
                AddTriangle_1(h);

                //data.Cell2DVertices.erase(data.Cell2DVertices.begin()+index_triangle);
                data.Cell2DVertices[index_triangle][0] = 0;
                data.Cell2DVertices[index_triangle][1] = 0;
                data.Cell2DVertices[index_triangle][2] = 0;
                int opposite_vertex2 = find_opposite_vertex(index, v1, v2);

                vector<int> vert = {v1,v2,opposite_vertex2};

                int mid_point_index1 = AddTriangle_0(vert);
                AddTriangle_1(vert);

                //data.Cell2DVertices.erase(data.Cell2DVertices.begin()+index-1);
                data.Cell2DVertices[index][0] = 0;
                data.Cell2DVertices[index][1] = 0;
                data.Cell2DVertices[index][2] = 0;
                    }
        }
    }

};

}

#endif // __EMPTY_H


