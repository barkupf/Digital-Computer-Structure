# Lab 2 - Preparation Task

This folder contains the **preparation task** for Lab 2.  
It includes the original task instructions and any starter code provided by the course staff.

## Contents
- Task instructions (PDF)
- Starter source files (`.c`, `.h`)

## Notes
- This task is completed before the real-time lab.
- Focuses on building up familiarity with the required hardware concepts.

## Aim of the Laboratory
This lab focuses on developing a portable embedded software system for the MSP430 microcontroller. The system is designed to operate in real-time and respond to user inputs through external interrupts, without using polling. Floating-point operations are avoided in favor of Q-format fixed-point arithmetic for performance.
## Description of the task
Design a FSM which contains the next states:
<details>
<summary><strong>💤 Idle State (State 0)</strong></summary>

- When no buttons are pressed, the system enters **sleep mode**.
- LCD screen is cleared.
- Timers are off.
- ADC is off.
- Power is conserved.
</details>

---

<details>
<summary><strong>🔁 State 1 (PB0)</strong></summary>

  **Frequency Counter**  
  - Measures the frequency of an external signal connected to P2.4 using Input Capture.
  - Displays the live frequency in Hz on the LCD in the range 50Hz – 20kHz with integer precision.
  - Only updates the numeric field of the screen for minimal refresh.
</details>

---

<details>
<summary><strong>➡️ State 2 (PB1)</strong></summary>

  **Stopwatch**
  - Implements a stopwatch using Timer_A0 in interrupt mode.
  - Displays elapsed time on the LCD in format MM:SS.
  - Starts when SW0 = 0
  - Stops when SW0 = 1
  - Resumes from last value when restarted
</details>

---

<details>
<summary><strong>🎛️ State 3 (PB2)</strong></summary>

  **Tone Generator**
  - Reads analog input from potentiometer (P1.3) using ADC12.
  - Converts input voltage to a square wave output with frequency 1kHz–2.5kHz using PWM.
  - Output is sent to P2.2 (buzzer).
  - The conversion use this linear transformation: fout = 1kHz + 1.5kHz * (N_ADC / 0x3FF)
</details>
