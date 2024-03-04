#include "cpu.h"
void create_CPU(CPU *cpu) {

  cpu->process = NULL;
  cpu->curr_tick = 0;
  cpu->curr_interactive_tick = 0;
  cpu->curr_background_tick = 0;
}
void set_proc(CPU *cpu, Process *process) { cpu->process = process; }
void exec(CPU *cpu) {
  cpu->curr_tick++;
  if (cpu->running) {
    if (cpu->process->interactivity)
      cpu->curr_interactive_tick++;
    else
      cpu->curr_background_tick++;
  }
  execute(cpu->process);

  if (cpu->process->curr_state == FINISHED) {
    cpu->process->end_time = cpu->curr_tick;
  }
}