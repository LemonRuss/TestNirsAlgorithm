//
//  MatchParam.cpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 11.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#include "MatchParam.hpp"
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
#include <omp.h>


MatchParam::MatchParam(RangeOfValues target, RangeOfValues clutter,
                       RangeOfValues ampl, RangeOfValues widthClutter,
                       vector<int> periodRecordImp){
  this->target = target;
  this->clutter = clutter;
  this->ampl = ampl;
  this->widthClutter = widthClutter;
  
  this->periodRecordImp = periodRecordImp;
}


vector<double> MatchParam::getParams(vector<cplx> signal, int numP,
                                     int fi0PP, int stepDopler) {
  
  vector<double> result(5);
  int nUmp = periodRecordImp[numP];
  
//  vector<vector<vector<vector<vector<double>>>>> fMMMP;
  
  std::size_t signalLenght = signal.size();
  
  vector<cplx> signalFFT(signalLenght, 0);
  signalFFT = dft(signal);
  vector<double> signalModule = absComplex(signalFFT);
  
  int targetStep = (target.max - target.min)/target.numbPoints;
  int clutterStep = (clutter.max - clutter.min)/clutter.numbPoints;
  int widthClutterStep = widthClutter.max/widthClutter.numbPoints;
  int amplStep = ampl.max/ampl.numbPoints;
  
  double threshold = 2000;
  
  std::ofstream outputFile;
  outputFile.open("/Users/Leman/GoogleDisk/University/TestAlgorithmNirs/TestAlgorithmNirs/errors.txt");
  outputFile << "signal = {";
  copy(signal.begin(), signal.end(), ostream_iterator<cplx>(outputFile , ", "));
  outputFile << "}" << endl;
  
  std::size_t freqTarget = target.min;
  
  #pragma omp parallel for
  for (freqTarget = target.min; freqTarget < target.max; freqTarget += targetStep) {
    for (std::size_t freqClutter = clutter.min; freqClutter < clutter.max; freqClutter += clutterStep) {
      for (std::size_t widClutter = widthClutter.min; widClutter < widthClutter.max;
           widClutter += widthClutterStep) {
        for (std::size_t aTarget = ampl.min; aTarget < ampl.max; aTarget += amplStep) {
          for (std::size_t aClutter = ampl.min; aClutter < ampl.max; aClutter += amplStep) {
            vector<cplx> bearingSignal(signalLenght);
            std::size_t n = widClutter/widthClutterStep + 1;
            
            double fd = 1200000/periodRecordImp[numP];
            
            for (std::size_t i = 0; i < signalLenght; ++i) {
              cplx clutt = cplx(0, 0);
              double value = (1/fd) * i;
              for (std::size_t j = 0; j < n; ++j) {
                double freqClutterI = freqClutter - widClutter/2 + widthClutterStep * j;
                clutt += cplx(aClutter, 0) * std::exp(cplx(0, 1) * freqClutterI);
              }
              bearingSignal[i] = cplx(aTarget, 0) * std::exp(cplx(0, 1) * cplx(freqTarget, 0) * cplx(value, 0)) + clutt * cplx(value, 0);
            }
            
            vector<cplx> bearingSpectr = dft(bearingSignal);
            vector<double> bearingModule = absComplex(bearingSpectr);
            vector<double> diff = difference(signalModule, bearingModule);
            
            double error = 0;
            for (auto const& value: diff) {
              error += value;
            }
//            outputFile << "difference = {";
//            copy(diff.begin(), diff.end(), ostream_iterator<double>(outputFile , ", "));
//            outputFile << "}";
//            outputFile << freqTarget << " ";
//            outputFile << freqClutter << " ";
//            outputFile << widClutter << " ";
//            outputFile << aTarget << " ";
//            outputFile << aClutter << " ";
//            
//            outputFile << "bearingModule = {";
//            copy(bearingSignal.begin(), bearingSignal.end(), ostream_iterator<cplx>(outputFile , ", "));
//            outputFile << "}";
//            outputFile << "error: " << error << endl;
            
            if (abs(error) < threshold) {
//              std::cout << error << endl;
              threshold = abs(error);
              result[0] = freqTarget;
              result[1] = freqClutter;
              result[2] = widClutter;
              result[3] = aTarget;
              result[4] = aClutter;
            }
            //            fMMMP[freqTarget][freqClutter][widClutter][aTarget][aClutter] = error;
          }
        }
      }
    }
  }
  outputFile.close();
//    std::ofstream outputFile("./errors.txt");
//    outputFile << "GLfloat vector[]={";
//    copy(fMMMP.begin(), fMMMP.end(), ostream_iterator<cplx>(outputFile , ", "));
//    outputFile << "}" << endl;
  return result;
}


vector<double> MatchParam::difference(vector<double> recieveSignal, vector<double> bearingSignal) {
  vector<double> result(recieveSignal.size());
  for (std::vector<int>::size_type k = 0; k != recieveSignal.size(); ++k) {
    result[k] = recieveSignal[k] - bearingSignal[k];
  }
  return result;
}