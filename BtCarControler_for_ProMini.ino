//藍芽腳位
//For Pro Mini
#include <SoftwareSerial.h>
SoftwareSerial BTC(14, 15);
char btcmd,btcmdlast;
//pin腳設定

const byte forwardPin = 2;
const byte backPin = 3;
const byte leftPin = 8;
const byte rightPin = 9;
const byte lowspeedPin = 10;
const byte highspeedPin = 11;



void setup() {
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(backPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(lowspeedPin, INPUT_PULLUP);
  pinMode(highspeedPin, INPUT_PULLUP);
  Serial.begin(9600);
  BTC.begin(9600);
  btcmd='s';
  btcmdlast='s';
}

void loop() {
  btcmdlast='s';

  if(digitalRead(forwardPin) == 0){
    btcmdlast='w';
  }

  if(digitalRead(backPin) == 0){
    btcmdlast='x';
  }

  if(digitalRead(leftPin) == 0){
    btcmdlast='a';
  }

  if(digitalRead(rightPin) == 0){
    btcmdlast='d';
  }

  if(digitalRead(lowspeedPin) == 0){
    btcmdlast='1';
  }

  if(digitalRead(highspeedPin) == 0){
    btcmdlast='2';
  }  
  

  //Serial.println(btcmdlast);
  
  
  if(btcmd != btcmdlast){
    delay(50);
    Serial.print("State=");
    switch (btcmdlast) {
    case 'w':
      BTC.write('w');
      Serial.println("Forward");
      break;
    case 'x':
      BTC.write('x');
      Serial.println("Backward");
      break;
    case 'a':
      BTC.write('a');
      Serial.println("Left");
      break;
    case 'd':
      BTC.write('d');
      Serial.println("Right");
      break;
    case 's':
      BTC.write('s');
      Serial.println("Stop");
      break; 
    case '1':
      BTC.write('1');
      Serial.println("Low Speed");
      break;
    case '2':
      BTC.write('2');
      Serial.println("High Speed");
      break;
    default:
      BTC.write('s');
      Serial.println("Stop");
    break;
    }
    btcmd = btcmdlast;
    
  }
}
