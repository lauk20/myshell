default: main.o parser.o
	gcc -o main main.o parser.o
main.o: main.c parser.h
	gcc -c main.c
parser.o: parser.c
	gcc -c parser.c
run:
	./main
