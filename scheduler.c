#include "scheduler.h"
#include "queue_basic.h"
#include "rr_queue.h"
#include "sjf_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randfrom(float min, float max) {
  float range = (max - min);
  float div = (float)RAND_MAX / range;
  return min + ((float)rand() / div);
}

void create_SCH(SCH *sch, size_t tasks_count, float k_interactive) {
  CPU new_cpu;
  create_CPU(&new_cpu);
  srand((unsigned int)time(0));
  sch->cpu = new_cpu;
  sch->tasks_count = tasks_count;
  sch->k_interactive = k_interactive;
  create_queue(&sch->interactive);
  create_queue(&sch->background);
  sch->tasks_count_backup = tasks_count;
}

void create_new_task(SCH *sch) {
  Process process;
  float remaining_time = 0;
  float expected_time = 0;
  if (randfrom((float)0.1, 1) >= RAND_BACKGROUND_TASK_GENERATOR_PROBABILITY) {
    remaining_time = randfrom(3.0, 10.0);
    expected_time = remaining_time + randfrom(-1.5, 1.5);
    create_process(&process, expected_time, remaining_time, true,
                   sch->cpu.curr_tick, 0, WAITING);
    add_process_to_list(sch, process, RR_Q);

  } else {
    remaining_time = randfrom(3.0, 10.0);
    expected_time = remaining_time + randfrom(-1.5, 1.5);
    create_process(&process, expected_time, remaining_time, false,
                   sch->cpu.curr_tick, 0, WAITING);
    add_process_to_list(sch, process, SJF_Q);
  }
  sch->tasks_count--;
}

void choose_queue(SCH *sch) {
  if (sch->interactive.procs_count != 0 || sch->background.procs_count != 0) {
    Process next_interactive = get_next_proc_rr(sch->interactive);
    Process next_background = get_next_proc_sjf(sch->background);
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
    if (sch->cpu.process->curr_state != NOT_CREATED) {
      sch->cpu.process->curr_state = WORKING;
      exec(&sch->cpu);
      if (sch->cpu.process->curr_state == FINISHED) {
        if (sch->cpu.process->interactivity) {
          add_process_to_list(
              sch, sch->interactive.procs[sch->interactive.next_proc_index],
              RR_Q_DONE);

        } else {
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