FLAGS = -std=c++11

all: main
	./main

main: Seq.o Cluster.o main.cpp
	g++ ${FLAGS} -o main	Seq.o Cluster.o main.cpp

Seq.o: Seq.cpp
	g++ ${FLAGS} -c Seq.cpp

Cluster.o: Cluster.cpp
	g++ ${FLAGS} -c Cluster.cpp

clean:
	rm -rf *.o main