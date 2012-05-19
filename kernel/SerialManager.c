#include "SerialManager.h"
void SendString(char * StringBuffer)
{
	while(*StringBuffer)
	{
		SendChar(*StringBuffer++);
	}
	SendChar('\n');
}


void uart_print(const char * format, ...)
{
	va_list arg;
    //int done = 0;

    va_start (arg, format);

	while( *format != '\0')
	{
		if( *format == '%')
        {
		 	if( *(format+1) == 'c' )
			{
				char c = (char)va_arg(arg, int);
				SendChar(c);
				format+=2;
			}
			else if(*(format+1) == 'u'&& *(format+2) == 'd')
			{
				char store[20];
                unsigned int i = va_arg(arg,unsigned int);
                char * str = store;
                itoa(i, store,10);
				while( *str != '\0') 
					SendChar(*str++); 
				format+=3;
			}
			else if( *(format+1) == 'x')
			{
				char store[20];
				int i = va_arg(arg, int);
                char * str = store;
                itoa(i, store, 16);
                while( *str != '\0') 
					SendChar(*str++); 
				format+=2;
			}
			else if( *(format+1) == 'p')
			{
				char store[20];
				long i = va_arg(arg, long);
                char * str = store;
                ltoa(i, store, 16);
                while( *str != '\0') 
					SendChar(*str++); 
				format+=2;
			}
			else if( *(format+1) == 's' )
            {
                char* str = va_arg(arg, char*);
                while( *str != '\0') 
					SendChar(*str++);
				format+=2;
            }
			else if(*(format+1) == 'u' && *(format+2) == 'l' )
            {
				char store[20];
                unsigned long i = va_arg(arg,unsigned long);
                char * str = store;
                ultoa(i, store,10);
				while( *str != '\0') 
					SendChar(*str++); 
				format+=3;
            }
		}
		else
		{
			SendChar(*format++);
		}
	}
 	va_end(arg);   

}
