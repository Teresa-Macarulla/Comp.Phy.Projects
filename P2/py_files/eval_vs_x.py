# eval_vs_x.py
import numpy as np
import matplotlib.pyplot as plt

# Load data: column 0 = x, columns 1..3 = eigenvectors
ana = np.loadtxt("../txt_files/evec_xi_ana.txt")
jac = np.loadtxt("../txt_files/evec_xi_jac.txt")

x = ana[:, 0]
assert np.allclose(x, jac[:, 0]), "x grids in the two files must match"

# Plot settings
markers = ['o', 's', '^']  # one marker per mode
plt.figure(figsize=(7, 4.5))

# Analytical (solid lines)
for i, m in zip(range(1, 4), markers):
    plt.plot(x, ana[:, i], marker='o', linestyle='-', label=f'Analytical v{i}', linewidth=1.5)

# Jacobi (dashed lines)
for i, m in zip(range(1, 4), markers):
    plt.plot(x, jac[:, i], marker='s', linestyle='--', label=f'Jacobi v{i}', linewidth=1.5)

plt.xlabel("x")
plt.ylabel("Eigenvector component")
plt.title("Analytical vs Jacobi eigenvectors (n=10)")
plt.grid(True, alpha=0.3)
plt.legend(ncols=2, fontsize=9)
plt.tight_layout()
plt.savefig("../pdf_files/eval_vs_x10.pdf")  # remove or change if you prefer not to save
plt.show()
