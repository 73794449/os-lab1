#include "process.h"
#include "scheduler_struct.h"
#include <stdlib.h>
size_t last_id = 0;
void create_process(Process *process, float expected_time, float remaining_time,
                    bool interactivity, float start_time, float end_time,
                    unsigned short int state) {
  process->id = last_id++;
  process->expected_time = expected_time;
  process->remaining_time = remaining_time;
  process->interactivity = interactivity;
  process->start_time = start_time;
  process->end_time = end_time;
  process->curr_state = state;
}
void execute(Process *process) {
  if (process->remaining_time > 0)
    process->remaining_time--;

  if (process->remaining_time <= 0) {
    process->remaining_time = 0;
    process->curr_state = FINISHED;
  }
}
