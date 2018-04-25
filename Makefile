CXXFLAGS=-Wall --std=c++0x -Dwindows -I ~/eigen/eigen-eigen-5a0156e40feb/

sources=main.cpp simulation.cpp calculatedVectorField.cpp scalarField.cpp mesh.cpp cartesianGrid.cpp cell.cpp face.cpp point.cpp
entetes=simulation.hpp calculatedVectorField.hpp scalarField.hpp  mesh.hpp cartesianGrid.hpp cell.hpp face.hpp point.hpp 
objects=$(sources:.cpp=.o)

main: $(objects)
	g++ -o $@ $^

main.o: main.cpp


clean:
	rm -f *^ *.o

mrproper: clean
	rm -f main
