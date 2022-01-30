// graph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "omp.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef vector<vector<vector<vector<int>>>> Tensor;
#define NUM_THREADS 8

Tensor maxpooling(Tensor op, int k = 3, int p = 1, int s = 2)
{
    /*
        k = kernel size, default 3
        p = padding elem, default 1
        s = stride, default 2
    */


    // get the size of op
    int d4 = op.size();
    int d3 = op[0].size();
    int edge = op[0][0].size();

    //calculate the size of output
    int w = floor((edge - k + 2 * p) / s) + 1;

    Tensor result(d4, vector<vector<vector<int>>>(d3, vector<vector<int>>(w, vector<int>(w, 0))));

    omp_set_num_threads(NUM_THREADS);
    // padding and maxpooling
    for (int x = 0; x < result.size(); x++)
    {
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            int nthrds = omp_get_num_threads();
            for (int y = id; y < result[0].size(); y = y+nthrds)
            {
            
                // padding 
               
                vector<vector<int>> patch = op[x][y];

                // pad row
                //#pragma omp parallel for
                for (int r = 0; r < patch.size(); r++)
                {
                    patch[r].insert(patch[r].begin(), p);
                    patch[r].insert(patch[r].end(), p);

                }
                // new col size
                int col = patch[0].size();

                // pad col
                vector<int> padding(col, p);
                patch.insert(patch.begin(), padding);
                patch.push_back(padding);

                // new row size
                int row = patch.size();


                // maxpooling
                for (int i = 0; i < result[0][0].size(); i++)
                {
                    for (int j = 0; j < result[0][0].size(); j++)
                    {
                        // identify numbers in patch

                        int row_end = i * s + k;
                        int col_end = j * s + k;


                        vector<int> tmp;
                        for (int r = i; r < row_end; r++)
                        {
                            for (int c = j; c < col_end; c++)
                            {
                                tmp.push_back(patch[r][c]);

                            }

                        }

                        // find the max value in the current patch
                        sort(tmp.begin(), tmp.end());


                        // assign value
                        result[x][y][i][j] = tmp[tmp.size() - 1];

                    }

                }

            }
        }

    }

    return result;

}



Tensor elemwiseadd(Tensor op1, Tensor op2)
{

    // compare size
    // op1
    const int op1_d4 = op1.size();
    const int op1_d3 = op1[0].size();
    const int op1_w = op1[0][0].size();

    // op2

    const int op2_d4 = op2.size();
    const int op2_d3 = op2[0].size();
    const int op2_w = op2[0][0].size();

    // set the size of the results
    int d4 = max(op1_d4, op2_d4);
    int d3 = max(op1_d3, op2_d3);
    int w = max(op1_w, op2_w);


    // new a result space

    Tensor res(d4, vector<vector<vector<int>>>(d3, vector<vector<int>>(w, vector<int>(w, 0))));

    // element wise add
    for (int x = 0; x < res.size(); x++)
    {
        for (int y = 0; y < res[0].size(); y++)
        {
            for (int r = 0; r < res[0][0].size(); r++)
            {
                for (int c = 0; c < res[0][0][0].size(); c++)
                {

                    res[x][y][r][c] = op1[x % op1_d4][y % op1_d3][r % op1_w][c % op1_w] +
                        op2[x % op2_d4][y % op2_d3][r % op2_w][c % op2_w];
                }


            }

        }

    }


    return res;
}


Tensor backward(Tensor output, Tensor input)
{
    /*back propagation*/
    return input;

}
