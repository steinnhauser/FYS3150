CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas

test.x: main.o planet.o solver.o initializer.o write_file.o mercury.o
	${CXX} -o test.x main.o planet.o solver.o initializer.o write_file.o mercury.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
