#include <Servo.h>
#define LDRpin A0

Servo myservo;  // create servo object to control a servo

int LDRValue = 0;
int pos=0;
int incr=1;
int timer=0;
void setup()
{
  //myservo.attach(9);
  Serial.begin(9600);
  //myservo.write(0);
}

void loop()
{
 /* if(LDRValue>300)
  {
    
  }
  */
  LDRValue = analogRead(LDRpin);
  myservo.attach(9);

  while(LDRValue<300)
  {

    myservo.write(pos);
    delay(2);
    

  
 
    pos=pos+incr;
    timer+=1;
    //LDRValue = analogRead(LDRpin);
    LDRValue = analogRead(LDRpin);
    if(timer>1000){timer=1; incr= incr*-1;}


  }
  myservo.detach();
  //if(LDRValue>300 
  if(timer>1000){timer=1; incr= incr*-1;}
  //Serial.println("timer:");
  Serial.println(timer);
  //Serial.println("LDR:");
 // Serial.println(LDRValue);
  delay(100);
}
