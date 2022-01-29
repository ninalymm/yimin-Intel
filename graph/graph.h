#ifndef GRAPH_h
#define GRAPH_h

#include <vector>
using namespace std;

typedef vector<vector<vector<vector<int>>>> Tensor;
Tensor maxpooling(Tensor op, int k = 3, int p = 1, int s = 2);
Tensor elemwiseadd(Tensor op1, Tensor op2);
Tensor backward(Tensor output, Tensor input);

#endif // GRAPH_h
