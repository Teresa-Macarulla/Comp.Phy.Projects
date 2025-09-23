This repository documents the workflow and codes for Project 1.
The files are described in order of use, following the progression of the project.
.cpp, .exe and .hpp files are in "cpp_files" folder 

* problem2.cpp:
C++ program that sets up the tridiagonal A and solves the ecuation from Problem 2.
The results are written to eval_evec.txt

* eval_evec.txt:
Contains the eigenvalues and eigenvectors analytical values and Armadillo values for Problem 2.

* max_offdiag_symmetric.cpp:
Function that can identify the largest off-diagonal element of a matrix for Problem 3.

* problem3.cpp:
Short C++ program that test max_offdiag_symmetric.cpp function with a given matrix from Problem 3.

* Jacobi_rotation.cpp:
Function that applies the Jacobi rotation method. 

* problem4.cpp:
Applies the Jacobi rotation method to solve eigenvalues problem with the case N=6. 
It uses the functions Jacobi_rotation.cpp and max_offdiag_symmetric.cpp

* problem5.cpp:
Is a copy of problem4.cpp code but with an extra loop to try different values of N. This is for the solution of Problem 5.

* eval_evec_trans.txt:
Contains the eigenvalues, eigenvectors, and the number of transformations required to solve the eigenvalue problem for each value of N. The data are reported for N=6 up to N=12.

* transformations_vs_N.py:
Contains a short python code to plot the number of transformations required for each N case. The data for this plot is taken from "eval_evec_trans,txt".

* transformations_vs_N.pdf:
The plot of transformations vs N.

* problem6.cpp
Similar to problem5 but in this case it only works for a single value of N. The program calculates the eigenvalues and eigenvectors of A (using Jacobi algorithm) and storages the eigenvectors corresponding to tree minimum eigenvalues to evec_vd_xi.txt file. It also storages calculates the analytical solutions to the same eigenvectors.

* three_min.cpp
Function used in problem6.cpp to find the three lowest eigenvalues.

* evec_xi_jac.txt
Contains four colums. The first one are the discrete x values, the second the third and the fourth are the eigenvectors corresponding to the tree minimum eigenvalues calculated with Jacobi algorithm.  

* evec_xi_ana.txt
Contains four colums. The first one are the discrete x values, the second the third and the fourth are the eigenvectors corresponding to the tree minimum eigenvalues calculated analytically.  

* eval_vs_x.py:
Contains a short python code to plot the eigenvectors obtained from "evec_xi_jac.txt" and "evec_xi_ana.txt" vs the discretized x values.

* .pdf:
The plot of eigenvectors vs x.