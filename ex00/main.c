/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/12 00:10:39 by cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"   

/*
UBRR = Usart Baudrate Register
UCSR = Usart Control and Status Register
TXEN = Transmiter Enable
UCSZ = Usart Control Size
UPMn = Usart Parity Mode
USBS = Usart Stop Bit Select
UDRn = Usart Data Buffer Register
UDRE = Usart Data Register Empty
*/

void uart_init(void)
{
    /*Set baudrate prescaler (cf p.204)*/
    UBRR0H = (uint8_t)(MYUBRR >> 8);
    UBRR0L = (uint8_t)(MYUBRR);

    /* Enable double speed mode (cf p.199) */
    SET(UCSR0A, U2X0);

    /* enable transmitter (cf p.202)*/
    SET(UCSR0B,TXEN0);                       

    /* set the size of the transmited data to 8 (cf p.202)*/
    SET(UCSR0C,UCSZ01);  
    SET(UCSR0C,UCSZ00);  

    /* disable parity (cf .203) */
    CLEAR(UCSR0C,UPM01);
    CLEAR(UCSR0C,UPM00);
    
    /* set the number of stop bits to one (cf p.203)*/
    CLEAR(UCSR0C,USBS0);
}

void uart_tx(char c)
{
    /* wait for UDRN (transmiter buffer) to be empty (cf p.200)*/
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

int main(void)
{
    uart_init();

    while (1)
    {
        uart_tx('Z');
        _delay_ms(1000);
    }

    return (0);
}