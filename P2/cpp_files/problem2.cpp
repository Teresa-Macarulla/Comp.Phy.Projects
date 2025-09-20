#include <armadillo>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

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
    }

    // Write the eigenvalues and eigenvectors
    std::ofstream out("../txt_files/eval_evec.txt");
    out << std::scientific << std::setprecision(14);
    
    // eval_ana
    out << "# eval_ana (N entries)\n";
    for (int i = 0; i < N; ++i)
        out << std::setw(22) << eval_ana(i) << "\n";
    out << "\n";

    // eval_num
    out << "# eval_num (N entries)\n";
    for (int i = 0; i < N; ++i)
        out << std::setw(22) << eval_num(i) << "\n";
    out << "\n";

    // evec_ana
    out << "# evec_ana (N x N)\n";
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c)
            out << std::setw(22) << evec_ana(r, c);
        out << "\n";
    }
    out << "\n";

    // evec_num
    out << "# evec_num (N x N)\n";
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c)
            out << std::setw(22) << evec_num(r, c);
        out << "\n";
    }
    out << "\n";

    out.close();
    
    return 0;
}
