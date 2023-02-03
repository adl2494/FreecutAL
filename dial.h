/*
 * dial.h
 *
 * Interface for front panel dials.
 *
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

#ifndef DIALS_H
#define DIALS_H

// Enum to declare the ADC input channel numbers
enum
{ 
    DIAL_SIZE =0,		// only on some machines this is a potentiometer, most have a quadrature encoder for the RH dial
    DIAL_SPEED,
    DIAL_PRESSURE,
    MAX_DIALS
};


extern void dial_poll( void );
extern void dial_init( void );

#endif
