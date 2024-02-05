#include <Servo.h>
#define LDRpin A0

Servo myservo;  // create servo object to control a servo

int LDRValue = 0;
int pos=0;
int incr=1;
int timer=0;
void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0);
}

void loop()
{
  LDRValue = analogRead(LDRpin);
  if(LDRValue<300)
  {
    myservo.write(pos);
    delay(2);
    if(pos==180){

      incr=(-1)*incr;;
    }
    if(pos==0&&timer!=0){

      incr=(-1)*incr;;
    }    
     // incr=(-1)*incr;
    
    pos=pos+incr;
    timer+=1;
    //LDRValue = analogRead(LDRpin);
  }
  //if(LDRValue>300 
  if(timer==1000){timer=1;}
  //Serial.println("timer:");
  //Serial.println(timer);
  //Serial.println("LDR:");
  //Serial.println(LDRValue);
  delay(100);
}
