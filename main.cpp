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
