/**
  simple stack based VM
**/

#include <stdio.h>
#include <stdbool.h>

bool running = true;
int ip = 0;
int sp = -1;

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
    return program[ip];
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            printf("done\n");
            break;
        }
        case PSH: {
          printf("push %d\n", program[ip+1]);
          stack[++sp] = program[++ip];
          break;
        }
        case POP: {
          int val_popped = stack[sp--];
          printf("popped %d\n", val_popped);
          break;
      }
      case ADD: {
          int a = stack[sp--];
          int b = stack[sp--];
          printf("add %d %d\n", a, b);
          int result = b + a;
          stack[++sp] = result;
          break;
      }
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
}
