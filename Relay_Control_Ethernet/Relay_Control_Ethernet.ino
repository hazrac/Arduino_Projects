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

// Relay pin definitions
const int RELAY_1 = 2;
const int RELAY_2 = 3;
const int RELAY_3 = 4;
const int RELAY_4 = 5;

// Network configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Initialize Ethernet server on port 80
EthernetServer server(80);

// Relay states
bool relayStates[4] = {false, false, false, false};

// Move static HTML/CSS to PROGMEM to save RAM
const char PAGE_HEADER[] PROGMEM =
  "<!DOCTYPE HTML><html><head><title>Relay Control</title></head><body><h1>Relay Control</h1>";

const char PAGE_FOOTER[] PROGMEM =
  "</body></html>";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Relay Control System Starting...");
  
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
  
  // Start Ethernet connection
  Ethernet.begin(mac, ip, gateway, subnet);
  
  // Start the server
  server.begin();
  
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("Relay Control System Ready!");
}

void loop() {
  // Listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    
    // An HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    String currentLine = "";
    String request = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        
        // If you've got to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // Send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          
          // Send the HTML page
          sendHTMLPage(client);
          break;
        }
        
        if (c == '\n') {
          // You're starting a new line
          currentLineIsBlank = true;
          currentLine = "";
        } else if (c != '\r') {
          // You've gotten a character on the current line
          currentLineIsBlank = false;
          currentLine += c;
        }
      }
    }
    
    // Parse the request for relay commands
    parseRequest(request);
    
    // Give the web browser time to receive the data
    delay(1);
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}

void parseRequest(String request) {
  // Parse GET requests for relay control
  if (request.indexOf("GET") != -1) {
    // Individual relay control
    if (request.indexOf("/relay1/on") != -1) {
      setRelay(0, true);
      Serial.println("Relay 1 ON");
    } else if (request.indexOf("/relay1/off") != -1) {
      setRelay(0, false);
      Serial.println("Relay 1 OFF");
    } else if (request.indexOf("/relay2/on") != -1) {
      setRelay(1, true);
      Serial.println("Relay 2 ON");
    } else if (request.indexOf("/relay2/off") != -1) {
      setRelay(1, false);
      Serial.println("Relay 2 OFF");
    } else if (request.indexOf("/relay3/on") != -1) {
      setRelay(2, true);
      Serial.println("Relay 3 ON");
    } else if (request.indexOf("/relay3/off") != -1) {
      setRelay(2, false);
      Serial.println("Relay 3 OFF");
    } else if (request.indexOf("/relay4/on") != -1) {
      setRelay(3, true);
      Serial.println("Relay 4 ON");
    } else if (request.indexOf("/relay4/off") != -1) {
      setRelay(3, false);
      Serial.println("Relay 4 OFF");
    }
    // Pair control
    else if (request.indexOf("/pair1/on") != -1) {
      setRelay(0, true);
      setRelay(1, true);
      Serial.println("Pair 1 ON (Relays 1 & 2)");
    } else if (request.indexOf("/pair1/off") != -1) {
      setRelay(0, false);
      setRelay(1, false);
      Serial.println("Pair 1 OFF (Relays 1 & 2)");
    } else if (request.indexOf("/pair2/on") != -1) {
      setRelay(2, true);
      setRelay(3, true);
      Serial.println("Pair 2 ON (Relays 3 & 4)");
    } else if (request.indexOf("/pair2/off") != -1) {
      setRelay(2, false);
      setRelay(3, false);
      Serial.println("Pair 2 OFF (Relays 3 & 4)");
    }
    // All relays control
    else if (request.indexOf("/all/on") != -1) {
      setRelay(0, true);
      setRelay(1, true);
      setRelay(2, true);
      setRelay(3, true);
      Serial.println("All Relays ON");
    } else if (request.indexOf("/all/off") != -1) {
      setRelay(0, false);
      setRelay(1, false);
      setRelay(2, false);
      setRelay(3, false);
      Serial.println("All Relays OFF");
    }
  }
}

void setRelay(int relayIndex, bool state) {
  int pin;
  switch (relayIndex) {
    case 0: pin = RELAY_1; break;
    case 1: pin = RELAY_2; break;
    case 2: pin = RELAY_3; break;
    case 3: pin = RELAY_4; break;
    default: return;
  }
  
  relayStates[relayIndex] = state;
  digitalWrite(pin, state ? LOW : HIGH);  // LOW = ON, HIGH = OFF (active-low)
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