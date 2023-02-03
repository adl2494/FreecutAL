/*
 * timer.c
 *
 * Timer 0 is used as overall (slow) event timer, as well sleep delay timer.
 * Timer 1 is used as solenoid PWM, through OC1B output
 * Timer 2 is used for stepper timing 
 * Timer 3 is used to generate tones on the speaker through OC3A output, 
 * period is adjusted for tone.
 *
 *
 * Copyright 2010 <freecutfirmware@gmail.com> 
 *
 * This file is part of FreecutAL.
 *
 * FreecutAL is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2.
 *
 * FreecutAL is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreecutAL. If not, see http://www.gnu.org/licenses/.
 *
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <string.h>
#include <stdio.h>
#include "timer.h"
#include "stepper.h"
#include "lcd.h"
static uint8_t count_Hz = 250;
static uint8_t count_25Hz = 10;
volatile uint8_t flag_Hz;
volatile uint8_t flag_25Hz;
static int current_pen_pressure; 
static int current_stepper_speed; 
static int last_pen_pressure;
static int last_stepper_speed;

/*
 * called @250 Hz, divide further in software for slow events 
 */
ISR( TIMER0_COMP_vect ) 
{
    if( --count_25Hz == 0 )
    {
        count_25Hz = 10;
        flag_25Hz = 1;
    }
    if( --count_Hz == 0 )
    {
	count_Hz = 250;
	flag_Hz = 1;
    }
}        

/*
 * Timer 2 compare match, update stepper motors.
 */
ISR( TIMER2_COMP_vect ) 
{
    stepper_tick( );
}        

/*
 * Turn on beeper. Hz specifies frequency of the tone.
 */
void beeper_on( int Hz )
{
    DDRE |= (1 << 3);
    OCR3A = (8000000L + Hz/2) / Hz - 1;
}

void beeper_off( void )
{
    DDRE &= ~(1 << 3);
}

/*
 * usleep: sleep (approximate/minimum) number of microseconds. We use timer0 
 * which runs at 62.50 kHz, or at 16 usec/tick. Maximum delay is about 2 
 * milliseconds . For longer delays, use msleep().
 *
 */
void usleep( int usecs )
{
    signed char end = TCNT0 + usecs / 16;

    while( (signed char) (TCNT0 - end) < 0 )
	continue;
}

void msleep( unsigned msecs )
{
    while( msecs-- != 0 )
	usleep( 1000 );
}

int timer_get_stepper_speed()
{
	return current_stepper_speed;
//	return OCR0A+1;
}

void beep()
{
	beeper_on( 1760 );
	msleep( 10 );
	beeper_off( );
	
}
void timer_set_stepper_speed( int delay )
{
	last_stepper_speed=current_stepper_speed;
    uint8_t prescaler = 4; // default 1:64 prescaler

    if (delay > MAX_STEPPER_SPEED_RANGES) {
	    delay = MAX_STEPPER_SPEED_RANGES;
	    } else if (delay < 1) {
	    delay = 1;
    }

    current_stepper_speed = delay;
    delay = (255 - (delay * 25)); // inverse
    TCCR2 &= ~7; // stop timer, and clear prescaler bit
    OCR2 = delay - 1;
    TCCR2 |= prescaler;
	lcd_report_speed();	
}

/**
 * Sets the pen pressure according to a value from MIN_PEN_PRESSURE to MAX_PEN_PRESSURE.
 * 
 * @param pressure Integer 
 */
int timer_get_pen_pressure()
{
	return current_pen_pressure;
}
void timer_set_pen_pressure(int pressure) {
	
	last_pen_pressure=current_pen_pressure;
    // pen pressure is displayed in single increment steps
    // but internally each step represents 50 usecs delay in pwm
    // MAX_PEN_PWM is the max value for the PWM, not the maximum pressure
    // maximum value of 500 is basically no pressure at all
    // it could go as high as 1000 but that is pointless
    // since anything between 500 and 1000 results in 6 volts
    // which the solenoid doesn't care about.

    if (pressure > MAX_CUTTER_P_RANGES) {
        pressure = MAX_CUTTER_P_RANGES;
    } else if (pressure < 1) {
        pressure = 1;
    }

    current_pen_pressure = pressure;
	
    unsigned pwm = (pressure) * ((MAX_PEN_PWM - MIN_PEN_PWM) / MAX_CUTTER_P_RANGES);
    OCR1B = (MAX_PEN_PWM - pwm);
	lcd_report_pressure();
}

/*
int timer_get_pen_pressure()
{
	return current_pen_pressure;
}							
void timer_set_pen_pressure( int pressure )
{
    if( pressure > 1023 )
*/
/*
 * Init timers 
 */
void timer_init( void )
{
    // set timer 0 for 250 Hz period
    TCCR0  = (1 << WGM01) | 6;     		// prescaler 1:256 -> 62.50 kHz
    OCR0   = 249; 		  		// 125 kHz / 250 = 250 Hz 
    TIMSK  = (1 << OCIE0); 	    		// enable OVF interrupt 

    // set timer 1, WGM mode 7, fast PWM 10 bit
    DDRB   |= (1 << 6);				// PB6 is PWM output
    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1B1);
    TCCR1B = (1 << WGM12) | 1;	
    OCR1B  = 1023;				// lowest pressure

    // set timer 2, variable period for stepper
    TCCR2  = (1 << WGM21) | 4;			// prescaler 1/256 -> 250 kHz
    OCR2   = 99;				// default speed 2.5k steps
    TIMSK |= (1 << OCIE2);			//

     // Timer 3, WGM mode 15 (1111), Fast PWM using OCR3A
     TCCR3A = (1 << COM3A0) | (1 << WGM31) | (1 << WGM30);
     TCCR3B = (1 << WGM33) | (1 << WGM32) | 1;
}
