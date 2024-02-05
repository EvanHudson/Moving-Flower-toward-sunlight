#include <Servo.h>

#define LDRpin A0

Servo myservo;  // create a servo object to control a servo

int LDRValue = 0;
int pos = 0;
int incr = 1;
int timer = 0;
const int buttonPin = 5;
const int ledPin = 13;
const int ledPinRed = 11;//red

int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonPressCount = 0;
int currentMode = 0;
int lastMode=0;
bool rest = false;

int steps=0;
int LDRLeft=0;
int LDRRight=0;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinRed, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor
  for(int i=0; i<=20; i++)
    {
    digitalWrite(ledPin, HIGH);
    delay(20);
    digitalWrite(ledPinRed, HIGH);
    delay(20);
    digitalWrite(ledPin, LOW);
    delay(20);
    digitalWrite(ledPinRed, LOW);
    delay(20);
    }
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPinRed, LOW);
  playSong(8);

}

void slow() {
  Serial.print("LDR Value: ");
  Serial.println(LDRValue);
  if (LDRValue>300){rest=false; timer=1;}
  if (rest==false&&LDRValue < 300) {
    myservo.write(pos);
   // digitalWrite(ledPin, HIGH);

    delay(200);
    if (pos == 180) {
      incr = -incr;
    }
    if (pos == 0 && timer != 0) {
      incr = -incr;
    }
    pos = pos + incr;
    
    timer += 1;
  }
  /*
  else if(steps%30==0)
  {
    do
    {
    LDRValue = analogRead(LDRpin);

    myservo.write(pos-1);
    LDRLeft=analogRead(LDRpin);

    myservo.write(pos+2);
    LDRRight = analogRead(LDRpin);
    if(LDRValue<LDRRight) {pos=pos-1; myservo.write(pos);}
    else if(LDRValue<LDRLeft) {pos=pos-3; myservo.write(pos);}
    }
    while(LDRValue<LDRLeft || LDRValue<LDRRight);
  }
  else{
    steps+=1;
  }
  
*/
  if (timer == 3000) {
    rest = true;
    playSong(21);
    timer = 1;
  }
}

void fast() {
  Serial.print("LDR Value: ");
  Serial.println(LDRValue);
  if (LDRValue>300){rest=false; timer=1;}
  if (rest==false&&LDRValue < 300) {
    myservo.write(pos);
    //digitalWrite(ledPin, HIGH);

    delay(2);
    if (pos == 180) {
      incr = -incr;
    }
    if (pos == 0 && timer != 0) {
      incr = -incr;
    }
    pos = pos + incr;
    timer += 1;
  }
  /*******
  else if(steps%30==0)
  {
    Serial.println("executing FINDING BRIGHTEST LIGHT SOURCE");
    do
    {
    LDRValue = analogRead(LDRpin);
    Serial.println(LDRValue);
    myservo.write(pos-1);
    LDRLeft=analogRead(LDRpin);
    Serial.println(LDRLeft);
    myservo.write(pos+2);
    LDRRight = analogRead(LDRpin);
    Serial.println(LDRRight);
    if(LDRValue<LDRRight) {pos=pos+1; myservo.write(pos);Serial.println("new position right"); }
    else if(LDRValue<LDRLeft) {pos=pos-1; myservo.write(pos);Serial.println("new position left");}
    }
    while(LDRValue<LDRLeft || LDRValue<LDRRight);
  }
  else{
    steps+=1;
  }
  */
  if (timer == 30000) {
    rest = true;
    playSong(21);

    timer = 1;
  }
}

void spinRight() {
  myservo.write(pos);
  //digitalWrite(ledPinRed, HIGH);

  delay(2);
  if (pos == 180) {
    incr = -incr;
  }
  if (pos == 0 && timer != 0) {
    incr = -incr;
  }
  pos = pos + incr;
  timer += 1;
}

void spinLeft() {
  myservo.write(pos);
  //digitalWrite(ledPinRed, HIGH);

  delay(2);
  if (pos == 180) {
    incr = -incr;
  }
  if (pos == 0 && timer != 0) {
    incr = -incr;
  }
  pos = pos + incr;
  timer += 1;
}

void blinkSlow(int led) {
  digitalWrite(led, HIGH);
  delay(50);  // Adjust the delay as needed
  digitalWrite(led, LOW);
  delay(50);  // Adjust the delay as needed
}

void blinkFast(int led) {
  digitalWrite(led, HIGH);
  delay(20);  // Adjust the delay as needed
  digitalWrite(led, LOW);
  delay(20);  // Adjust the delay as needed
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        buttonPressCount++;

        if (buttonPressCount > 55) {
          buttonPressCount = 0;
        }

        // Toggle through three modes
        currentMode = buttonPressCount;
      }
    }
  }

  lastButtonState = reading;
  LDRValue = analogRead(LDRpin);
  // Perform actions based on the current mode
  if (currentMode!=lastMode)
  {
    for(int i=0; i<=currentMode; i++)
    {
    digitalWrite(ledPin, HIGH);
    delay(20);
    digitalWrite(ledPinRed, HIGH);
    delay(20);
    digitalWrite(ledPin, LOW);
    delay(20);
    digitalWrite(ledPinRed, LOW);
    delay(20);
    }

    
  }
  if (LDRValue>300)
    {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed, LOW);

        rest=false;
        timer=1;
    }
   if(rest)
   {
    Serial.println("resting");
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPinRed, LOW);
    
   }
   else
   {
  switch (currentMode) {
    case 0:
    if (LDRValue<300)     //blue regular
      {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed, LOW);


      }    
      slow();
      break;
    case 1:
    
    if (LDRValue<300)
      {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed, LOW);


      }    
      fast();
      break;
    case 2:
    if (LDRValue<300)
      {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed, LOW);


      }    
      spinRight();
      break;
    case 3:
    if (LDRValue<300)
      {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed, LOW);


      }    
      spinLeft();
      break;
    case 4:
    if (LDRValue<300)
      {
        digitalWrite(ledPin, LOW);     //red regular
        digitalWrite(ledPinRed, HIGH);


      }    
      slow();
      break;
    case 5:
    
    if (LDRValue<300)
      {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed, HIGH);


      }    
      fast();
      break;
    case 6:
        if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed, HIGH);


      } 
      spinRight();
      break;
    case 7:
    if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed, HIGH);


      } 
      spinLeft();
      break;    
    case 8:
    if (LDRValue<300)   //blue blink slow
      {
        blinkSlow(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      slow();
      break;
    case 9:
    
    if (LDRValue<300)
      {
        blinkSlow(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      fast();
      break;
    case 10:
    if (LDRValue<300)
      {
        blinkSlow(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      spinRight();
      break;
    case 11:
    if (LDRValue<300)
      {
        blinkSlow(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      spinLeft();
      break;
    case 12:
    if (LDRValue<300)
      {       //red blink slow
        digitalWrite(ledPin, LOW);
        blinkSlow(ledPinRed);


      }    
      slow();
      break;
    case 13:
    
    if (LDRValue<300)
      {
        digitalWrite(ledPin, LOW);
        blinkSlow(ledPinRed);


      }    
      fast();
      break;
    case 14:
        if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        blinkSlow(ledPinRed);


      } 
      spinRight();
      break;
    case 15:
    if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        blinkSlow(ledPinRed);


      } 
      spinLeft();
      break; 
    case 16:
    if (LDRValue<300)
      {                                     //blue blink fast
        blinkFast(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      slow();
      break;
    case 17:
    
    if (LDRValue<300)
      {
        blinkFast(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      fast();
      break;
    case 18:
    if (LDRValue<300)
      {
        blinkFast(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      spinRight();
      break;
    case 19:
    if (LDRValue<300)                                       //red blink fast
      {
        blinkFast(ledPin);
        digitalWrite(ledPinRed, LOW);


      }    
      spinLeft();
      break;
    case 20:
    if (LDRValue<300)
      {
        digitalWrite(ledPin, LOW);
        blinkFast(ledPinRed);


      }    
      slow();
      break;
    case 21:
    
    if (LDRValue<300)
      {
        digitalWrite(ledPin, LOW);
        blinkFast(ledPinRed);


      }    
      fast();
      break;
    case 22:
        if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        blinkFast(ledPinRed);


      } 
      spinRight();
      break;
    case 23:
    if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        blinkFast(ledPinRed);


      } 
      spinLeft();
      break; 
    case 24:          //flashing red blue
     if (LDRValue<300)

      {
        digitalWrite(ledPin, HIGH);
        delay(30);
        digitalWrite(ledPinRed, HIGH);
        delay(30);
        digitalWrite(ledPin, LOW);
        delay(30);
        digitalWrite(ledPinRed, LOW);
        delay(30);


      } 
      slow();
      break; 
    case 25:
     if (LDRValue<300)

      {
        digitalWrite(ledPin, HIGH);
        delay(30);
        digitalWrite(ledPinRed, HIGH);
        delay(30);
        digitalWrite(ledPin, LOW);
        delay(30);
        digitalWrite(ledPinRed, LOW);
        delay(30);


      } 
      fast();
      break; 
    case 26:
     if (LDRValue<300)

      {
        digitalWrite(ledPin, HIGH);
        delay(30);
        digitalWrite(ledPinRed, HIGH);
        delay(30);
        digitalWrite(ledPin, LOW);
        delay(30);
        digitalWrite(ledPinRed, LOW);
        delay(30);


      } 
      spinRight();
      break; 
   case 27:
     if (LDRValue<300)

      {
        digitalWrite(ledPin, HIGH);
        delay(30);
        digitalWrite(ledPinRed, HIGH);
        delay(30);
        digitalWrite(ledPin, LOW);
        delay(30);
        digitalWrite(ledPinRed, LOW);
        delay(30);


      } 
      spinLeft();
      break; 
    
    case 28:                    //just lights
    if (LDRValue<300)

      {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed, LOW);


      } 
      //spinLeft();
      break; 
    case 29:
    if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed, HIGH);


      } 
      //spinLeft();
      break; 
    case 30:
    if (LDRValue<300)

      {
        blinkSlow(ledPin);
        digitalWrite(ledPinRed, LOW);


      } 
      //spinLeft();
      break;   
    case 31:
    if (LDRValue<300)

      {
        blinkFast(ledPin);
        digitalWrite(ledPinRed, LOW);


      } 
      //spinLeft();
      break; 
    case 32:
    if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);

        blinkSlow(ledPinRed);


      } 
      //spinLeft();
      break;   
   case 33:
    if (LDRValue<300)

      {
        digitalWrite(ledPin, LOW);

        blinkFast(ledPinRed);


      } 
      //spinLeft();
      break; 
   case 34:
     if (LDRValue<300)

      {
        digitalWrite(ledPin, HIGH);
        delay(10);
        digitalWrite(ledPinRed, HIGH);
        delay(10);
        digitalWrite(ledPin, LOW);
        delay(10);
        digitalWrite(ledPinRed, LOW);
        delay(10);


      } 
      //slow();
      break; 


      /////////////////////////////////music
   case 35:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(1);
    }
      //spinLeft();
      break; 
   case 36:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(2);
    }
      //spinLeft();
      break; 
         case 37:
    if (LDRValue<300)

      {
       digitalWrite(ledPinRed,HIGH);

 
        digitalWrite(ledPin, HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
       digitalWrite(ledPinRed,HIGH);
 
        digitalWrite(ledPin, HIGH);
      playSong(3);
    }
      //spinLeft();
      break; 
         case 38:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(4);
    }
      //spinLeft();
      break; 
         case 39:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(5);
    }
      //spinLeft();
      break; 
        case 40:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(6);
    }
      //spinLeft();
      break; 
      case 41:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(7);
    }
      //spinLeft();
      break; 
     case 42:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(9);
    }
      //spinLeft();
      break; 
      case 43:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(10);
    }
      //spinLeft();
      break; 
            case 44:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(11);
    }
      //spinLeft();
      break; 
            case 45:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(12);
    }
      //spinLeft();
      break; 
            case 46:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(13);
    }
      //spinLeft();
      break;
            case 47:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(14);
    }
      //spinLeft();
      break;  
            case 48:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(15);
    }
      //spinLeft();
      break; 
            case 49:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(16);
    }
      //spinLeft();
      break; 
            case 50:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(17);
    }
      //spinLeft();
      break; 
            case 51:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(18);
    }
      //spinLeft();
      break; 
            case 52:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,LOW);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(19);
    }
      //spinLeft();
      break; 
            case 53:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(20);
    }
      //spinLeft();
      break; 
            case 54:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(22);
    }
      //spinLeft();
      break; 
            case 55:
    if (LDRValue<300)

      {
 
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPinRed,HIGH);


      } 
    if(lastMode!= currentMode&&LDRValue<300)
    {
      playSong(23);
    }
      //spinLeft();
      break; 
    default:
      Serial.println("Default Case");
      slow();
      break;
  }
  lastMode=currentMode;//last mode logic so turn led on when switch modes and on during finding stage in dark also implement logic when dark for five minutes

  Serial.println("Mode: " + String(currentMode) + " LDR: " + String(LDRValue));
   }
}
