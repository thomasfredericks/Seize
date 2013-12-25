#include <Seize.h>

/*
SERIAL BAUD
=======================
57600

SEIZE RECEIVE & SEND
=======================
Simple echo of anything received
Also send out a debug message through Serial.print and Serial.println

*/



void setup()  {
  
        Serial.begin(57600);
        
}

void loop() {

        while ( Seize.available() ) {
               
               Seize.write( Seize.channel(), Seize.data() );
               
               // You can still debug messages with Serial.print and Serial.println:
               Serial.print("Received : channel ");
               Serial.print(Seize.channel());
               Serial.print(" and data ");
               Serial.print(Seize.data());
               Serial.println();
               
        }

}


