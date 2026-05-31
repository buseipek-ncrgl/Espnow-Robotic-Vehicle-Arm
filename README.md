# 🤖 ESP-NOW Controlled Robotic Vehicle with Robotic Arm

![ESP32](https://img.shields.io/badge/ESP32-ESP--NOW-red)
![Deneyap](https://img.shields.io/badge/Deneyap-Kart%201A%20V2%20%26%20Mini%20V2-blue)
![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

A wireless robotic vehicle and robotic arm platform developed using Deneyap Kart, ESP-NOW communication protocol, L298N motor driver, and SG90 servo motors.

---

# 📖 Project Overview

This project is a wireless robotic vehicle equipped with a robotic arm and controlled through ESP-NOW communication.

The system consists of two separate units:

## 🎮 Controller Unit

- Deneyap Mini V2
- Two analog joystick modules
- ESP-NOW transmitter

## 🚗 Vehicle Unit

- Deneyap Kart 1A V2
- L298N Motor Driver
- 4 DC geared motors
- 4 SG90 servo motors
- LM2596 Buck Converter
- ESP-NOW receiver

The controller sends movement and robotic arm commands wirelessly to the vehicle without requiring any Wi-Fi router or internet connection.

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
- Gripper / bucket control

## 📡 Communication

- ESP-NOW protocol
- No router required
- Low latency communication
- Reliable wireless control

---

# 🛠 Hardware Components

| Component | Quantity |
|------------|------------|
| Deneyap Kart 1A V2 | 1 |
| Deneyap Mini V2 | 1 |
| L298N Motor Driver | 1 |
| DC Gear Motors | 4 |
| SG90 Servo Motors | 4 |
| Analog Joystick Modules | 2 |
| 18650 Batteries | 2 |
| 5V Buck Converter | 1 |
| Power Switch | 1 |
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
┌───────────────────────┐
│ Deneyap Kart 1A V2    │
│                       │
│ L298N Driver          │
│ 4 DC Motors           │
│                       │
│ 4 SG90 Servos         │
│ Robotic Arm           │
└───────────────────────┘
```

---

# 🔋 Power System

The vehicle is powered by a 2-cell 18650 battery pack.

The battery output is distributed to:

- L298N motor driver
- 5V buck converter

The buck converter provides a stable 5V supply for the SG90 servo motors.

---

# ❓ Why Is a Buck Converter Used?

Although SG90 servo motors are small, they can draw significant current when moving under load.

Using four servos simultaneously may cause:

- Voltage drops
- Servo jitter
- ESP32 brownout resets
- Communication failures
- Unstable system behavior

To prevent these problems, the servos are powered from a dedicated LM2596 buck converter instead of the Deneyap board.

### Advantages

✅ Stable 5V output

✅ Reliable servo operation

✅ Better power distribution

✅ Protection against voltage drops

---

# ⚡ Power Distribution

```text
18650 Battery Pack
         │
         ▼
     Power Switch
         │
         ├────────► L298N Motor Driver
         │
         └────────► 5V Buck Converter
                         │
                         ▼
                     SG90 Servos
```

### Common Ground Connection

The following grounds must be connected together:

```text
Battery GND
L298N GND
Deneyap GND
Buck Converter GND
Servo GND
```

This common ground connection is mandatory for proper operation.

---

# 🔘 Power Switch

A physical power switch is installed between the battery pack and the power distribution system.

Benefits:

- Safe startup and shutdown
- Prevents accidental battery drain
- Easier testing and maintenance
- Improved electrical safety

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

## L298N Connections

| L298N Pin | Deneyap Kart |
|------------|------------|
| ENA | D8 |
| ENB | D0 |
| IN1 | D12 |
| IN2 | D13 |
| IN3 | D14 |
| IN4 | D9 |
| GND | GND |

### Motor Outputs

| Motors | Output |
|---------|---------|
| Left Side Motors | OUT1 - OUT2 |
| Right Side Motors | OUT3 - OUT4 |

---

## SG90 Servo Connections

| Servo | Function | Signal Pin |
|---------|----------|------------|
| Servo 1 | Base Rotation | D1 |
| Servo 2 | Main Arm | D4 |
| Servo 3 | Forearm | SDA |
| Servo 4 | Gripper / Bucket | A0 |

### Servo Wiring

| Wire Color | Connection |
|------------|------------|
| Orange / Yellow | Signal |
| Red | +5V |
| Brown | GND |

All SG90 servos are powered directly from the LM2596 output.

---

# 🎯 Control Logic

## Vehicle Movement

Joystick #1 controls vehicle movement.

| Direction | Action |
|------------|---------|
| Up | Forward |
| Down | Backward |
| Left | Turn Left |
| Right | Turn Right |

---

## Arm Mode 0

Joystick #2 controls:

| Direction | Function |
|------------|----------|
| Left / Right | Base Rotation |
| Up / Down | Main Arm |

---

## Arm Mode 1

Press the joystick button once.

| Direction | Function |
|------------|----------|
| Left / Right | Forearm |
| Up | Open Gripper |
| Down | Close Gripper |

Press the button again to return to Mode 0.

---

# 📡 ESP-NOW Setup

## Step 1

Upload:

```text
mac_adresi_bul.ino
```

Open Serial Monitor at:

```text
115200 baud
```

Example:

```text
94:3C:C6:DA:F2:A4
```

---

## Step 2

Replace the MAC address inside:

```cpp
uint8_t aracMAC[]
```

with your vehicle MAC address.

---

## Step 3

Upload:

```text
kumanda_espnow.ino
```

to the controller board.

---

## Step 4

Upload:

```text
arac_espnow.ino
```

to the vehicle board.

---

# 📂 Project Structure

```text
deneyap-espnow-robotic-vehicle-arm
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

- Battery voltage monitoring
- OLED status display
- Mobile application support
- Camera integration
- Adjustable servo speed control
- 3D printed robotic arm components
- Additional interchangeable end-effectors

---



# 👨‍💻 Technologies Used

- Deneyap Kart 1A V2
- Deneyap Mini V2
- ESP32
- Arduino IDE
- ESP-NOW
- L298N
- 5V Buck Converter
- SG90 Servo Motors

---
