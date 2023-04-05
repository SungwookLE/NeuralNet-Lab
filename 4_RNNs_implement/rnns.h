#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "readCSV.h"

using namespace std;

namespace preprocessing
{
    void normalized(vector<double> &X, double scaled)
    {

        double sumX = 0;
        for (int i = 0; i < X.size(); ++i)
            sumX += X[i] * X[i];

        double meanSumX = sumX / X.size();
        double rootMeanSumX = sqrt(meanSumX);

        for (int i = 0; i < X.size(); ++i)
            X[i] = X[i] / rootMeanSumX * scaled;

        return;
    }

    void transpose(vector<vector<double>> &X)
    {
        vector<vector<double>> trans_X(X[0].size(), vector<double>());
        for (int i = 0; i < X.size(); ++i)
        {
            for (int j = 0; j < X[i].size(); ++j)
            {
                trans_X[j].push_back(X[i][j]);
            }
        }
        X = trans_X;
        return;
    }
}
