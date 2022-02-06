#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "graph.h" 
#include "omp.h"


typedef vector<vector<vector<vector<float>>>> Tensor;
using namespace std;

// main test
int main()
{

    //initialisation
    Tensor s1(32, vector<vector<vector<float>>>(64, vector<vector<float>>(112, vector<float>(112, 0))));
    Tensor s2(32, vector<vector<vector<float>>>(1, vector<vector<float>>(56, vector<float>(56, 2))));
    Tensor output = elemwiseadd(maxpooling(s1), s2);

     // testoutput
    /*
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