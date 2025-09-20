#include <armadillo>
#include <cmath>
#include <cassert>

// Function to find the largest off-diagonal element of a symmetric matrix
double max_offdiag_symmetric(const arma::mat& A, int& k, int& l) {
    
    assert(A.is_square() && "Matrix must be square.");
    assert(A.n_rows > 1 && "Matrix must be larger than 1x1.");

    double max_val=0.0;
    int n=A.n_rows;

    // Loop through the upper triangle (matrix is symmetric)
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            double val=std::abs(A(i, j));
            if (val>max_val) {
                max_val=val;
                k=i;
                l=j;
            }
        }
    }

    return max_val;
}
