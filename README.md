# Digital-Computer-Structure
This repository contains Labs from a university course on computer structure, covering C programming, system programming, GPIO, interrupts, timers, ADC/DAC, DMA, and serial communication. The labs are conducted on **real hardware using the MSP430 microcontroller** and developed using C and embedded programming techniques.
Each lab has a **preparation task** and a **real time task**.

## Table of contents 🔗
- [Structure](#Structure)
- [Tools/Setup](#Tools/Setup)
- [Labs](#Labs)
    - [Lab 1](###lab-1)
    - [Lab 2](###lab-2)
    - [Lab 3](###lab-3)
    - [Lab 4](###lab-4)
    - [Final Project](#final-project)

 ## Structure
For each Lab will be 3 folders:
- `Lab_j_PreTask` — contains the task files provided by **Hanan Ribo**, including instructions and any starter code.
- `Lab_j_PreSol` — contains the **preparation task solution code**, including `.c` source files and `.h` header files.
- `Lab_j_RealTime` — contains the **real-time task description** and the corresponding solution code, including `.c` and `.h` files, as well as a description of the implementation.

> `j` represents the lab number (e.g., `Lab_1_PreTask`, `Lab_2_RealTime`, etc.).

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
1. *Idle State (0 = Idle = State)*: When no buttons are pushed, the system enters the sleep mode, turning off the LEDs and conserving power.
2. *State 1 (PB0)*: When PB0 is first pushed, turn on 8 LEDs in a binary counting pattern (counting upwards). When it is pushed for the second time, turn on 8 LEDs in a binary counting pattern (counting downwards). This toggling continues with each press. The counting resumes from where it last stopped. The counting will occur in a periodic loop with a delay of 0.5 seconds between each increment/decrement. This mode will run for 10 seconds before the system transitions to the idle state.
3. *State 2 (PB1)*: When PB1 is pushed, a single LED will be turned on, moving from right to left with a delay of 0.5 seconds between each step. This mode will run for 7 seconds, with the LED continuing from where it left off in subsequent activations.
4. *State 3 (PB2)*: When PB2 is first pushed, generate a PWM signal on pin P2.7 with a frequency of 4 kHz and a 75% Duty Cycle. When it is pushed for the second time, generate a PWM signal on pin P2.7 with a frequency of 2 kHz and a 25% Duty Cycle. This toggling continues with each press.

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





