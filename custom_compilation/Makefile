INSTR_FNS_PATH = ./instr_fns.c

SAFE_FNS = safe_fn

KGUARD_INSTR = -finstrument-functions \
			   -finstrument-functions-exclude-function-list=$(SAFE_FNS) \
			   -finstrument-functions-exclude-file-list=$(INSTR_FNS_PATH) \
			   $(INSTR_FNS_PATH)

all: example py_ex daemon

example: example.c instr_fns.c
	gcc $(KGUARD_INSTR) -o example example.c 

py_ex: py_ex.c asm_trap.py
	gcc -S py_ex.c -o tmp.s; python3 asm_trap.py tmp.s; gcc tmp.s -o py_ex

daemon:
	gcc -o daemon -std=c99 -O2 daemon.c

clean:
	rm -f example py_ex tmp.s daemon
