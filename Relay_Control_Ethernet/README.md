# Relay Control System with Ethernet Shield

This Arduino project controls four relays using a SparkFun RedBoard Plus with an Arduino Ethernet Shield. The system allows individual control of each relay or control of relay pairs via a web interface.

## Features

- **Individual Relay Control**: Control each of the four relays independently
- **Pair Control**: Control relays in predefined pairs (1&2, 3&4)
- **All Relays Control**: Turn all relays on or off simultaneously
- **Web Interface**: Modern, responsive web interface accessible via Ethernet
- **Real-time Status**: Live status updates of all relay states
- **Serial Monitoring**: Debug output via Serial Monitor

## Hardware Requirements

### Main Components
- **SparkFun RedBoard Plus** (or Arduino Uno compatible)
- **Arduino Ethernet Shield**
- **4x Relay Modules** (5V relay modules with optoisolator)
- **Ethernet Cable**
- **Power Supply** (12V recommended for relay modules)

### Relay Module Specifications
- Operating Voltage: 5V
- Control Signal: 3.3V/5V TTL compatible
- Relay Contact Rating: 10A @ 250V AC / 10A @ 30V DC
- Isolation: Optoisolator protection

## Wiring Diagram

### Relay Connections
```
SparkFun RedBoard Plus    Relay Module
┌─────────────────┐      ┌─────────────┐
│                 │      │             │
│ Pin 5 ──────────┼──────┤ IN1         │
│ Pin 6 ──────────┼──────┤ IN2         │
│ Pin 7 ──────────┼──────┤ IN3         │
│ Pin 8 ──────────┼──────┤ IN4         │
│                 │      │             │
│ 5V ─────────────┼──────┤ VCC         │
│ GND ────────────┼──────┤ GND         │
│                 │      │             │
└─────────────────┘      └─────────────┘
```

### Power Connections
```
Power Supply (12V)       Relay Module
┌─────────────┐         ┌─────────────┐
│             │         │             │
│ 12V ────────┼─────────┤ VCC (if 12V)│
│ GND ────────┼─────────┤ GND         │
│             │         │             │
└─────────────┘         └─────────────┘
```

## Network Configuration

### Default Settings
- **IP Address**: 192.168.1.177
- **Gateway**: 192.168.1.1
- **Subnet**: 255.255.255.0
- **MAC Address**: DE:AD:BE:EF:FE:ED
- **Port**: 80

### Customizing Network Settings
Edit these lines in the Arduino sketch:
```cpp
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
```

## Installation and Setup

### 1. Hardware Setup
1. Connect the Ethernet Shield to the RedBoard Plus
2. Connect relay modules to pins 5, 6, 7, and 8
3. Connect power supply to relay modules
4. Connect Ethernet cable to the Ethernet Shield

### 2. Software Setup
1. Open Arduino IDE
2. Install required libraries:
   - SPI (usually included)
   - Ethernet (usually included)
3. Open `Relay_Control_Ethernet.ino`
4. Modify network settings if needed
5. Upload the sketch to your RedBoard Plus

### 3. Network Configuration
1. Connect the Ethernet cable to your network
2. Ensure the IP address doesn't conflict with other devices
3. Check that the gateway and subnet match your network

## Usage

### Web Interface
1. Open a web browser
2. Navigate to `http://192.168.1.177` (or your configured IP)
3. Use the web interface to control relays

### Available Commands

#### Individual Relay Control
- `http://[IP]/relay1/on` - Turn Relay 1 ON
- `http://[IP]/relay1/off` - Turn Relay 1 OFF
- `http://[IP]/relay2/on` - Turn Relay 2 ON
- `http://[IP]/relay2/off` - Turn Relay 2 OFF
- `http://[IP]/relay3/on` - Turn Relay 3 ON
- `http://[IP]/relay3/off` - Turn Relay 3 OFF
- `http://[IP]/relay4/on` - Turn Relay 4 ON
- `http://[IP]/relay4/off` - Turn Relay 4 OFF

#### Pair Control
- `http://[IP]/pair1/on` - Turn Pair 1 (Relays 1 & 2) ON
- `http://[IP]/pair1/off` - Turn Pair 1 (Relays 1 & 2) OFF
- `http://[IP]/pair2/on` - Turn Pair 2 (Relays 3 & 4) ON
- `http://[IP]/pair2/off` - Turn Pair 2 (Relays 3 & 4) OFF

#### All Relays Control
- `http://[IP]/all/on` - Turn All Relays ON
- `http://[IP]/all/off` - Turn All Relays OFF

### Serial Monitor
Open the Serial Monitor (9600 baud) to see:
- System startup messages
- Relay state changes
- Client connection status
- Debug information

## Troubleshooting

### Common Issues

#### Relays Not Responding
1. Check power supply connections
2. Verify relay module connections
3. Check if relays are active-high or active-low
4. Test with Serial Monitor for debug output

#### Network Connection Issues
1. Verify Ethernet cable connection
2. Check IP address conflicts
3. Ensure gateway and subnet are correct
4. Test with `ping [IP_ADDRESS]`

#### Web Interface Not Loading
1. Check if the Arduino is connected to the network
2. Verify the IP address in your browser
3. Check firewall settings
4. Try accessing from a different device

### Debug Mode
Enable additional debug output by uncommenting debug lines in the code:
```cpp
// Add debug prints in parseRequest() function
Serial.println("Request received: " + request);
```

## Safety Considerations

### Electrical Safety
- **High Voltage Warning**: Relay modules can switch high voltage circuits
- **Proper Grounding**: Ensure proper grounding of all components
- **Power Rating**: Do not exceed relay contact ratings
- **Isolation**: Use optoisolated relay modules for safety

### Network Security
- **Default Credentials**: Change default network settings
- **Firewall**: Consider implementing network security measures
- **Access Control**: Limit access to trusted devices only

## Customization

### Adding More Relays
1. Add additional relay pins
2. Update relay state array
3. Add control functions
4. Update web interface

### Changing Relay Logic
If your relays are active-high instead of active-low:
```cpp
// Change this line in setRelay() function
digitalWrite(pin, state ? HIGH : LOW);  // HIGH = ON, LOW = OFF
```

### Adding Authentication
Consider adding basic authentication for production use:
```cpp
// Add authentication check in parseRequest()
if (!isAuthenticated(request)) {
    return;
}
```

## License

This project is open source and available under the MIT License.

## Support

For issues and questions:
1. Check the troubleshooting section
2. Review the Serial Monitor output
3. Verify hardware connections
4. Test with a simple relay test sketch first 
