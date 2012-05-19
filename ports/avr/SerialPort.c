#include "SerialManager.h"
#include <avr/io.h>




void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8data,  */
	UCSR1C = (3<<UCSZ10);
} // USART_Init


void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) )
		;
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

