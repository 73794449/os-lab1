#include "process.h"
#include "scheduler_struct.h"
#include <stdlib.h>
size_t last_id = 1;
void create_process(Process *process, float expected_time, float remaining_time,
                    bool interactivity, float start_time, float end_time,
                    unsigned short int state) {
  if (state != NOT_CREATED)
    process->id = last_id++;
  else
    process->id = 0;
  process->expected_time = expected_time;
  process->remaining_time = remaining_time;
  process->interactivity = interactivity;
  process->start_time = start_time;
  process->end_time = end_time;
  process->curr_state = state;
  process->work_time = 0;
  process->wait_time = 0;
}
void execute(Process *process, float CLK) {
  if (process->remaining_time > 0) {
    process->remaining_time -= CLK;
    process->work_time += CLK;
  }

  if (process->remaining_time <= 0) {
    process->remaining_time = 0;
    process->curr_state = FINISHED;
  }
}
