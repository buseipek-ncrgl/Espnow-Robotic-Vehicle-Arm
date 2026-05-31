# 🤖 ESP-NOW Controlled Robotic Vehicle with Robotic Arm

![ESP32](https://img.shields.io/badge/ESP32-ESP--NOW-red)
![Deneyap](https://img.shields.io/badge/Deneyap-1A%20V2%20%26%20Mini%20V2-blue)
![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-green)

A wireless robotic vehicle and robotic arm platform developed using Deneyap Kart, ESP-NOW communication protocol, L298N motor driver, and a 4-DOF robotic arm.

---

# 📖 Project Overview

This project was developed to create a fully wireless robotic vehicle capable of movement and object manipulation using a robotic arm.

The system consists of two independent units:

### 🎮 Controller Unit
- Deneyap Mini V2
- Two analog joysticks
- ESP-NOW wireless transmitter

### 🚗 Vehicle Unit
- Deneyap Kart 1A V2
- L298N Motor Driver
- 4 DC geared motors
- 4 servo motors
- Buck converter (5V regulator)
- ESP-NOW wireless receiver

The controller transmits commands wirelessly using ESP-NOW, allowing the vehicle and robotic arm to operate without any Wi-Fi router or internet connection.

---

# ✨ Features

## 🚗 Vehicle Control
- Forward movement
- Backward movement
- Left turn
- Right turn
- Real-time wireless control

## 🦾 Robotic Arm Control
- Base rotation
- Main arm movement
- Forearm movement
- Gripper/Bucket control

## 📡 Communication
- ESP-NOW protocol
- No router required
- Low latency
- Reliable communication

---

# 🛠 Hardware Components

| Component | Quantity |
|------------|------------|
| Deneyap Kart 1A | 1 |
| Deneyap Mini V2 | 1 |
| L298N Motor Driver | 1 |
| DC Gear Motors | 4 |
| Servo Motors | 4 |
| Analog Joystick Modules | 2 |
| 18650 Batteries | 2 |
| LM2596 Buck Converter | 1 |
| Breadboard | 1 |
| Jumper Wires | Multiple |
| Robotic Chassis | 1 |

---

# 🧠 System Architecture

```text
Controller Unit
┌────────────────────┐
│ Deneyap Mini V2    │
│                    │
│ Joystick #1        │
│ Vehicle Control    │
│                    │
│ Joystick #2        │
│ Arm Control        │
└─────────┬──────────┘
          │
          │ ESP-NOW
          ▼
┌────────────────────┐
│ Deneyap Kart 1A    │
│                    │
│ L298N Driver       │
│ 4 DC Motors        │
│                    │
│ 4 Servo Motors     │
│ Robotic Arm        │
└────────────────────┘
```

---

# 🔋 Why Is a Buck Converter Used?

A common mistake in robotics projects is powering multiple servo motors directly from the microcontroller board.

Servo motors can draw significant current during movement and under load.

For example:

```text
1 Servo ≈ 500mA – 1000mA
4 Servos ≈ Up to 4A
```

The Deneyap Kart cannot safely supply this amount of current.

Without an external regulator, the following issues may occur:

- Random resets
- ESP32 brownout errors
- Communication failures
- Servo jitter
- Unstable operation

To solve this problem, a dedicated 5V buck converter is used.

### Advantages

✅ Stable 5V output

✅ High current capability

✅ Reliable servo operation

✅ Protects the ESP32 from voltage drops

---

# ⚡ Power Distribution

```text
Battery Pack
     │
     ├────────► L298N Motor Driver
     │
     └────────► LM2596 Buck Converter
                      │
                      ▼
                 Servo Motors
```

### Important

All grounds must be connected together:

```text
Battery GND
L298N GND
Deneyap GND
Buck Converter GND
Servo GND
```

This common ground connection is essential for proper operation.

---

# 🎮 Controller Connections

## Movement Joystick

| Joystick Pin | Deneyap Mini V2 |
|-------------|----------------|
| VCC | 3V3 |
| GND | GND |
| VRX | A0 |
| VRY | A1 |

## Arm Joystick

| Joystick Pin | Deneyap Mini V2 |
|-------------|----------------|
| VCC | 3V3 |
| GND | GND |
| VRX | A2 |
| VRY | A3 |
| SW | D2 |

---

# 🚗 Vehicle Connections

## L298N Motor Driver

| L298N | Deneyap Kart |
|--------|-------------|
| ENA | D8 |
| ENB | D0 |
| IN1 | D12 |
| IN2 | D13 |
| IN3 | D14 |
| IN4 | D9 |
| GND | GND |

### Motor Outputs

| Motors | L298N Output |
|---------|-------------|
| Left Side Motors | OUT1 - OUT2 |
| Right Side Motors | OUT3 - OUT4 |

---

## Servo Connections

| Servo | Function | Signal Pin |
|---------|----------|------------|
| Servo 1 | Base Rotation | D1 |
| Servo 2 | Main Arm | D4 |
| Servo 3 | Forearm | SDA |
| Servo 4 | Gripper/Bucket | A0 |

### Servo Wiring

| Servo Wire | Connection |
|------------|------------|
| Orange / Yellow | Signal |
| Red | +5V |
| Brown / Black | GND |

All servo motors are powered directly from the LM2596 regulator.

---

# 🎯 Control Logic

## Driving Mode

The first joystick controls vehicle movement.

| Action | Vehicle |
|---------|----------|
| Up | Forward |
| Down | Backward |
| Left | Turn Left |
| Right | Turn Right |

---

## Arm Mode 0

The second joystick controls:

| Action | Function |
|---------|----------|
| Left / Right | Base Rotation |
| Up / Down | Main Arm |

---

## Arm Mode 1

Press the joystick button once to switch modes.

| Action | Function |
|---------|----------|
| Left / Right | Forearm |
| Up | Open Gripper |
| Down | Close Gripper |

Press the button again to return to Mode 0.

---

# 📡 ESP-NOW Setup

## Step 1 – Get Vehicle MAC Address

Upload:

```text
mac_adresi_bul.ino
```

Open Serial Monitor at:

```text
115200 baud
```

Example output:

```text
94:3C:C6:DA:F2:A4
```

---

## Step 2 – Update Controller Code

Replace the MAC address inside:

```cpp
uint8_t aracMAC[]
```

with your own vehicle MAC address.

---

## Step 3 – Upload Controller Code

Upload:

```text
kumanda_espnow.ino
```

to the Deneyap Mini V2.

---

## Step 4 – Upload Vehicle Code

Upload:

```text
arac_espnow.ino
```

to the Deneyap Kart 1A.

---

# 📂 Project Structure

```text
deneyap-espnow-robot-vehicle
│
├── mac_adresi_bul/
│   └── mac_adresi_bul.ino
│
├── kumanda_espnow/
│   └── kumanda_espnow.ino
│
├── arac_espnow/
│   └── arac_espnow.ino
│
└── README.md
```

---

# 🔧 Future Improvements

- Proportional speed control based on joystick position
- Dedicated button controls for gripper operation
- Battery voltage monitoring system
- OLED status display for connection and battery information
- Adjustable servo speed and angle limits
- Mobile application for remote control
- Real-time telemetry feedback from the vehicle
- Camera module integration for remote monitoring
- Modular end-effector support (gripper, bucket, claw, etc.)

---

# 👨‍💻 Technologies Used

- Deneyap Kart 1A
- Deneyap Mini V2
- ESP32
- Arduino IDE
- ESP-NOW
- L298N
- LM2596 Buck Converter

---
