#include <Seize.h>

/*
Control the debug LED through Seize channel 13.

SERIAL BAUD
=======================
57600

SEIZE RECEIVE
=======================
channel    data
13         sets digitalWrite of pin 13
*/



void setup()  {
  
        Serial.begin(57600);
        pinMode(13,OUTPUT);
        
}

void loop() {

        while ( Seize.available() ) {
               if ( Seize.channel() == 13 ) {
                 digitalWrite(13,Seize.data());
               }
        }

}


