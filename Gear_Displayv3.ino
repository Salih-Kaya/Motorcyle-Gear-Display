#include <EEPROM.h>
//input
const int callButton = 2;
int analogInput = A0;

//output
const int ledA = 3; 
const int ledB = 4;       //   --A--
const int ledC = 5;       //  F     B
const int ledD = 6;       //   --G--
const int ledE = 7;       //  E     C
const int ledF = 8;       //   --D--   (DP)
const int ledG = 9;
const int ledDP = 10;

//variables
int callButtonState,lastButtonState=0;
int val =0;
int eepromCheck =0;
int analogReading = 0;
int callCounter = 0;
int x=10;

//eprom adress
byte gear1min; //EEPROM Adress :0
byte gear1max; //EEPROM Adress :1
byte gear2min; //EEPROM Adress :2
byte gear2max; //EEPROM Adress :3
byte gear3min; //EEPROM Adress :4
byte gear3max; //EEPROM Adress :5
byte gear4min; //EEPROM Adress :6
byte gear4max; //EEPROM Adress :7
byte gear5min; //EEPROM Adress :8
byte gear5max; //EEPROM Adress :9
byte gear6min; //EEPROM Adress :10
byte gear6max; //EEPROM Adress :11
byte gearNmin; //EEPROM Adress :12
byte gearNmax; //EEPROM Adress :13

void setup() {
  //Serial port - can be used to control the program from the computer
  Serial.begin(9600);

  //defination input-output
  pinMode (callButton,INPUT);
  pinMode (analogInput,INPUT);
  pinMode (ledA,OUTPUT);
  pinMode (ledB,OUTPUT);
  pinMode (ledC,OUTPUT);
  pinMode (ledD,OUTPUT);
  pinMode (ledE,OUTPUT);
  pinMode (ledF,OUTPUT);
  pinMode (ledG,OUTPUT);        
  pinMode (ledDP,OUTPUT);
  
  //animation
  digitalWrite(ledDP,LOW);
  delay(100);
  digitalWrite(ledG,LOW);
  delay(100);
  digitalWrite(ledF,LOW);
  delay(100);
  digitalWrite(ledE,LOW);
  delay(100);
  digitalWrite(ledD,LOW);
  delay(100);
  digitalWrite(ledC,LOW);
  delay(100);
  digitalWrite(ledB,LOW);
  delay(100);
  digitalWrite(ledA,LOW);
  delay(100);
  digitalWrite(ledA,HIGH);
  delay(100);
  digitalWrite(ledB,HIGH);
  delay(100);
  digitalWrite(ledC,HIGH);
  delay(100);
  digitalWrite(ledD,HIGH);
  delay(100);
  digitalWrite(ledE,HIGH);
  delay(100);
  digitalWrite(ledF,HIGH);
  delay(100);
  digitalWrite(ledG,HIGH);
  delay(100);
  for (int i = 0;i<10;i++){
    digitalWrite(ledDP,HIGH);
    delay(100);
    digitalWrite(ledDP,LOW);
    delay(100);
  }

  //eprom control
  gear1min = EEPROM.read(0);
  gear1max = EEPROM.read(1);
  
  if (gear1min ==255 && gear1max == 255){
    eepromCheck = 1;
  }
  else {
    gear1min = EEPROM.read(0);
    gear1max = EEPROM.read(1);
    gear2min = EEPROM.read(2);
    gear2max = EEPROM.read(3);
    gear3min = EEPROM.read(4);
    gear3max = EEPROM.read(5);
    gear4min = EEPROM.read(6);
    gear4max = EEPROM.read(7);
    gear5min = EEPROM.read(8);
    gear5max = EEPROM.read(9);
    gear6min = EEPROM.read(10);
    gear6max = EEPROM.read(11);
    gearNmin = EEPROM.read(12);
    gearNmax = EEPROM.read(13);
  }
}

void loop() {
  // can be used to read gear value from pc. just connect to computer and open serial port screen
  Serial.println(val);
  if (eepromCheck==1){
    gear6();
  }
  else{
    callButtonState = digitalRead(callButton);
    analogReading = analogRead(A0);
    val = analogReading /4;
    if (x==10){
    if (val >gear1min && val<=gear1max){
      gear1();
    }
    else if (val >gear2min && val<= gear2max){
      gear2();
    }
    else if (val >gear3min && val<= gear3max){
      gear3();
    }
    else if (val >gear4min && val<= gear4max){
      gear4();
    }
    else if (val >gear5min && val<= gear5max){
      gear5();
    }
    else if (val >gear6min && val<= gear6max){
      gear6(); 
    }
    else if (val >gearNmin && val<= gearNmax){
      gearN();   
    }  
    }
    if (x==10){
      if (callButtonState != lastButtonState){
          if(callButtonState==HIGH){
            delay(2000);
            x=1;
            callCC();
          }
          lastButtonState = callButtonState ;
        }     
    }

    if (x<10){
      if (callButtonState != lastButtonState){
          if(callButtonState==HIGH){
            delay(1000);
            x++;
            gearDisplay();
          }
          lastButtonState = callButtonState ;
        }   
    }
  }
}

void gearDisplay(){
  switch (x){
    case 1:
      callCC();
      break;
    case 2:
      gear1();
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      
      break;
    case 3:
      analogReading = analogRead(A0);
      val = analogReading /4;
      gear1min = val -3;
      gear1max = val +3;
      EEPROM.write(0,gear1min);
      EEPROM.write(1,gear1max);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      gear2();
      delay(200);
      break;
    case 4:
      analogReading = analogRead(A0);
      gear2min = val -3;
      gear2max = val +3;
      EEPROM.write(2,gear2min);
      EEPROM.write(3,gear2max);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      gear3();
      delay(200);
      break;
    case 5:
      analogReading = analogRead(A0);
      gear3min = val -3;
      gear3max = val +3;
      EEPROM.write(4,gear3min);
      EEPROM.write(5,gear3max);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      gear4();
      delay(200);
      break;
    case 6:
      analogReading = analogRead(A0);
      gear4min = val -3;
      gear4max = val +3;
      EEPROM.write(6,gear4min);
      EEPROM.write(7,gear4max);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      gear5();
      delay(200);
      break;
    case 7:
      analogReading = analogRead(A0);
      gear5min = val -3;
      gear5max = val +3;
      EEPROM.write(8,gear5min);
      EEPROM.write(9,gear5max);
      delay(200);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);      
      gear6();
      break;
    case 8:
      analogReading = analogRead(A0);
      gear6min = val -3;
      gear6max = val +3;
      EEPROM.write(10,gear6min);
      EEPROM.write(11,gear6max);
      delay(200);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      gearN();
      break;
   case 9:
      analogReading = analogRead(A0);
      gearNmin = val-3;
      gearNmax = val+3;
      EEPROM.write(12,gearNmin);
      EEPROM.write(13,gearNmax);
      delay(200);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      delay(300);
      digitalWrite(ledDP,LOW);
      delay(300);
      digitalWrite(ledDP,HIGH);
      animation();
      x=10;
      break;
  }
}

void gear1(){  
  digitalWrite(ledA,HIGH);
  digitalWrite(ledB,LOW);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,HIGH);
  digitalWrite(ledE,HIGH);
  digitalWrite(ledF,HIGH);
  digitalWrite(ledG,HIGH);
  digitalWrite(ledDP,HIGH);
}

void gear2(){
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,LOW);
  digitalWrite(ledC,HIGH);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,LOW);
  digitalWrite(ledF,HIGH);
  digitalWrite(ledG,LOW);
  digitalWrite(ledDP,HIGH);
}

void gear3(){
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,LOW);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,HIGH);
  digitalWrite(ledF,HIGH);
  digitalWrite(ledG,LOW);
  digitalWrite(ledDP,HIGH);
}

void gear4(){
  digitalWrite(ledA,HIGH);
  digitalWrite(ledB,LOW);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,HIGH);
  digitalWrite(ledE,HIGH);
  digitalWrite(ledF,LOW);
  digitalWrite(ledG,LOW);
  digitalWrite(ledDP,HIGH);
}

void gear5(){
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,HIGH);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,HIGH);
  digitalWrite(ledF,LOW);
  digitalWrite(ledG,LOW);
  digitalWrite(ledDP,HIGH);
}

void gear6(){
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,HIGH);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,LOW);
  digitalWrite(ledF,LOW);
  digitalWrite(ledG,LOW);
  digitalWrite(ledDP,HIGH);
}

void gearN(){
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,LOW);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,LOW);
  digitalWrite(ledF,LOW);
  digitalWrite(ledG,HIGH);
  digitalWrite(ledDP,HIGH);
}

void animation(){
  digitalWrite(ledDP,LOW);
  delay(100);
  digitalWrite(ledG,LOW);
  delay(100);
  digitalWrite(ledF,LOW);
  delay(100);
  digitalWrite(ledE,LOW);
  delay(100);
  digitalWrite(ledD,LOW);
  delay(100);
  digitalWrite(ledC,LOW);
  delay(100);
  digitalWrite(ledB,LOW);
  delay(100);
  digitalWrite(ledA,LOW);
  delay(100);
  digitalWrite(ledA,HIGH);
  delay(100);
  digitalWrite(ledB,HIGH);
  delay(100);
  digitalWrite(ledC,HIGH);
  delay(100);
  digitalWrite(ledD,HIGH);
  delay(100);
  digitalWrite(ledE,HIGH);
  delay(100);
  digitalWrite(ledF,HIGH);
  delay(100);
  digitalWrite(ledG,HIGH);
  delay(100);
  for (int i=0; i<10;i++){
    digitalWrite(ledDP,LOW);
    delay(100);
    digitalWrite(ledDP,HIGH);
    delay(100);
  }
}

void callCC(){
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,HIGH);
  digitalWrite(ledC,HIGH);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,LOW);
  digitalWrite(ledF,LOW);
  digitalWrite(ledG,HIGH);
  digitalWrite(ledDP,LOW);
  delay(500);
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,HIGH);
  digitalWrite(ledC,HIGH);
  digitalWrite(ledD,LOW);
  digitalWrite(ledE,LOW);
  digitalWrite(ledF,LOW);
  digitalWrite(ledG,HIGH);
  digitalWrite(ledDP,LOW);
  delay(500);
}
