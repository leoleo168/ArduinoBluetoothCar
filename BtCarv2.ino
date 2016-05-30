//BtCarv2.ino
//藍芽腳位
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(11, 12);
char btcmd; //藍芽指令


//DFplayer設定
#include <DFPlayer_Mini_Mp3.h>



//pin腳設定
const byte ENA = 5;
const byte ENB = 6;
const byte IN1 = 7;
const byte IN2 = 8;
const byte IN3 = 9;
const byte IN4 = 10;

//速度設定
int speed;

//開機設定
byte startup = 0;
byte state = 0;

//動作設定
void forward(){
	analogWrite(ENA, speed);
	digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	analogWrite(ENB, speed);
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);	
}

void left(){
	analogWrite(ENA, speed);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH);
	analogWrite(ENB, speed);
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);	

}

void right(){
	analogWrite(ENA, speed);
	digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	analogWrite(ENB, speed);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);

}

void back(){
	analogWrite(ENA, speed);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH);
	analogWrite(ENB, speed);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);	

}

void stop(){
	digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
}

void startengine(){
  speed = 150;
  delay(5000);
  forward();
  delay(100);
  back();
  delay(100);
  forward();
  delay(100);
  back();
  delay(100);  
  forward();
  delay(100);
  back();
  delay(100);
  stop();
}

//主程式

void setup() {
	pinMode(ENA, OUTPUT);
	pinMode(ENB, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
  pinMode(2,INPUT);    //藍芽狀態腳位
	Serial.begin(9600);
	BTSerial.begin(9600);
	/*
	Serial.println(ENA);
	Serial.println(ENB);
	Serial.println(IN1);
	Serial.println(IN2);
	Serial.println(IN3);
	Serial.println(IN4);
	*/
	stop(); //起始暫停
  speed=60;

  //mp3
  //mp3Serial.begin (9600);
  mp3_set_serial (Serial);    //set softwareSerial for DFPlayer-mini mp3 module 
  delay(100);                     // delay 10ms to set volume
  mp3_set_volume (25);          // value 0~30
}




void loop() {	
	//forward();

  //開機判斷
  while(startup == 0){
    state = digitalRead(2);

    if(state == 1){
      Serial.print("state=");
      Serial.println(state);
      mp3_play (1);
      startengine();
      delay (3000);
      startup = 1; //開機完成
   }else{
      Serial.print("state=");
      Serial.println(state);
      startup == 0;
   }  
     
  };

Serial.println("startup done");
Serial.print("startup=");
Serial.println(startup);



  //讀取藍芽字元
	if(BTSerial.available()>0){
		btcmd = BTSerial.read();
    Serial.println(btcmd);
    Serial.print("speed=");
    Serial.println(speed);
	  switch (btcmd) {
		    case 'w':
		      forward();// 前進
          mp3_play (3);
		      break;
		    case 'x':
		      back();// 後退
          mp3_play (3);
		      break;
		    case 'a':
		      left();// 左轉
          mp3_play (3);
		      break;
		    case 'd':
		      right();// 右轉
          mp3_play (3);
		      break;
        case 's':
          stop();// 停止
          //mp3_play (2);
          mp3_single_loop (2);
          break;
        case '1':
          speed = speed - 30;// 減速
          if(speed < 60){
            speed = 60;
          }
          break;
        case '2':
          speed = speed + 30;// 加速
          if(speed > 240){
            speed = 240;
          }
          break;          
		    default:
		      stop();// 其他狀態也是停止
          mp3_single_loop (2);
          //mp3_play (2);
		      break;
         }
	 }

}
