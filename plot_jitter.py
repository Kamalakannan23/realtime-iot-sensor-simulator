import matplotlib.pyplot as plt
import numpy as np

# Simulated jitter data for visualization
jitters = np.random.normal(0, 0.2, 100)
plt.plot(jitters, marker='o', linestyle='-', color='b')
plt.title("IoT Sensor Jitter Visualization")
plt.xlabel("Sample Index")
plt.ylabel("Jitter (ms)")
plt.grid(True)
plt.show()