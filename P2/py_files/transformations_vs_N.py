import matplotlib.pyplot as plt

# Data
N = [6, 7, 8, 9, 10, 11, 12]
transf = [41, 79, 102, 136, 161, 214, 254]

# Plot
plt.figure(figsize=(6,4))
plt.plot(N, transf, marker='o', linestyle='-', color='b')

# Labels
plt.xlabel("N")
plt.ylabel("Number of transformations")
plt.grid(True)

# Save and show
plt.tight_layout()
plt.savefig("../pdf_files/transformations_vs_N.pdf")
plt.show()
