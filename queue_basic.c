#include "queue_basic.h"
#include "list_moves.h"
void create_queue(Queue *q) {
  q->procs = NULL;
  q->procs_count = 0;
  q->completed_procs = NULL;
  q->completed_procs_count = 0;
  q->next_proc_index = 0;
}
void clean_from_finished(Queue Q) {
  for (size_t i = 0; i < Q.procs_count; i++) {
    if (Q.procs[i].curr_state == FINISHED) {
      for (size_t k = i + 1; k < Q.procs_count; k++) {
        Q.procs[k - 1] = Q.procs[k];
      }
      Q.procs_count--;
      Process *new_procs = (Process *)malloc(Q.procs_count * sizeof(Process));
      for (size_t k = 0; k < Q.procs_count; k++) {
        new_procs[k] = Q.procs[k];
      }
    }
  }
}