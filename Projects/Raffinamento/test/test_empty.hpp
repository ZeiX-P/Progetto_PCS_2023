#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "empty_class.hpp"

using namespace testing;



TEST(TestAlgo, TestMergeSortAlgorithm)

{
    ProjectLibrary::Mesh m("./Cell0Ds.csv", "./Cell1Ds.csv","./Cell2Ds.csv");

    ProjectLibrary::TriangularMesh mesh = m.mesh;
    vector<double> area = {6, 7.5, 3, 2, 0.2,2.2};
    ProjectLibrary::Sort_Area_Triangles s(mesh);
    ProjectLibrary::index_value h[6];
    for(int j=0;j<6;j++){

        ProjectLibrary:: index_value a;
        a.i = j;

        a.value = area[j];

        h[j] = a;


    }

    vector<double> sortedV = {0.2, 2,2.2 ,3 ,6 ,7.5};
    cout << endl;

    s.MergeSortAlgorithm(h, 0, 5);
    for(int i=0;i<6;i++){
        area[i] = h[i].value;

    }

    EXPECT_EQ(area, sortedV);
}

TEST(TestAlgo, TestRaffAlgo){

    ProjectLibrary::Mesh m("./Cell0Ds.csv", "./Cell1Ds.csv","./Cell2Ds.csv");

    ProjectLibrary::TriangularMesh mesh = m.mesh;
    ProjectLibrary::Sort_Area_Triangles s(mesh);
    ProjectLibrary::Algorithm algo(mesh);



    int step = 20;
    int k = 5;

    algo.raff(s, k);

}

#endif // __TEST_EMPTY_H
