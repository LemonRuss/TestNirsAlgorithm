//
//  GeneratorParams.h
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 08.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//
#include <vector>

#ifndef GeneratorParams_hpp
#define GeneratorParams_hpp
using namespace std;

struct ModelParams {
  vector<int> periodRecordImp;
  vector<int> ampl;
  int numbImp;
  int numbFFT;
  int numbParam;
  int stepWidthSpect;
  int stepDoplerMax;
  int numbExp;
  double noisePower;
};

struct RangeOfValues {
  int numbPoints = 0;
  int max = 0;
  int min = 0;
};

#endif /* GeneratorParams_h */
