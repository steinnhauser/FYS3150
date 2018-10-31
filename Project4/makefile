CXX= g++
PROG= test

test.x: main.o
	${CXX} -o test.x main.o ${LDLIBS}

%.o: %.cpp %.h
	$(CXX) -c $<

main.o: src/main.cpp
	${CXX} -c src/main.cpp
