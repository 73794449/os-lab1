#include "list_moves.h"
void resize_list(SCH *sch, unsigned short int to_list, size_t count) {
  switch (to_list) {
  case RR_Q:
    sch->interactive.procs =
        (Process *)realloc(sch->interactive.procs, sizeof(Process) * count);
    break;
  case RR_Q_DONE:
    sch->interactive.completed_procs = (Process *)realloc(
        sch->interactive.completed_procs, sizeof(Process) * count);
    break;
  case SJF_Q:
    sch->background.procs =
        (Process *)realloc(sch->background.procs, sizeof(Process) * count);
    break;
  case SJF_Q_DONE:
    sch->background.completed_procs = (Process *)realloc(
        sch->background.completed_procs, sizeof(Process) * count);
    break;
  }
}
void add_process_to_list(SCH *sch, Process process,
                         unsigned short int to_list) {
  switch (to_list) {
  case RR_Q:
    sch->interactive.procs_count++;
    resize_list(sch, to_list, sch->interactive.procs_count);
    sch->interactive.procs[sch->interactive.procs_count - 1] = process;
    break;
  case RR_Q_DONE:
    sch->interactive.completed_procs_count++;
    resize_list(sch, to_list, sch->interactive.completed_procs_count);
    sch->interactive
        .completed_procs[sch->interactive.completed_procs_count - 1] = process;
    break;
  case SJF_Q:
    sch->background.procs_count++;
    resize_list(sch, to_list, sch->background.procs_count);
    sch->background.procs[sch->background.procs_count - 1] = process;
    break;
  case SJF_Q_DONE:
    sch->background.completed_procs_count++;
    resize_list(sch, to_list, sch->background.completed_procs_count);
    sch->background.completed_procs[sch->background.completed_procs_count - 1] =
        process;
    break;
  };
}
void clean_from_finished(SCH *sch, unsigned short int to_list) {
  if (to_list == RR_Q) {
    for (size_t i = 0; i < sch->interactive.procs_count; i++) {
      if (sch->interactive.procs[i].curr_state == FINISHED) {
        for (size_t k = i + 1; k < sch->interactive.procs_count; k++) {
          sch->interactive.procs[k - 1] = sch->interactive.procs[k];
        }
        sch->interactive.procs_count--;
        Process *new_procs =
            (Process *)malloc(sch->interactive.procs_count * sizeof(Process));
        for (size_t k = 0; k < sch->interactive.procs_count; k++) {
          new_procs[k] = sch->interactive.procs[k];
        }
      }
    }
  } else {
    for (size_t i = 0; i < sch->background.procs_count; i++) {
      if (sch->background.procs[i].curr_state == FINISHED) {
        for (size_t k = i + 1; k < sch->background.procs_count; k++) {
          sch->background.procs[k - 1] = sch->background.procs[k];
        }
        sch->background.procs_count--;
        Process *new_procs =
            (Process *)malloc(sch->background.procs_count * sizeof(Process));
        for (size_t k = 0; k < sch->background.procs_count; k++) {
          new_procs[k] = sch->background.procs[k];
        }
      }
    }
  }
}