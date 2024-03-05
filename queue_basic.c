#include "queue_basic.h"
#include "list_moves.h"
void create_queue(Queue *q) {
  q->procs = NULL;
  q->procs_count = 0;
  q->completed_procs = NULL;
  q->completed_procs_count = 0;
  q->next_proc_index = 0;
}
