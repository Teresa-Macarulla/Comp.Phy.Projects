#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib> 

double u(double x) {
    return 1.0 - (1.0 - std::exp(-10.0)) * x - std::exp(-10.0 * x);  // Definition of the u(x) function.
}

int main() {
    const int N = 200;  // Number of x points to be evaluated
    const double a = 0.0, b = 1.0;  // Boundary condition
    const double dx = (b-a)/(N-1);  // distance between x values to be evaluated

    std::string filename = "data.txt";
    std::ofstream data;
    data.open(filename);

    int width = 12;  // Width parameters to format the output "data.txt" file
    int prec  = 4;  // Precision of the values in "data.txt" fila

    for (int i = 0; i < N; i++) {  // Create x and y data values
        double x = a+i*dx;
        double y = u(x);

        data << std::setw(width) << std::setprecision(prec) << std::scientific << x
             << std::setw(width) << std::setprecision(prec) << std::scientific << y
             << std::endl;  // Write the data in "data.txt" file
    }
    data.close();

    return 0;
}
