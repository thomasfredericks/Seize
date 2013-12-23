#include <Seize.h>

/*
SERIAL BAUD
=======================
57600

SEIZE RECEIVE
=======================
channel  data
13       sets digitalWrite on pin 13


SEIZE SEND
=======================
channel  data
0        result of analogRead(0)
1        result of analogRead(1)
2        result of analogRead(2)  
3        result of analogRead(3)
4        result of analogRead(4)
5        result of analogRead(5)
6        result of millis()
*/



unsigned long timeStamp;


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

        if ( millis() >= timeStamp + 10 ) {
                timeStamp = millis();

                for ( int i =0 ; i < 6 ; i++ )  {
                        Seize.write(i,analogRead(i));
                }

                Seize.write(6,(long) millis());

        }

}


