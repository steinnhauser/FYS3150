CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas


test.x: main.o Eulers_method.o Verlet_method.o Write_Vectors_file.o
	${CXX} -o test.x main.o Eulers_method.o Verlet_method.o Write_Vectors_file.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: main.cpp
	${CXX} -c main.cpp
