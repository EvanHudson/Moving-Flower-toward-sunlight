const int buttonPin = 5;
const int ledPin = 13;
int button_timer = 0;
int buttonState = 0;
int buttonPressCount = 0;
int currentMode = 0;
bool button = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor
  digitalWrite(ledPin, LOW);
}

int debounceButton() {
  delay(50);  // Adjust the delay as needed
  return digitalRead(buttonPin);
}

void turnOnLed() {
  digitalWrite(ledPin, HIGH);
}

void blinkSlow() {
  digitalWrite(ledPin, HIGH);
  delay(500);  // Adjust the delay as needed
  digitalWrite(ledPin, LOW);
  delay(500);  // Adjust the delay as needed
}

void blinkFast() {
  digitalWrite(ledPin, HIGH);
  delay(200);  // Adjust the delay as needed
  digitalWrite(ledPin, LOW);
  delay(200);  // Adjust the delay as needed
}

void loop() {
  buttonState = debounceButton();

  if (buttonState == LOW && !button) {
    buttonPressCount++;
    button = true;
    if(buttonPressCount==4)
    {
      buttonPressCount=0;
    }
    
    // Reset buttonPressCount and currentMode if more than 3 seconds have passed
    if (button_timer > 3000) {
      buttonPressCount = 1;
      currentMode = 0;
    }

    // Toggle through three modes
    currentMode = buttonPressCount % 4;

    // Perform actions based on the current mode
    switch (currentMode) {
      case 1:
        turnOnLed();
        break;
      case 2:
        blinkSlow();
        break;
      case 3:
        blinkFast();
        break;
      default:
        digitalWrite(ledPin, LOW);  // Default mode, turn off LED
        break;
    }
  } else if (buttonState == HIGH && button) {
    button = false;
  }

  Serial.println(currentMode);

  button_timer++;
  if (button_timer > 3000) {
    button_timer = 0;
    buttonPressCount = 0;
    currentMode = 0;
  }
}
