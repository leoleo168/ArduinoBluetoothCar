//BtCarv2.ino
//藍芽腳位
#include <SoftwareSerial.h>
SoftwareSerial BT(11, 12);
char btcmd; //藍芽指令


//pin腳設定
const byte ENA = 5;
const byte ENB = 6;
const byte IN1 = 7;
const byte IN2 = 8;
const byte IN3 = 9;
const byte IN4 = 10;

//速度設定
int speed;

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

//主程式

void setup() {
	pinMode(ENA, OUTPUT);
	pinMode(ENB, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	Serial.begin(9600);
	BT.begin(9600);
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
}




void loop() {	
	//讀取藍芽字元
	if(BT.available()>0){
		btcmd = BT.read();
    Serial.println(btcmd);
    Serial.print("speed=");
    Serial.println(speed);
	  switch (btcmd) {
		    case 'w':
		      forward();// 前進
		      break;
		    case 'x':
		      back();// 後退
		      break;
		    case 'a':
		      left();// 左轉
		      break;
		    case 'd':
		      right();// 右轉
		      break;
        case 's':
          stop();// 停止
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
		      break;
         }
	 }

}
