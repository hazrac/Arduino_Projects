/*
 * Relay Test Sketch
 * 
 * Simple test to verify relay connections and functionality
 * before using the full Ethernet control system.
 * 
 * This sketch will cycle through each relay individually,
 * then test pairs, and finally test all relays together.
 */

// Relay pin definitions
const int RELAY_1 = 2;
const int RELAY_2 = 3;
const int RELAY_3 = 4;
const int RELAY_4 = 5;

// Test timing
const int RELAY_ON_TIME = 1000;  // 1 second
const int RELAY_OFF_TIME = 500;  // 0.5 seconds
const int PAUSE_BETWEEN_TESTS = 2000;  // 2 seconds

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Relay Test System Starting...");
  
  // Initialize relay pins
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  
  // Initialize all relays to OFF state
  digitalWrite(RELAY_1, HIGH);  // HIGH = OFF (assuming active-low relays)
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
  
  Serial.println("All relays initialized to OFF state");
  Serial.println("Starting relay test sequence...");
  Serial.println();
}

void loop() {
  // Test individual relays
  Serial.println("=== Testing Individual Relays ===");
  
  testRelay(1, RELAY_1);
  testRelay(2, RELAY_2);
  testRelay(3, RELAY_3);
  testRelay(4, RELAY_4);
  
  delay(PAUSE_BETWEEN_TESTS);
  
  // Test relay pairs
  Serial.println("=== Testing Relay Pairs ===");
  
  Serial.println("Testing Pair 1 (Relays 1 & 2)");
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  Serial.println("Pair 1 ON");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  Serial.println("Pair 1 OFF");
  delay(RELAY_OFF_TIME);
  
  Serial.println("Testing Pair 2 (Relays 3 & 4)");
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  Serial.println("Pair 2 ON");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
  Serial.println("Pair 2 OFF");
  delay(RELAY_OFF_TIME);
  
  delay(PAUSE_BETWEEN_TESTS);
  
  // Test all relays
  Serial.println("=== Testing All Relays ===");
  
  Serial.println("All relays ON");
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  delay(RELAY_ON_TIME);
  
  Serial.println("All relays OFF");
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
  delay(RELAY_OFF_TIME);
  
  delay(PAUSE_BETWEEN_TESTS);
  
  // Sequential pattern test
  Serial.println("=== Testing Sequential Pattern ===");
  
  // Pattern: 1, 12, 123, 1234, 234, 34, 4, off
  digitalWrite(RELAY_1, LOW);
  Serial.println("Relay 1 ON");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_2, LOW);
  Serial.println("Relay 2 ON");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_3, LOW);
  Serial.println("Relay 3 ON");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_4, LOW);
  Serial.println("Relay 4 ON");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_1, HIGH);
  Serial.println("Relay 1 OFF");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_2, HIGH);
  Serial.println("Relay 2 OFF");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_3, HIGH);
  Serial.println("Relay 3 OFF");
  delay(RELAY_ON_TIME);
  
  digitalWrite(RELAY_4, HIGH);
  Serial.println("Relay 4 OFF");
  delay(RELAY_ON_TIME);
  
  delay(PAUSE_BETWEEN_TESTS);
  
  Serial.println("=== Test Cycle Complete ===");
  Serial.println("Starting next cycle in 5 seconds...");
  Serial.println();
  delay(5000);
}

void testRelay(int relayNumber, int pin) {
  Serial.print("Testing Relay ");
  Serial.print(relayNumber);
  Serial.println(" ON");
  digitalWrite(pin, LOW);
  delay(RELAY_ON_TIME);
  
  Serial.print("Testing Relay ");
  Serial.print(relayNumber);
  Serial.println(" OFF");
  digitalWrite(pin, HIGH);
  delay(RELAY_OFF_TIME);
} 