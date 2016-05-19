/**
simple stack based VM
**/

#include <stdio.h>
#include <stdbool.h>

bool running = true;

typedef enum {
    // GENERAL PURPOSE
    A,
    B,
    C,
    D,
    E,
    F,
    //INSTRUCTION POINTER
    IP,
    // STACK POINTER
    SP,
    REGISTER_SIZE //hack for get current register size
} Registers;

static int registers[REGISTER_SIZE];
// bool is_jmp = false;

#define SP (registers[SP])
#define IP (registers[IP])

int stack[256];

typedef enum {
    HLT, // 0 -- hlt :: halts program
    PSH, // 1 -- psh val :: pushes <val> to stack
    POP, // 2 -- pop :: pops value from stack
    ADD, // 3 -- add :: adds top two vals on stack
    MUL, // 4 -- mul :: multiplies top two vals on stack
    DIV, // 5 -- div :: divides top two vals on stack
    SUB, // 6 -- sub :: subtracts top two vals on stack
    MOV, // 7 -- mov reg_a, reg_b :: movs the value in reg_a to reg_b
    SET, // 8 -- set reg, val :: sets the reg to value
    IF,  // 9 - if reg val ip :: if the register == val branch to the ip
    IFN, // 10 - ifn reg val ip :: if the register != val branch to the ip
    GLD, // 11 -- gld reg :: loads a register to the stack
    GPT, // 12 -- gpt reg :: pushes top of stack to the given register
    NOP,
} InstructionSet;

const int instructions[] = {
    SET, A, 21,     // 3
    GLD, A,         // 5
    PSH, 1,         // 7
    SUB,            // 8
    GPT, A,         // 10
    IFN, A, 0, 2,        // 14
    HLT
};

int fetch() {
    return instructions[IP];
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            printf("done\n");
            break;
        }
        case PSH: {
            printf("push %d\n", instructions[IP+1]);
            stack[++SP] = instructions[++IP];
            break;
        }
        case POP: {
            printf("popped %d\n", stack[SP]);
            SP = SP -1;
            break;
        }
        //arithmetic
        case ADD: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];
            registers[C] = registers[B] + registers[A];
            printf("add %d %d = %d\n", registers[A], registers[B], registers[C]);
            stack[++SP] = registers[C];
            break;
        }
        case SUB: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];
            registers[C] = registers[B] - registers[A];
            printf("add %d %d = %d\n", registers[A], registers[B], registers[C]);
            stack[++SP] = registers[C];
            break;
        }
        case DIV: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];
            registers[C] = registers[B] / registers[A];
            printf("add %d %d = %d\n", registers[A], registers[B], registers[C]);
            stack[++SP] = registers[C];
            break;
        }
        case MUL: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];
            registers[C] = registers[B] * registers[A];
            printf("add %d %d = %d\n", registers[A], registers[B], registers[C]);
            stack[++SP] = registers[C];
            break;
        }

        //register operations
        case MOV: {
            printf("move %d\n", stack[SP]);
            registers[instructions[IP + 2]] = registers[instructions[IP + 1]];
            IP = IP + 2;
            break;
        }
        case SET: {
            printf("set %d\n", stack[SP]);
            registers[instructions[IP + 1]] = instructions[IP + 2];
            IP = IP + 2;
            break;
        }
        case IF: {
            printf("IF\n");
            printf("%d\n", registers[instructions[IP + 1]]);
            printf("%d\n", registers[instructions[IP + 2]]);
            if (registers[instructions[IP + 1]] == instructions[IP + 2]) {
                IP = instructions[IP + 3];
                // is_jmp = true;
            }
            else{
                IP = IP + 3;
            }
            break;
        }
        case IFN: {
            printf("IFN\n");
            if (registers[instructions[IP + 1]] != instructions[IP + 2]) {
                IP = instructions[IP + 3];
            }
            else {
                IP = IP + 3;
            }
            break;
        }
        case GLD: {
            printf("GLD\n");
            SP = SP + 1;
            IP = IP + 1;
            stack[SP] = registers[instructions[IP]];
            break;
        }
        case GPT: {
            printf("GPT\n");
            registers[instructions[IP + 1]] = stack[SP];
            IP = IP + 1;
            break;
        }
        case NOP: {
            printf("do nothing\n");
            break;
        }
        default: {
            printf("unknown instruction %d\n", instr);
            break;
        }
    }
}

int main() {
    SP = -1;
    while (running) {
        eval(fetch());
        IP++;
    }
}
