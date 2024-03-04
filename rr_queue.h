#include "process.h"
#include "queue_basic.h"
#include <stdlib.h>
#ifndef RR_QUEUE_H
#define RR_QUEUE_H
typedef Queue INTERACTIVE_QUEUE; // Variant 8
Process get_next_proc_rr(INTERACTIVE_QUEUE Q);
#endif