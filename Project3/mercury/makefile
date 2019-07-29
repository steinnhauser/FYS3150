CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas

test.x: main.o
	${CXX} -o test.x main.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
