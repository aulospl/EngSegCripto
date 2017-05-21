all:
	g++ -Wall -o cripto main.cpp cripto.cpp

clean:
	rm cripto
	rm *.o
