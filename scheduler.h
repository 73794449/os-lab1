#ifndef SCHEDULER_H
#define SCHEDULER_H
#define RAND_BACKGROUND_TASK_GENERATOR_PROBABILITY 0.5
#define INTERACTIVE_BOOL 1
#define BACKGROUND_BOOL 0
#define GET_K_INTERACTIVE(x, y) x / (x + y)
#include "list_moves.h"

void create_SCH(SCH *sch, size_t tasks_count, float k_interactive, float minI,
                float maxI, float minB, float maxB, float ExpectedFloating,
                float ChanceOfInteractive, float CLK);
void add_to_completed(SCH *sch, Process *process);
void run_SCH(SCH *sch);
#endif