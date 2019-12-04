void CalculaDigitos( int hor, int minu)
   {
      int8_t Digit0 = minu %10 ;
      int8_t Digit1 = (minu % 100) / 10 ;
      int8_t Digit2 = hor % 10 ;
      int8_t Digit3 = (hor % 100) / 10 ;

      Digitos[3] = Digit0 ;
      Digitos[2] = Digit1 ;
      Digitos[1] = Digit2 ;
      Digitos[0] = Digit3 ;

      Display1.display(Digitos);
   }
void hora_digital_alarm(){


  static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    pos = newPos;
    hora_alarm = newPos;


     if(hora_alarm  < 0 ){


     hora_alarm = 0;

     
     }
   if(hora_alarm  > 23 ){
   hora_alarm  = 23;
    
   }
     
  } // if

} // loop ()
  



void minuto_digital_alarm(){




  static int posB = 0;
  encoder.tick();

  int newPosB = encoder.getPosition();
  if (posB != newPosB) {
    posB = newPosB;
    minuto_alarm = newPosB;
 if(minuto_alarm > 59){
minuto_alarm = 59;

  
 }
 if(minuto_alarm < 0){

  minuto_alarm = 0;
 }
    
  } // if
} // loop ()

void zerar_vars(){

Mode = 0;
alarm = false;
    hora_alarm = 0;
   minuto_alarm = 0;

   encoder.setPosition(0);
   Serial.print("Vars zeradas.");
  }


  void save_alarm_digital(int hora, int minuto){
  
if(select_alarm_principal(ID_RESERVERD) == 0){


insert_alarm_principal(ID_RESERVERD,hora,minuto);
  
}else{

  
  update_alarm_principal(ID_RESERVERD,hora,minuto);
  
}





zerar_vars();
  
  }

  

void rotaryMenu() { //This handles the bulk of the menu functions without needing to install/include/compile a menu library
  //DEBUGGING: Rotary encoder update display if turned
const size_t count = 3;


if(Mode >= modeMax){


Mode = 0;

  
}
  // Button reading with non-delay() debounce - thank you Nick Gammon!
  byte buttonState = digitalRead (pushButton); 
  if (buttonState != oldButtonState){
    if (millis () - buttonPressTime >= debounceTime){ // debounce
      buttonPressTime = millis ();  // when we closed the switch 
      oldButtonState =  buttonState;  // remember for next time 
      if (buttonState == LOW){
        Serial.println ("Button closed"); // DEBUGGING: print that button has been closed
        buttonPressed = 1;
        numbPress = numbPress + 1 ;
        alarm = true;
         

          Serial.print("MODOATUAL");
               Serial.println(Mode); //DEBUGGING: print which mode has been selected
Mode = Mode + 1;
      }
      else {
        Serial.println ("Button opened"); // DEBUGGING: print that button has been opened
        buttonPressed = 0;  
      }  
    }  // end if debounce time up
  } // end of state change

  //Main menu section
  if (Mode > 0) {
 
    if (buttonPressed){ 

      Serial.print("Mode selected: "); //DEBUGGING: print which mode has been selected
      Serial.println(Mode); //DEBUGGING: print which mode has been selected
      buttonPressed = 0; // reset the button status so one press results in one action
  encoder.setPosition(0);
    }
  }  
  if(alarm == true){




    
 
if(Mode == 1) {
  hora_digital_alarm(); 
    
 }
 if(Mode == 2) {
 
  minuto_digital_alarm();
    
 }
if(Mode == 3) {
  save_alarm_digital(hora_alarm, minuto_alarm);
    alarm = false;


    
 }

// Serial.println(numbPress);
          CalculaDigitos(hora_alarm, minuto_alarm);
         // Serial.print(Mode);
          }
} 
