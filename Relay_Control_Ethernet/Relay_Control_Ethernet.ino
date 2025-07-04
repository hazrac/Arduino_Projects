/*
 * Relay Control with Ethernet Shield
 * 
 * This project controls four relays using a SparkFun RedBoard Plus
 * with an Arduino Ethernet Shield. Relays can be controlled individually
 * or in pairs via Ethernet commands.
 * 
 * Hardware:
 * - SparkFun RedBoard Plus
 * - Arduino Ethernet Shield
 * - 4x Relay modules (connected to pins 2, 3, 4, 5)
 * 
 * Relay Pairs:
 * - Pair 1: Relays 1 & 2
 * - Pair 2: Relays 3 & 4
 * - All relays can be controlled individually
 */

#include <SPI.h>
#include <Ethernet.h>
#include <avr/pgmspace.h>
#include "config.h"


// Relay pin definitions (from config.h)
const int RELAY_1 = RELAY_1_PIN;
const int RELAY_2 = RELAY_2_PIN;
const int RELAY_3 = RELAY_3_PIN;
const int RELAY_4 = RELAY_4_PIN;

// tracking the pin activated and its state
int pin;
bool state;


// Network configuration (from config.h)
byte mac[] = MAC_ADDRESS;
IPAddress ip(IP_ADDRESS);
IPAddress gateway(GATEWAY_ADDRESS);
IPAddress subnet(SUBNET_MASK);

// Initialize Ethernet server on port 80
EthernetServer server(SERVER_PORT);

// Relay states
bool relayStates[4] = {false, false, false, false};

// Move static HTML/CSS to PROGMEM to save RAM
const char PAGE_HEADER[] PROGMEM =
  "<!DOCTYPE HTML><html><head><title>Relay Control</title></head><body><h1>Relay Control</h1>";

const char PAGE_FOOTER[] PROGMEM =
  "</body></html>";

// Function prototypes
void setRelay(int relayIndex, bool state);
void parseRequestBuffer(const char* request);
void sendHTMLPage(EthernetClient client);
void printProgmem(EthernetClient& client, const char* str);

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Relay Control System Starting...");
  
  // Initialize relay pins
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Start Ethernet connection with static IP
  Serial.println("Starting Ethernet connection with static IP...");
  
  Ethernet.begin(mac, ip, gateway, subnet);
  Serial.print("Static IP assigned: ");
  Serial.println(Ethernet.localIP());
  
  // Start the server
  server.begin();
  
  Serial.println("Relay Control System Ready!");
  Serial.println("Connect to the IP address shown above in your web browser");
}

void loop() {

  // Listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    
    // Read the first line of the request with timeout
    String requestLine = "";
    unsigned long startTime = millis();
    const unsigned long timeout = 3000; // 3 second timeout
    
    while (client.connected() && (millis() - startTime) < timeout) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          break; // End of first line
        }
        requestLine += c;
        startTime = millis(); // Reset timeout on new data
      }
      delay(1);
    }
    
    Serial.print("Request line: ");
    Serial.println(requestLine);
    
    // Always try to parse the request
    parseRequestBuffer(requestLine.c_str());
    
    // Send HTTP response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    
    // Send the HTML page
    sendHTMLPage(client);
    
    // Give the web browser time to receive the data
    delay(1);
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}

void parseRequestBuffer(const char* request) {
  Serial.println("=== PARSE REQUEST BUFFER CALLED ===");
  Serial.print("Parsing request: ");
  Serial.println(request);
  
  // Parse GET requests for relay control
  if (strstr(request, "GET") != NULL) {
    Serial.println("GET request detected");
    Serial.println(request);
    
    // Individual relay control
    if (strstr(request, "/relay1/on") != NULL) {
      setRelay(0, true);
      Serial.println("Relay 1 ON");
    } else if (strstr(request, "/relay1/off") != NULL) {
      setRelay(0, false);
      Serial.println("Relay 1 OFF");
    } else if (strstr(request, "/relay2/on") != NULL) {
      setRelay(1, true);
      Serial.println("Relay 2 ON");
    } else if (strstr(request, "/relay2/off") != NULL) {
      setRelay(1, false);
      Serial.println("Relay 2 OFF");
    } else if (strstr(request, "/relay3/on") != NULL) {
      setRelay(2, true);
      Serial.println("Relay 3 ON");
    } else if (strstr(request, "/relay3/off") != NULL) {
      setRelay(2, false);
      Serial.println("Relay 3 OFF");
    } else if (strstr(request, "/relay4/on") != NULL) {
      setRelay(3, true);
      Serial.println("Relay 4 ON");
    } else if (strstr(request, "/relay4/off") != NULL) {
      setRelay(3, false);
      Serial.println("Relay 4 OFF");
    }
    // Pair control
    else if (strstr(request, "/pair1/on") != NULL) {
      setRelay(0, true);
      setRelay(1, true);
      Serial.println("Pair 1 ON (Relays 1 & 2)");
    } else if (strstr(request, "/pair1/off") != NULL) {
      setRelay(0, false);
      setRelay(1, false);
      Serial.println("Pair 1 OFF (Relays 1 & 2)");
    } else if (strstr(request, "/pair2/on") != NULL) {
      setRelay(2, true);
      setRelay(3, true);
      Serial.println("Pair 2 ON (Relays 3 & 4)");
    } else if (strstr(request, "/pair2/off") != NULL) {
      setRelay(2, false);
      setRelay(3, false);
      Serial.println("Pair 2 OFF (Relays 3 & 4)");
    }
    // All relays control
    else if (strstr(request, "/all/on") != NULL) {
      setRelay(0, true);
      setRelay(1, true);
      setRelay(2, true);
      setRelay(3, true);
      Serial.println("All Relays ON");
    } else if (strstr(request, "/all/off") != NULL) {
      setRelay(0, false);
      setRelay(1, false);
      setRelay(2, false);
      setRelay(3, false);
      Serial.println("All Relays OFF");
    } else {
      Serial.println("No relay command found in request");
    }
  } else {
    Serial.println("No GET request detected");
  }
  Serial.println("=== PARSE REQUEST BUFFER END ===");
}

void setRelay(int relayIndex, bool state) {
  DEBUG_PRINT("setRelay called: relay=");
  DEBUG_PRINT(relayIndex);
  DEBUG_PRINT(", state=");
  DEBUG_PRINTLN(state ? "ON" : "OFF");
  
  int pin = GET_RELAY_PIN(relayIndex);
  if (pin == -1) {
    DEBUG_PRINTLN("Invalid relay index");
    return;
  }
  
  relayStates[relayIndex] = state;
  set_relay_state(pin,state);

  
  DEBUG_PRINT("Pin ");
  DEBUG_PRINT(pin);
  DEBUG_PRINT(" set to ");
  DEBUG_PRINT(state ? "ON" : "OFF");
  DEBUG_PRINT(" (");
  DEBUG_PRINT(RELAY_ACTIVE_HIGH ? (state ? "HIGH" : "LOW") : (state ? "LOW" : "HIGH"));
  DEBUG_PRINTLN(")");
}

void sendHTMLPage(EthernetClient client) {
  printProgmem(client, PAGE_HEADER);

  // Individual relay controls (minimal, no CSS)
  for (uint8_t i = 1; i <= 4; i++) {
    client.print("Relay "); client.print(i); client.print(": ");
    client.print(relayStates[i-1] ? "ON" : "OFF");
    client.print(" <a href='/relay"); client.print(i); client.print("/on'>ON</a> ");
    client.print("<a href='/relay"); client.print(i); client.print("/off'>OFF</a><br>");
  }

  // Pair controls
  client.print("<br>Pair 1 (1&2): <a href='/pair1/on'>ON</a> <a href='/pair1/off'>OFF</a><br>");
  client.print("Pair 2 (3&4): <a href='/pair2/on'>ON</a> <a href='/pair2/off'>OFF</a><br>");

  // All relays control
  client.print("<br>All: <a href='/all/on'>ON</a> <a href='/all/off'>OFF</a><br>");

  // Status (very minimal)
  client.print("<br>IP: "); client.print(Ethernet.localIP());

  printProgmem(client, PAGE_FOOTER);
}

// Helper to print PROGMEM strings to client
void printProgmem(EthernetClient& client, const char* str) {
  char c;
  while ((c = pgm_read_byte(str++))) {
    client.write(c);
  }
} 
void set_relay_state(int pin, bool state) {
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin, LOW);
  }