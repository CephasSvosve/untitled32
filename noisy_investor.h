//
// Created by Cephas Svosve on 21/12/2021.
//

#ifndef UNTITLED30_NOISY_INVESTOR_H
#define UNTITLED30_NOISY_INVESTOR_H

#include "price.h"
#include "fund.h"
#include <map>
#include <Eigen/Dense>
#include <boost/random.hpp>

using namespace std;
using namespace Eigen;

class noisy_investor
        :public fund{

public:
noisy_investor();

//std::map<int,order>
//noise_demand();

//MatrixXd
//generateWhiteNoise(int rows, int columns);
//
//double
//lateralcorrcoef(VectorXd a);

};
#endif //UNTITLED30_NOISY_INVESTOR_H
