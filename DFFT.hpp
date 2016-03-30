//
//  DFFT.hpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 08.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#ifndef DFFT_hpp
#define DFFT_hpp

#include <stdio.h>
#include <math.h>
#include <vector>

#include "Types.hpp"
#include "ModelParams.hpp"

using namespace std;

vector<cplx> dft(vector<cplx> in);
vector< vector<double> > signalAbs(vector< vector<cplx> > signal);
vector<double> absComplex(vector<cplx> signal);

#endif /* DFFT_hpp */
