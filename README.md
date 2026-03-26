# 🌌 ASCII Space Sim

A lightweight, physics-based orbital simulation written in C and rendered entirely within the terminal. This project uses ANSI escape sequences to create a real-time "graphics engine" out of ASCII characters, modeling the gravitational dance of celestial bodies.

## 🚀 Overview
Unlike a scripted animation, this simulation uses a **discrete-time integration** approach to calculate the movement of planets. Every frame, the program calculates the gravitational pull between every object in the system, updating their velocities and positions based on mass and distance.

## 🛠 Features
* **N-Body Simulation:** Every planet influences every other planet—there is no "static" center.
* **ANSI Terminal Rendering:** Uses escape codes (`\033[2J`) for high-performance terminal clearing and cursor positioning, avoiding the "flicker" associated with standard `printf` loops.
* **Physics Engine:** Implements the classic gravitational force formula:
  $$F = G \frac{m_1 m_2}{r^2}$$
* **Zero Dependencies:** Written in standard C using only `<stdio.h>`, `<math.h>`, and `<unistd.h>`.

## 🪐 The System
The current simulation initializes 5 bodies:
* **The Sun (`*`):** A high-mass central body (1000 units).
* **Planets (`o`, `@`, `+`, `O`):** Four distinct bodies initialized with specific tangential velocities to achieve stable (yet drifting) orbits.
