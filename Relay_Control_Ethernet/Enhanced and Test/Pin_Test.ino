/*
 * Simple Pin Test for Arduino Uno
 * Tests if pin 2 can be controlled properly
 */

const int TEST_PIN = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("Pin Test Starting...");
  
  pinMode(TEST_PIN, OUTPUT);
  
  Serial.println("Pin 2 initialized as OUTPUT");
  Serial.println("Pin 2 will cycle: HIGH (5V) -> LOW (0V) -> HIGH (5V)");
}

void loop() {
  Serial.println("Pin 2: HIGH (5V)");
  digitalWrite(TEST_PIN, HIGH);
  delay(3000);
  
  Serial.println("Pin 2: LOW (0V)");
  digitalWrite(TEST_PIN, LOW);
  delay(3000);
} 