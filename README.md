# Digital Clock using PIC18F4520 and Timer1

## 📌 Project Overview

This project implements a real-time digital clock using the PIC18F4520 microcontroller. The clock displays minutes and seconds on a multiplexed 4-digit seven-segment display. Timer1 is configured to generate precise time intervals, while interrupts are used for accurate time counting. Push buttons allow the user to pause/resume the clock and reset the timer.

The project demonstrates interrupt programming, timer configuration, multiplexed display interfacing, and real-time embedded system design using Embedded C.

---

## 🚀 Features

- Real-time MM:SS digital clock
- Timer1 interrupt-based time counting
- 4-digit multiplexed seven-segment display
- Pause/Resume functionality
- Reset button
- Accurate timing using hardware timer
- Low CPU utilization through interrupt handling

---

## 🛠 Hardware Components

- PIC18F4520 Microcontroller
- 4-Digit Common Cathode Seven Segment Display
- Push Buttons
- Crystal Oscillator (4 MHz)
- Capacitors
- Breadboard / PCB
- 5V Power Supply

---

## 💻 Software Used

- MPLAB X IDE
- XC8 Compiler
- Proteus Design Suite
- Embedded C

---

## ⚙ Working Principle

1. Timer1 is configured to generate a 10 ms interrupt.
2. Every interrupt increments an internal software counter.
3. After 100 interrupts, one second is added.
4. The display continuously refreshes using multiplexing.
5. The Pause button freezes or resumes the clock.
6. The Reset button sets the timer back to 00:00.

---


---

## 📖 Concepts Used

- Embedded C Programming
- PIC18F4520 Microcontroller
- Timer1 Configuration
- Interrupt Service Routine (ISR)
- Seven Segment Display Interfacing
- Multiplexing Technique
- Digital Clock Design
- Real-Time Embedded Systems

---

## 🎯 Applications

- Digital Wall Clocks
- Stopwatch Systems
- Embedded Timing Devices
- Industrial Timers
- Educational Embedded Projects
- Electronic Time Displays

---


## 👩‍💻 Author

**Harshada Sunil Jadhav**

B.Tech (Electronics and Telecommunication Engineering)


---

⭐ If you found this project useful, don't forget to give it a Star!
