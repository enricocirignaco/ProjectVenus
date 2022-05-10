#include <LowPower.h>

/*
  TvRemoteEdith V 1.3

  Read Code from IR receiver    
  If button Pressed, Send saved Code with IR transmitter

  IR LED must use Pin #3
  IR Diode is set on Pin #4
  Interrupt Button must use Pin #2

  Sender
  Pin 3 = Output -- Brown
  Pin 4 = VCC    -- Black
  Pin 5 = GND    -- White

  Receiver
  Pin 6 = Input  -- Orange
  Pin 7 = VCC    -- Yellow
  Pin 8 = GND    -- Green

  Button Red
  Pin GND = GND -- Grey
  Pin 2= Input  -- Violet

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

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

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
  
  /**********************************************************/
      // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUp, LOW);
    
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
    
    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0); 
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.
  /**********************************************************/

  // Enter Pair-Mode if button pressed
  if(!digitalRead(button_input)){
    digitalWrite(inputIR_VCC, HIGH);
    digitalWrite(13, HIGH);
    setPreset();
    digitalWrite(13, LOW);
    digitalWrite(inputIR_VCC, LOW);

  }
  else{
  
  //Send the saved code if Button pressed
    digitalWrite(outputIR_VCC, HIGH);
    irsend.sendSony(code, 12); 
    digitalWrite(outputIR_VCC, LOW);
  }

  delay(30);
}
