#Al berro

clean :
	rm ./src/inputs* *.o ./inputs*

build :
	g++ -o main.o ./src/main.cc

