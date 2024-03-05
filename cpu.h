#include "process.h"
#include <stdbool.h>
#ifndef CPU_H
#define CPU_H
struct cpu {
  Process *process;
  float curr_tick;
  float curr_interactive_tick;
  float curr_background_tick;
  bool running;
  float CLK;
};
typedef struct cpu CPU;

void create_CPU(CPU *cpu, float CLK);
void set_proc(CPU *cpu, Process *process);
unsigned short int exec(CPU *cpu);

#endif