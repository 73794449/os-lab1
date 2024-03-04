#include "rr_queue.h"
#include "process.h"
Process get_next_proc_rr(INTERACTIVE_QUEUE Q) {
  if (Q.procs_count != 0) {
    clean_from_finished(Q);
    if (Q.next_proc_index < Q.procs_count)
      return Q.procs[Q.next_proc_index++];
    else
      return Q.procs[Q.next_proc_index = 0];
  } else {
    Process process;
    create_process(&process, 0, 0, 0, 0, 0, NOT_CREATED);
    return process;
  }
}