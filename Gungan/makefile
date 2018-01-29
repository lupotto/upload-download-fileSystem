all: gungan

api.o: api.c api.h
	gcc -c api.c -Wall -Wextra
main.o: main.c api.h
	gcc -c main.c -Wall -Wextra
gungan: main.o api.o
	gcc main.o api.o -o gungan

clean: 
	rm -rf *.o