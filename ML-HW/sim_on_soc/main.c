#include "sim.h"

extern unsigned int _test_start;

volatile unsigned int *ecg_addr  = (volatile unsigned int *) 0x20140000; // DRAM @50000

int main(void) {
  int cls = inference(ecg_addr);
  *(&_test_start) = cls;
  return 0;
}
