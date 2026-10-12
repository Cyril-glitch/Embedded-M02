/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/12 17:42:23 by cycolonn         ###   ########.fr       */
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

void interuption_init(void)
{
    /*Global Interrupt Enable (cf p.20)*/
    SET(SREG, SREG_I);

    /*enables interrupt on the RXCn Flag (cf p.201)*/
    SET(UCSR0B, RXCIE0);
}

char switch_case(char c)
{
    if (c >= 'a' && c <= 'z')
        c -= 32;
    else if (c >= 'A' && c <= 'Z')
        c += 32;
    return c;
}

SIGNAL(USART_RX_vect)
{
        uart_tx(switch_case(UDR0));
}

int main(void)
{      
    uart_init();
    interuption_init();
    while (1);
}