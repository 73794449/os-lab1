#include <stdbool.h>
#include <stdlib.h>
#ifndef PROCESS_H
#define PROCESS_H

#define WAITING 0
#define WORKING 1
#define FINISHED 2
#define NOT_CREATED 3

#define RR_Q 0
#define RR_Q_DONE 1
#define SJF_Q 3
#define SJF_Q_DONE 4

struct process {
  size_t id;
  float expected_time;
  float remaining_time;
  bool interactivity;
  float start_time;
  float end_time;
  float work_time;
  float wait_time;
  unsigned short int curr_state;
};
typedef struct process Process;

void create_process(Process *process, float expected_time, float remaining_time,
                    bool interactivity, float start_time, float end_time,
                    unsigned short int state);
void execute(Process *process, float CLK);
#endif