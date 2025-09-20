#include <armadillo>
#include <iostream>
#include "max_offdiag_symmetric.hpp"  // Include the header

int main() {
    // Define the 4x4 symmetric matrix from the problem
    arma::mat A={
        {1.0, 0.0, 0.0, 0.5},
        {0.0, 1.0, -0.7, 0.0},
        {0.0, -0.7, 1.0, 0.0},
        {0.5, 0.0, 0.0, 1.0}
    };

    int k=1, l=2;
    double max_val=max_offdiag_symmetric(A, k, l);

    // Print result: maximum off-diagonal value and its position
    std::cout << "Maximum off-diagonal value: " << max_val << std::endl;
    std::cout << "Position: (" << k << "," << l << ")" << std::endl;

    return 0;
}
