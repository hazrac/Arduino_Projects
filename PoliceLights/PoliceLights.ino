// Project 1 - Police Lights by Dave1324

int ledDelay = 50; // delay by 50ms
int redPin = 11;
int bluePin = 9;


void setup() {
 Serial.begin(9600);
    
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {

digitalWrite(redPin, HIGH); // turn the red light on
Serial.println("Red!");
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, LOW); // turn the red light off
Serial.println("Red!");
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, HIGH); // turn the red light on
Serial.println("Red!");
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, LOW); // turn the red light off
Serial.println("Red!");
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, HIGH); // turn the red light on
Serial.println("Red!");
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, LOW); // turn the red light off
Serial.println("Red!");
delay(ledDelay); // wait 50 ms

delay(100); // delay midpoint by 100ms

digitalWrite(bluePin, HIGH); // turn the blue light on
Serial.println("Blue!");
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, LOW); // turn the blue light off
Serial.println("Blue!");
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, HIGH); // turn the blue light on
Serial.println("Blue!");
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, LOW); // turn the blue light off
Serial.println("Blue!");
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, HIGH); // turn the blue light on
Serial.println("Blue!");
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, LOW); // turn the blue light off
Serial.println("Blue!");
delay(ledDelay); // wait 50 ms

}
