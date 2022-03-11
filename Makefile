all: 
	gcc -c src/reader.c 
	gcc -c src/error.c
	gcc -c src/pool.c
	gcc -c src/main.c
	gcc -c src/access.c
	gcc -c src/class.c
	gcc  reader.o error.o pool.o main.o access.o class.o -o bin/java
	rm *.o
