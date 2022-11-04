#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

#include "PIT.h"

// other includes, as *required* for this implementation

/////////////////////////////////////////////////////////////////////////////
// local prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// library variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// function implementations
/////////////////////////////////////////////////////////////////////////////
int PIT_Init(unsigned long bus, ChanelSelection chan, unsigned long intervalus)
{

  unsigned short fac8 = 1;
  unsigned long cycles = (unsigned long)(bus / ((unsigned long)1E6f / intervalus));

  if (cycles > 16777215ul) // 2^24-1
    return -1;

  while (fac8 < 256 && ((cycles % fac8 != 0) || (cycles / fac8 > 65535)))
    ++fac8;

  if (fac8 > 255)
    return -1;

  if (chan == 0)
  {
    PITMTLD0 = (byte)(fac8 - 1);
    PITLD0 = (unsigned short)(cycles / fac8 - 1);
  }
  else if (chan == 1)
  {
    PITMTLD1 = (byte)(fac8 - 1);
    PITLD1 = (unsigned short)(cycles / fac8 - 1);
      PITMUX_PMUX1=1;
  }
  // enable chan 0
  if (chan == 1)
  {
    PITCE_PCE1 = 1;
  }
  else
  {
    PITCE_PCE0 = 1;
  }

  // finally, enable periodic interrupt, normal in wait, PIT stalled in freeze
  // PIT still runs in wait mode (relevant next course)
  // PIT stalls when debugging so PIT events don’t pile up while stepping

  PITCFLMT = PITCFLMT_PITE_MASK | PITCFLMT_PITFRZ_MASK;
  return 0;
}

void PIT_Sleep(unsigned long  bus, ChanelSelection chan, unsigned int delay)
{
  // configure channel to chan, 1ms intervals
  (void)PIT_Init(bus, chan, 1000);
  // enter the blocking loop to kill ms time
  while (delay)
  {
    // kill 1ms
    if (chan == 1)
    {
      while (!PITTF_PTF1)
        ;
      // clear channel flag for channel
      PITTF = PITTF_PTF1_MASK;
      delay--;
    }
     else if(chan==0){
    while (!PITTF_PTF0)
        ;
      // clear channel flag for channel0
      PITTF = PITTF_PTF0_MASK;
      delay--;


   }
  }
 
}