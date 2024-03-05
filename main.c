#include "printer.h"
#include "process.h"
#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct param {
  float min_i;
  float max_i;
  float min_b;
  float max_b;
  float chance_i;
  float util_time_i;
  float expected_f;
  size_t count;
  bool skip;
  float clk;
};
typedef struct param Param;

int main(int argc, char *argv[]) {
  Param params = {3.0, 10.0, 2.0, 5.0, 0.5, (float)0.8, 1.5, 10, false, 1.0};
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-mini") == 0 && i + 1 < argc) {
      params.min_i = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-maxi") == 0 && i + 1 < argc) {
      params.max_i = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-minb") == 0 && i + 1 < argc) {
      params.min_b = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-maxb") == 0 && i + 1 < argc) {
      params.max_b = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-chancei") == 0 && i + 1 < argc) {
      params.chance_i = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-utilk") == 0 && i + 1 < argc) {
      params.util_time_i = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-expf") == 0 && i + 1 < argc) {
      params.expected_f = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-clk") == 0 && i + 1 < argc) {
      params.clk = (float)atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
      char *endptr;
      params.count = strtoul(argv[i + 1], &endptr, 10);
      if (*endptr != '\0') {
        exit(-1);
      }
      i++;
    } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      printf(
          "-mini <float>\t\t- Minimal interactive proccess remaining time\n");
      printf(
          "-maxi <float>\t\t- Maximum interactive proccess remaining time\n");
      printf("-minb <float>\t\t- Minimal background proccess remaining time\n");
      printf("-maxb <float>\t\t- Maximum background proccess remaining time\n");
      printf("-expf <float>\t\t- Jitter for min and max proccess remaining "
             "time\n");
      printf(
          "-chancei <float(0 to 1)>\t\t- Chance of born interactive process\n");
      printf(
          "-utilk <float(0 to 1)>\t\t- Target utilization time proportion\n");
      printf("-clk <float>\t\t- Clock speed k\n");
      printf("-c <size_t>\t\t- Count of proccesses\n");
      printf("-v \t\t- Version\n");
      printf("-h or --help \t\t- This help\n");
      params.skip = true;
    } else if (strcmp(argv[i], "-v") == 0) {
      printf("0.1 Release by @t3ry4|Terentiev I.D. KV-11|14\n");
      params.skip = true;
    }
  }
  if (!params.skip) {
    SCH sch1;
    create_SCH(&sch1, params.count, params.util_time_i, params.min_i,
               params.max_i, params.min_b, params.max_b, params.expected_f,
               params.chance_i, params.clk);
    run_SCH(&sch1);
    print_completed(&sch1);
  }
  return 0;
}