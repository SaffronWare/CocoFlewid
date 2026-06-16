<img width="472" height="322" alt="image" src="https://github.com/user-attachments/assets/0dc7a3b9-6198-4bca-891d-8dcc56d4381f" />

# Eulerian Fluid Simulation

A real-time 2D Eulerian fluid simulation prototype built with OpenGL compute shaders for the **Dawson Aerospace Club**.

This project was inspired by the fluid simulation explanation from the **Ten Minute Physics** video on Eulerian fluids. I used it as a first step toward building more advanced simulation and visualization tools for Dawson Aerospace, while learning how grid-based fluid solvers can be implemented on the GPU.

## Overview

The simulation uses a 2D grid representation of fluid quantities and updates them through a series of compute shader passes. The goal was to experiment with the basic structure of an Eulerian fluid solver and learn how to organize GPU-based simulation code using ping-pong buffers and separate shader passes.

This is an early prototype, but it is part of a larger direction toward more advanced aerospace-related simulations, including wind-tunnel visualization, obstacle interaction, 3D fluids, and more realistic rendering.

## Features

* Real-time 2D Eulerian fluid simulation
* Built for Dawson Aerospace Club
* OpenGL compute shader implementation
* Grid-based velocity and density fields
* Semi-Lagrangian-style advection
* Multiple compute passes for simulation steps
* Ping-pong textures/buffers for safe GPU updates
* Race-condition-aware shader structure
* Real-time visualization

## Technical Notes

The simulation is split into several compute shader passes. Instead of updating the same texture in-place, the project uses ping-pong buffers so each pass can read from one buffer and write into another. This avoids many common race-condition issues when running simulation updates in parallel on the GPU.

The project helped me better understand how GPU simulations are structured: each simulation step becomes a separate shader pass, and the order of those passes determines how the fluid state evolves over time.

## Motivation

I built this project to explore the foundations of GPU-based fluid simulation and to begin developing simulation tools for Dawson Aerospace Club.

Even though the current version is simple, it gave me experience with the core architecture behind larger GPU simulations: grid data, shader passes, buffer swapping, numerical updates, and real-time visualization.

## Current Status

This project is an early learning prototype. It is not intended to be a complete or physically accurate fluid solver yet.

I am using it as a foundation for more advanced upcoming projects, including:

* Interactive wind-tunnel-style simulation
* Obstacle interaction and boundary handling
* More stable incompressible fluid projection
* 3D fluid simulation
* SPH / particle-based fluid simulation
* Spatial hashing for particle simulations
* Ray-marched visualization of fluid volumes

## Running the Project

Build the project with CMake and run the executable.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Exact build steps may vary depending on the repository structure and development environment.
