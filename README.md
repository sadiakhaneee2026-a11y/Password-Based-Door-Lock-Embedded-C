# Password-Based Door Lock System (Embedded C)

## Project Overview
This project is a secure, microcontroller-based digital door lock system designed using **Embedded C**. The entire system operation is controlled by firmware coded in **MPLAB X IDE** and its functionality has been verified via hardware simulation in **Proteus**.

## Hardware & System Components
- **Microcontroller:** PIC / AVR Microcontroller (Coded in MPLAB X)
- **Input Interface:** 4x4 Matrix Keypad (For user password entry)
- **Output Display:** 16x2 Character LCD (To display system status like "Enter Pass", "Access Granted", "Locked")
- **Actuator:** DC Motor / Solenoid Lock (To simulate the physical door unlocking mechanism)

## Key Features
- **Security Lockout:** Automatically triggers an error/alarm state if an incorrect password is typed consecutively.
- **FSM Control Logic:** Modeled using structural states to ensure smooth transition between idle, entering password, open, and locked states.
- **Real-time Feedback:** Provides instant visual prompts on the LCD screen based on user actions.

## Repository Files
- `main.c`: Contains the core firmware and state machine architecture written in Embedded C.
- `project_306.pdsprj`: The official Proteus hardware simulation layout file.

## How to Run the Simulation
1. Open the `.pdsprj` file in **Proteus ISIS**.
2. Double-click the microcontroller unit in the workspace.
3. Link the compiled `.hex` file generated from the `main.c` script.
4. Click the **Play/Run** button at the bottom of Proteus to interact with the keypad.

