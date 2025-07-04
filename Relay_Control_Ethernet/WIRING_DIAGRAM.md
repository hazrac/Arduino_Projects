# Wiring Diagram for Relay Control System

## Overview
This document provides detailed wiring instructions for connecting four relay modules to a SparkFun RedBoard Plus with an Arduino Ethernet Shield.

## Components Required

### Hardware Components
1. **SparkFun RedBoard Plus** (or Arduino Uno compatible)
2. **Arduino Ethernet Shield**
3. **4x 5V Relay Modules** (with optoisolator)
4. **12V Power Supply** (for relay modules)
5. **Ethernet Cable**
6. **Breadboard** (optional, for testing)
7. **Jumper Wires**

### Relay Module Specifications
- **Operating Voltage**: 5V
- **Control Signal**: 3.3V/5V TTL compatible
- **Relay Contact Rating**: 10A @ 250V AC / 10A @ 30V DC
- **Isolation**: Optoisolator protection
- **Trigger Level**: Active Low (LOW = ON, HIGH = OFF)

## Detailed Wiring Diagram

### 1. Ethernet Shield Connection
```
┌─────────────────────────────────────────────────────────────┐
│                    SparkFun RedBoard Plus                   │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                                                     │    │
│  │  ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ │    │
│  │  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │    │
│  │  └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ │    │
│  │                                                     │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                  Arduino Ethernet Shield                    │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                                                     │    │
│  │  ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ │    │
│  │  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │    │
│  │  └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ │    │
│  │                                                     │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

### 2. Relay Module Connections

#### Individual Relay Module Layout
```
┌─────────────────────────────────────────────────────────────┐
│                        Relay Module                         │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                                                     │    │
│  │  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐      │    │
│  │  │ VCC │  │ GND │  │ IN1 │  │ IN2 │  │ IN3 │      │    │
│  │  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘      │    │
│  │                                                     │    │
│  │  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐      │    │
│  │  │ IN4 │  │ COM │  │ NO1 │  │ NC1 │  │ COM │      │    │
│  │  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘      │    │
│  │                                                     │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

#### Complete Wiring Diagram
```
SparkFun RedBoard Plus + Ethernet Shield    Relay Modules
┌─────────────────────────────────────────┐  ┌─────────────────┐
│                                         │  │                 │
│  ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ │  │  ┌─┐ ┌─┐ ┌─┐ ┌─┐ │
│  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │  │  │ │ │ │ │ │ │ │ │
│  └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ │  │  └─┘ └─┘ └─┘ └─┘ │
│                                         │  │                 │
│  Pin 2 ─────────────────────────────────┼──┤ IN1 (Relay 1)   │
│  Pin 3 ─────────────────────────────────┼──┤ IN2 (Relay 2)   │
│  Pin 4 ─────────────────────────────────┼──┤ IN3 (Relay 3)   │
│  Pin 5 ─────────────────────────────────┼──┤ IN4 (Relay 4)   │
│                                         │  │                 │
│  5V ────────────────────────────────────┼──┤ VCC             │
│  GND ───────────────────────────────────┼──┤ GND             │
│                                         │  │                 │
└─────────────────────────────────────────┘  └─────────────────┘
```

### 3. Power Supply Connections
```
12V Power Supply                    Relay Modules
┌─────────────────┐                ┌─────────────────┐
│                 │                │                 │
│ 12V ────────────┼────────────────┤ VCC (if 12V)    │
│ GND ────────────┼────────────────┤ GND             │
│                 │                │                 │
└─────────────────┘                └─────────────────┘
```

## Step-by-Step Connection Instructions

### Step 1: Prepare the Ethernet Shield
1. Carefully align the Ethernet Shield with the RedBoard Plus
2. Press down firmly to seat all pins
3. Ensure the shield is properly connected

### Step 2: Connect Relay Module Power
1. Connect the 12V power supply positive (+) to the VCC terminal on each relay module
2. Connect the 12V power supply negative (-) to the GND terminal on each relay module
3. **Important**: Use a separate power supply for the relay modules to avoid interference

### Step 3: Connect Control Signals
1. **Relay 1**: Connect RedBoard Plus Pin 2 to Relay Module IN1
2. **Relay 2**: Connect RedBoard Plus Pin 3 to Relay Module IN2
3. **Relay 3**: Connect RedBoard Plus Pin 4 to Relay Module IN3
4. **Relay 4**: Connect RedBoard Plus Pin 5 to Relay Module IN4

### Step 4: Connect Arduino Power to Relay Modules
1. Connect RedBoard Plus 5V to Relay Module VCC (for logic power)
2. Connect RedBoard Plus GND to Relay Module GND (for common ground)

### Step 5: Connect Ethernet Cable
1. Connect an Ethernet cable to the Ethernet Shield
2. Connect the other end to your network router/switch

## Pin Assignment Summary

| Arduino Pin | Relay Module | Function |
|-------------|--------------|----------|
| Pin 2       | IN1          | Relay 1 Control |
| Pin 3       | IN2          | Relay 2 Control |
| Pin 4       | IN3          | Relay 3 Control |
| Pin 5       | IN4          | Relay 4 Control |
| 5V          | VCC          | Logic Power |
| GND         | GND          | Common Ground |

## Safety Considerations

### Electrical Safety
- **High Voltage Warning**: Relay modules can switch high voltage circuits
- **Proper Grounding**: Ensure proper grounding of all components
- **Power Rating**: Do not exceed relay contact ratings (10A @ 250V AC)
- **Isolation**: Use optoisolated relay modules for safety

### Power Supply Requirements
- **Arduino**: 5V USB power or 7-12V barrel jack
- **Relay Modules**: 12V power supply (recommended)
- **Current Rating**: Ensure power supply can handle relay coil current

### Testing Procedure
1. **Before Power On**: Double-check all connections
2. **Initial Test**: Use the `Relay_Test.ino` sketch first
3. **Network Test**: Verify Ethernet connection
4. **Full System Test**: Use the main control sketch

## Troubleshooting

### Common Issues

#### Relays Not Responding
- Check power supply connections
- Verify control signal connections
- Test with multimeter for proper voltage levels
- Check relay module specifications

#### Network Connection Issues
- Verify Ethernet cable connection
- Check IP address configuration
- Ensure no IP conflicts on network
- Test with `ping` command

#### Power Issues
- Check power supply voltage and current rating
- Verify ground connections
- Ensure proper isolation between Arduino and relay power

### Testing with Multimeter
1. **Voltage Test**: Measure voltage at relay control pins
2. **Continuity Test**: Test relay contacts when activated
3. **Ground Test**: Verify proper ground connections

## Additional Notes

### Relay Module Types
- **Active Low**: Most common, LOW signal activates relay
- **Active High**: Less common, HIGH signal activates relay
- **Check your specific module's datasheet**

### Network Configuration
- Default IP: 192.168.1.177
- Default Gateway: 192.168.1.1
- Default Subnet: 255.255.255.0
- Modify in `Config.h` if needed

### Code Configuration
- Edit `Config.h` to change pin assignments
- Modify network settings as needed
- Adjust relay logic if using active-high modules 