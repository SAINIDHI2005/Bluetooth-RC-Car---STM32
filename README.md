# Bluetooth Controlled RC Car (STM32 Bare-Metal)

## 📌 Project Overview
This project is a **Bluetooth-controlled RC car** built using the **STM32 Nucleo F446RE** microcontroller.  
The entire firmware is written in **bare-metal, register-level C**, without using HAL or any standard peripheral libraries.

The goal of this project was to deeply understand how STM32 peripherals work by:
- Reading STM32 reference manuals and datasheets
- Configuring GPIO, RCC, and USART registers manually
- Implementing UART communication from scratch for Bluetooth control

The RC car is controlled wirelessly using a mobile Bluetooth app via the **HC-05** module.

---

## ⚙️ Key Features
- Bare-metal STM32 programming (no HAL / CMSIS drivers)
- UART-based Bluetooth communication
- Real-time motor control using L298N motor driver
- Battery-powered standalone operation
- Simple and modular hardware setup

---

## 🔩 Hardware Components Used

| Component | Description |
|---------|------------|
| STM32 Nucleo F446RE | Main microcontroller board |
| HC-05 Bluetooth Module | Wireless communication with mobile phone |
| L298N Motor Driver | Drives DC motors and controls direction |
| DC–DC Buck Converter | Steps down battery voltage to required levels |
| 2 × 18650 Li-ion Batteries (3.7V each) | Power source (used as a 2-cell pack) |
| 18650 Battery Holder | Holds and connects the batteries |
| Breadboard | Prototyping and connections |
| 2WD Acrylic Car Kit | Chassis with wheels |
| 300 RPM BO Motors (×2) | Drive motors for the RC car |

---

## 🧠 Software Approach
- Written entirely using **C** in STM32 CubeIDE
- Direct register-level access for:
  - RCC (clock configuration)
  - GPIO (pin modes and control)
  - USART (Bluetooth communication)
- No abstraction layers (HAL / LL)

---

## 🚀 Learning Outcomes
- Hands-on understanding of STM32 clock tree and peripheral buses
- Practical experience with UART communication at register level
- Improved debugging skills using datasheets and reference manuals
- Confidence in writing standalone embedded firmware

---

## 📷 Demo
(Add images or videos of the RC car here)

---

## 📄 Notes
This project was built purely for **learning and experimentation** and focuses on understanding the hardware at a low level rather than rapid development.
