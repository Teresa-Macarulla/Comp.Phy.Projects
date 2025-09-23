#include <iostream>
#include <iomanip>
#include "max_offdiag_symmetric.hpp"
#include "Jacobi_rotation.hpp"
#include "three_min.hpp"


int main(){
    using arma::mat; using arma::vec;

    const int N=9;
    const int n=N+1;          // number of intervals
    const double h=1.0/n;
    const double a=-1.0/(h*h);
    const double d=2.0/(h*h);

    // Define the vector with discrete x_i values containing the boundaries
    std::vector<double> x(N + 2);    // N+2 points from 0 to 1
    for (int i = 0; i < N + 2; ++i) {
        x[i] = i * h;                // equispaced points
    }


    // JACOBI ALGORITHM----------------------------------------------------------------------

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
    arma::vec eval= A.diag();
    std::vector<double> eval_jac(eval.begin(), eval.end());

    // Find the three lowest eigenvalues 
    std::vector<int> idx1 = three_min(eval_jac);

    // ANALYTICAL RESULTS-------------------------------------------------------------

    // Analytical eigenvalues and eigenvectors
    arma::vec eval_(N);
    mat evec_ana(N,N);
    for (int j=1; j<=N; ++j) {
        double theta=(j*arma::datum::pi)/(N+1.0);
        eval_(j-1)=d+2.0*a*std::cos(theta);
        for (int k=1; k<=N; ++k)
            evec_ana(k-1,j-1)=std::sin(j*k*arma::datum::pi/(N+1.0));
        // unit norm
        evec_ana.col(j-1)=normalise(evec_ana.col(j-1));
    }

    std::vector<double> eval_ana(eval_.begin(), eval_.end());

    // Find the three lowest eigenvalues 
    std::vector<int> idx2 = three_min(eval_ana);

    // WRITE THE RESULTS--------------------------------------------------------------

    // Write the eigenvectors and corresponding x_i to evec_xi_ana.txt 
    std::ofstream out1("../txt_files/evec_xi_jac.txt");
    std::ofstream out2("../txt_files/evec_xi_ana.txt");
    out1 << std::scientific << std::setprecision(14);
    out2 << std::scientific << std::setprecision(14);

    // x=0 boundary
    out1 << x[0] << std::setw(22) << 0.0 << std::setw(22) << 0.0 << std::setw(22) << 0.0 << "\n";
    out2 << x[0] << std::setw(22) << 0.0 << std::setw(22) << 0.0 << std::setw(22) << 0.0 << "\n";

    for (int i = 1; i < N + 1; ++i) {       
        out1 << x[i] << std::setw(22) << R(i-1,idx1[0])<< std::setw(22) << R(i-1,idx1[1])<< std::setw(22) << R(i-1,idx1[2])<< "\n";
        out2 << x[i] << std::setw(22) << evec_ana(i-1,idx2[0])<< std::setw(22) << evec_ana(i-1,idx2[1])<< std::setw(22) << evec_ana(i-1,idx2[2])<< "\n";
    }

    // x=1 boundary
    out1 << x[N+1] << std::setw(22) << 0.0 << std::setw(22) << 0.0 << std::setw(22) << 0.0 << "\n";
    out2 << x[N+1] << std::setw(22) << 0.0 << std::setw(22) << 0.0 << std::setw(22) << 0.0 << "\n";

    out1.close();
    out2.close();
    return 0;
}