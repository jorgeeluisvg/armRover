#include <Servo.h>
#define numOfValsRec 10
#define digitsPerValRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

//PUENTE H VARIABLES
int in1 = 12;
int in2 = 13;
int ENA = 6;
int ENB = 5;
int in1b = 2;
int in2b = 3;

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;//$00000
int counter = 0;
bool counterStart = false;
String receivedString;

void setup() {
  Serial.begin(9600);
  //<-- SERVOS SETUP-->
  servoThumb.attach(7);
  servoIndex.attach(9);
  servoMiddle.attach(11);
  servoRing.attach(8);
  servoPinky.attach(10);

  //<-- PUENTE H SETUP-->
  pinMode(in1,OUTPUT); //12
  pinMode(in2,OUTPUT); //13
  pinMode(ENA,OUTPUT); //6
  
  pinMode(in1b,OUTPUT); //2
  pinMode(in2b,OUTPUT); //3
  pinMode(ENB,OUTPUT); //5
}

void receiveData(){
  while(Serial.available())
  {
    char c = Serial.read();

    if(c=='$'){
      counterStart = true;
    }
    if(counterStart){
      if(counter < stringLength){
        receivedString = String(receivedString+c);
        counter++;
      }
      if (counter >= stringLength){
        //$00000
        for(int i =0; i<numOfValsRec; i++)
        {
          int num = (i*digitsPerValRec)+1;
          valsRec[i] = receivedString.substring(num,num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}
void loop() {
  receiveData();
  if(valsRec[0] == 1){servoThumb.write(180);}else{servoThumb.write(0);}
  if(valsRec[1] == 1){servoIndex.write(180);}else{servoIndex.write(0);}
  if(valsRec[2] == 1){servoMiddle.write(180);}else{servoMiddle.write(0);}
  if(valsRec[3] == 1){servoRing.write(180);}else{servoRing.write(0);}
  if(valsRec[4] == 1){servoPinky.write(180);}else{servoPinky.write(0);}

  //<-- Puente H -->
  if(valsRec[5] == 1){analogWrite(ENA,180);digitalWrite(in1,HIGH);digitalWrite(in2,LOW);}else{analogWrite(ENA,0);digitalWrite(in1,LOW);digitalWrite(in2,LOW);}
  if(valsRec[6] == 1){analogWrite(ENB,180);digitalWrite(in1b,HIGH);digitalWrite(in2b,LOW);}else{analogWrite(ENB,0);digitalWrite(in1b,LOW);digitalWrite(in2b,LOW);}
  if(valsRec[7] == 1){}else{}
  if(valsRec[8] == 1){}else{}
  if(valsRec[9] == 1){}else{}

  delay(300);
  Serial.println(valsRec[0]);
  Serial.println(valsRec[1]);
  Serial.println(valsRec[2]);
  Serial.println(valsRec[3]);
  Serial.println(valsRec[4]);
  Serial.println();
}
