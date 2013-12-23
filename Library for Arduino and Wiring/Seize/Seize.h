
/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */



/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 Main code by Thomas O Fredericks (tof@t-o-f.info)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef seize_h
#define seize_h

#include <inttypes.h>


class SeizeSerial {
public:
	SeizeSerial();
	//void write(uint8_t channel, uint8_t data)
	void write(uint8_t channel, int data);
	void write(uint8_t channel, long data);
	uint8_t available( );
	uint8_t channel();
	long data();

private:

	uint8_t buffer[6];
	uint8_t receivedChannel;
	uint8_t receivedCount;
	long receivedData;
	uint8_t expecting;

} ; 

extern SeizeSerial Seize;

#endif