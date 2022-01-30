#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "graph.h" 
#include "omp.h"

typedef vector<vector<vector<vector<int>>>> Tensor;
using namespace std;

// main test
int main()
{

    //initialisation
    Tensor s1(32, vector<vector<vector<int>>>(64, vector<vector<int>>(112, vector<int>(112, 0))));
    Tensor s2(32, vector<vector<vector<int>>>(1, vector<vector<int>>(56, vector<int>(56, 2))));


    /*
     // input
    int k = 0;
    for (int i = 0; i < s1.size(); i++)
    {

        for (int j = 0; j < s1[0].size(); j++)
        {
            for (int p = 0; p< s1[0][0].size(); p++)
            {
                for (int q = 0; q < s1[0][0][0].size(); q++)
                {
                    s1[i][j][p][q] = k++;

                }
            }
        }
    }*/

    Tensor output;
    //Tensor src1;

    /*formula
        dst[32,64,56,56] = max_pooling(src1[32,64,112,112]) + src2[32,1,56,56]

        that is: output = maxpooling(tensor1) + tensor2
    */

    output = elemwiseadd(maxpooling(s1), s2);

    /*
     // testoutput
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 0; j < output[0].size(); j++)
        {
            for (int p = 0; p < output[0][0].size(); p++)
            {
                for (int q = 0; q < output[0][0][0].size(); q++)
                {
                    cout << output[i][j][p][q] << " ";


                }
                cout << '\n';
                cout << "output  " << "first round" << "";
                cout << '\n';

            }
            cout << '\n';
            cout << "output  " << "second round" << "";
            cout << '\n';
        }
        cout << '\n';
        cout << "output  " << "third round" << "";
        cout << '\n';
    }*/

    return 0;


}