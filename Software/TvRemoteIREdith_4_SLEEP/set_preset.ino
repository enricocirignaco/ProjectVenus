
// On Pair Button pressed the program will enter this function
// The program will wait until a signal from the IR receiver is detected
// Will save it on the EEPROM and return
  
void setPreset(){
  
  long int new_code = 0;
  
  // Enable the IR Receiver
  irrecv.enableIRIn();

  while(new_code == 0){
    if (irrecv.decode(&results)){
      new_code = results.value; 
      irrecv.resume();
    }   
  }
  
  EEPROMWritelong(code_addres, new_code);
  code     = new_code;
  
  return;
}

