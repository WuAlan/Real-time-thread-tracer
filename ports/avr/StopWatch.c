#include <avr/interrupt.h>
#include "StopWatch.h"

static unsigned long Overflow_Time=0;
ISR(TIMER3_OVF_vect)
{
	Overflow_Time++;
	TCNT3=0x0000;
}
 
void InitWatch()
{
	TIMSK3=(1<<TOIE3);
	TCCR3B=(1<<CS31);//f=2MHZ     0.5us each
//	TCCR3B=(0<<CS31)|(1<<CS32)|(1<<CS30);//f=1024/16MHZ 64us each
	TCCR3B|=1<<WGM32;

}
unsigned long GetTime()
{
	uint16_t t=TCNT3;
	unsigned long result=0;
	result=(Overflow_Time*65535+t)/2;
	return result;

}



