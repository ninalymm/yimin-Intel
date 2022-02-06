#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "graph.h" 
#include "omp.h"
#include <emmintrin.h>
#include <immintrin.h>
#include <xmmintrin.h>




typedef vector<vector<vector<vector<float>>>> Tensor;
using namespace std;

// main test
int main()
{

    //initialisation
    Tensor s1(32, vector<vector<vector<float>>>(64, vector<vector<float>>(112, vector<float>(112, 0))));
    Tensor s2(32, vector<vector<vector<float>>>(1, vector<vector<float>>(56, vector<float>(56, 2))));


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
    vector<vector<float>> aa (16, vector<float>(16, 1));
    vector<vector<float>> bb (16, vector<float>(16, 3));

    vector<vector<float>> cc (16, vector<float>(16, 0));

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j+=4)
        {
            __m128 op1_m = _mm_loadu_ps(&aa[i][j]);
            __m128 op2_m = _mm_loadu_ps(&bb[i][j]);

            __m128 vres = _mm_add_ps(op1_m, op2_m);


            _mm_store_ss(&cc[i][j], vres);
            cout << cc[i][j]<< cc[i][j] << cc[i][j] << cc[i][j] << endl;

        }

    }
    */

    /*
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            cout << cc[i][j] << endl;

        }

    }*/

    


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