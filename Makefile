CC=g++
INCLUDES = -I /sw/include -I/sw/opt/boost-1_58/include/ -I/home/vskokov/lib/include
LIBS= -L /sw/lib/ -L/home/vskokov/lib/lib -L interp2d
LIBIN=-lgsl -lgslcblas -linterp2d 
CFLAGS= -std=c++11 -O2 

all: 
	cd interp2d && cmake . && make 
	g++ $(INCLUDES) $(LIBS) $(CFLAGS) mc_dijet.cpp -o mc_dijet.x  $(LIBIN)
clean:
	rm -rf mc_dijet.x interp2d/Makefile interp2d/*.a interp2d/CMakeCache.txt interp2d/CMakeFiles interp2d/cmake_install.cmake
