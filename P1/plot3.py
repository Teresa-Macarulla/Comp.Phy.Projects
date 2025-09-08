import numpy as np
import matplotlib.pyplot as plt

# Read absolute error data from "data3_abs.txt"

data_abs=np.loadtxt("data3_abs.txt")
start=0
end=10

for i in range(4): # Change m acording to the n_steps cases you have 
    x,y=data_abs[start+1:end-1,0], data_abs[start+1:end-1,1]
    start=end+1
    end=end+10**(i+2)

    n=10**(i+1)
    plt.plot(x,y, label="n="+str(n))

plt.xlabel("x")
plt.ylabel("log absolute error")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("plot3_abs.pdf")  
plt.close()

# Read relative error data from "data3_abs.txt"

data_abs=np.loadtxt("data3_rel.txt")
start=0
end=10

for i in range(4): # Change m acording to the n_steps cases you have 
    x,y=data_abs[start+1:end-1,0], data_abs[start+1:end-1,1]
    start=end+1
    end=end+10**(i+2)

    n=10**(i+1)
    plt.plot(x,y, label="n="+str(n))

plt.xlabel("x")
plt.ylabel("log relative error")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("plot3_rel.pdf")  
plt.close()

