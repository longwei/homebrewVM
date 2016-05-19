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
    REGISTER_SIZE
} Registers;

static int registers[REGISTER_SIZE];

#define SP (registers[SP])
#define IP (registers[IP])

int stack[256];

typedef enum {
    HLT,
    PSH,
    POP,
    ADD,
} InstructionSet;

const int program[] = {
    PSH, 5,
    PSH, 2,
    ADD,
    PSH, 10,
    PSH, 12,
    ADD,
    ADD,
    POP,
    HLT
};

int fetch() {
    return program[IP];
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            printf("done\n");
            break;
        }
        case PSH: {
            printf("push %d\n", program[IP+1]);
            stack[++SP] = program[++IP];
            break;
        }
        case POP: {
            printf("popped %d\n", stack[SP]);
            SP = SP -1;
            break;
        }
        case ADD: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];
            registers[C] = registers[B] + registers[A];
            printf("add %d %d = %d\n", registers[A], registers[B], registers[C]);
            stack[++SP] = registers[C];
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
