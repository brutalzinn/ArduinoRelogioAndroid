
void database(){

 

  

    

     pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    //Serial.begin(9600);


  Serial.print(db_name);

    if (!sd.begin(53)) {
    sdErrorMsg("\ncardBegin failed");
    return;
  }

    // Check dir for db files
    if (!sd.exists("/db")) {
        Serial.println("Dir for Db files does not exist, creating...");
        sd.mkdir("/db");
    }

    if (sd.exists(db_name)) {

        dbFile = sd.open(db_name, FILE_WRITE);

        // Sometimes it wont open at first attempt, espessialy after cold start
        // Let's try one more time
        if (!dbFile) {
            dbFile = sd.open(db_name, FILE_WRITE);
        }

        if (dbFile) {
            Serial.print("Openning current table... ");
            EDB_Status result = db.open(0);
            if (result == EDB_OK) {
                Serial.println("DONE");
            } else {
                Serial.println("ERROR");
                Serial.println("Did not find database in the file " + String(db_name));
                Serial.print("Creating new table... ");
                db.create(0, TABLE_SIZE, (unsigned int)sizeof(logEvent));
                Serial.println("DONE");
                return;
            }
        } else {
            Serial.println("Could not open file " + String(db_name));
            return;
        }
    } else {
        Serial.print("Creating table... ");
        // create table at with starting address 0
        dbFile = sd.open(db_name, FILE_WRITE);
        db.create(0, TABLE_SIZE, (unsigned int)sizeof(logEvent));
        Serial.println("DONE");

      
    }



    
  //  dbFile.close();
}


void setup() {

  Serial.begin(9600);  //computador
Serial1.begin(9600); // bluetooth 

digitalWrite(10, HIGH);
 if(Debugger == true){

Serial.print("EXECUTANDO EM MODO DE DEBBUGER");
  cmdInit(&Serial);
  // cmdInit(&Serial1);
   //cmdInit(&Serial1);
 }else{
Serial.print("EXECUTANDO EM MODO DE BLUETOOTH");
 cmdInit(&Serial1);
  
 }
  

   

cmdAdd("test", test);
cmdAdd("database", database);
cmdAdd("readall", readall);
cmdAdd("counts", counts);


  Display1.set();
  Display1.init();

  rtc.begin();
   if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
 database();
//Serial1.listen();

  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  pinMode (pushButton, INPUT_PULLUP); // setup the button pin

   pinMode(buzzer, OUTPUT);
  // button section of setup
 // pinMode (pushButton, INPUT_PULLUP); // setup the button pin
}
