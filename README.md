# MCDijet

A Monte Carlo  implementation to probe the distribution of linearly polarized gluons and
elliptic azimuthal anisotropy in DIS dijet production at high energy

## Dependencies

* g++ and gcc or compatible compiler 

* [GNU Scientific library](https://www.gnu.org/software/gsl/)

	On Linux Debian-based platforms run 

	```
	sudo apt-get install gsl-bin libgsl0-dev 
	```

	On OS X with [Homebrew](https://github.com/Homebrew) run 

	```
	brew install gsl 
	```

* [Boost libraries](https://www.boost.org) might be required for older versions of g++  

	On Linux Debian-based platforms run 
	
	```
	sudo apt-get install libboost-random-dev libboost-math-dev  
	```

	On OS X with [Homebrew](https://github.com/Homebrew) run 
	
	```
	brew install boost 
	```

* [cmake V3.3.2 or higher](https://cmake.org)
	
	On Linux Debian-based platforms run 
	
	```
	sudo apt-get install cmake 
	```

	On OS X with [Homebrew](https://github.com/Homebrew) run 
	
	```
	brew install cmake
	```

## Compiling 

* Adjust paths if required in Makefile 

* Run 
	
	```
	make
	```


## Running 


This section provides a brief description of the output of McDijet and
how to work with it. _To understand the calculations performed by the code 
we strongly recommend to read arXiv:..._ 

* By default the flag PRINT\_PARTONS, see mc\_dijet.cpp, is set and the output refers to
  the momenta of the produced quark and anti-quark. The code also
  prints the virtuality of the photon etc.
  The order is specified in the 5th line of the output file. Every
  line after that corresponds to a particular gamma\* + A --> q + qbar
  event.

  In particular:
  	- pol: photon polarization (0=transverse, 1=longitudinal)
  	- xS is the differential cross section at the given Q2, W, Pt,
	qt, z, phi, for the given photon polarization
	- phiT is the azimuthal angle of Pt
	- phiT + phi is the azimuthal angle of qt

* Run  

	```
	./mc_dijet.x > output.dat
	```
  By default 30 000 events will be produced and stored in the file output.dat. 

* If you would like to directly plot this output then you would
  probably want to remove header and "Events processed ..."
  lines first:

	```
  	sed -i -e 1,5d output.dat
  	sed -i -n '/Events/d' output.dat
   	```
  
  (this edits the file *in place*, make a backup first to preserve the
  original version)


## Pythia as an AfterBurner
You can use Pythia8 to produce paticle showers from the two genrated partons. 
For this you have to 

* Download Pythia 8 from http://home.thep.lu.se/~torbjorn/pythia8/pythia8235.tgz 
* Extract it to the same folder, where McDijet folder is; that is "pythia8255" and "McDijet"  should be located in the same folder
* Configure and compile Pythia: ./configure; make 
* Uncomment line 33 in mcdijet.cpp: #include "PythiaAfterBurner.h" 
* Comment line 944 in mcdijet.cpp: AfterBurner * afterBurner = new NoBurner; 
* Uncomment line 945 in mcdijet.cpp: AfterBurner * afterBurner = new PythiaAfterBurner; 
* Run make pythiaAfterBurner; it will produce the executable mcdijet.x
* The events are not saved in a file; instead you might consider adding your analysis routins to PythiaAfterBurner.cpp, see line 183

## Reporting bugs

Please report bugs directly to vladi@skokov.net





## License 


Code is under the [GNU General Public License](https://www.gnu.org/licenses/gpl-3.0.en.html). 
Please cite ... if used 
