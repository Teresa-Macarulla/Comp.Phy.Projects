#include <armadillo>
#include <cmath>
#include <iostream>
#include <iomanip>

int main() {
    using arma::mat; using arma::vec; using arma::normalise;
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

    // Solve eigenvalue problem with Armadillo 
    vec  eval_num; // the eigenvalues will be stored here
    mat  evec_num; // the eigenvectors will be stored here
    arma::eig_sym(eval_num, evec_num, A);

    // Analytical eigenvalues and eigenvectors
    vec eval_ana(N);
    mat evec_ana(N,N);
    for (int j=1; j<=N; ++j) {
        double theta=(j*arma::datum::pi)/(N+1.0);
        eval_ana(j-1)=d+2.0*a*std::cos(theta);
        for (int k=1; k<=N; ++k)
            evec_ana(k-1,j-1)=std::sin(j*k*arma::datum::pi/(N+1.0));
        // unit norm
        evec_ana.col(j-1)=normalise(evec_ana.col(j-1));
        // eigenvectors are unique up to sign; align with numeric
        double s=arma::dot(evec_ana.col(j-1),evec_num.col(j-1))>=0.0?1.0:-1.0;
        evec_ana.col(j-1)*=s;
    }

    // Report max absolute differences
    double max_ev_diff = arma::abs(eval_num - eval_ana).max();
    double max_vec_diff = (evec_num - evec_ana).abs().max();

    std::cout << std::setprecision(10) << std::scientific;
    std::cout << "Analytical eigenvalues (N=6):\n";
    eval_ana.t().raw_print(std::cout);

    std::cout << "\nMax |lambda_num - lambda_ana| = " << max_ev_diff << "\n";
    std::cout << "Max |v_num - v_ana (sign-aligned)|_inf = " << max_vec_diff << "\n";
    return 0;
}
