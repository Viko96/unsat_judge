#Al berro

clean :
	rm ./src/inputs* *.o ./inputs*

build :
	g++ -std=gnu++17 -o main.o ./src/main.cc

