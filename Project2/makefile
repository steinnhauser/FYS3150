GCC= c++
PROG= test.x
LIB = -llapack -larmadillo -lblas

${PROG} :	   ${PROG} main.o ${GCC} main.o ${LIB} -o ${PROG}


main.o : 		${GCC} -c main.cpp
