#include "sjf_queue.h"
Process get_next_proc_sjf(BACKGROUND_QUEUE Q) {
  if (Q.procs_count != 0) {
    if (Q.procs[Q.next_proc_index].curr_state == FINISHED) {
      clean_from_finished(Q);
      float min = Q.procs[0].expected_time;
      Q.next_proc_index = 0;
      for (size_t i = 0; i < Q.procs_count; i++) {
        if (min > Q.procs[i].expected_time) {
          min = Q.procs[i].expected_time;
          Q.next_proc_index = i;
        }
      }
    }
    return Q.procs[Q.next_proc_index];
  } else {
    Process process;
    create_process(&process, 0, 0, 0, 0, 0, NOT_CREATED);
    return process;
  }
}