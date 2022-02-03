#include <iostream>
#include "omp.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <limits.h>
#include <nmmintrin.h>

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

    //calculate the size of output
    const int w = floor((op[0][0].size() - k + 2 * p) / s) + 1;

    Tensor result(op.size(), vector<vector<vector<int>>>(op[0].size(), vector<vector<int>>(w, vector<int>(w, 0))));

    omp_set_num_threads(NUM_THREADS);
    
    // padding and maxpooling
    for (int y = 0; y < result[0].size(); y++)
    {
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            int nthrds = omp_get_num_threads();
            for (int x = id; x < result.size(); x += nthrds)
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


                        int max_num = patch[i][j];
                        
                        for (int c = j; c < col_end; c++)
                        {
                           for (int r = i; r < row_end; r++)
                           {
                                if (patch[r][c] >= max_num)
                                {
                                    max_num = patch[r][c];
                                }

                           }

                        }

                        // assign value
                        result[x][y][i][j] = max_num;

                    }

                }

            }
        }

    }

    return result;

}



Tensor elemwiseadd(Tensor op1, Tensor op2)
{
    const int op1_d4 = op1.size();
    const int op1_d3 = op1[0].size();
    const int op1_w = op1[0][0].size();  
    
    
    const int op2_d4 = op2.size();
    const int op2_d3 = op2[0].size();
    const int op2_w = op2[0][0].size();


    // set the size of the results
    const int d4 = max(op1_d4, op2_d4);
    const int d3 = max(op1_d3, op2_d3);
    const int w = max(op1_w, op2_w);


    // new a result space

    Tensor res(d4, vector<vector<vector<int>>>(d3, vector<vector<int>>(w, vector<int>(w, 0))));

    // element wise add
    #pragma omp parallel for
    for (int x = 0; x < res.size(); x++)
    {   
        #pragma omp parallel
        {   
            int id = omp_get_thread_num();
            int nthrds = omp_get_num_threads();

            for (int y = id; y < res[0].size(); y += nthrds)
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

    }
    return res;
}


Tensor backward(Tensor output, Tensor input)
{
    /*back propagation*/
    return input;

}
