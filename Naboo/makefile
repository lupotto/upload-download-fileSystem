all: naboo

api.o: api.c api.h
	gcc -c api.c -Wall -Wextra
main.o: main.c api.h
	gcc -c main.c -Wall -Wextra
semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c -Wall -Wextra
list.o: list.c list.h
	gcc -c list.c -Wall -Wextra
naboo: main.o api.o semaphore.o list.o
	gcc main.o api.o semaphore.o list.o -o naboo

clean: 
	rm -rf *.o