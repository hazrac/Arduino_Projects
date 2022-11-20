void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int dl = 500;

  for (unsigned i=0; i<3; ++i) {
    blinkFunc(dl);
  }

  dl = 1000;

  for (unsigned i=0; i<3; ++i) {
    blinkFunc(dl);
  }

  dl = 500;

  for (unsigned i=0; i<3; ++i) {
    blinkFunc(dl);
  }

  delay(3000);
}


  void blinkFunc (int dl) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(dl);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(dl);                      // wait for a second
  }
