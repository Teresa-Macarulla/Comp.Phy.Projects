#include <iostream>
#include <iomanip>
#include "max_offdiag_symmetric.hpp"
#include "Jacobi_rotation.hpp"

int main(){
    using arma::mat; using arma::vec;
    const int N=6;
    const int n=N+1;          // number of intervals
    const double h=1.0/n;
    const double a=-1.0/(h*h);
    const double d=2.0/(h*h);

    // Build tridiagonal A (N x N)
    arma::mat A=arma::mat(N,N); 
    A.diag().fill(d);
    A.diag( 1).fill(a);
    A.diag(-1).fill(a);

    mat R=arma::eye<mat>(N,N);       // eigenvector accumulator
    const double eps=1e-12;          // tolerance for off-diagonal max
    const int    Kmax=50*N*N;        // safety cap on iterations

    int it=0;
    while (true) {
        int p=0, q=1;
        double max_off=max_offdiag_symmetric(A,p,q);   // your function

        if (max_off<eps||it>=Kmax) break;

        if (p>q) std::swap(p,q);      // ensure p < q as assumed by rotation
        Jacobi_rotation(A,R,p,q);    // single rotation
        ++it;
    }

    // Results: eigenvalues on diag(A), eigenvectors are columns of R
    vec evals=A.diag();

    std::cout << std::scientific << std::setprecision(6);
    std::cout << "Iterations: " << it << "\n";
    std::cout << "Eigenvalues (diag A):\n" << evals.t();
    std::cout << "Eigenvectors (columns of R):\n" << R << "\n";

    return 0;
}
