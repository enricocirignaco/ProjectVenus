/*
  TvRemoteEdith V 1.2

  Read Code from IR receiver
  If button Pressed, Send saved Code with IR transmitter

  IR LED must use Pin #3
*/

#include <IRremote.h>

const int receiverPin = 4;
const int buttonPin   = 7;


decode_type_t manufacturer;
long int      code;

// Create IR Send Object
IRsend irsend;
// Define IR Receiver and Results Objects
IRrecv irrecv(receiverPin);
decode_results results;

void setup(){
  // Enable the IR Receiver
  irrecv.enableIRIn();
  pinMode(buttonPin, INPUT);
}

void loop(){

  // Recive and save Code
  if (irrecv.decode(&results)){
    code = results.value;
    manufacturer = results.decode_type;
    irrecv.resume();
  } 

  //Send the saved code if Button pressed
  if(digitalRead(buttonPin)){
    switch(manufacturer){
      
      case NEC: 
        irsend.sendNEC(code, 32); 
        break;
      case SONY: 
        irsend.sendSony(code, 12); 
        break;
      case RC5: 
        irsend.sendRC5(code, 12);
        break;
      case RC6: 
        irsend.sendRC6(code, 20);
        break;
    }
  }
  
  delay(30);
}
