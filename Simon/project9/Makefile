#to run: make
#to elminate .o file: make clean
calc: calcTst.o calc.o stack.o list.o
	g++ -o calc calcTst.o calc.o stack.o list.o

calcTst.o: calcTst.cpp
	g++ -c calcTst.cpp 

calc.o: calc.cpp
	g++ -c calc.cpp 

stack.o: stack.cpp
	g++ -c stack.cpp 

list.o: list.cpp
	g++ -c list.cpp 

clean :
	rm *.o
