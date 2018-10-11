//=============================================================
//
//  AfterBurner.h
//
//  To install your own after burner (plug in) make
//  your own class inherit from this one and implement
//  the methods you need to overwrite, init(), event(),
//  and finish().
//
//  Example:
//      class MyAfterBurner : public Afterburner {...};
//
//  Then in mc_dijet.cpp change the line
//       AfterBurner* afterBurner = new AfterBurner;
//  to
//       AfterBurner* afterBurner = new MyAfterBurner;
//  and include your header file
//  # include "MyAfterBurner.h"
//
//  That's all. Methods init(), event(), and finish() are called
//  automatically.
//
//  Methods:
//      void init(double E_e, double E_p, int A);
//  called once after MCDijet is initialized
//
//      void event(vector<double>& evt);
//  called every event
//
//      void finish();
//  called once at the end of the run.
//
//  Event structure:
//    The vector passed to event() has the following content:
//    Pt, qt, z, phi, phiT, xS, W, Q, Pol, k1x, k1y, k1z,
//    k1E, k2x, k2y, k2z, k2E
//
//
//=============================================================
#ifndef AfterBurner_h
#define AfterBurner_h
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h> 
#include <unistd.h> 
#include "string_conv.h"

using namespace std;

class AfterBurner
{
	public: 
		AfterBurner(); 
		virtual ~AfterBurner(); 
		virtual bool init(double iE_e, double iE_p, int iA) =0;
		virtual bool event(vector<double> & EventPar) =0; 
		virtual bool finish() =0; 
};


inline  AfterBurner::AfterBurner() {}
inline  AfterBurner::~AfterBurner() {}
inline  bool AfterBurner::init(double iE_e, double iE_p, int iA) { return true; }
inline  bool AfterBurner::event(vector<double>& EventPar) { return true; }
inline  bool AfterBurner::finish() { return true; }

#endif

class NoBurner: public AfterBurner{
	public:
		ofstream* output;
		int A; 
		double E_e, E_p;

		bool exists_test (const std::string& name) 
		{ struct stat buffer; 
			return (stat (name.c_str(), &buffer) == 0); 
		}

		string filename(void)
		{
			string out; 
			string base = string("parton_output_"); 
			string suff = string(".dat"); 
			for(int i=0;i<INT_MAX; i++)
			{
				out = base+toString(i)+suff;
				if ( exists_test(out) == 0 ) return out; 
			}
			cout << "Too many data files in he current directory...\n"; 
			exit(1);
		}


		bool init(double iE_e, double iE_p, int iA)
		{
			A=iA; 
			E_e=iE_e; 
			E_p=iE_p;

			string fn = filename();
			output = new ofstream; 
			output->open(fn.c_str());
			
			cout << "Output file: " << fn << endl << flush;

			*output << "#  A=" << A << "; E_e=" << E_e <<  "; E_p=" << E_p << "\n";  
			*output << "#  Pt\t qt\t z\t phi\t phiT\t xS\t W\t Q\t Pol\t k1x\t k1y\t k1z\t k1E\t k2x\t k2y\t k2z\t k2E\n"<<flush;
			return true;
		}

		bool finish()
		{
			output->close();
			return true;
		}

		bool event(vector<double>& EventPar) 
		{
			for(int i=0; i< EventPar.size() ; i++)
			{
				*output << EventPar.at(i) << " "; 
			}
			*output << endl; 
			return true;
		}

		~NoBurner()
		{
			delete(output);
		}
};

