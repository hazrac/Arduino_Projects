/* Sketch to create a 4 EL wire nightlight using SparkFun's El Escudo Dos and a button
Right now -> turn EL channels (A-D) on with the press of a button

Eventually turn on EL channels A&B on one press, turn them off while turning C&D on two presses
turn A,B,C,D on three presses, and turn them all off on four presses.
If the lights are on, turn them off after 30 minutes.

Created by David Mitchell (@hazrac)
Credit to Mike Grusin of SparkFun Electronics & Tom Igoe

Notes from button Sketch:
 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

*/

// static variables:
// set the buttonPin
const int buttonPin = 11;
// set the EL pins
const int ledPinA = 2;
const int ledPinB = 3;
const int ledPinC = 4;
const int ledPinD = 5;
// set your timeout
const int timeOut = 1800000; // 30 min is 1800000ms
// set Debonce Time
const long debounceDelay = 20;    // the debounce time; increase if the output flickers

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonPushCounter = 0;   // counter for the number of button presses, should be 0
int lastbuttonPushCounter = 0; // just a holder until I figure this out
int lastButtonState = 0;     // previous state of the button
long lastDebounceTime = 0;  // the last time the output pin was toggled


void setup() {
  // The EL channels are on pins 2 through 9
  // Initialize the pins as outputs
  pinMode(ledPinA, OUTPUT);  // channel A
  pinMode(ledPinB, OUTPUT);  // channel B
  pinMode(ledPinC, OUTPUT);  // channel C
  pinMode(ledPinD, OUTPUT);  // channel D
  

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // Serial.println(buttonState);
  // If the switch changed, due to noise or pressing:
  if (buttonState != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    Serial.print("millis minus last debounce");
    Serial.println(millis() - lastDebounceTime);
    Serial.print("debounce delay:");
    Serial.println(debounceDelay);


    if ((millis() - lastDebounceTime) > debounceDelay) {
        // if the state has changed, increment the counter
        if (buttonState == 1) {
         // if the current state is HIGH then the button
         // went from off to on:
         buttonPushCounter++;
         Serial.println("on");
         Serial.print("number of button pushes:  ");
         Serial.println(buttonPushCounter);
       }
     }
  }

  Serial.print("button push counter: ");
  Serial.println(buttonPushCounter);
  // This needs to be a case statement
  if (buttonPushCounter != lastbuttonPushCounter) {
    switch (buttonPushCounter) {
      case 1:
        //Button pushed once white light
        digitalWrite(ledPinA, HIGH);   // turn the EL channel on
        digitalWrite(ledPinB, HIGH);   // turn the EL channel on
        Serial.println("Case 1");
        break;
      case 2:
        //Button pushed twice blue light
        digitalWrite(ledPinA, LOW);   // turn the EL channel off
        digitalWrite(ledPinB, LOW);   // turn the EL channel off
        digitalWrite(ledPinC, HIGH);   // turn the EL channel on
        digitalWrite(ledPinD, HIGH);   // turn the EL channel on
        Serial.println("Case 2");
        break;
      case 3:
        //Button pushed three times blue & white lights
        digitalWrite(ledPinA, HIGH);   // turn the EL channel on
        digitalWrite(ledPinB, HIGH);   // turn the EL channel on
        digitalWrite(ledPinC, HIGH);   // turn the EL channel on
        digitalWrite(ledPinD, HIGH);   // turn the EL channel on
        Serial.println("Case 3");
        break;
      case 4:
        // Turn EL wire off and reset counter
        digitalWrite(ledPinA, LOW);   // turn the EL channel off
        digitalWrite(ledPinB, LOW);   // turn the EL channel off
        digitalWrite(ledPinC, LOW);   // turn the EL channel off
        digitalWrite(ledPinD, LOW);   // turn the EL channel off
        Serial.println("Case 4");
        buttonPushCounter = 0;
        break;
    } // switch statement end
  }  // if push button counter change end

    // when last debounce time - now is greater than timeout shutoff lights
    if ((millis() - lastDebounceTime) > timeOut) {
      digitalWrite(ledPinA, LOW);   // turn the EL channel off
      digitalWrite(ledPinB, LOW);   // turn the EL channel off
      digitalWrite(ledPinC, LOW);   // turn the EL channel off
      digitalWrite(ledPinD, LOW);   // turn the EL channel off
      Serial.println("Hit timeout");
      buttonPushCounter = 0;
    }

    lastbuttonPushCounter = buttonPushCounter;
    lastButtonState = buttonState;

}
