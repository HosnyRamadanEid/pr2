#include "USART_Tx.h"
void SWUART_init(uint32_t baudrate)
{
	UCSRC&=~(1<<UMSEL); // Async mode
	UCSRC |=(1<<UPM0)|(1<<UPM1); // Odd Parity Check
	UCSRC |=(1<<UCSZ0)|(1<<UCSZ1); // 8 bit character size
	UCSRC |=(1<<USBS0); // 2 stop bit
	UCSRB|=(1<<TXEN)|(1<<RXEN); // Enable Transmit ahd Receive Mode
	/* //#define MYUBRR (FOSC/(16*BAUD))-1 = 8*10^6 /16*9600 -1 = 51*/
	UBRRL = (uint8_t)(F_CPU/16/baudrate -1) ;    //send the low  8 bits of the UBRR = 51
	UBRRH = (uint8_t)((F_CPU/16/baudrate -1)<<8);//send the high 4 bits of the UBRR = 0
	UCSRA|=(1<<TXC);
	UCSRB|=(1<<UDRIE); // Enable Transmitinterrupt

}
void SWUART_send(uint8_t data)
{
while((UCSRA&(1<<UDRE))==0);
UDR= data ;
}
void  SWUART_recive(uint8_t * data)
{
	while((UCSRA&(1<<RXC))==0);
	UDR = *data;
}
uint8_t UART_transmit_receive(uint8_t data)
{
	while((UCSRA&(1<<UDRE))==0);
	UDR= data ;
	while((UCSRA&(1<<RXC))==0);
	 return UDR;
}

void UART_transmit_Ascii(uint8_t*ptr,uint8_t size)
{
	uint8_t i;
	for (i=0;i<size;i++)
	{
		UART_transmit(*ptr);
		lcd_out(0,i,ptr);
		ptr++;
	}
}
void UART_receive_Ascii(uint8_t size)
{
	uint8_t i;
	uint8_t arr[size];
	for (i=0;i<size;i++)
	{
		arr[i]= UART_receive();
		lcd_out(1,i,&arr[i]);
	}
}
