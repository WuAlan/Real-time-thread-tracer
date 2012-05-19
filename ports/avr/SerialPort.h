
#define FOSC 16000000// Clock Speed
#define BAUD 57600
#define MYUBRR FOSC/16/BAUD-1



#define SendChar(c) USART_Transmit(c)

#define SerialInit(Baud) USART_Init(Baud);

void USART_Transmit(unsigned char data);
