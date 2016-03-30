//
//  DFFT.cpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 08.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#include "DFFT.hpp"


void compute_dft(const cplx in[], cplx out[], int n) {
  for (int k = 0; k < n; k++) {
    double sumreal = 0;
    double sumimag = 0;
    for (int t = 0; t < n; t++) {
      double angle = 2 * M_PI * t * k / n;
      double real =  std::real(in[t]);
      double imag = std::imag(in[t]);
      sumreal +=  real * cos(angle) + real * sin(angle);
      sumimag += -imag * sin(angle) + imag * cos(angle);
    }
    out[k] = cplx(sumreal, sumimag);
  }
}

vector<cplx> dft(vector<cplx> in) {
  vector<cplx> out;
  for (int k = 0; k < in.size(); k++) {
    double sumreal = 0;
    double sumimag = 0;
    for (vector<int>::size_type t = 0; t != in.size(); t++) {
      double angle = 2 * M_PI * t * k / in.size();
      double real =  std::real(in[t]);
      double imag = std::imag(in[t]);
      sumreal +=  real * cos(angle) + real * sin(angle);
      sumimag += -imag * sin(angle) + imag * cos(angle);
    }
    out.push_back(cplx(sumreal, sumimag));
  }
  return out;
}

vector<double> absComplex(vector<cplx> signal) {
  vector<double> signalAbs;
  for (auto const& value: signal) {
    signalAbs.push_back(std::abs(value));
  }
  return signalAbs;
}

vector< vector<double> > signalAbs(vector< vector<cplx> > signal) {
  vector< vector<double> > signalABS;
  for (auto const& value: signal) {
    vector<cplx> signalFFT = dft(value);
    signalABS.push_back(absComplex(signalFFT));
  }
  return signalABS;
}


