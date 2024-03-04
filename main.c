#include "printer.h"
#include "process.h"
#include "scheduler.h"

int main() {
  SCH sch1;
  create_SCH(&sch1, 10, (float)0.8);
  run_SCH(&sch1);
}