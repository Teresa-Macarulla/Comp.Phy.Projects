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

* max_offdiag_symetric.hpp:
Contains the function declaration.

* problem3.cpp:
Short C++ program that test max_offdiag_symmetric.cpp function with a given matrix from Problem 3.

* Jacobi_rotation.cpp:
Function that applies the Jacobi rotation method. 

* Jacobi_rotation.hpp:
Contains the function declaration.

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