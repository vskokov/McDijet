CC=g++
LIBS=  -L interp2d
LIBIN=-lgsl -lgslcblas -linterp2d 
CFLAGS= -std=c++11 -O2 

all: 
	cd interp2d && cmake . && make 
	g++ $(INCLUDES) $(LIBS) $(CFLAGS) mc_dijet.cpp -o mc_dijet.x  $(LIBIN)
clean:
	rm -rf mc_dijet.x interp2d/Makefile interp2d/*.a interp2d/CMakeCache.txt interp2d/CMakeFiles interp2d/cmake_install.cmake
