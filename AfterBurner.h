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
		//AfterBurner(); 
		//virtual ~AfterBurner(); 
		double A, E_e, E_p;
		virtual bool init(double iA, double iE_e, double iE_p) =0; 
		virtual bool event(vector<double> * EventPar) =0; 
		virtual bool finish() =0; 
};



class NoBurner: public AfterBurner{
	public:
		ofstream* output;

		bool exists_test (const std::string& name) 
		{ struct stat buffer; 
			return (stat (name.c_str(), &buffer) == 0); 
		}

		string filename(void)
		{
			string out; 
			string base = string("NoAFB_"); 
			string suff = string(".dat"); 
			for(int i=0;i<INT_MAX; i++)
			{
				out = base+toString(i)+suff;
				if ( exists_test(out) == 0 ) return out; 
			}
			cout << "Too many data files in he current directory...\n"; 
			exit(1);
		}


		bool init(double iA, double iE_e, double iE_p)
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

		bool event(vector<double> * EventPar) 
		{
			for(int i=0; i< EventPar->size() ; i++)
			{
				*output << EventPar->at(i) << " "; 
			}
			*output << endl; 
			return true;
		}

		~NoBurner()
		{
			delete(output);
		}
};

//Thomas 
class PythiaBurner: public AfterBurner{
	public:
		bool init(double iA, double iE_e, double iE_p)
		{
			A=iA; 
			E_e=iE_e; 
			E_p=iE_p; 
			
			return true;
		}

		bool finish()
		{
			return true;
		}

		bool event(vector<double> * EventPar) 
		{
			return true;
		}

};

