#include "process.h"
#include <stdlib.h>
#ifndef QUEUE_BASIC
#define QUEUE_BASIC
struct queue {
  Process *procs;
  size_t procs_count;
  Process *completed_procs;
  size_t completed_procs_count;
  size_t next_proc_index;
};
typedef struct queue Queue;
void create_queue(Queue *q);
void clean_from_finished(Queue Q);
#endif