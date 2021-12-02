INSTR_FNS_PATH = ./instr_fns.c

SAFE_FNS = safe_fn

KGUARD_INSTR = -finstrument-functions \
			   -finstrument-functions-exclude-function-list=$(SAFE_FNS) \
			   -finstrument-functions-exclude-file-list=$(INSTR_FNS_PATH) \
			   $(INSTR_FNS_PATH)

all: example

example: example.c instr_fns.c
	gcc $(KGUARD_INSTR) -o example example.c 

clean:
	rm example
