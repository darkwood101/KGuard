INSTR_FNS_PATH = instr_fns.c

KGUARD_INSTR = -finstrument-functions \
			   -finstrument-functions-exclude-file-list=$(INSTR_FNS_PATH) \
			   $(INSTR_FNS_PATH)

all: overflow overflow-protect daemon test1 test2 test3 test4 test5 \
	 example \
	 setjmp_example \
	 test_fork \
	 test_thread

overflow: overflow.c
	gcc -z execstack -fno-stack-protector -o overflow overflow.c

overflow-protect: overflow.c
	gcc $(KGUARD_INSTR) -z execstack -fno-stack-protector -o overflow-protect overflow.c

daemon:
	gcc -o daemon -std=c99 -O2 daemon.c

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

example:
	gcc $(KGUARD_INSTR) -o example example.c

setjmp_example:
	gcc $(KGUARD_INSTR) -o setjmp_example setjmp_example.c

test_fork:
	gcc $(KGUARD_INSTR) -o test_fork test_fork.c

test_thread:
	gcc $(KGUARD_INSTR) -o test_thread -pthread test_thread.c

clean:
	rm -f daemon overflow overflow-protect test1 test2 test3 test4 test5 \
		  example \
		  setjmp_example \
		  test_fork \
		  test_thread

