/*
 * usb.h
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
#ifndef USB_H
#define USB_H

#include <stdio.h>
#include "serial.h"
void usb_init( void );
int usb_haschar(void);
void usb_putc( uint8_t c);
uint8_t usb_getc(void);
void usb_puts(const char *s );

#endif
