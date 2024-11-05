#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <tof.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i;
  int iDistance;
  int model, revision;

  // For Raspberry Pi's, the I2C channel is usually 1
  // For other boards (e.g. OrangePi) it's 0
  i = tofInit(0, 0x29, 0); // dont set long range mode (closer precision)
  if (i != 1) {
    return -1; // problem - quit
  }
  printf("VL53L0X device successfully opened.\n");
  i = tofGetModel(&model, &revision);
  printf("Model ID - %d\n", model);
  printf("Revision ID - %d\n", revision);

  for (i = 0; i < 1200; i++) // read values 20 times a second for 1 minute
  {
    iDistance = tofReadDistance();
    if (iDistance < 4096) // valid range?
      printf("Distance = %dmm\n", iDistance);
    usleep(50000); // 50ms
  }

  return 0;
}
