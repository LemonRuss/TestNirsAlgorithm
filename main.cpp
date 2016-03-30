//
//  main.cpp
//  TestAlgorithmNirs
//
//  Created by Alex Lavrinenko on 08.03.16.
//  Copyright © 2016 Alex Lavrinenko. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <chrono>
#include <random>

#include "MatchParam.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
  
  ModelParams params = ModelParams();
  
  //Количество отсчетов на период
  params.periodRecordImp.push_back(720);
  params.periodRecordImp.push_back(920);
  params.periodRecordImp.push_back(864);
  
  //Количество импульсов
  params.numbImp = 6;
  
  // Не знаю
  params.numbFFT = 1024;
  
  //Шаг по ширине спектра
  params.stepWidthSpect = 10;
  
  //Максимальный шаг по доплеру
  params.stepDoplerMax = 10;
  
  //Номер парамметра?
  params.numbParam = 3;
  
  //Номер N_exp
  params.numbExp = 1;
  
  //Амплитуда
  params.ampl.push_back(1);
  params.ampl.push_back(1);
  
  //  for (int l = 300; l < 1000; l += 30) {
  //Params for Lmax
  RangeOfValues target = RangeOfValues();
  target.numbPoints = 1000;
  target.max = 1340;
  target.min = 0;
  
  RangeOfValues clutter = RangeOfValues();
  clutter.numbPoints = 1000;
  clutter.max = 400;
  clutter.min = 0;
  
  RangeOfValues widthClutter = RangeOfValues();
  widthClutter.numbPoints = 10;
  widthClutter.max = 100;
  
  RangeOfValues ampl = RangeOfValues();
  ampl.numbPoints = 2;
  ampl.max = 2;
  
  MatchParam* matchParam = new MatchParam(target, clutter, ampl, widthClutter, params.periodRecordImp);
  
  double fd = 1200000/params.periodRecordImp[0];
  
  params.noisePower = 0.001;
  double freqTarget = 300;
  double freqClutter = 100;
  double widClutter = 50;
  double amplT = 1;
  double amplC = 1;
  int widthClutterStep = widthClutter.max/widthClutter.numbPoints;
  std::size_t n = widClutter/widthClutterStep + 1;
  
  double avrNoise = 0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> d(0.01, 0.03);
  
  vector<cplx> firstImpulse(params.numbImp);
  
  for (std::vector<int>::size_type z = 0; z != firstImpulse.size(); ++z) {
    cplx clutt = cplx(0, 0);
    
    double value = (1/fd) * z;
    for (std::size_t j = 0; j < n; ++j) {
      double freqClutterI = freqClutter - widClutter/2 + widthClutterStep * j;
      clutt += cplx(amplC, 0) * std::exp(cplx(0, 1) * cplx(freqClutterI, 0));
    }
    
    double noise = d(gen);
    firstImpulse[z] = cplx(amplT, 0) * std::exp(cplx(0, 1) * cplx(freqTarget, 0) * cplx(value, 0)) + clutt * cplx(value, 0)
    + noise;
    avrNoise += noise;
  }
  
  avrNoise /= firstImpulse.size();
  
  
  
  int fi0PP = 50;
  int stepDopler = 10;
  
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  vector<double> result = matchParam->getParams(firstImpulse, 0, fi0PP, stepDopler);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
  cout << duration << endl;
  
  cout << result[0] << " " << result[1] << " " << result[2] << " " << result[3] << " " << result[4] << endl
  return 0;
}


/*
 for (std::vector<int>::size_type z = 0; z != firstImpulse.size(); ++z) {
 firstImpulse[z] = cplx(2, 0) * std::exp(cplx(0, 1) * cplx(70, 0));
 }
 В результате - получаем 0 70 0 0 2, т.е - частота помехи 70 и амплитуда помехи 70
 */


