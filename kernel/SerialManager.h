#include <stdarg.h>
#include <stdlib.h>
#include "SerialPort.h"

void SendString(char * StringBuffer);
void SendChar(unsigned char data);

void SerialInit(unsigned int Baud);


void uart_print(const char * format, ...);
