/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 11:21:28 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/12 15:22:37 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int is_set(uint8_t reg, int pos)
{
    return (reg & (1 << pos));
}

int is_press(uint8_t sw, int pos)
{
    return !(sw & (1 << pos));
}

int is_release(uint8_t sw, int pos)
{
    return (sw & (1 << pos));
}

void ignite(volatile uint8_t *led, int pos)
{
    volatile uint8_t* ddr = led - 1;
    SET(*led, pos);
    SET(*ddr, pos);
}

void turnoff(volatile uint8_t *led, int pos)
{
    volatile uint8_t* ddr = led - 1;
    CLEAR(*led, pos);
    CLEAR(*ddr, pos);
}


void decrease_duty(volatile uint8_t *val)
{
    static volatile uint8_t saved_state = 0;
    static volatile uint8_t cur_state = 0;

    cur_state = is_press(PIN_D, 4);                 // get cur bouton state
    if (cur_state > saved_state)                    // detect falling edge
    {
        if ((*val) >= 20)
            (*val) -= 10; 
    }
    saved_state = cur_state;                        // saved bouton state for next loop
}

void increase_duty(volatile uint8_t *val)
{
    static volatile uint8_t saved_state = 0;
    static volatile uint8_t cur_state = 0;

    cur_state = is_press(PIN_D, 2);                 // get cur bouton state
    if (cur_state > saved_state)                    // detect falling edge
    {
        if ((*val) <= 90)
            (*val) += 10;
    }
    saved_state = cur_state;                        // saved bouton state for next loop
}

void uart_init(void)
{
    /*Set baudrate prescaler (cf p.204)*/
    UBRR0H = (uint8_t)(MYUBRR >> 8);
    UBRR0L = (uint8_t)(MYUBRR);

    /* Enable double speed mode (cf p.199) */
    SET(UCSR0A, U2X0);

    /* enable transmitter (cf p.202)*/
    SET(UCSR0B,TXEN0);                       

    /* enable receiver (cf p.202)*/
    SET(UCSR0B,RXEN0);                       

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

void uart_printstr(const char* str)
{
    while(*str)
        uart_tx(*(str++));
}

void watchdog_2s(void)
{
    /* enable watchdog (cf p.64) */
    WDTCSR |= (1 << WDCE) | (1 << WDE);

    /* set the timeout signal (cf p.64)*/
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);
}