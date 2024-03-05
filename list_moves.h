#ifndef LIST_MOVES_H
#define LIST_MOVES_H
#include "process.h"
#include "scheduler_struct.h"
void resize_list(SCH *sch, unsigned short int to_list, size_t count);
void add_process_to_list(SCH *sch, Process process, unsigned short int to_list);
void clean_from_finished(SCH *sch, unsigned short int to_list);
#endif