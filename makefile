all: main.o
	gcc -o main main.o

main.o: main.c
	gcc -c main.c

run:
	./main

clean:
	rm -rf main.o
	rm -rf newnyc_pop.csv
