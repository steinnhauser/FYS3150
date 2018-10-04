CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas


test.x: main.o Eulers_method.o
	${CXX} -o test.x main.o Eulers_method.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
