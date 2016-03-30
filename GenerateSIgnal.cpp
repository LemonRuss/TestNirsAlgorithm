//
//  GenerateSIgnal.cpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 08.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#include "GenerateSIgnal.hpp"
#include <math.h>
#include <random>
#include "DFFT.hpp"

SignalGenerator::SignalGenerator(ModelParams params) {
  this->params = params;
  vector<vector<cplx>> vec(params.numbParam, vector<cplx>(params.numbImp));
  this->signal = vec;
}

void SignalGenerator::generateSignal() {
  for (std::size_t i = 0; i < params.numbParam; ++i) {
    double fd = 12 * 10e5/params.periodRecordImp[i];
    
    int widthSpectr = 50;
    int fTarget = 100;
    
    // Why?
    int stepDopler = widthSpectr/ceil(widthSpectr/params.stepDoplerMax);
    
    
    // Unused for unknown reason
    //    int fdMin = fTarget  - widthSpectr/2;
    //    int fdMax = fTarget + widthSpectr/2;
    
    int fdopler[2] = {10, 90};
    if (widthSpectr == 0) {
      fdopler[0] = fTarget;
      fdopler[1] = fTarget;
    }
    
    vector<double> x(params.numbImp);
    for (std::vector<int>::size_type k = 0; k != x.size(); ++k) {
      double value = (1/fd) * k;
      x[i] = value;
    }
    
    double fi0 = M_PI/3;
    int koef = 4;
    
    //6 records of real and image parts
    vector<double> sinRecords(params.numbImp);
    vector<double> cosRecords(params.numbImp);
    
    // Length of array fdopler
    int jMax = sizeof(fdopler)/sizeof(*fdopler);
    for (std::size_t j = 0; j < jMax; ++j) {
      koef = params.ampl[j];
      for (std::vector<int>::size_type z = 0; z != sinRecords.size(); ++z) {
        sinRecords[z] += koef * sin(2 * M_PI * fdopler[j] * x[z] + fi0);
        cosRecords[z] += koef * cos(2 * M_PI * fdopler[j] * x[z] + fi0);
      }
    }
    
    //add Noise and write it
    for (std::vector<int>::size_type z = 0; z != sinRecords.size(); ++z) {
//      sinRecords[z] += params.noisePower + sampleNormal();
//      cosRecords[z] += params.noisePower + sampleNormal();
      this->signal[i][z] = cplx(cosRecords[z], sinRecords[z]);
    }
  }
}

// Signal module
vector<vector<double>> SignalGenerator::signalAbs() {
  return ::signalAbs(this->signal);
}

vector<vector<cplx>> SignalGenerator::getSignal() {
  return this->signal;
}


// Random numbers following a normal distribution
//http://stackoverflow.com/questions/2325472/generate-random-numbers-following-a-normal-distribution-in-c-c
double SignalGenerator::sampleNormal() {
  double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
  double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
  double r = u * u + v * v;
  if (r == 0 || r > 1) return sampleNormal();
  double c = sqrt(-2 * log(r) / r);
  return u * c;
}
