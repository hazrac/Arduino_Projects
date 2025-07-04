/*
 * Enhanced Relay Control with Ethernet Shield
 * 
 * This enhanced version includes:
 * - Configuration file support
 * - State persistence (optional)
 * - Better error handling
 * - Enhanced debug output
 * - Safety features
 * 
 * Hardware:
 * - SparkFun RedBoard Plus
 * - Arduino Ethernet Shield
 * - 4x Relay modules
 */

#include <SPI.h>
#include <Ethernet.h>
#include "Config.h"

#if ENABLE_STATE_PERSISTENCE
#include <EEPROM.h>
#endif

// Network configuration using Config.h
byte mac[] = MAC_ADDRESS;
IPAddress ip(IP_ADDRESS);
IPAddress gateway(GATEWAY_ADDRESS);
IPAddress subnet(SUBNET_MASK);

// Initialize Ethernet server
EthernetServer server(SERVER_PORT);

// Relay states
bool relayStates[4] = {false, false, false, false};

// Connection status
bool ethernetConnected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_BAUD_RATE);
  DEBUG_PRINTLN("Enhanced Relay Control System Starting...");
  
  // Initialize relay pins
  initializeRelays();
  
  // Load saved states if persistence is enabled
  #if ENABLE_STATE_PERSISTENCE
  loadRelayStates();
  #endif
  
  // Initialize Ethernet connection
  initializeEthernet();
  
  DEBUG_PRINTLN("Enhanced Relay Control System Ready!");
}

void loop() {
  // Maintain Ethernet connection
  maintainEthernetConnection();
  
  // Handle web clients
  handleWebClients();
  
  // Small delay to prevent overwhelming the system
  delay(10);
}

void initializeRelays() {
  DEBUG_PRINTLN("Initializing relay pins...");
  
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
  pinMode(RELAY_4_PIN, OUTPUT);
  
  // Initialize all relays to OFF state
  SET_RELAY_STATE(RELAY_1_PIN, false);
  SET_RELAY_STATE(RELAY_2_PIN, false);
  SET_RELAY_STATE(RELAY_3_PIN, false);
  SET_RELAY_STATE(RELAY_4_PIN, false);
  
  DEBUG_PRINTLN("All relays initialized to OFF state");
}

void initializeEthernet() {
  DEBUG_PRINTLN("Initializing Ethernet connection...");
  
  // Start Ethernet connection
 // if (Ethernet.begin(mac, ip, gateway, subnet)) {
 //   ethernetConnected = true;
 //   DEBUG_PRINT("Ethernet initialized successfully. IP: ");
 //   DEBUG_PRINTLN(Ethernet.localIP());
 // } else {
 //   DEBUG_PRINTLN("Failed to configure Ethernet using DHCP");
 //   DEBUG_PRINTLN("Using static IP configuration...");
    
    // Try static configuration
    Ethernet.begin(mac, ip, gateway, subnet);
    DEBUG_PRINTLN("This is what I say your IP is: ");
    DEBUG_PRINT(ip);
    ethernetConnected = true;
    DEBUG_PRINT("Static IP configured: ");
    DEBUG_PRINTLN(Ethernet.localIP());
  }
  
  // Start the server
  server.begin();
  DEBUG_PRINT("Server started on port ");
  DEBUG_PRINTLN(SERVER_PORT);
}

void maintainEthernetConnection() {
  // Check if Ethernet connection is still active
  if (!ethernetConnected) {
    DEBUG_PRINTLN("Ethernet connection lost. Attempting to reconnect...");
    initializeEthernet();
  }
}

void handleWebClients() {
  // Listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    DEBUG_PRINTLN_DETAILED("New client connected");
    
    // An HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    String currentLine = "";
    String request = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        
        // If you've got to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended
        if (c == '\n' && currentLineIsBlank) {
          // Send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          
          // Send the HTML page
          sendEnhancedHTMLPage(client);
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
    parseEnhancedRequest(request);
    
    // Give the web browser time to receive the data
    delay(1);
    
    // Close the connection
    client.stop();
    DEBUG_PRINTLN_DETAILED("Client disconnected");
  }
}

void parseEnhancedRequest(String request) {
  DEBUG_PRINT_VERBOSE("Request received: ");
  DEBUG_PRINTLN_VERBOSE(request);
  
  // Parse GET requests for relay control
  if (request.indexOf("GET") != -1) {
    // Individual relay control
    if (request.indexOf("/relay1/on") != -1) {
      setRelayEnhanced(0, true);
      DEBUG_PRINTLN("Relay 1 ON");
    } else if (request.indexOf("/relay1/off") != -1) {
      setRelayEnhanced(0, false);
      DEBUG_PRINTLN("Relay 1 OFF");
    } else if (request.indexOf("/relay2/on") != -1) {
      setRelayEnhanced(1, true);
      DEBUG_PRINTLN("Relay 2 ON");
    } else if (request.indexOf("/relay2/off") != -1) {
      setRelayEnhanced(1, false);
      DEBUG_PRINTLN("Relay 2 OFF");
    } else if (request.indexOf("/relay3/on") != -1) {
      setRelayEnhanced(2, true);
      DEBUG_PRINTLN("Relay 3 ON");
    } else if (request.indexOf("/relay3/off") != -1) {
      setRelayEnhanced(2, false);
      DEBUG_PRINTLN("Relay 3 OFF");
    } else if (request.indexOf("/relay4/on") != -1) {
      setRelayEnhanced(3, true);
      DEBUG_PRINTLN("Relay 4 ON");
    } else if (request.indexOf("/relay4/off") != -1) {
      setRelayEnhanced(3, false);
      DEBUG_PRINTLN("Relay 4 OFF");
    }
    // Pair control
    else if (request.indexOf("/pair1/on") != -1) {
      setRelayEnhanced(PAIR_1_RELAY_1, true);
      setRelayEnhanced(PAIR_1_RELAY_2, true);
      DEBUG_PRINTLN("Pair 1 ON (Relays 1 & 2)");
    } else if (request.indexOf("/pair1/off") != -1) {
      setRelayEnhanced(PAIR_1_RELAY_1, false);
      setRelayEnhanced(PAIR_1_RELAY_2, false);
      DEBUG_PRINTLN("Pair 1 OFF (Relays 1 & 2)");
    } else if (request.indexOf("/pair2/on") != -1) {
      setRelayEnhanced(PAIR_2_RELAY_1, true);
      setRelayEnhanced(PAIR_2_RELAY_2, true);
      DEBUG_PRINTLN("Pair 2 ON (Relays 3 & 4)");
    } else if (request.indexOf("/pair2/off") != -1) {
      setRelayEnhanced(PAIR_2_RELAY_1, false);
      setRelayEnhanced(PAIR_2_RELAY_2, false);
      DEBUG_PRINTLN("Pair 2 OFF (Relays 3 & 4)");
    }
    // All relays control
    else if (request.indexOf("/all/on") != -1) {
      setAllRelaysEnhanced(true);
      DEBUG_PRINTLN("All Relays ON");
    } else if (request.indexOf("/all/off") != -1) {
      setAllRelaysEnhanced(false);
      DEBUG_PRINTLN("All Relays OFF");
    }
    // Status request
    else if (request.indexOf("/status") != -1) {
      DEBUG_PRINTLN("Status request received");
    }
  }
}

void setRelayEnhanced(int relayIndex, bool state) {
  // Safety check
  if (relayIndex < 0 || relayIndex >= 4) {
    DEBUG_PRINTLN("Invalid relay index");
    return;
  }
  
  // Check maximum simultaneous relays limit
  if (state && MAX_SIMULTANEOUS_RELAYS > 0) {
    int currentOnCount = 0;
    for (int i = 0; i < 4; i++) {
      if (relayStates[i]) currentOnCount++;
    }
    
    if (currentOnCount >= MAX_SIMULTANEOUS_RELAYS) {
      DEBUG_PRINTLN("Maximum simultaneous relays limit reached");
      return;
    }
  }
  
  int pin = GET_RELAY_PIN(relayIndex);
  if (pin == -1) {
    DEBUG_PRINTLN("Invalid relay pin");
    return;
  }
  
  relayStates[relayIndex] = state;
  SET_RELAY_STATE(pin, state);
  
  // Save state if persistence is enabled
  #if ENABLE_STATE_PERSISTENCE
  saveRelayStates();
  #endif
  
  DEBUG_PRINT_DETAILED("Relay ");
  DEBUG_PRINT_DETAILED(relayIndex + 1);
  DEBUG_PRINT_DETAILED(" set to ");
  DEBUG_PRINTLN_DETAILED(state ? "ON" : "OFF");
}

void setAllRelaysEnhanced(bool state) {
  for (int i = 0; i < 4; i++) {
    setRelayEnhanced(i, state);
  }
}

#if ENABLE_STATE_PERSISTENCE
void saveRelayStates() {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(i, relayStates[i] ? 1 : 0);
  }
  DEBUG_PRINTLN_VERBOSE("Relay states saved to EEPROM");
}

void loadRelayStates() {
  for (int i = 0; i < 4; i++) {
    relayStates[i] = (EEPROM.read(i) == 1);
    int pin = GET_RELAY_PIN(i);
    if (pin != -1) {
      SET_RELAY_STATE(pin, relayStates[i]);
    }
  }
  DEBUG_PRINTLN("Relay states loaded from EEPROM");
}
#endif

void sendEnhancedHTMLPage(EthernetClient client) {
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.print("<title>");
  client.print(WEB_PAGE_TITLE);
  client.println("</title>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<style>");
  client.println("body { font-family: Arial, sans-serif; margin: 20px; background-color: #f0f0f0; }");
  client.println(".container { max-width: 800px; margin: 0 auto; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }");
  client.println("h1 { color: #333; text-align: center; }");
  client.println(".relay-section { margin: 20px 0; padding: 15px; border: 1px solid #ddd; border-radius: 5px; }");
  client.println(".relay-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 15px; margin: 20px 0; }");
  client.println(".relay-item { text-align: center; padding: 15px; border: 2px solid #ddd; border-radius: 8px; }");
  client.println(".relay-item.active { border-color: #4CAF50; background-color: #e8f5e8; }");
  client.println(".btn { padding: 10px 20px; margin: 5px; border: none; border-radius: 5px; cursor: pointer; font-size: 14px; text-decoration: none; display: inline-block; }");
  client.println(".btn-on { background-color: #4CAF50; color: white; }");
  client.println(".btn-off { background-color: #f44336; color: white; }");
  client.println(".btn-pair { background-color: #2196F3; color: white; }");
  client.println(".btn-all { background-color: #FF9800; color: white; }");
  client.println(".status { font-weight: bold; margin: 10px 0; }");
  client.println(".connection-status { padding: 10px; border-radius: 5px; margin: 10px 0; }");
  client.println(".connected { background-color: #d4edda; color: #155724; border: 1px solid #c3e6cb; }");
  client.println(".disconnected { background-color: #f8d7da; color: #721c24; border: 1px solid #f5c6cb; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class='container'>");
  client.print("<h1>");
  client.print(WEB_PAGE_TITLE);
  client.println("</h1>");
  
  // Connection status
  client.print("<div class='connection-status ");
  client.print(ethernetConnected ? "connected" : "disconnected");
  client.println("'>");
  client.print("<strong>Connection Status:</strong> ");
  client.print(ethernetConnected ? "Connected" : "Disconnected");
  client.println("</div>");
  
  // Individual relay controls
  client.println("<div class='relay-section'>");
  client.println("<h2>Individual Relay Control</h2>");
  client.println("<div class='relay-grid'>");
  
  for (int i = 1; i <= 4; i++) {
    client.print("<div class='relay-item");
    if (relayStates[i-1]) client.print(" active");
    client.print("'>");
    client.print("<h3>Relay ");
    client.print(i);
    client.println("</h3>");
    client.print("<div class='status'>Status: ");
    client.print(relayStates[i-1] ? "ON" : "OFF");
    client.println("</div>");
    client.print("<a href='/relay");
    client.print(i);
    client.print("/on'><button class='btn btn-on'>ON</button></a>");
    client.print("<a href='/relay");
    client.print(i);
    client.print("/off'><button class='btn btn-off'>OFF</button></a>");
    client.println("</div>");
  }
  
  client.println("</div>");
  client.println("</div>");
  
  // Pair controls
  client.println("<div class='relay-section'>");
  client.println("<h2>Pair Control</h2>");
  client.println("<div class='relay-grid'>");
  
  client.println("<div class='relay-item'>");
  client.println("<h3>Pair 1 (Relays 1 & 2)</h3>");
  client.println("<a href='/pair1/on'><button class='btn btn-pair'>Pair 1 ON</button></a>");
  client.println("<a href='/pair1/off'><button class='btn btn-pair'>Pair 1 OFF</button></a>");
  client.println("</div>");
  
  client.println("<div class='relay-item'>");
  client.println("<h3>Pair 2 (Relays 3 & 4)</h3>");
  client.println("<a href='/pair2/on'><button class='btn btn-pair'>Pair 2 ON</button></a>");
  client.println("<a href='/pair2/off'><button class='btn btn-pair'>Pair 2 OFF</button></a>");
  client.println("</div>");
  
  client.println("</div>");
  client.println("</div>");
  
  // All relays control
  client.println("<div class='relay-section'>");
  client.println("<h2>All Relays Control</h2>");
  client.println("<div style='text-align: center;'>");
  client.println("<a href='/all/on'><button class='btn btn-all'>All ON</button></a>");
  client.println("<a href='/all/off'><button class='btn btn-all'>All OFF</button></a>");
  client.println("</div>");
  client.println("</div>");
  
  // System information
  client.println("<div class='relay-section'>");
  client.println("<h2>System Information</h2>");
  client.print("<p><strong>IP Address:</strong> ");
  client.print(Ethernet.localIP());
  client.println("</p>");
  client.print("<p><strong>MAC Address:</strong> ");
  for (int i = 0; i < 6; i++) {
    if (i > 0) client.print(":");
    if (mac[i] < 16) client.print("0");
    client.print(mac[i], HEX);
  }
  client.println("</p>");
  client.print("<p><strong>Server Port:</strong> ");
  client.print(SERVER_PORT);
  client.println("</p>");
  
  #if ENABLE_STATE_PERSISTENCE
  client.println("<p><strong>State Persistence:</strong> Enabled</p>");
  #else
  client.println("<p><strong>State Persistence:</strong> Disabled</p>");
  #endif
  
  #if MAX_SIMULTANEOUS_RELAYS > 0
  client.print("<p><strong>Max Simultaneous Relays:</strong> ");
  client.print(MAX_SIMULTANEOUS_RELAYS);
  client.println("</p>");
  #endif
  
  #if ENABLE_AUTO_REFRESH
  client.print("<p><em>Page will refresh automatically every ");
  client.print(PAGE_REFRESH_INTERVAL / 1000);
  client.println(" seconds</em></p>");
  #endif
  
  client.println("</div>");
  
  client.println("</div>");
  
  #if ENABLE_AUTO_REFRESH
  client.println("<script>");
  client.print("setTimeout(function(){ location.reload(); }, ");
  client.print(PAGE_REFRESH_INTERVAL);
  client.println(");");
  client.println("</script>");
  #endif
  
  client.println("</body>");
  client.println("</html>");
} 