#include "cpu.h"
#include "queue_basic.h"
#include <stdlib.h>
#ifndef SCHEDULER_STRUCT_H
#define SCHUDULER_STRUCT_H

struct scheduler {
  size_t tasks_count;
  size_t tasks_count_backup;
  float k_interactive;
  Queue interactive;
  Queue background;
  CPU cpu;
  float min_r_gen_rr;
  float min_r_gen_sjf;
  float max_r_gen_rr;
  float max_r_gen_sjf;
  float e_float;
  float chance_of_i;
};
typedef struct scheduler SCH;
#endif