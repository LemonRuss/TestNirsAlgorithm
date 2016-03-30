//
//  GenerateSIgnal.hpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 08.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#ifndef GenerateSIgnal_hpp
#define GenerateSIgnal_hpp

#include <stdio.h>
#include <complex>
#include "ModelParams.hpp"
#include "Types.hpp"
#include <vector>
using namespace std;

class SignalGenerator {
public:
  SignalGenerator(ModelParams params);
  void generateSignal();
  vector<vector<double>> signalAbs();
  vector<vector<cplx>> getSignal();
  
  double sampleNormal();
private:
  ModelParams params;
  
  vector<vector<cplx>> signal;
};

#endif /* GenerateSIgnal_hpp */
