CC=g++
LIBS= -L interp2d 
LIBSPY= -L ../pythia8235/lib/
LIBIN= -lgsl -lgslcblas -linterp2d  
LIBPY= -lpythia8
CFLAGS= -std=c++11 -O2 
INCLUDES= 
INCLUDESPY= -I ../pythia8235/include/ 

all: 
	cd interp2d && cmake . && make 
	$(CC) $(INCLUDES) $(LIBS) $(CFLAGS) mc_dijet.cpp -o mc_dijet.x $(LIBIN)

pythiaAfterBurner:
	cd interp2d && cmake . && make 
	$(CC) -c $(INCLUDES) $(INCLUDESPY) $(LIBS) $(CFLAGS) PythiaAfterBurner.cpp -o PyAB.o 
	$(CC) $(INCLUDES) $(INCLUDESPY) $(LIBS) $(LIBSPY) $(CFLAGS) mc_dijet.cpp -o mc_dijet.x PyAB.o $(LIBIN) $(LIBPY) 

clean:
	rm -rf mc_dijet.x interp2d/Makefile interp2d/*.a interp2d/CMakeCache.txt interp2d/CMakeFiles interp2d/cmake_install.cmake
	rm -rf PyAB.o 
