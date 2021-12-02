import sys

prologue_indicators = ['push', 'rbp']
epilogue_indicators = ['ret']

prologue_extension = ['\tmovq\t$42, %rax\n']
epilogue_extension = ['\tmovq\t$263, %rax\n']

if __name__ == '__main__':
    assert len(sys.argv) == 2, 'asm_trap.py takes 1 command line argument'
    asm_file_name = sys.argv[1]

    with open(asm_file_name, 'r') as f:
        lines = f.readlines() 

    newlines = []
    for i, line in enumerate(lines):
        if all([ind in line for ind in prologue_indicators]):
            newlines.extend(prologue_extension)
        if all([ind in line for ind in epilogue_indicators]):
            newlines.extend(epilogue_extension)
        newlines.append(line)

    with open(asm_file_name, 'w') as f:
        f.writelines(newlines)
