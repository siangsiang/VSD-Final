#include "sim.h"

extern unsigned int _test_start;

volatile unsigned int *ecg_addr  = (volatile unsigned int *) 0x20140000; // DRAM @50000

int main(void) {
  unsigned int buf[360];
  for (int i = 0; i < 360; ++i) {
    buf[i] = ecg_addr[i];
  }
  int cls = inference(buf);
  *(&_test_start) = cls;
  return 0;
}
