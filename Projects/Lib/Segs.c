#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "Segs.h"

#define Segs_WLATCH PORTA &=(~0x01); PORTA |=0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |=0X02;


// setup ports to speak with 7-segs
void Segs_Init (void)
{
    //ensure port pins high
    PORTA |=0X03;
    
    //configure direction of port pins as outputs
    DDRA |=0X03;

    //configure direction of port pins as outputs
    DDRB=0Xff;
}

void Segs_Normal (unsigned char Addr, unsigned char Value, Segs_DPOption dp)
{
   //trim address to range
   Addr &=0x07; 
   
   //Bank A,Normal op, Decode,Hex,No Data Coming
   Addr |=0b01011000;
   
   //suppressing decimal point
   if(dp)
   {
    Value &=(~0x80);
   }
   else{
     Value |=0x80;
   }

   //present control byte
   PORTB = Addr;
   Segs_MH //present comman with mode high

   Segs_WLATCH //latch commmand

   //present data
   PORTB=Value;
   Segs_ML //present data with mode low

   Segs_WLATCH //latch data

}

// control segs manually
void Segs_Custom (unsigned char Addr, unsigned char Value)
{
    //trim address to range
   Addr &=0x07; 
   
   //Bank A,Normal op, Decode,Hex,No Data Coming
   Addr |=0b01111000;
   
//    //suppressing decimal point
//    if(dp)
//    {
//     Value &=(~0x80);
//    }
//    else{
//      Value |=0x80;
//    }

   //present control byte
   PORTB = Addr;
   Segs_MH //present comman with mode high

   Segs_WLATCH //latch commmand

   //present data
   PORTB=Value;
   Segs_ML //present data with mode low

   Segs_WLATCH //latch data
}