



// end variaveis do menu


//dbconnection

#include <SoftwareSerial.h>


    static char buffer[20];

// Use the external SPI sd card as storage
#include <SPI.h>
#include <TM1637.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <Time.h>
//dbconnection

#include "Arduino.h"




// end

#include <RTClib.h>
#include <Cmd.h>
#include "SdFat.h"
#include "sdios.h"

 #include <RotaryEncoder.h>
//SoftwareSerial Serial1(2,3); // RX | TX
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data




#include "variables.h"

#include "dbConnection.h"





#include "commands.h"

#include "setup.h"

#include "menu.h"
void loop() {







  

 
 

if(alarm == false){
clock();
 morningalarm();

  }
 
//Serial.listen()
 
  // while there is data coming in, read it
  // and send to the hardware serial port: 

// comentado para debug

//transmit();


rotaryMenu();


 // end comentario
 cmdPoll();
}
void transmit() {
 unsigned long currentMillis = millis();    //Tempo atual em ms
  if (currentMillis - previousMillis > 40) { 
    previousMillis = currentMillis; 

  // while there is data coming in, read it
  // and send to the hardware serial port:
  if (Serial1.available() > 0) {
    char inByte = Serial1.read();
    Serial2.print(inByte + "\r\n");
  }

  // blank line to separate data from the two ports:


  // Now listen on the second port

  // while there is data coming in, read it
  // and send to the hardware serial port:
  
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    Serial2.write(inByte + "\r");
 
  }

  // blank line to separate data from the two ports:

  // while there is data coming in, read it
  // and send to the hardware serial port:
 
  if (Serial2.available() > 0) {
    char inByte = Serial2.read();
    Serial.print(inByte);
  }
  }

  
}



void clock(){

  unsigned long currentMillis = millis();    //Tempo atual em ms
  if (currentMillis - previousMillis > redLedInterval) { 
    previousMillis = currentMillis; 
  
DateTime tstamp = rtc.now();

//    Serial.print(", Date (D/M/Y) = ");
//    Serial.print(tm.Day);
//    Serial.write('/');
//    Serial.print(tm.Month);
//    Serial.write('/');
//    Serial.print(tmYearToCalendar(tm.Year));
//    Serial.println();

    horas = tstamp.hour();
    minutos = tstamp.minute();
    segundos = tstamp.second();
    CalculaDigitos(horas, minutos);
    if (alterna)
      {
        Display1.point(POINT_OFF);
        alterna = false;
      }
      else
      {
        Display1.point(POINT_ON);
        alterna = true;
      }
    
 
  }

  
}


void start_connection(int arg_cnt, char **args)
{
 Serial1.println("Conexão aceita pelo HC-05.");
Serial1.println("1");
  Serial.print("Conexão bluetooth iniciada.");
}





   // despertador
   void  morningalarm(){



    unsigned long currentMillisAlarm = millis();

  if (currentMillisAlarm - previousMillisAlarm >= intervalAlarm) {
    // save the last time you blinked the LED
    previousMillisAlarm = currentMillisAlarm;


    

//    Serial.print("Ok, Time = ");

//Serial.print(weekday(selectAllAlamrsWITHDATE));
   

 uint8_t* returned = selectALLalarmsAndSetAlarm();
  
     DateTime tstamp = rtc.now();

    int atualday = weekday(tstamp.day(),tstamp.month(),tstamp.year());
//Serial.print(atualday);
    if(atualday == returned[5]){

isAlarmtoday = true;
//Serial.print("Dia atual: DOMINGO");
    }
     if(atualday == returned[6]){

isAlarmtoday = true;
//Serial.print("Dia atual: SEGUNDA");
    }
     if(atualday == returned[7]){

isAlarmtoday = true;
//Serial.print("Dia atual: TERÇA");
    }
     if(atualday == returned[8]){

isAlarmtoday = true;
//Serial.print("Dia atual: QUARTA");
    }
     if(atualday == returned[9]){

isAlarmtoday = true;
//Serial.print("Dia atual: QUINTA");
    }
     if(atualday == returned[10]){

isAlarmtoday = true;
//Serial.print("Dia atual: SEXTA");
    }
     if(atualday == returned[11]){

isAlarmtoday = true;
//Serial.println("Dia atual: SABADO");
    }
    
    if(isAlarmtoday = true){


      
  
           if(tstamp.hour() == returned[3] &&  tstamp.minute() == returned[4] ){
  Serial.print("DAY:" );
Serial.print(atualday);
if(Debugger == false && AlarmIsOn == false){

 if (AlarmState == LOW) {
      AlarmState = HIGH;
      fade_buzzer = 150;
    } else {
      AlarmState = LOW;
      fade_buzzer = 0;
    }
  
}


      Serial.println("HORA DE ACORDAR");
}
if(Debugger == false && AlarmIsOn == false){
analogWrite(buzzer, fade_buzzer);
 
}
       }    
// calcula por data

        

    // set the LED with the ledState of the variable: 
    
  


 





  
}
   }
    
 
int weekday(int day, int month,int year)
/* Calculate day of week in proleptic Gregorian calendar. Sunday == 0. */
{
  int adjustment, mm, yy;
  if (year<2000) year+=2000;
  adjustment = (14 - month) / 12;
  mm = month + 12 * adjustment - 2;
  yy = year - adjustment;
  return (day + (13 * mm - 1) / 5 +
    yy + yy / 4 - yy / 100 + yy / 400) % 7;
}
