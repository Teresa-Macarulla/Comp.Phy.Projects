import numpy as np
import matplotlib.pyplot as plt

# Read data from "data.txt"
x,y=np.loadtxt("data.txt", unpack=True)

# Read data from "data2.txt"
data2=np.loadtxt("data2.txt")

x1,y1=data2[0:10,0], data2[0:10,1]
x2,y2=data2[0:100,2], data2[0:100,3]
x3,y3=data2[0:1000,4], data2[0:1000,5]
x4,y4=data2[0:10000,6], data2[0:10000,7]

# Plot
plt.plot(x, y, label="u(x)", marker="o", linestyle="-")        
plt.plot(x1, y1, label="n=10", marker="s", linestyle="--")     
plt.plot(x2, y2, label="n=100", marker="^", linestyle="-")     
plt.plot(x3, y3, label="n=1000", marker="d", linestyle="--")   
plt.plot(x4, y4, label="n=10000", marker=".", linestyle="-")

plt.xlabel("x")
plt.ylabel("u(x)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("plot2.pdf")  

