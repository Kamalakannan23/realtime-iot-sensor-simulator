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

=======
# Real-Time IoT Sensor Simulator

### 📡 Overview
A modern **C++20-based real-time IoT sensor simulation**, built to demonstrate:
- Deterministic timing (using `std::chrono`)
- Multithreaded data generation (`std::jthread`)
- Jitter computation and analysis
- Cross-platform design for Linux/Windows

This project serves as a **sample use case** for candidates applying to embedded or IoT software engineering roles (like at embedded ocean GmbH).

---

### ⚙️ Features
- Two simulated sensors producing temperature-like data at different intervals
- Thread-safe logging with `std::mutex`
- Graceful stop mechanism using `std::atomic`
- Jitter statistics for evaluating timing precision
- Clean RAII-based thread management using `std::jthread`

---

### 🛠️ Build & Run

```bash
git clone https://github.com/Kamalakannan23/realtime-iot-sensor-simulator.git
cd realtime-iot-sensor-simulator
mkdir build && cd build
cmake ..
make
./realtime_iot_sensor_simulator
