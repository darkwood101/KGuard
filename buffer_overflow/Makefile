INSTR_FNS_PATH = ../custom_compilation/instr_fns.c

KGUARD_INSTR = -finstrument-functions \
			   -finstrument-functions-exclude-file-list=$(INSTR_FNS_PATH) \
			   $(INSTR_FNS_PATH)

all: overflow

overflow: overflow.c
	gcc -z execstack -fno-stack-protector -o overflow overflow.c

overflow-protect: overflow.c
	gcc $(KGUARD_INSTR) -z execstack -fno-stack-protector -o overflow overflow.c

clean:
	rm overflow
