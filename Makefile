src = src/reader.c src/pool.c src/access.c src/class.c src/mem.c \
	src/main.c
tp-src = third-party/log/src/log.c
incl_dir = third-party/log/src/
all: $(src) $(tp-src)
	gcc -c $(src) $(tp-src) -I$(incl_dir)
	gcc  reader.o error.o pool.o main.o access.o class.o mem.o log.o -o bin/java
	rm *.o
