CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas

test.x: main.o planet.o solver.o eulers_method.o verlet_method.o
	${CXX} -o test.x main.o planet.o solver.o eulers_method.o verlet_method.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
