<<<<<<< HEAD
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <atomic>

using namespace std::chrono;

class Sensor {
public:
    Sensor(std::string name, double baseValue)
        : name_(std::move(name)), baseValue_(baseValue), running_(false) {}

    void start(int interval_us) {
        running_ = true;
        thread_ = std::thread(&Sensor::run, this, interval_us);
    }

    void stop() {
        running_ = false;
        if (thread_.joinable()) thread_.join();
    }

private:
    void run(int interval_us) {
        std::mt19937 rng(std::random_device{}());
        std::normal_distribution<double> noise(0.0, 0.05);

        while (running_) {
            auto now = high_resolution_clock::now();
            double value = baseValue_ + noise(rng);
            auto ts = duration_cast<microseconds>(now.time_since_epoch()).count();

            {
                std::lock_guard<std::mutex> lock(io_mutex_);
                std::cout << "[" << ts << " µs] "
                          << name_ << " reading: " << value << std::endl;
            }

            std::this_thread::sleep_for(microseconds(interval_us));
        }
    }

    std::string name_;
    double baseValue_;
    std::atomic<bool> running_;
    std::thread thread_;
    static std::mutex io_mutex_;
};

std::mutex Sensor::io_mutex_;

int main() {
    std::cout << "Starting real-time IoT Sensor Simulator...\n";

    Sensor temp("Temperature", 25.0);
    Sensor humid("Humidity", 60.0);

    temp.start(500000);
    humid.start(700000);

    std::this_thread::sleep_for(seconds(5));

    temp.stop();
    humid.stop();

    std::cout << "Simulation complete.\n";
}
=======
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>
#include <mutex>
#include <vector>
#include <numeric>
#include <iomanip>

/*
 * Real-Time IoT Sensor Simulator
 * ------------------------------
 * Simulates periodic sensor data generation and network transmission
 * using C++20 features (jthread, chrono, random, mutex, RAII).
 *
 * Demonstrates:
 *   - std::jthread (C++20 scoped threads)
 *   - std::chrono for time precision
 *   - atomic flag for graceful stop
 *   - mutex for thread-safe logging
 *   - computation of jitter statistics
 */

using namespace std::chrono_literals;

// Mutex for synchronized output between threads
std::mutex cout_mutex;

// Atomic flag used to signal stop between threads safely
std::atomic<bool> stop_flag{false};

// Simulated IoT sensor task
void sensor_task(int id, int interval_ms, std::vector<double>& jitters) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> noise(-0.5, 0.5);  // Simulated noise

    auto next_time = std::chrono::steady_clock::now();
    auto last_time = next_time;

    while (!stop_flag.load()) {
        // Calculate time delta (jitter)
        auto now = std::chrono::steady_clock::now();
        double jitter = std::chrono::duration<double, std::milli>(now - last_time).count() - interval_ms;
        jitters.push_back(jitter);
        last_time = now;

        // Simulate data
        double sensor_value = 25.0 + noise(gen); // Temperature-like reading

        {
            std::scoped_lock lock(cout_mutex);
            std::cout << "[Sensor " << id << "] "
                      << "Value: " << std::fixed << std::setprecision(2) << sensor_value
                      << " °C | Jitter: " << std::showpos << std::setprecision(3) << jitter << " ms\n";
        }

        // Wait until next scheduled tick
        next_time += std::chrono::milliseconds(interval_ms);
        std::this_thread::sleep_until(next_time);
    }
}

// Function to calculate and display jitter statistics
void print_jitter_stats(const std::vector<double>& jitters) {
    if (jitters.empty()) return;
    double avg = std::accumulate(jitters.begin(), jitters.end(), 0.0) / jitters.size();
    double max_jitter = *std::max_element(jitters.begin(), jitters.end());
    double min_jitter = *std::min_element(jitters.begin(), jitters.end());

    std::cout << "\n=== Jitter Statistics ===\n";
    std::cout << "Average: " << std::fixed << std::setprecision(3) << avg << " ms\n";
    std::cout << "Min: " << min_jitter << " ms | Max: " << max_jitter << " ms\n";
}

int main() {
    std::cout << "Starting Real-Time IoT Sensor Simulator...\n";

    // Create jitter data containers
    std::vector<double> sensor1_jitters;
    std::vector<double> sensor2_jitters;

    // Create two jthreads for sensors with 1000 ms and 500 ms intervals
    std::jthread sensor1(sensor_task, 1, 1000, std::ref(sensor1_jitters));
    std::jthread sensor2(sensor_task, 2, 500, std::ref(sensor2_jitters));

    // Run simulation for 10 seconds
    std::this_thread::sleep_for(10s);
    stop_flag.store(true);

    // Threads automatically join when out of scope (RAII behavior of std::jthread)

    std::cout << "\nSimulation ended. Calculating jitter stats...\n";
    print_jitter_stats(sensor1_jitters);
    print_jitter_stats(sensor2_jitters);

    std::cout << "\nProgram finished cleanly.\n";
    return 0;
}
>>>>>>> 0fb444f (Initial commit - Real-time IoT Sensor Simulator)
