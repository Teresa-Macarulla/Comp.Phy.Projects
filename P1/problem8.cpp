#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include "safe_max.hpp"

// Exact solution u(x)
double u(double x) {
    return 1.0-(1.0-std::exp(-10.0))*x-std::exp(-10.0*x);
}

// Log Absolute error
double abso(double u, double v ){
    return std::log10(std::fabs(u-v));
}

// Log Relative error
double rela(double u, double v ){
    return std::log10(std::fabs((u-v)/u));
}

// Relative error
double relat(double u, double v ){
    return std::fabs((u-v)/u);
}

int main() {

    std::ifstream in("data2.txt");  // Imput data from "data2.txt"
    std::ofstream outabs("data3_abs.txt");  // Log. of absolute error data to "data3_abs.txt"
    std::ofstream outrel("data3_rel.txt");  // Log. of relative error data to "data3_real.txt"
    std::ofstream error("data3_error.txt");  // Maximum relative error to "data3_error.txt"
    outabs << std::scientific << std::setprecision(14);
    outrel << std::scientific << std::setprecision(14);   
    error << std::scientific << std::setprecision(14);

    // Read the data in "data2.txt" 
    std::vector<std::vector<double>> col; // vector of vectors for data
    std::string line;
    
    // Read file line by line
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        double value;
        int col_index = 0;

        // Read each number in the row
        while (iss >> value) {
            // Make sure col has enough columns
            if (col_index >= (int)col.size()) {
                col.push_back(std::vector<double>()); 
            }
            col[col_index].push_back(value);
            col_index++;
        }
    }

    in.close();

    int m = col.size();
    std::cout << m << std::endl;

    for (int j=2; j<=m; j+=2) {

        // Itinialize log. absolute, log. of relative and relative errors vector
        std::vector<double> abs(std::pow(10, j/2));
        std::vector<double> rel(std::pow(10, j/2));
        std::vector<double> rel_(std::pow(10, j/2));

        // Calculate log. absolute, log. relative and relative errors
        for (int i=0; i<std::pow(10, j/2); i++) {
            abs[i]=abso(u(col[j-2][i]),col[j-1][i]);
            rel[i]=rela(u(col[j-2][i]),col[j-1][i]);
            rel_[i]=relat(u(col[j-2][i]),col[j-1][i]);

            outabs << std::setw(30) << col[j-2][i] << std::setw(30) << abs[i];
            outabs << "\n";

            outrel << std::setw(30) << col[j-2][i] << std::setw(30) << rel[i]; 
            outrel << "\n";
        }

        // Obtain the maximum relative error for each case leaving the boundaries
        std::vector<double> max_rel(2);
        std::vector<double> rel_sub(rel_.begin()+1, rel_.end()-1);
        max_rel[1]=std::pow(10, j/2);
        max_rel[2]=safe_max(rel_sub);

        error << std::setw(30) << max_rel[1] << std::setw(30) << max_rel[2];
        error << "\n";
    }

    outabs.close();
    outrel.close();
    error.close();

    return 0;
}
