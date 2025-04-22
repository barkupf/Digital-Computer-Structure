# Digital-Computer-Structure
This repository contains Labs from a university course on computer structure, covering C programming, system programming, GPIO, interrupts, timers, ADC/DAC, DMA, and serial communication. The labs are conducted on **real hardware using the MSP430 microcontroller** and developed using C and embedded programming techniques.
Each lab has a **preparation task** and a **real time task**.

## 👥 Contributors

- [Bar Kupferschmied](https://github.com/barkupf)
- [Rotem Arbiv](https://github.com/RotemArbiv27)


## Table of contents 🔗
- [Structure](#Structure)
- [Tools/Setup](#Tools/Setup)
- [Labs](#Labs)
    - [Lab 1](#lab-1)
    - [Lab 2](#lab-2)
    - [Lab 3](#lab-3)
    - [Lab 4](#lab-4)
    - [Final Project](#final-project)

 ## Structure
In each Lab folder will be 3 folders:
- `PreTask` — contains the task files provided by **Hanan Ribo**, including instructions and any starter code.
- `PreSol` — contains the **preparation task solution code**, including `.c` source files and `.h` header files.
- `RealTime` — contains the **real-time task description** and the corresponding solution code, including `.c` and `.h` files, as well as a description of the implementation.

## Tools/Setup 🛠️

For this course, the following tools and environment setup are required to work with the MSP430 microcontroller:

### Compiler/IDE:
- **Code Composer Studio(CCS)** (Recommended IDE for MSP430)
  - Installation: [Code Composer Studio Download](https://www.ti.com/tool/CCSTUDIO)
  
  OR

- **IAR Embedded Workbench** (Alternative IDE)
  - Installation: [IAR Embedded Workbench](https://www.iar.com/iar-embedded-workbench/)
  
### Programmer/Debugger:
- **MSP430 LaunchPad** (Used to program and debug the MSP430 microcontroller)
  - Required for flashing code onto the hardware.
  
### Drivers:
- **MSP430 USB Drivers**  
  - Ensure that the necessary drivers are installed to interface with the LaunchPad via USB.
  - Installation guide: [MSP430 USB Drivers](https://www.ti.com/tool/MSP430-USB-Debug-Interface)

### Libraries:
- **MSP430 Driver Library** (for easier peripheral and I/O management)
  - Documentation: [MSP430 Driver Library](https://www.ti.com/tool/MSP430-DRIVER-LIBRARY)

### Operating System:
- Compatible with **Windows** or **Linux**.

 ## Labs

 ### Lab 1
 #### Aim of the Laboratory:
The goal of this lab is to implement a generic system-level code in C, structured into abstraction layers. The code will be based on a finite state machine (FSM) and will be designed to run on two different processor families (MSP430x2xx and MSP430x4xx).
#### Lab task:
Design a FSM which contains the next states:
1. *Idle State (0 = Idle = State)*:sleep mode, turning off the LEDs and conserving power.
2. *State 1 (PB0)*: When PB0 is pushed perform a binary counting pattern (counting upwards/downwards).
3. *State 2 (PB1)*: When PB1 is pushed, a single LED will be turned on, moving from right to left.
4. *State 3 (PB2)*: When PB2 is first pushed, generate a PWM signal on pin P2.7.

 ### Lab 2
 #### Aim of the Laboratory:
#### Lab task:

### Lab 3
 #### Aim of the Laboratory:
#### Lab task:

### Lab 4
 #### Aim of the Laboratory:
#### Lab task:

### Final Project
 #### Aim of the Laboratory:
#### Lab task:





