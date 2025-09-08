import numpy as np
import matplotlib.pyplot as plt

# Read data from "data.txt"
x,y=np.loadtxt("timing_general.txt", unpack=True)
x2,y2=np.loadtxt("timing_special.txt", unpack=True)

x=np.log10(x)
x2=np.log10(x2)

# Plot
plt.plot(x, y, label="General Algorithm", marker="o", linestyle="-")   
plt.plot(x2, y2, label="Special Algorithm", marker="^", linestyle="-")      


plt.xlabel("log(n)")
plt.ylabel("time [s]")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("plot4_timing.pdf")  
