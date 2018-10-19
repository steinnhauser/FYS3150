CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas

test.x: main.o body.o integrator.o euler.o verlet.o writefiles.o
	${CXX} -o test.x main.o body.o integrator.o euler.o verlet.o writefiles.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
