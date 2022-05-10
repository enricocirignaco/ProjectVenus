
/*
  TvRemoteEdith V 1.3

  Read Code from IR receiver
  If button Pressed, Send saved Code with IR transmitter

  IR LED must use Pin #3
  IR Diode is set on Pin #4
  Interrupt Button must use Pin #2

  Sender
  Pin 3 = Output
  Pin 4 = VCC
  Pin 5 = GND

  Receiver
  Pin 6 = Input
  Pin 7 = VCC
  Pin 8 = GND

  Button Red
  Pin GND = GND
  Pin 2= Input

  Button
  Pin 11 = GND
  Pin 12 = Input
  
*/

#include <EEPROM.h>
#include <IRremote.h>

const int code_addres         = 0x00;

const int buttonRed_input = 2;
const int outputIR_VCC    = 4;
const int outputIR_GND    = 5;
const int inputIR         = 6;
const int inputIR_VCC     = 7;
const int inputIR_GND     = 8;
const int button_GND      = 11;
const int button_input    = 12;

long int      code;

// Create IR Send Object
IRsend irsend;
// Define IR Receiver and Results Objects
IRrecv irrecv(inputIR);
decode_results results;

void setup(){

  pinMode(outputIR_VCC, OUTPUT);
  pinMode(outputIR_GND, OUTPUT);

  pinMode(inputIR, INPUT);
  pinMode(inputIR_VCC, OUTPUT);
  pinMode(inputIR_GND, OUTPUT);

  pinMode(buttonRed_input, INPUT_PULLUP);
  pinMode(button_GND, OUTPUT);
  pinMode(button_input, INPUT_PULLUP);

  digitalWrite(outputIR_GND, LOW);
  digitalWrite(inputIR_GND, LOW);
  digitalWrite(button_GND, LOW);
  
  code = EEPROMReadlong(code_addres);
  // code to turn ON/OFF TV
  //code = 0xa90;                        
}

void loop(){
  
  // Enter Pair-Mode if button pressed
  if(!digitalRead(button_input)){
    digitalWrite(inputIR_VCC, HIGH);
    digitalWrite(13, HIGH);
    setPreset();
    digitalWrite(13, LOW);
    digitalWrite(inputIR_VCC, LOW);

  }
  
  //Send the saved code if Button pressed
  if(!digitalRead(buttonRed_input)){
    digitalWrite(outputIR_VCC, HIGH);
    irsend.sendSony(code, 12); 
    digitalWrite(outputIR_VCC, LOW);
  }

  delay(30);
}
