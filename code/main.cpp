#include <iostream>
#include "Solution.h"

using namespace std;

int main()
{
    srand(time(0));
    Solution sol;
    string inputDirPath = "data.txt";
    sol.solve(inputDirPath);

    return 0;
}
