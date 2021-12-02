INSTR_FNS_PATH = ../custom_compilation/instr_fns.c

KGUARD_INSTR = -finstrument-functions \
			   -finstrument-functions-exclude-file-list=$(INSTR_FNS_PATH) \
			   $(INSTR_FNS_PATH)

all: overflow daemon

overflow: overflow.c
	gcc -z execstack -fno-stack-protector -o overflow overflow.c

overflow-protect: overflow.c
	gcc $(KGUARD_INSTR) -z execstack -fno-stack-protector -o overflow overflow.c

daemon:
	gcc -o daemon -std=c99 -O2 daemon.c

clean:
	rm overflow daemon
