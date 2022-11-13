all:
	g++ -pthread -o scanner main.cpp
clean:
	rm scanner