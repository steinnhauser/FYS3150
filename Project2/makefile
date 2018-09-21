CXX= g++
PROG= test
LDLIBS = -llapack -larmadillo -lblas

test.x: main.o functions.o test_functions.o
	${CXX} -o test.x main.o functions.o test_functions.o ${LDLIBS}

main.o: main.cpp
	${CXX} -c main.cpp

functions.o: functions.cpp functions.h
	${CXX} -c functions.cpp

test_functions.o: test_functions.cpp test_functions.h
	${CXX} -c test_functions.cpp
