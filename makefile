default: main.o parser.o executor.o
	gcc -o main main.o parser.o executor.o
main.o: main.c parser.h executor.h
	gcc -c main.c
parser.o: parser.c
	gcc -c parser.c
executor.o: executor.c
	gcc -c executor.c
run:
	./main
