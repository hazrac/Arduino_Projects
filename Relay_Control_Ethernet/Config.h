/*
 * Configuration Header for Relay Control System
 * 
 * This file contains all configurable parameters for the relay control system.
 * Modify these values to customize the system for your specific setup.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// RELAY PIN CONFIGURATION
// ============================================================================

// Digital pins connected to relay modules
#define RELAY_1_PIN 2
#define RELAY_2_PIN 3
#define RELAY_3_PIN 4
#define RELAY_4_PIN 5

// Relay logic configuration
// Set to true if your relays are active-high (HIGH = ON, LOW = OFF)
// Set to false if your relays are active-low (LOW = ON, HIGH = OFF)
#define RELAY_ACTIVE_HIGH true

// ============================================================================
// NETWORK CONFIGURATION
// ============================================================================

// MAC address (should be unique on your network)
#define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }

// IP configuration
#define IP_ADDRESS { 192, 168, 1, 177 }
#define GATEWAY_ADDRESS { 192, 168, 1, 1 }
#define SUBNET_MASK { 255, 255, 255, 0 }

// Server port
#define SERVER_PORT 80

// ============================================================================
// TIMING CONFIGURATION
// ============================================================================

// Serial communication baud rate
#define SERIAL_BAUD_RATE 9600

// Web page auto-refresh interval (milliseconds)
#define PAGE_REFRESH_INTERVAL 5000

// ============================================================================
// RELAY PAIR CONFIGURATION
// ============================================================================

// Define relay pairs (0-based indexing)
#define PAIR_1_RELAY_1 0  // Relay 1 (index 0)
#define PAIR_1_RELAY_2 1  // Relay 2 (index 1)
#define PAIR_2_RELAY_1 2  // Relay 3 (index 2)
#define PAIR_2_RELAY_2 3  // Relay 4 (index 3)

// ============================================================================
// DEBUG CONFIGURATION
// ============================================================================

// Enable/disable debug output
#define DEBUG_ENABLED true

// Debug output levels
#define DEBUG_LEVEL_NONE 0
#define DEBUG_LEVEL_BASIC 1
#define DEBUG_LEVEL_DETAILED 2
#define DEBUG_LEVEL_VERBOSE 3

// Set debug level (0-3)
#define DEBUG_LEVEL DEBUG_LEVEL_BASIC

// ============================================================================
// SAFETY CONFIGURATION
// ============================================================================

// Maximum number of relays that can be on simultaneously
// Set to 0 to disable limit
#define MAX_SIMULTANEOUS_RELAYS 0

// Relay state persistence (save state to EEPROM)
#define ENABLE_STATE_PERSISTENCE false

// ============================================================================
// WEB INTERFACE CONFIGURATION
// ============================================================================

// Page title
#define WEB_PAGE_TITLE "Relay Control System"

// Enable/disable auto-refresh
#define ENABLE_AUTO_REFRESH true

// ============================================================================
// HELPER MACROS
// ============================================================================

// Macro to get relay pin by index
#define GET_RELAY_PIN(index) \
  ((index) == 0 ? RELAY_1_PIN : \
   (index) == 1 ? RELAY_2_PIN : \
   (index) == 2 ? RELAY_3_PIN : \
   (index) == 3 ? RELAY_4_PIN : -1)

// Macro to set relay state based on configuration
#define SET_RELAY_STATE(pin, state) \
  digitalWrite(pin, RELAY_ACTIVE_HIGH ? (state ? HIGH : LOW) : (state ? LOW : HIGH))

// Debug print macros
#if DEBUG_ENABLED
  #if DEBUG_LEVEL >= DEBUG_LEVEL_BASIC
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
  #else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
  #endif
  
  #if DEBUG_LEVEL >= DEBUG_LEVEL_DETAILED
    #define DEBUG_PRINT_DETAILED(x) Serial.print(x)
    #define DEBUG_PRINTLN_DETAILED(x) Serial.println(x)
  #else
    #define DEBUG_PRINT_DETAILED(x)
    #define DEBUG_PRINTLN_DETAILED(x)
  #endif
  
  #if DEBUG_LEVEL >= DEBUG_LEVEL_VERBOSE
    #define DEBUG_PRINT_VERBOSE(x) Serial.print(x)
    #define DEBUG_PRINTLN_VERBOSE(x) Serial.println(x)
  #else
    #define DEBUG_PRINT_VERBOSE(x)
    #define DEBUG_PRINTLN_VERBOSE(x)
  #endif
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT_DETAILED(x)
  #define DEBUG_PRINTLN_DETAILED(x)
  #define DEBUG_PRINT_VERBOSE(x)
  #define DEBUG_PRINTLN_VERBOSE(x)
#endif

#endif // CONFIG_H 