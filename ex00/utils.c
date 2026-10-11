/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 11:21:28 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/10 13:10:12 by cyril            ###   ########.fr       */
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

