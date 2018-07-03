# MCDiJet

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
		make all 
	```

## Running 

* Run  


	```
		mc_dijet.x > output.dat
	```

## Reporting bugs

Please report bugs directly to vladi@skokov.net

## License 


Code is under the [GNU General Public License](https://www.gnu.org/licenses/gpl-3.0.en.html). 
Please cite ... if used 
