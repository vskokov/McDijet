//===============================================================
//
//  MyAfterBurner.cpp (Example)
//
//  Afterburner is a plug-in for MCDijet.
//  It performs:
//  Showering and hadronization of the partons produced
//  using PYTHIA8.
//
//  For more details see comment block in Afterburner.cpp
//
//  Author: Thomas Ullrich
//  Last update: September 1, 2018
//===============================================================
//
//  How to plug it into MCDiJet
//
//  In mc_dijet.cpp:
//
//    Add include file:
//    #include "PythiaAfterBurner.h"
//
//    In main():
//     Change:
//         AfterBurner* afterBurner = new NoBurner;
//     to
//         AfterBurner* afterBurner = new PythiaAfterBurner;
//
//   Dependencies: PYTHIA8
//
//===============================================================
#include "AfterBurner.h"
#include "PythiaAfterBurner.h"
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include "Pythia8/Pythia.h"

PythiaAfterBurner::PythiaAfterBurner()
{
    mEe = mEp = 0;
    mA = 0;
    mEventNumber = 0;
    mPythia = nullptr;
}

PythiaAfterBurner::~PythiaAfterBurner()
{
    delete mPythia;
}

bool PythiaAfterBurner::init(double E_e, double E_p, int A)
{
    mEventNumber = 0;
    mEe = E_e;
    mEp = E_p;
    mA  = A;
    
    if (mPythia) delete mPythia;
    
    //
    //  Setup PYTHIA
    //
    mPythia = new Pythia8::Pythia();
    
    // Key requirement: switch off ProcessLevel, and thereby also PartonLevel.
    mPythia->readString("ProcessLevel:all = off");   // That's the whole trick!
    // Optionally switch off/on resonance decays, or only showers in them.
    mPythia->readString("ProcessLevel:resonanceDecays = on");
    mPythia->readString("PartonLevel:FSRinResonances = on");
    
    // Optionally switch off/on ordinary decays.
    mPythia->readString("HadronLevel:Decay = on");
    
    // Switch off automatic event listing in favour of manual.
    mPythia->readString("Next:numberShowInfo = 0");
    mPythia->readString("Next:numberShowProcess = 0");
    mPythia->readString("Next:numberShowEvent = 0");
    
    // Initialize.
    mPythia->init();
    
    cout << "MyAfterBurner: Pythia is initialized" << endl;
	return true; 
}

bool PythiaAfterBurner::finish()
{
    cout << "MyAfterBurner: All done. Bye." << endl;
	return true; 
}


bool PythiaAfterBurner::event(vector<double>& vec)
{
    mEventNumber++;

    //
    // Extract from event vector the variables we need
    //
    double Q = vec[7];
    double k1x = vec[9];
    double k1y = vec[10];
    double k1z = vec[11];
    double k1E = vec[12];
    double k2x = vec[13];
    double k2y = vec[14];
    double k2z = vec[15];
    double k2E = vec[16];

    //
    //  Get parton 4 momenta.
    //  Slight correction to match Pythia8 u quark mass
    //
    double umass = mPythia->particleData.m0(2);
    k1E = sqrt((k1x*k1x+k1y*k1y+k1z*k1z)+umass*umass);
    k2E = sqrt((k2x*k2x+k2y*k2y+k2z*k2z)+umass*umass);
    
    Pythia8::Vec4 parton1(k1x, k1y, k1z, k1E);
    Pythia8::Vec4 parton2(k2x, k2y, k2z, k2E);
    
    //
    //  Pythia8 as afterburner for showering and hadronization
    //
    //  Taken from Pythia8 example main21.
    //  Here we are using only type 12 which is explained in main21
    //  as  "q qbar plus parton shower".
    //
    Pythia8::Event& event = mPythia->event;
    event.reset();
    
    // Information on a q qbar system, to be hadronized.
    int id = 2;  // 1 = d, 2 = u, 3 = s, 4 = c
    int status = 23; // outgoing (21-29 are particles of the hardest subprocess
    int pol = 9;     // unknown polarization, not used anyway
    int colorTag = 101;
    int antiColorTag = 0;
    
    event.append(id, status, colorTag, antiColorTag, parton1, parton1.mCalc());
    event.append(-id, status, antiColorTag, colorTag, parton2, parton2.mCalc());

    event[1].scale(parton1.e());
    event[2].scale(parton2.e());
    double scale = Q;
    
    //
    // Now actually do the showering, for range of partons, and max scale.
    // (Most restrictive of global and individual applied to each parton.)
    //
    mPythia->forceTimeShower(1, 2, scale);  // see PYTHIA8 manual Hadron-Level Standalone
    
    //
    // Generate event
    //
    if (!mPythia->next()) {
        cout << " Event generation in Pythia8 aborted prematurely, owing to error!\n";
        return false;
    }
    
    //
    // List generated particles for first few events
    //
    if (mEventNumber < 30) {
        event.list();
        cout << "List of final state particles in McDijet frame:" << endl;
        for (int i = 0; i < event.size(); i++) {
            if (event[i].status() > 0) {
                cout << "pythia (stable): i=" << i
                << ", px=" << event[i].px()
                << ", py=" << event[i].py()
                << ", pz=" << event[i].pz()
                << ", E=" << event[i].e()
                << ", pt=" << sqrt(event[i].px()*event[i].px() + event[i].py()*event[i].py())
                << ", phi=" << event[i].phi()
                << ", eta=" << event[i].eta()
                << endl;
            }
        }
    }

	// ******************************************
	// User routines here ...
	// ******************************************
	//
	//
	//
	//
	//
	//

	return true; 
}
