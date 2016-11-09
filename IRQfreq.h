#ifndef IRQfreq_h
#define IRQfreq_h
#include "Arduino.h"

//#define XTAL_FREQ 20000000
#define XTAL_FREQ 16000000

class IRQfreq{
  private:
  int Prescale;
  int PreCount;
  int LastFreq;
  public: 
  int Tcnt_1;
  void FreqSet(int f);
  bool CheckPrescale();
  void FreqInit();
  IRQfreq();
  ~IRQfreq();
};
#endif
