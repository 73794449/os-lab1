#include "cpu.h"
#include "rr_queue.h"
#include "sjf_queue.h"
#include <stdlib.h>
#ifndef SCHEDULER_STRUCT_H
#define SCHUDULER_STRUCT_H

struct scheduler {
  size_t tasks_count;
  size_t tasks_count_backup;
  float k_interactive;
  INTERACTIVE_QUEUE interactive;
  BACKGROUND_QUEUE background;
  CPU cpu;
};
typedef struct scheduler SCH;
#endif