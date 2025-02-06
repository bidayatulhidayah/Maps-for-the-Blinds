# Maps-for-the-Blinds

# Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Control Flow Chart](#control-flow-chart)
- [Libraries Required](#libraries-required)
- [Installation](#installation)
- [Troubleshooting](#troubleshooting)
- [Reference Video and Image](#reference-video-and-image)
- [License](#license)
- [Full Report](#full-report)


## Overview
This project, "Maps for the Blind," is an Arduino-based assistive technology designed to help visually impaired individuals navigate a tactile map with stepper motor-driven guidance and audio feedback. 

The objective of "Globed for the Blind" is to create a user-friendly and educational system that enables blind people to comprehend continents spatially. This project seeks to give a multimodal experience that enables blind people to explore, navigate, and visualize the layout of the state in Malaysia by combining tactile and interactive features.

This project has two modes:
- **Mode A** includes a Braille keypad with a push button, an XY-gantry for map movement, and automatic audio feedback. The Braille keypad allows easy navigation, while the XY-gantry lifts and moves the map for tactile exploration. The system provides informative audio feedback about the map's content. This technology enhances accessibility, independence, and understanding of maps for visually impaired individuals, promoting inclusivity and empowering them to navigate their surroundings with greater confidence.
- **Mode B** is the assistive technology system, where each state is equipped with a touch sensor. When a user touches the touch sensor, it triggers the system to turn on the audio feature. This modification ensures that the audio is activated and ready to provide information as soon as the user engages with the touch sensor. This added functionality enhances the user experience by streamlining the process of accessing audio instructions and information, allowing visually impaired individuals to quickly and easily engage with the system.

## Features
- **Stepper motor control** for precise pointer positioning.
- **Audio guidance** using the DFPlayer Mini MP3 module.
- **Multiplexer-based input handling** for efficient signal processing.
- **Multiple modes** (`MODE_A` and `MODE_B`) for different navigation experiences.
- **Predefined coordinate mapping** for enhanced accessibility.
- **Touch sensor activation** for seamless interaction.

## Components
- Arduino-compatible microcontroller: Arduino Mega 2560
- CNC shield (for stepper motor control)
- Stepper motors (X and Y axis)
- Motor driver stepper motor (A4988)
- Linear actuator (LA-T8)
- Motor driver linear actuator (L298N)
- DFPlayer Mini MP3 module
- Capacitive touch sensor module (TTP223)
- Push Button
- Speaker or headphones
- Micro limit Switch
- 16-Channel Analog Multiplexer (Mux) for input handling
- Power supply (as per stepper motor and Arduino requirements)

## Circuit Diagram

<img src="https://github.com/bidayatulhidayah/Maps-for-the-Blinds/blob/main/Images%20and%20Diagram/Circuit%20Diagram.png?raw=true" alt="Circuit Diagram" width="300" />


## Control Flow Chart

<img src="https://github.com/bidayatulhidayah/Maps-for-the-Blinds/blob/20a31c9c758edd0da6fb29db0f302e74e2757fc4/Images%20and%20Diagram/Control%20Flow%20Chart.png" width="300" />


## Library Required
- `AccelStepper` by Mike McCauley [(Download)](https://www.airspayce.com/mikem/arduino/AccelStepper/)
- `MultiStepper` (included with AccelStepper)
- `SoftwareSerial` by Arduino [(Download)](https://www.arduino.cc/en/Reference/softwareSerial)
- `DFRobotDFPlayerMini` by DFRobot [(Download)](https://github.com/DFRobot/DFRobotDFPlayerMini)
- `Mux` by Seeed Studio [(Download)](https://github.com/Seeed-Studio/Arduino_Mux_Library)

## Installation
1. Install the necessary libraries in the Arduino IDE.
2. Connect the hardware components as per the pin definitions in `maps-for-the-blind.ino`.
3. Upload the `.ino` sketch to your Arduino board.
4. Place the MP3 files onto an SD card and insert it into the DFPlayer Mini.
5. Power the system and interact with the tactile map for guided navigation.

## Troubleshooting
- **No audio output:** Ensure the SD card is formatted correctly and contains the required MP3 files.
- **Stepper motors not moving:** Check wiring connections and ensure the correct power supply is used.
- **Unresponsive inputs:** Verify the multiplexer connections and input signals.
- **Arduino upload failure:** Make sure the correct board and port are selected in the Arduino IDE.

## Reference Video and Image

- [YouTube Video](https://youtu.be/ZxWtpYeG-e8)

<img src="https://github.com/bidayatulhidayah/Maps-for-the-Blinds/blob/99c398113041ae10c4479dce7a31d58ecb4e8c76/Images%20and%20Diagram/Front%20View.jpg" width="400" />

<img src="https://github.com/bidayatulhidayah/Maps-for-the-Blinds/blob/main/Images%20and%20Diagram/Testing%201.jpg?raw=true" width="400" />

<img src="https://github.com/bidayatulhidayah/Maps-for-the-Blinds/blob/main/Images%20and%20Diagram/Testing%202.jpg?raw=true" width="400" />


## License
This project is open-source under the MIT License.

## Full Report

[📥 Final Report (PDF)](https://github.com/bidayatulhidayah/Maps-for-the-Blinds/blob/e2624b9da062374908c3aef1aec64a42eee2abff/Report/IDP%20Final%20Report%20-%20Maps%20for%20the%20Blind.pdf)




