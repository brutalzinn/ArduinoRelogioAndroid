#include "StringSplitter.h"

void week_day_insert( int id, int alarm_dayFinal, int alarm_monthFinal, int alarm_yearFinal, int alarm_hour, int alarm_minute, String result, int isenabled){



 StringSplitter *splitter = new StringSplitter(result, ':', 7);
int itemCount = splitter->getItemCount();

int seg = 0;
int ter= 0;
int qua= 0;
int quin= 0;
int sex= 0;
int sab= 0;
int dom= 0;
for(int i = 0; i < itemCount; i++){
  String item = splitter->getItemAtIndex(i);

if(item == "1"){

seg = 1;

  
}
if(item == "2"){

ter = 1;

  
}

if(item == "3"){

qua = 1;

  
}

if(item == "4"){

quin = 1;

  
}

if(item == "5"){

sex = 1;

  
}

if(item == "6"){

sab = 1;

  
}
if(item == "7"){

dom = 1;

  
}





}



    appendOneRecord(id,alarm_dayFinal,alarm_monthFinal,alarm_yearFinal,alarm_hour,alarm_minute,dom,seg,ter,qua,quin,sex,sab,isenabled);



}
void week_day_update( int id, int alarm_dayFinal, int alarm_monthFinal, int alarm_yearFinal, int alarm_hour, int alarm_minute, String result, int isenabled){



 StringSplitter *splitter = new StringSplitter(result, ':', 7);
int itemCount = splitter->getItemCount();

int seg = 0;
int ter= 0;
int qua= 0;
int quin= 0;
int sex= 0;
int sab= 0;
int dom= 0;
for(int i = 0; i < itemCount; i++){
  String item = splitter->getItemAtIndex(i);
Serial.print(item);
if(item == "1"){

dom = 1;

  
}
if(item == "2"){

seg = 1;

  
}

if(item == "3"){

ter = 1;

  
}

if(item == "4"){

qua = 1;

  
}

if(item == "5"){

quin = 1;

  
}

if(item == "6"){

sex = 1;

  
}
if(item == "7"){

sab = 1;

  
}





}


Serial.print ( " UPDATE RECORRING ");
    UpdateDatabase(id,alarm_dayFinal,alarm_monthFinal,alarm_yearFinal,alarm_hour,alarm_minute,dom,seg,ter,qua,quin,sex,sab,isenabled);



}


void readall(int arg_cnt, char **args)
{

selectAll();
  
}


void test(int arg_cnt, char **args)
{
}





void counts(int arg_cnt, char **args){

countRecords();

//dbFile.close();
}

void database(int arg_cnt, char **args){

char* command = args[1];
String list;
int id = 0;
int alarm_hour = 0;
int alarm_minute = 0;

int i=0;
int alarm_dayFinal = 0;

int alarm_monthFinal = 0;

int alarm_yearFinal = 0;
String alarm_weekdays = "";
int memory = 0;
int seg = 0;
int ter= 0;
int qua= 0;
int quin= 0;
int sex= 0;
int sab= 0;
int dom= 0;
int isenabled = 0;
 
 
 if(arg_cnt == 10)
  {
 id = cmdStr2Num(args[2], 10);
    alarm_dayFinal = cmdStr2Num(args[3], 10);
      alarm_monthFinal = cmdStr2Num(args[4], 10);
       alarm_yearFinal = cmdStr2Num(args[5], 10);
         alarm_hour = cmdStr2Num(args[6], 10);
    alarm_minute = cmdStr2Num(args[7], 10);   
       alarm_weekdays = args[8];     
       isenabled = cmdStr2Num(args[9], 10); 
 
  }
  if(arg_cnt == 3){
 id = cmdStr2Num(args[2], 10);

   
  }



Serial.print("ARGS: ");
Serial.println (arg_cnt);
int result = str2enum(command);
Serial.print("COMANDO:");
Serial.println(result);
switch(result){
  
case 0: 
Serial.print("INSERT");
//type = 0;



 if(arg_cnt == 10)
  {

 
week_day_insert(id,alarm_dayFinal,alarm_monthFinal,alarm_yearFinal,alarm_hour,alarm_minute,alarm_weekdays,isenabled);
    
  }

 



break;


case 1:
Serial.print("UPDATE");
 if(arg_cnt == 10)
  {


week_day_update(id,alarm_dayFinal,alarm_monthFinal,alarm_yearFinal,alarm_hour,alarm_minute,alarm_weekdays,isenabled);

  }


  
break;

case 2:
deleteAll();


break;

case 3:

//select case

SelectCASE(id);


break;
case 4:
// deletar record especifico
//select case
 if(arg_cnt == 3)
  {

deleteOneRecord(id);
  }
break;
   default: 

   break;



  
}



  
}
