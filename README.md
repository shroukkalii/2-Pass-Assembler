# 2-Pass-Assembler

Implemented in C containing 2 passes where:

-PASS1: “define symbolic”

Read the input file, Assigned the address of all statements, Saved addresses assigned to labels to be used in pass 2, Added LOCCTR column to the input file to be used as an intermediate file for pass 2, Assigned a symbol table containing the label name and its location, and finally output an intermediate file “intermediate.txt” and symbol table “symtab.txt”.

PASS2: “assemble instructions and generate object code”

Read the intermediate file, Assigned the address of all statements, Translated opcode & lookup addresses, Generated data values defined by BYTE/WORD, Performed directives, Added object code column to the intermediate file and store it in an output file, and finally output object program “objprog.txt” and object code “output.txt”
