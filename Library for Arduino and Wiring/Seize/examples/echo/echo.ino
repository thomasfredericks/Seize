#include <Seize.h>

/*
SERIAL BAUD
=======================
57600

SEIZE RECEIVE & SEND
=======================
Simple echo of anything received

*/



void setup()  {
  
        Serial.begin(57600);
        
}

void loop() {

        while ( Seize.available() ) {
               
               Seize.write( Seize.channel(), fuck );
        }

}


