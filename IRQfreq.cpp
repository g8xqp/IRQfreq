#include <IRQfreq.h>
//#define MAXFREQ 7000
#define MAXFREQ 30000
void IRQfreq::FreqSet(int f){
  int Freq;
  if (f!=LastFreq){
    LastFreq=f;
    switch (f){
    case 0:
    case 1:
      Prescale=2000;
      Freq=2000;
      break;
    case 2 ... 499:
      Prescale=2000/f;
      Freq=f*Prescale;
      break;
    case 500 ... (MAXFREQ - 1):
      Freq=f;
      Prescale=1;
      break;
    default:// (max 30kHz? default 7kHz)
      Freq=MAXFREQ;
      Prescale=1;
      break;
    }
    Tcnt_1=65536-XTAL_FREQ/Freq;
  }
  
bool IRQfreq::CheckPrescale(){
  PreCount++;
  if (PreCount>=Prescale){
    PreCount=0;
    return(true);
  } else {
    return(false);
  }
}

#define SETBIT(x) ( 1 << x)
void IRQfreq::FreqInit(){
    FreqSet(1000); 
    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = Tcnt_1;
    TCCR1B |= SETBIT(CS10);   // hardware prescalar div1 
    TIMSK1 |= SETBIT(TOIE1);  // enable timer overflow interrupt
    interrupts();             // enable all interrupts
}
#undef SETBIT

IRQfreq::IRQfreq():PreCount(0),LastFreq(0){}
IRQfreq::~IRQfreq(){}

// ISR(TIMER_OVF_vect){
//   TCNT1 = IRQfreq.Tcnt_1;
// if interrupt frequency above 500, do not need to test prescale
//   if(IRQfreq.CheckPrescale()){
//
//    put interrupt code here
//
//   }
// }
