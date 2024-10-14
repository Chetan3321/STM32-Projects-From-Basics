# OLED Interfacing with STM32F401 Blackpill

This project demonstrates how to interface an **OLED display** with the **STM32F401 Blackpill** development board. The OLED display will be used to display custom text, graphics, and sensor data by communicating via an **I2C interface**. This guide provides an overview of the components required, the setup process, and the circuit diagram to help you get started.

## Introduction

The **STM32F401 Blackpill** is a powerful and compact development board based on the ARM Cortex-M4 core. It is widely used for embedded systems projects due to its low power consumption and high processing capabilities.

The **OLED display**, typically based on the SSD1306 driver, is a popular choice for embedded projects because of its low power consumption, high contrast, and clear visibility. It uses the **I2C communication protocol**, making it straightforward to interface with microcontrollers like the STM32F401.

In this project, the OLED display will be connected to the STM32F401 via I2C pins, and we will display text or graphical content on the screen using suitable libraries and drivers.

## Components Required

- **STM32F401 Blackpill Development Board**
- **0.96" I2C OLED Display** (SSD1306-based, 128x64 pixels)
- **I2C Pull-up Resistors** (if required)
- **Connecting Wires**
- **Breadboard** (optional)

## Circuit Diagram

Here is the circuit diagram for connecting the STM32F401 Blackpill to the OLED display using the I2C protocol.

```
            STM32F401 Blackpill        OLED Display
            ------------------        ------------
               3.3V    ------------------>   VCC
               GND     ------------------>   GND
               PB8 (I2C1_SCL) ------------->   SCL
               PB9 (I2C1_SDA) ------------->   SDA
```

### Pin Connections

- **VCC**: Connect the VCC pin of the OLED to the 3.3V pin on the STM32F401.
- **GND**: Connect the GND pin of the OLED to the GND pin of the STM32F401.
- **SCL**: Connect the SCL pin of the OLED to the PB8 pin (I2C1_SCL) on the STM32F401.
- **SDA**: Connect the SDA pin of the OLED to the PB9 pin (I2C1_SDA) on the STM32F401.

### Important Notes:
- Ensure the **OLED display operates at 3.3V**. If the OLED module requires 5V, use appropriate level shifters for SCL and SDA signals.
- In some setups, **pull-up resistors** (typically 4.7kΩ) might be required for the SCL and SDA lines, depending on the board and display you're using. Some OLED modules already have pull-up resistors on board, so check the module specifications.

## Libraries Required

To control the OLED display, you will need the appropriate driver libraries for the STM32. The most commonly used driver for OLED displays with SSD1306 is the `Adafruit SSD1306` library or the equivalent STM32 HAL libraries for I2C communication.

---

By completing this project, you'll learn how to set up an I2C interface, send data from the STM32 to the OLED display, and implement simple graphics or text rendering.