#include "queue_sjf.h"
Process get_next_proc_sjf(SCH *sch) {
  if (sch->background.procs_count != 0) {
    if (sch->background.procs[sch->background.next_proc_index].curr_state ==
        FINISHED) {
      clean_from_finished(sch, SJF_Q);
      float min = sch->background.procs[0].expected_time;
      sch->background.next_proc_index = 0;
      for (size_t i = 0; i < sch->background.procs_count; i++) {
        if (min > sch->background.procs[i].expected_time) {
          min = sch->background.procs[i].expected_time;
          sch->background.next_proc_index = i;
        }
      }
    }
    return sch->background.procs[sch->background.next_proc_index];
  } else {
    Process process;
    create_process(&process, 0, 0, 0, 0, 0, NOT_CREATED);
    return process;
  }
}