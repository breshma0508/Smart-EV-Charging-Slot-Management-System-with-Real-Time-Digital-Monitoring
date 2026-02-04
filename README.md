# Smart EV Charging Slot Management System with Real-Time Digital Monitoring

**This project is a software-controlled embedded system that manages EV charging slots using Arduino-based logic. The system allocates charging slots based on user-entered payment amount, tracks charging duration using millis()-based timers, and displays real-time status on a 16×2 I2C LCD.**

## Overview
This system demonstrates how embedded software can control and monitor EV charging slot usage. It manages multiple slots, assigns charging time based on user input, continuously tracks remaining time, and automatically releases slots after the allocated time expires.

## How the System Works
- On startup, the LCD displays welcome and system messages.
- The user enters a payment amount through the Serial Monitor (simulating QR/digital payment).
- Based on the entered amount, the system allocates a predefined charging duration.
- The first available slot (out of three slots) is assigned automatically.
- Slot end time is calculated using the `millis()` function.
- Remaining charging time is displayed in hours and minutes on the LCD.
- Once the charging time expires, the slot is freed automatically.

## Output

### LCD Display
- Welcome and system messages
- Allocated slot number
- Assigned charging time
- Remaining charging time (hours and minutes)
- Slot availability messages

### Serial Monitor
- Entered payment amount
- Slot allocation details
- Remaining time updates
- Slot release notifications

## Components Used

### Hardware Components
- Arduino UNO / Nano
- 16×2 I2C LCD Display
- Solar Panel
- Battery
- Charge Controller
- EV Battery / Load (Prototype)  

### Software Components
- Arduino IDE  
- Embedded C Programming  
- Wire.h (I2C communication library)  
- LiquidCrystal_I2C.h (LCD control library)  

## Key Features
- Software-based charging slot allocation
- Real-time time tracking using `millis()`
- Automatic slot release after time expiry
- Multi-slot management using arrays
- Digital monitoring through LCD display

## Applications
- EV charging slot management (prototype level)
- Smart parking and charging systems
- Embedded systems learning and demonstrations
- Academic mini and final-year projects

## Demo Instructions

### Example:

1. Upload code to Arduino
2. Open Serial Monitor
3. Enter amount (100–600)
4. Observe LCD output
   
 Total cost around 3000 without car (wooden)
## Limitations (Current Code)
- Payment input is simulated via Serial Monitor
- No real charging power control implemented
- LCD updates include delays which may cause brief flickering
- No IoT or remote monitoring in current version
