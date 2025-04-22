# Lab 1 - Preparation Task

This folder contains the **preparation task** for Lab 1.  
It includes the original task instructions and any starter code provided by the course staff.

## Contents
- Task instructions (PDF)
- Starter source files (`.c`, `.h`)

## Notes
- This task is completed before the real-time lab.
- Focuses on building up familiarity with the required hardware concepts.

## Aim of the Laboratory
The goal of this lab is to implement a generic system-level code in C, structured into abstraction layers. The code will be based on a finite state machine (FSM) and will be designed to run on two different processor families (MSP430x2xx and MSP430x4xx).

## Description of the task
Design a FSM which contains the next states:
<details>
<summary><strong>💤 Idle State (State 0)</strong></summary>

- When no buttons are pressed, the system enters **sleep mode**.
- All LEDs are turned off.
- Power is conserved.
</details>

---

<details>
<summary><strong>🔁 State 1 (PB0)</strong></summary>

- 🟢 **First press:**  
  Starts binary counting **upwards** using 8 LEDs.

- 🔄 **Second press:**  
  Switches to binary counting **downwards**.

- 🔃 **Behavior:**  
  - Alternates between up/down with each PB0 press.
  - Counting resumes from the previous value.
  - Delay: **0.5 seconds** between each increment/decrement.
  - Runs for **10 seconds**, then returns to **Idle state**.
  - **Non-interruptible**: Other states cannot interrupt until it finishes.
</details>

---

<details>
<summary><strong>➡️ State 2 (PB1)</strong></summary>

- 💡 A single LED moves **right to left**, one at a time.

- 🔃 **Behavior:**  
  - Delay: **0.5 seconds** between each shift.
  - Runs for **7 seconds**.
  - Resumes from the last LED in subsequent runs.
  - **Non-interruptible**: Cannot be interrupted until completed.
</details>

---

<details>
<summary><strong>🎛️ State 3 (PB2)</strong></summary>

- 🔁 **Toggle behavior with each press of PB2:**
  - **First press:**  
    Generate **PWM** on pin **P2.7** at **4 kHz**, **75% duty cycle**.
  - **Second press:**  
    Generate **PWM** on pin **P2.7** at **2 kHz**, **25% duty cycle**.

- 🔄 This toggling continues on subsequent presses.

- ⚠️ **Interruptible**:  
  Since the PWM is continuous, **other states *can* interrupt** this one.
</details>
