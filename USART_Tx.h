
#ifndef USART_TX_H_
#define USART_TX_H_
#include "ADC.h"
void UART_transmit_receive_init();
void UART_transmit(uint8_t data);
uint8_t UART_receive();
uint8_t UART_transmit_receive(uint8_t data);
void UART_transmit_Ascii(uint8_t*ptr,uint8_t size);
void UART_receive_Ascii(uint8_t size);



#endif /* USART_H_ */