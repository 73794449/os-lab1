#include "printer.h"
#include "process.h"
#include <stdio.h>
#include <stdlib.h>
int cmpfunc(const void *a, const void *b) {
  Process *pA = (Process *)a;
  Process *pB = (Process *)b;
  if (pA->id < pB->id)
    return -1;
  else if (pA->id > pB->id)
    return 1;
  else
    return 0;
}
Process *getAll(SCH *sch) {
  Process *elementsForOut = malloc(sch->tasks_count_backup * sizeof(Process));
  if (elementsForOut == NULL)
    exit(-1);
  for (size_t i = 0; i < sch->interactive.completed_procs_count; i++)
    elementsForOut[i] = sch->interactive.completed_procs[i];
  for (size_t i = 0; i < sch->background.completed_procs_count; i++)
    elementsForOut[i + sch->interactive.completed_procs_count] =
        sch->background.completed_procs[i];
  qsort(elementsForOut, sch->tasks_count_backup, sizeof(Process), cmpfunc);
  return elementsForOut;
}
void print_completed(SCH *sch) {
  Process *elements = getAll(sch);
  printf("#####################################################################"
         "#######\n");
  printf("|ID|I|Start time|End time  |Expected time|Utilized time|Work "
         "time|Wait time|\n");
  printf("|--|-|----------|----------|-------------|-------------|---------|---"
         "------|\n");
  for (size_t i = 0; i < sch->tasks_count_backup; i++) {
    printf("|%2lu|", elements[i].id);
    if (elements[i].interactivity)
      printf("I|");
    else
      printf("B|");
    printf("%10.1f|%10.1f|%13.3f|%13.1f|%9.1f|%9.1f|\n", elements[i].start_time,
           elements[i].end_time, elements[i].expected_time,
           elements[i].end_time - elements[i].start_time, elements[i].work_time,
           elements[i].wait_time);
  }
  printf("#####################################################################"
         "#######\n");
  float avg_wait = 0;
  float avg_full = 0;
  float avg_i_wait = 0;
  float avg_b_wait = 0;
  for (size_t i = 0; i < sch->tasks_count_backup; i++) {
    avg_wait += elements[i].wait_time;
    if (elements[i].interactivity)
      avg_i_wait += elements[i].wait_time;
    else
      avg_b_wait += elements[i].wait_time;
    avg_full += elements[i].end_time - elements[i].start_time;
  }
  avg_wait = avg_wait / (float)sch->tasks_count_backup;
  avg_full = avg_full / (float)sch->tasks_count_backup;
  avg_i_wait = avg_i_wait / (float)sch->tasks_count_backup;
  avg_b_wait = avg_b_wait / (float)sch->tasks_count_backup;
  printf("AVG Wait time: %.2f\n", avg_wait);
  printf("AVG Utilized time: %.2f\n", avg_full);
  printf("AVG Wait time INTERACTIVE: %.2f\n", avg_i_wait);
  printf("AVG Wait time BACKGROUND: %.2f\n", avg_b_wait);
}

void print_element(Process *proc) {
  printf("ID = %5lu|RTime = %10f|ETime = %10f|Inter = %d|STime = %8f|ETime = "
         "%10f\n",
         proc->id, proc->remaining_time, proc->expected_time,
         proc->interactivity, proc->start_time, proc->end_time);
}