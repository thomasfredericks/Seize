
// Please read Seize.h for information about the liscence and authors

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Seize.h"

#define SEIZE_NONE 0
#define SEIZE_INT_COUNT 3
#define SEIZE_LONG_COUNT 5




SeizeSerial::SeizeSerial() {
	receivedCount = 0;
	expecting = SEIZE_NONE;
}



void SeizeSerial::write(uint8_t channel, int data) {
	// 192  | channel << 2 | 2 bits
	// 7 bits
	// 7 bits
	Serial.write( 192 |  ((channel & 15) << 2) |  (data & 3) );
	
	Serial.write( (data >> 2) & 127 );
	Serial.write( (data>>9) & 127 );
	
	
}

void SeizeSerial::write(uint8_t channel, long data) {
	// 128  | channel << 2 | type
	// 7 bits
	// 7 bits
	// 7 bits
	// 7 bits
	// 4 bits (3 high bits are unused)
	Serial.write( 128 | ( (channel & 15 ) << 2) );
	Serial.write( (data) & 127 );
	Serial.write( (data>>7) & 127 );
	Serial.write( (data>>14) & 127 );
	Serial.write( (data>>21) & 127 );
	Serial.write( (data>>28) & 127 );
	
	
}

uint8_t SeizeSerial::available( ) {
	 while ( Serial.available() ) {
				byte data = Serial.read();

				if ( data > 191 ) { 
						
						expecting = SEIZE_INT_COUNT;
						
						receivedChannel = (data & 0x3C) >> 2;
						buffer[0] =  (data & 0x03);
						receivedCount = 1;
/*
						if ( receivedCount == 3 ) {
								receivedData = buffer[0] | (buffer[1]<<7)
								| (buffer[2]<<14);
								receivedCount = 0;
								return 1;
						}

						receivedCount = 0;
*/

				}
				else if ( data > 127 ) { 
				
						if ( ( data & 3 ) == 0 ) {
							expecting = SEIZE_LONG_COUNT;
							receivedCount = 0;
							receivedChannel = (data & 0x3C) >> 2;
						} else {
							expecting = SEIZE_NONE;
						}
						
						/*
						if ( receivedCount == 5 ) {
								receivedChannel = (data & 0x3C) >> 2;
								receivedData = (long)buffer[0] | ((long)buffer[1]<<7)
								| ((long)buffer[2]<<14) | ((long)buffer[3]<<21)
								| ((long)buffer[4]<<28) ;
								receivedCount = 0;
								return 1;
						}

						receivedCount = 0;
						*/


				}
				else { // 127 and less
						if ( expecting > 0 ) {
							buffer[receivedCount] =  (data);
							receivedCount++;
							
							if ( receivedCount == expecting ) {
								if ( expecting == SEIZE_INT_COUNT ) {
									receivedData = buffer[0] | (buffer[1]<<2)
										| (buffer[2]<<9);
									return 1;
								} else { // expecting == SEIZE_LONG_COUNT
								
									receivedData =  buffer[4] ;
									receivedData = (receivedData << 7) | buffer[3];
									receivedData = (receivedData << 7) | buffer[2];
									receivedData = (receivedData << 7) | buffer[1];
									receivedData = (receivedData << 7) | buffer[0];
									
									/*
									receivedData = (((((((buffer[4] << 7) | buffer[3]) << 7) | buffer[2]) << 7) | buffer[1]) << 7) | buffer[0];
									*/
									return 1;
									
								}
							} 
						}

				}

		}

	return 0;
}
uint8_t SeizeSerial::channel() {
	return receivedChannel;
}
long SeizeSerial::data() {
	return  receivedData;
}

// Preinstantiate Object //////////////////////////////////////////////////////
SeizeSerial Seize = SeizeSerial();