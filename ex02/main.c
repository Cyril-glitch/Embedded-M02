/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/12 15:43:27 by cycolonn         ###   ########.fr       */
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
WDTCSR = Watchdog Timer Control Register
*/


char uart_rx(void)
{
    /* wait for the UDR0 (buffer) to be full(cf p.200)*/
    while (!(UCSR0A & (1 << RXC0)));

    /* return received data from buffer */
    return UDR0;
}

int main(void)
{
    uart_init();
    while (1)
    {
        uart_tx(uart_rx());
    }    
}