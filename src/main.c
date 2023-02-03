/*
 * FreecutAL.c
 * main.c
 *
 * Created: 1/22/2023 2:00:55 PM
 * Author : AL
 * 
 * FreecutAL firmware, main program
 *
 * This source originally developed by  https://github.com/Arlet/Freecut
 * Further Developed by https://github.com/thetazzbot/FreeExpression
 * This Iteration by https://github.com/adl2494/FreecutAL/ 
 * This file is part of FreecutAL.
 *
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <inttypes.h>
#include <stdio.h>

#include "usb.h"
#include "keypad.h"
#include "lcd.h"				
#include "timer.h"
#include "stepper.h"
#include "cli.h"
#include "version.h"
#include "dial.h"
#include "hpgl.h"


void setup(void);


void setup(void)
{
	// Watchdogging disabled -- No use while debugging / testing 
	//wdt_enable( WDTO_30MS );
	timer_init( );
	keypad_init( );
	lcd_init();
	sei();	
	usb_init();
	stepper_init( );
	hpgl_init();
	dial_init( );
	sei();					// Start interrupts -- Motors will home immediately following this
	dial_poll();
	msleep(100);
	dial_poll();
	msleep(100);
	dial_poll();
	msleep(100);
	sync_states();
	//msleep(100);
	//usb_puts("\f");
	//usb_puts(VERSION);
	lcd_clear();
	fprintf( &lcd, "FreecutAL");
	sync_states();
	
}

int main( void )
{
	setup();
    while( 1 )
    {
        cli_poll( ); // polls ready bytes from USB  and processes them
		wdt_reset( );
		if( flag_25Hz )
		{
			flag_25Hz = 0;
			
			dial_poll( );  // polls the dials and processes their state
			keypad_poll( ); // polls the keypad and executes functions
			}
		if( flag_Hz )
		{
			flag_Hz = 0;
		}
    }
	//return 0;
}
