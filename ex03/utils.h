/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 11:19:44 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/12 17:22:43 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/*------------------------------------------------------------------------------*/

//REGISTRES ADRESSE

#define PORT_B  (*((volatile uint8_t *) 0x25))
#define PORT_D  (*((volatile uint8_t *) 0x2B))


#define DDR_B  (*((volatile uint8_t *) 0x24))
#define DDR_D  (*((volatile uint8_t *) 0x2A))

#define PIN_D (*(volatile uint8_t *) 0x29)


/*------------------------------------------------------------------------------*/

//TIMER

//#define F_CPU 16000000
#define PRESCALER 256
#define DUTYCYCLE 10
#define HZ1 ((F_CPU / PRESCALER) - 1)

void watchdog_2s(void);


/*------------------------------------------------------------------------------*/

//UART

#define UART_BAUDRATE 115200UL
#define MYUBRR (((F_CPU / (8UL * UART_BAUDRATE))) - 1)

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);

/*------------------------------------------------------------------------------*/

//BITWISE MACRO

#define SET(reg, pos) (reg |= (1U << pos))
#define SETFIELD(reg, len, start) ((reg) |= (((1U << (len)) - 1) << (start)))
#define CLEAR(reg, pos) (reg &= ~(1U << pos))
#define TOGGLE(reg, pos) (reg ^= (1U << pos))


/*------------------------------------------------------------------------------*/

//BIT STATUS
int is_set(uint8_t reg, int pos);

int is_press(uint8_t sw, int pos);

int is_release(uint8_t sw, int pos);

void ignite(volatile uint8_t *led, int pos);

void turnoff(volatile uint8_t *led, int pos);

/*------------------------------------------------------------------------------*/

//FALLING EDGE DETECTION

void increase_duty(volatile uint8_t *val);

void decrease_duty(volatile uint8_t *val);


#endif
