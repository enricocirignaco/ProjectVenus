/*
  IR Transmitter V 1.1
  Sony Bravia 
  Turn ON/OFF code = 0xA90 12 bits
  
  IR LED must use Pin #3
*/

#include <IRremote.h>

const int ButtonPin = 7;

// Create IR Send Object
IRsend irsend;

void setup()
{
  pinMode(ButtonPin, INPUT);
}

void loop() {
  
  // If button is pressed send power code command
   if (digitalRead(ButtonPin)) {
    irsend.sendSony(0xa90, 12);
  }
      
  // Add a small delay before repeating
  delay(30);
 
} 
