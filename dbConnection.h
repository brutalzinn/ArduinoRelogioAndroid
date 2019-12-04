#include "Arduino.h"
#include <EDB.h>

// Use the external SPI sd card as storage
#include <SPI.h>
#include "SdFat.h"
#define USE_SDIO 0
#define TABLE_SIZE 8192
// The number of demo records that should be created.  This should be less
// than (TABLE_SIZE - sizeof(EDB_Header)) / sizeof(LogEvent).  If it is higher,
// operations will return EDB_OUT_OF_RANGE for all records outside the usable range.
#define RECORDS_TO_CREATE 10


char* db_name = "/db/edb_test.db";

File dbFile;



#define sdErrorMsg(msg) sd.errorPrint(F(msg));




#if USE_sdIO
// Use faster sdioCardEX
sdFatsdioEX sd;
// sdFatsdio sd;
#else // USE_sdIO
SdFat sd;
#endif  // USE_sdIO





struct LogEvent {
    int id;
    int alarm_dayFinal;
    int alarm_monthFinal;
    int alarm_yearFinal;
      int alarm_hour;
int alarm_minute;
int seg;
int ter;
int qua;
int quin;
int sex;
int sab;
int dom;
int isenabled;
}
logEvent;


// The read and write handlers for using the sd Library
// Also blinks the led while writing/reading
void writer (unsigned long address, byte data) {
    digitalWrite(13, HIGH);
    dbFile.seek(address);
    dbFile.write(data);
    dbFile.flush();
    digitalWrite(13, LOW);
}

byte reader (unsigned long address) {
    digitalWrite(13, HIGH);
    dbFile.seek(address);
    byte b = dbFile.read();
    digitalWrite(13, LOW);
    return b;
}

// Create an EDB object with the appropriate write and read handlers
EDB db(&writer, &reader);
//------------------------------------------------------------------------------
// store error strings in flash
#define sdErrorMsg(msg) sd.errorPrint(F(msg));
//------------------------------------------------------------------------------



// utility functions
void printError(EDB_Status err)
{
    Serial.print("ERROR: ");
    switch (err)
    {
        case EDB_OUT_OF_RANGE:
            Serial.println("Recno out of range");
            break;
        case EDB_TABLE_FULL:
            Serial.println("Table full");
            break;
        case EDB_OK:
        default:
            Serial.println("OK");
            break;
    }
}
void recordLimit()
{
    Serial.print("Record Limit: ");
    Serial.println(db.limit());
}

void deleteOneRecord(int id)
{
for (int recno = 1; recno <= db.count(); recno++)
    {


db.readRec(recno, EDB_REC logEvent);

      
     if (logEvent.id == id) {


EDB_Status result = db.deleteRec(recno);
if (result == EDB_OK)
        {
Serial1.write("#DB:1");
          break;
        }
      
    

  
}
}
}

void deleteAll()
{
    Serial.print("Truncating table... ");
    db.clear();
    Serial.println("DONE");
}

void countRecords()
{
    Serial.print("Record Count: ");
    Serial.println(db.count());
}

void createRecords(int num_recs)
{
    Serial.print("Creating Records... ");
    for (int recno = 1; recno <= num_recs; recno++)
    {
        logEvent.id = recno;
//        logEvent.temperature = random(1, 125);
        EDB_Status result = db.appendRec(EDB_REC logEvent);
        if (result != EDB_OK) printError(result);
    }
    Serial.println("DONE");
}
uint8_t* selectALLalarmsAndSetAlarm(){

//Serial.print(minuto_alarm);
 
for (int recno = 1; recno <= db.count(); recno++)
    {


      
        EDB_Status result = db.readRec(recno, EDB_REC logEvent);
        if (result == EDB_OK)
        {
   static uint8_t values[11];


     values[0] = logEvent.alarm_minute;
     values[1] = logEvent.alarm_dayFinal;
    values[2] = logEvent.alarm_monthFinal;
    
       values[3] = logEvent.alarm_hour;
    values[4] = logEvent.alarm_minute;




unsigned int off = -1;
    if(logEvent.dom  == 1){

  values[5] = 0;
      
    }else{
values[5] = off;
      
    }
    

    if(logEvent.seg == 1){

 values[6] = 1;
      
    }else{
values[6] = off;
      
    }
    

    if(logEvent.ter == 1){

 values[7] = 2;
      
    }else{
values[7] = off;
      
    }
    

    if(logEvent.qua == 1){

 values[8] = 3;
      
    }else{
values[8] = off;
      
    }
    

    if(logEvent.quin == 1){

 values[9] = 4;
      
    }else{
values[9] = off;
      
    }
    

    if(logEvent.sex == 1){

 values[10] = 5;
      
    }else{
values[10] = off;
      
    }
    if(logEvent.sab == 1){
 values[11] = 6;

      
    }else{
values[11] = off;
      
    }
    
    values[12] = logEvent.isenabled;

    return values;      
}

    }
}








int select_alarm_principal(int id){


for (int recno = 1; recno <= db.count(); recno++)
    {


db.readRec(recno, EDB_REC logEvent);

      
     if (logEvent.id == id) {


return 1;
      
     }else{

      return 0;
     }

  
}
}
void update_alarm_principal(int id,int alarm_hour, int alarm_minute){

 for (int recno = 1; recno <= db.count(); recno++)
    {


db.readRec(recno, EDB_REC logEvent);


   if (logEvent.id == id) {

Serial.print("Updating record at recno: ");
    Serial.print(recno);
    Serial.print("... ");
    logEvent.alarm_dayFinal = 0;
 
logEvent.alarm_monthFinal = 0;

logEvent.alarm_yearFinal = 0;

    logEvent.alarm_hour = alarm_hour;
logEvent.alarm_minute = alarm_minute;
logEvent.seg = 1;
logEvent.ter = 1;
logEvent.qua = 1;
logEvent.quin = 1;
logEvent.sex = 1;
logEvent.sab = 1;
logEvent.dom = 1;
//    logEvent.temperature = 4321;
    EDB_Status result = db.updateRec(recno, EDB_REC logEvent);
    break;
    if (result == EDB_OK) {

      Serial.write("#DB:1");
    }
    


     }

    }
  
}
void insert_alarm_principal(int id,int alarm_hour, int alarm_minute){

logEvent.id = id;
 

logEvent.alarm_dayFinal = 0;
logEvent.alarm_monthFinal = 0;
logEvent.alarm_yearFinal = 0;
    logEvent.alarm_hour = alarm_hour;  
logEvent.alarm_minute = alarm_minute;

logEvent.seg = 1;
logEvent.ter = 1;
logEvent.qua = 1;
logEvent.quin = 1;
logEvent.sex = 1;
logEvent.sab = 1;
logEvent.dom = 1;


    EDB_Status result = db.appendRec(EDB_REC logEvent);
    if (result != EDB_OK) printError(result);
    Serial.println("DONE");
  
}


void SelectCASE(int id){



  for (int recno = 1; recno <= db.count(); recno++)
    {


   EDB_Status result = db.readRec(recno, EDB_REC logEvent);

      
     if (logEvent.id == id) {


   Serial.print(" RECNO: ");
            Serial.print(recno);
            Serial.print(" ID: ");
            Serial.print(logEvent.id);

     
               Serial.print(" Dia: ");
            Serial.println(logEvent.alarm_dayFinal);
               Serial.print(" Mês: ");
            Serial.println(logEvent.alarm_monthFinal);
               Serial.print(" Ano: ");
            Serial.println(logEvent.alarm_yearFinal);
            Serial.print(" Hora: ");
            Serial.println(logEvent.alarm_hour);
               Serial.print(" minuto: ");
            Serial.println(logEvent.alarm_minute);




 Serial.print(" days: ");
  Serial.print(" dom: ");
            Serial.println(logEvent.dom);
              Serial.print(" segb: ");
 Serial.println(logEvent.seg);
   Serial.print(" ter: ");
  Serial.println(logEvent.ter); 
    Serial.print(" qua: ");
  Serial.println(logEvent.qua);
    Serial.print(" quin: ");
   Serial.println(logEvent.quin);
     Serial.print(" sex: ");
    Serial.println(logEvent.sex);
      Serial.print(" sab: ");
     Serial.println(logEvent.sab);
     
            if (result == EDB_OK)
        {

Serial1.write("#DB:1");
          
        }
     }
    }
}
void selectAll()
{
    for (int recno = 1; recno <= db.count(); recno++)
    {
      
        EDB_Status result = db.readRec(recno, EDB_REC logEvent);
        if (result == EDB_OK)
        {

          Serial.print(" RECNO: ");
            Serial.print(recno);
            Serial.print(" ID: ");
            Serial.print(logEvent.id);

     
               Serial.print(" Dia: ");
            Serial.println(logEvent.alarm_dayFinal);
               Serial.print(" Mês: ");
            Serial.println(logEvent.alarm_monthFinal);
               Serial.print(" Ano: ");
            Serial.println(logEvent.alarm_yearFinal);
            Serial.print(" Hora: ");
            Serial.println(logEvent.alarm_hour);
               Serial.print(" minuto: ");
            Serial.println(logEvent.alarm_minute);




 Serial.println(" days: ");
  Serial.print(" dom: ");
            Serial.println(logEvent.dom);
              Serial.print(" seg: ");
 Serial.println(logEvent.seg);
   Serial.print(" ter: ");
  Serial.println(logEvent.ter); 
    Serial.print(" qua: ");
  Serial.println(logEvent.qua);
    Serial.print(" quin: ");
   Serial.println(logEvent.quin);
     Serial.print(" sex: ");
    Serial.println(logEvent.sex);
      Serial.print(" sab: ");
     Serial.println(logEvent.sab);
     Serial.print("HABILITADO: ");
     Serial.println(logEvent.isenabled);
            Serial1.write("DB:1");
        }
        else printError(result);
    }
}

void UpdateDatabase(int id,int alarm_dayFinal, int alarm_monthFinal, int alarm_yearFinal, int alarm_hour, int alarm_minute,int dom, int seg, int ter, int qua, int quin, int sex, int sab,int isenabled)
{

  for (int recno = 1; recno <= db.count(); recno++)
    {


 db.readRec(recno, EDB_REC logEvent);

      
     if (logEvent.id == id) {

Serial.print ( "ATUALIZANDO.");





 Serial.print("Updating record at recno: ");
    Serial.print(recno);
    Serial.print("... ");
        logEvent.alarm_dayFinal = alarm_dayFinal;
 
logEvent.alarm_monthFinal = alarm_monthFinal;

logEvent.alarm_yearFinal = alarm_yearFinal;
    logEvent.alarm_hour = alarm_hour;
logEvent.alarm_minute = alarm_minute;
logEvent.seg = seg;
logEvent.ter = ter;
logEvent.qua = qua;
logEvent.quin = quin;
logEvent.sex = sex;
logEvent.sab = sab;
logEvent.dom = dom;
logEvent.isenabled = isenabled;





      
      
     EDB_Status result = db.updateRec(recno, EDB_REC logEvent);
    
   if (result == EDB_OK)
        {
Serial1.write("DB:1");
          break;
        }


     
    }



    
  
   

//    logEvent.temperature = 4321;
  
}
    
}





void appendOneRecord(int id, int alarm_dayFinal, int alarm_monthFinal, int alarm_yearFinal, int alarm_hour, int alarm_minute,int dom, int seg, int ter, int qua, int quin, int sex, int sab, int isenabled)
{
 
   
   logEvent.id = id;
 

logEvent.alarm_dayFinal = alarm_dayFinal;
logEvent.alarm_monthFinal = alarm_monthFinal;
logEvent.alarm_yearFinal = alarm_yearFinal;
    logEvent.alarm_hour = alarm_hour;  
logEvent.alarm_minute = alarm_minute;

logEvent.seg = seg;
logEvent.ter = ter;
logEvent.qua = qua;
logEvent.quin = quin;
logEvent.sex = sex;
logEvent.sab = sab;
logEvent.dom = dom;
logEvent.isenabled = isenabled;

    EDB_Status result = db.appendRec(EDB_REC logEvent);
    if (result == EDB_OK)
        {
Serial1.write("DB:1");
        
        }
}
