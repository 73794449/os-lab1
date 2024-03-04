#include "process.h"
#include "queue_basic.h"
#include <stdlib.h>
#ifndef SJF_QUEUE_H
#define SJF_QUEUE_H
typedef Queue BACKGROUND_QUEUE; // Variant 8
Process get_next_proc_sjf(BACKGROUND_QUEUE Q);
#endif