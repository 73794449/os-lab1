#include "cpu.h"
#include "stdbool.h"

void create_CPU(CPU *cpu, float CLK) {
  cpu->process = NULL;
  cpu->curr_tick = 0;
  cpu->curr_interactive_tick = 0;
  cpu->curr_background_tick = 0;
  cpu->CLK = CLK;
}

void set_proc(CPU *cpu, Process *process) { cpu->process = process; }

unsigned short int exec(CPU *cpu) {
  cpu->curr_tick += cpu->CLK;
  if (cpu->process->interactivity) {
    cpu->curr_interactive_tick += cpu->CLK;
  } else {
    cpu->curr_background_tick += cpu->CLK;
  }

  execute(cpu->process, cpu->CLK);

  if (cpu->process->curr_state == FINISHED) {
    cpu->process->end_time = cpu->curr_tick;
    cpu->process->wait_time = cpu->process->end_time -
                              cpu->process->start_time -
                              cpu->process->work_time;
    return FINISHED;
  }

  return WAITING;
}