
// Use the external SPI sd card as storage



 //id reservado para alarme rpincipal.
int ID_RESERVERD = 400; 

// end




// debug
boolean Debugger = false;
boolean AlarmIsOn = true;
boolean Debugger_memory = true;
  
typedef enum {INSERT,UPDATE,DELETEALL,SELECT,DELETE
} db_command;

int fade_buzzer = 0;


const static struct {
    db_command val;
    const char *str;
} conversion [] = {
    {INSERT, "INSERT"},
    {UPDATE, "UPDATE"},
    {DELETEALL, "DELETEALL"},
       {SELECT, "SELECT"},
           {DELETE, "DELETE"}
};


typedef enum {
SEG, TER, QUA, QUIN, SEXTA, SAB, DOM
} dias_semana;

str2enum (const char *str)
{
     int j;
     for (j = 0;  j < sizeof (conversion) / sizeof (conversion[0]);  ++j)
         if (!strcmp (str, conversion[j].str))
             return conversion[j].val;    
     Serial.print ("no such string");
}



String content = "";
// end debug
boolean newData = false;
RTC_DS1307 rtc;
#define CLK A3
#define DIO A2
 int numbPress;
int requestIdx=0;
int myhour=15 ;
int myminute=7;
int mysecond=0;
int myyear = 2019;
int myday = 25;
int mymonth = 10;
int input;


    int buttonFirst = 0;
int menu = 0;
char requestBuffer[100];
TM1637 Display1(CLK, DIO);
  int8_t Digitos[] = {0,1,2,3};
  int horas;
  int segundos;
  int minutos;
  boolean alterna;
int hora_alarm  = 0;
int minuto_alarm = 0;
int buzzer = 9;
int brightness = 0; 
int fadeAmount = 5; 
int pushButton = 4;




  RotaryEncoder encoder(A0, A1);



  // variaveis do menu

int encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
int oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent
// Button reading, including debounce without delay function declarations

byte oldButtonState = HIGH;  // assume switch open because of pull-up resistor
const unsigned long debounceTime = 10;  // milliseconds
unsigned long buttonPressTime;  // when the switch last changed state
boolean buttonPressed = 0; // a flag variable
// Menu and submenu/setting declarations
int Mode = 0;   // This is which menu mode we are in at any given time (top level or one of the submenus)
int modeMax = 3; // This is the number of submenus/settings you want
byte setting1 = 0;  // a variable which holds the value we set 
byte setting2 = 0;  // a variable which holds the value we set 
byte setting3 = 0;  // a variable which holds the value we set 
boolean alarm = false;
boolean isRecv = false;
int buzzer_intensity = 50;
/* Note: you may wish to change settingN etc to int, float or boolean to suit your application. 
 Remember to change "void setAdmin(byte name,*BYTE* setting)" to match and probably add some 
 "modeMax"-type overflow code in the "if(Mode == N && buttonPressed)" section*/
boolean btReceived = false;
long previousMillis = 0;        // Variável de controle do tempo
long redLedInterval = 1000;  




boolean isAlarmtoday = false;
int AlarmState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillisAlarm = 0;        // will store last time LED was updated

// constants won't change:
const long intervalAlarm = 1000;   
