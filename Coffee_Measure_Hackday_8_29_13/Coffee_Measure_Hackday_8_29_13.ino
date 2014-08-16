// Coffee Measurement tool for Amplify Hackday 8.29.13

 /*
 * ------------------ 
 * This script looks at a sensor (in this case a elastic band) 
 * and sends a metric to Graphite if that sensor is tripped then
 * returns to normal.
 * ------------------
 * Written using this driver: https://github.com/Seeed-Studio/WiFi_Shield/blob/master/Examples/wifly_test/wifly_test.ino
 * which is for a WiFly shield using RN-171b chipset
 */

#include <Debug.h>
#include <WiFly.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Credentials.h"
#include "ServerClientConfigs.h"

// Pins' connection
// Arduino       WiFly
//  7    <---->    TX (first char)
//  6    <---->    RX (second char)
SoftwareSerial uart(7,6); //(TX,RX)
WiFly wifly(&uart);

void setupUDP(const char *host_ip, uint16_t remote_port, uint16_t local_port)
{
  char cmd[32];
  
  wifly.sendCommand("set w j 1\r", "AOK");   // enable auto join
  
  wifly.sendCommand("set i p 1\r", "AOK");
  snprintf(cmd, sizeof(cmd), "set i h %s\r", host_ip);
  wifly.sendCommand(cmd, "AOK");
  snprintf(cmd, sizeof(cmd), "set i r %d\r", remote_port);
  wifly.sendCommand(cmd, "AOK");
  snprintf(cmd, sizeof(cmd), "set i l %d\r", local_port);
  wifly.sendCommand(cmd, "AOK");
  wifly.sendCommand("save\r");
  wifly.sendCommand("reboot\r");
}

int LDR = A2;       // select the input pin for the LDR (analog input)
int ledPin = 13;   // select the pin for the LED - 13 is the on-board ledPin
int val = 0;       // variable to store the value coming from the sensor
//char handel[4]; // current handel state
//char old_handel[4]; //old handel state
String handel = String(4);
String old_handel = String(4);
String up = String("up");
String down = String("down");

void setup() {

  
  Serial.begin(9600);
   
  Serial.println("--------- WiFi Configuration --------");
  uart.begin(9600);//use the hardware serial to communicate with the PC 
    wifly.reset();
  
  while (1) {
    Serial.println("Try to join " SSID );
    if (wifly.join(SSID, KEY, AUTH)) {
      Serial.println("Succeed in joining " SSID);
      wifly.clear();
      break;
    } else {
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 1 second and try again...");
      delay(1000);
    }
  }
  
  setupUDP(STATSD_HOST, STATSD_PORT, UDP_LOCAL_PORT);
  
  delay(10000);
  wifly.clear();
  
  
} // end setup

unsigned int time_point = 0;

void loop() {

  int flexreader = analogRead(LDR);       // read the value from the sensor

  val = map(flexreader, 470, 520, 0, 1);  // converting larger range to smaller
  Serial.print("Read value:");
  Serial.println(flexreader);
  Serial.print("Mapped value:");
  Serial.println(val);
  

  if (val == 1){
     handel = "down";
  }
  
  if (val == 0){
     handel = "up";   
  }
  
  Serial.println(handel);
  
  
  // WiFi Send 
  if (wifly.available()) {
    Serial.print((char)wifly.read());
  }

 // if the state has changed let graphite know we made some coffee!!
  if ( handel.equals(down) && old_handel.equals(up)){
    wifly.send("office.coffee.made:1|c\r\n");
    Serial.println("Sent Metric");
    delay(30000);
  } 

  old_handel = handel;
  delay(100);

} // end loop

