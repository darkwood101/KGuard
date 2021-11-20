all: daemon test1 test2 test3 test4 test5

daemon:
	gcc -o daemon -std=c99 -O2 -D_GNU_SOURCE daemon.c

test1:
	gcc -o test1 -std=c99 -O2 -D_GNU_SOURCE test1.c

test2:
	gcc -o test2 -std=c99 -O2 -D_GNU_SOURCE test2.c

test3:
	gcc -o test3 -std=c99 -O2 -D_GNU_SOURCE test3.c

test4:
	gcc -o test4 -std=c99 -O2 -D_GNU_SOURCE test4.c

test5:
	gcc -o test5 -std=c99 -O2 -D_GNU_SOURCE test5.c

clean:
	rm -f daemon test1 test2 test3 test4 test5

