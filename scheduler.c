#include "scheduler.h"
#include "printer.h"
#include "queue_rr.h"
#include "queue_sjf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #define VERBOSE
// uncomment for real-time
float randfrom(float min, float max) {
  float range = (max - min);
  float div = (float)RAND_MAX / range;
  return min + ((float)rand() / div);
}

void create_SCH(SCH *sch, size_t tasks_count, float k_interactive, float minI,
                float maxI, float minB, float maxB, float ExpectedFloating,
                float ChanceOfInteractive, float CLK) {
  CPU new_cpu;
  create_CPU(&new_cpu, CLK);
  srand((unsigned int)time(0));
  sch->cpu = new_cpu;
  sch->tasks_count = tasks_count;
  sch->k_interactive = k_interactive;
  create_queue(&sch->interactive);
  create_queue(&sch->background);
  sch->tasks_count_backup = tasks_count;
  sch->min_r_gen_rr = minI;
  sch->max_r_gen_rr = maxI;
  sch->min_r_gen_sjf = minB;
  sch->max_r_gen_sjf = maxB;
  sch->e_float = ExpectedFloating;
  sch->chance_of_i = ChanceOfInteractive;
}

void create_new_task(SCH *sch) {
  Process process;
  float remaining_time = 0;
  float expected_time = 0;
  if (randfrom((float)0.01, 1) >= sch->chance_of_i) {
    remaining_time = randfrom(sch->min_r_gen_rr, sch->max_r_gen_rr);
    expected_time =
        remaining_time + randfrom(sch->e_float * (float)(-1.0), sch->e_float);
    create_process(&process, expected_time, remaining_time, true,
                   sch->cpu.curr_tick, 0, WAITING);
    add_process_to_list(sch, process, RR_Q);

  } else {
    remaining_time = randfrom(sch->min_r_gen_sjf, sch->max_r_gen_sjf);
    expected_time =
        remaining_time + randfrom(sch->e_float * (float)(-1.0), sch->e_float);
    create_process(&process, expected_time, remaining_time, false,
                   sch->cpu.curr_tick, 0, WAITING);
    add_process_to_list(sch, process, SJF_Q);
  }
  sch->tasks_count--;
}

void choose_queue(SCH *sch) {
  if (sch->interactive.procs_count != 0 || sch->background.procs_count != 0) {
    Process next_interactive = get_next_proc_rr(sch);
    Process next_background = get_next_proc_sjf(sch);
    // interactive ticks / sum of interactive ticks and background ticks >=
    // interactive koef

    if (GET_K_INTERACTIVE(sch->cpu.curr_interactive_tick,
                          sch->cpu.curr_background_tick) >=
        sch->k_interactive) {
      if (next_background.curr_state != NOT_CREATED)
        sch->cpu.process =
            &sch->background.procs[sch->background.next_proc_index];
      else
        sch->cpu.process =
            &sch->interactive.procs[sch->interactive.next_proc_index];
    } else {
      if (next_interactive.curr_state != NOT_CREATED)
        sch->cpu.process =
            &sch->interactive.procs[sch->interactive.next_proc_index];
      else
        sch->cpu.process =
            &sch->background.procs[sch->background.next_proc_index];
    }
  } else {
    Process process;
    create_process(&process, 0, 0, 0, 0, 0, NOT_CREATED);
    sch->cpu.process = &process;
  }
}

void run_SCH(SCH *sch) {
  while (1) {
    if (sch->tasks_count > 0)
      create_new_task(sch);
    else if (sch->interactive.completed_procs_count +
                 sch->background.completed_procs_count ==
             sch->tasks_count_backup)
      break;

    choose_queue(sch);
    if (sch->cpu.process->curr_state != NOT_CREATED &&
        sch->cpu.process->curr_state != FINISHED) {
      sch->cpu.process->curr_state = WORKING;
      if (exec(&sch->cpu) == FINISHED) {
        if (sch->cpu.process->interactivity) {
#ifdef VERBOSE
          print_element(
              &sch->interactive.procs[sch->interactive.next_proc_index]);
#endif
          add_process_to_list(
              sch, sch->interactive.procs[sch->interactive.next_proc_index],
              RR_Q_DONE);
        } else {
#ifdef VERBOSE
          print_element(
              &sch->background.procs[sch->background.next_proc_index]);
#endif
          add_process_to_list(
              sch, sch->background.procs[sch->background.next_proc_index],
              SJF_Q_DONE);
        }

        sch->cpu.process = NULL;
      } else
        sch->cpu.process->curr_state = WAITING;
    }
  }
}