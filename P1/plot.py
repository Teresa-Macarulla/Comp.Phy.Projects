import numpy as np
import matplotlib.pyplot as plt

# Read two-column data: x y
x,y=np.loadtxt("data.txt", unpack=True)

plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("u(x)")
plt.grid(True)
plt.tight_layout()
plt.savefig("plot.pdf")  # saves to PDF

