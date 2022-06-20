CC     := clang
AR 	   := ar
CFLAGS := -O3

make: hashmap.h hashmap.o libhashmap.a libhashmap.so

hashmap.h:
	cp src/hashmap.h bin/hashmap.h

hashmap.o:
	${CC} ${CFLAGS} -c src/hashmap.c -o bin/hashmap.o

libhashmap.a: hashmap.o
	${AR} rcs bin/libhashmap.a bin/hashmap.o

libhashmap.so:
	${CC} ${CFLAGS} -shared src/hashmap.c -o bin/libhashmap.so

clean:
	rm bin/*

test: clean make test.c
	LD_LIBRARY_PATH=./bin ./bin/test

test.c:
	${CC} ${CFLAGS} src/test/test.c -o bin/test -lhashmap -Lbin/
