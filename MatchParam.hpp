//
//  MatchParam.hpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 11.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#ifndef MatchParam_hpp
#define MatchParam_hpp

#include <stdio.h>
#include <complex>
#include "ModelParams.hpp"
#include "Types.hpp"
#include "DFFT.hpp"

using namespace std;

class MatchParam {
public:
  MatchParam(RangeOfValues target, RangeOfValues clutter,
             RangeOfValues ampl, RangeOfValues widthClutter,
             vector<int> periodRecordImp);
  vector<double> getParams(vector<cplx> signal, int numP,
                    int fi0PP, int stepDopler);
private:
  
  RangeOfValues target;
  RangeOfValues clutter;
  RangeOfValues ampl;
  RangeOfValues widthClutter;
  
  vector<int> periodRecordImp;
  
  vector<double> difference(vector<double> recieveSignal, vector<double> bearingSignal);
};

#endif /* MatchParam_hpp */
