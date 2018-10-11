//===============================================================
//
//  PythiaAfterBurner.h (Example)
//
//  Afterburner is an example plug-in for MCDijet.
//  It performs:
//  Showering and hadronization of the partons produced
//  by MCDijet using PYTHIA8.
//
//  For more details see comment block in Afterburner.cpp
//
//  Author: Thomas Ullrich
//  Last update: September 1, 2018
//===============================================================
#ifndef MyAfterBurner_h
#define MyAfterBurner_h

#include <vector>
#include <iostream>
#include "Pythia8/Pythia.h"

using namespace std;

class PythiaAfterBurner : public AfterBurner {
public:
    PythiaAfterBurner();
    ~PythiaAfterBurner();
    
    bool init(double E_e, double E_p, int A);
    bool event(vector<double>&);
    bool finish();

private:
    Pythia8::Pythia *mPythia;
    double mEe;
    double mEp;
    double mA;
    int mEventNumber;
};
#endif
