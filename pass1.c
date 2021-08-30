#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passOne(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]);
void display();

int main()
{
    // for reading from input
    char label[10], opcode[10], operand[10];
    // for reading from optab
    char code[10], mnemonic[3];
    // function
    passOne(label, opcode, operand, code, mnemonic);

    return 0;
}

void passOne(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3])
{
    int locctr, start, length;

    FILE *fp1, *fp2, *fp3, *fp4, *fp5; // file pointers

    // read mode
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    // write mode
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermediate.txt", "w");
    fp5 = fopen("length.txt", "w");

    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);  // read first line

    if (strcmp(opcode, "START") == 0) {
        //stdlib.h to use atoi, btconvert string le int
        start = atoi(operand); 
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);     // write it f interm. file
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);          // read next line
    }
    else {
        locctr = 0;
    }

    //while opcode msh end
    while (strcmp(opcode, "END") != 0) {

        //transfer address and read line to output file
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

		//u need to know which one is a label, stars fl empty
        if (strcmp(label, "**") != 0) { 
            fprintf(fp3, "%s\t%d\n", label, locctr);//output it b2a
        }

        //read mn optab (code and mnemonic value)
        fscanf(fp2, "%s\t%s", code, mnemonic);

        // till end of optab file
        while (strcmp(code, "END") != 0) {
            if (strcmp(opcode, code) == 0) { //found, hplus 3 w done
                locctr += 3;
                break;
            }
            // read next line
            fscanf(fp2, "%s\t%s", code, mnemonic); //as an increment
        }

        // 5. Searching opcode for WORD, RESW, BYTE, RESB keywords and updating locctr

                // lw WORD  +3
        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        }
                // lw RESW  3*operand 
        else if (strcmp(opcode, "RESW") == 0) {
            locctr += (3 * (atoi(operand)));  // convert operand to int
        }
                // lw BYTE +1
        else if (strcmp(opcode, "BYTE") == 0) {
            ++locctr;
        }
                // RESB add operand kolo as an int to locctr
        else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        }

        // read next line ml input
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    // line el end
    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // Close el files
    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);

    // display outputs fl exe ande
    display();

    // save program length f file 2023-2000
    length = locctr - start;
    fprintf(fp5, "%d", length);
    fclose(fp5);
    printf("\nThe length of the code : %d\n", length); //fl exe
}

void display() {

    char str;
    FILE *fp1, *fp2, *fp3;

    //input.txt of pass1
    printf("\n Input contents :\n\n");
    fp1 = fopen("input.txt", "r");
    str = fgetc(fp1);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp1);
    }
    fclose(fp1);

    //output of pass 1
    printf("\n\n Output contents: INTERMEDIATE :\n\n");
    fp2 = fopen("intermediate.txt", "r");
    str = fgetc(fp2);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp2);
    }
    fclose(fp2);

    // symtable of pass1
    printf("\n\n SYMTABLE :\n\n");
    fp3 = fopen("symtab.txt", "r");
    str = fgetc(fp3);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp3);
    }
    fclose(fp3);
}

