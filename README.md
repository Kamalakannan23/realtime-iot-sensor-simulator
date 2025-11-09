# Real-Time IoT Sensor Simulator

A lightweight C++20 example that simulates temperature and humidity sensors publishing data at microsecond precision.  
Demonstrates multithreading, timing accuracy, and clean C++ design for real-time IoT edge applications.

## Features
- Modern C++20 threading and chrono timing
- Deterministic data generation with microsecond timestamps
- Cross-platform (Linux/Windows)
- Simple build via CMake

## Build
```bash
mkdir build && cd build
cmake ..
make
./realtime_iot_sensor_simulator
