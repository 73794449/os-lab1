#include "queue_rr.h"
Process get_next_proc_rr(SCH *sch) {
  if (sch->interactive.procs_count != 0) {
    clean_from_finished(sch, RR_Q);
    if (sch->interactive.next_proc_index < sch->interactive.procs_count - 1) {
      sch->interactive.next_proc_index++;
    } else
      sch->interactive.next_proc_index = 0;

    return sch->interactive.procs[sch->interactive.next_proc_index];
  } else {
    Process process;
    create_process(&process, 0, 0, 0, 0, 0, NOT_CREATED);
    return process;
  }
}