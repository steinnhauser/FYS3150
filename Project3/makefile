CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas


test.x: main.o eulers_method.o verlet_method.o write_vectors_function.o
	${CXX} -o test.x main.o eulers_method.o verlet_method.o write_vectors_function.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
