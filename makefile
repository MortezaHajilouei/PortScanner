all:
	g++ -pthread -o scanner.out main.cpp
clean:
	rm scanner.out