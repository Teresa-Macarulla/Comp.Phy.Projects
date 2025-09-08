#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <chrono>

double f(double x) {
    return 100.0*std::exp(-10.0*x);  // Definition of the f(x) function, right part of the Poisson equation.
}

double v_start=0.0;  // Boundary condition u(0)=0
double v_end=0.0;  // Boundary condition u(1)=0
int m=6; // Cases from n=10 to n=10^7

int main() {
    int n=1; // Initialize number of steps for discretization. This value will change for each case n=10, n=100, n=1000 ...

    std::string filename = "data4.txt";  // Data file containig the values to be ploted
    std::ofstream out;  
    out.open(filename);
    out << std::scientific << std::setprecision(14);  // Formating parameters for the putùt data

    std::ofstream tim("timing_special.txt");  // Store the timing information in "timing_special.txt"
    tim << std::scientific << std::setprecision(14);

    // Create vectors containing vectors to store x and v for different n steps values
    std::vector<std::vector<double>> X(m);
    std::vector<std::vector<double>> V(m);

    // Create a vector to store timing information of each n case
    std::vector<double> time(m);

    for (int j=0; j<=m-1; j++) {  // Each 'for' loop corresponds to a certain n value
        
        n = n*10;  // Number of discretization points 
        double h=1.0/(n-1.0); // Discretization interval

        std::vector<double> g(n-2);  // Right-hand side of Av=g
        
        // x and v vectors have 2 more elements because of the boundary points
        std::vector<double> x(n);
        std::vector<double> v(n);  

        std::vector<double> g2(n-2); // Vector g' for the Forward substitution and Back substitution
        std::vector<double> b2(n-2); // Vector b' for the Forward substitution and Back substitution

        for (int i=1; i<=n-2; i++) {  // Build g and x vectors
            x[i]=i*h;            
            if (i==1) {
                g[i-1]=h*h*f(x[i])+v_start; // First g value
            } else if (i==n-2) {
                g[i-1]=h*h*f(x[i])+v_end;   // Last g value
            } else {
                g[i-1]=h*h*f(x[i]);           
            }
        }

        // FORWARD SUBSTITUTION 
        auto t1 = std::chrono::high_resolution_clock::now(); // Start measuring time for SPECIAL ALGORITHM

        b2[0]=2.0;
        g2[0]=g[0];

        for (int i=1; i<n-2; i++) {
            b2[i]=2.0-1.0/b2[i-1];
            g2[i]=g[i]+g2[i-1]/b2[i-1];
        }

        // BACK SUBSTITUTION 
        v[n-2]=g2[n-3]/b2[n-3];

        for (int i=n-3; i>0; i--) {
            v[i]=(g2[i-1]+v[i+1])/b2[i-1];
        }

        auto t2 = std::chrono::high_resolution_clock::now();  // End measuring time for SPECIAL ALGORITHM
        time[j]= std::chrono::duration<double>(t2 - t1).count();

        // Write time information
        tim << std::setw(30) << std::pow(10, j+1) << std::setw(30) << time[j];
        tim << "\n";

        // Establish boundary conditions for x and v vectors.
        x[0]=0.0;
        x[n-1]=1.0;
        v[0]=v_start;
        v[n-1]=v_end;

        X[j]=x;
        V[j]=v;

    }
    tim.close();

    // Now we write all the data in 'data2.txt' file
    for (size_t i = 0; i < std::pow(10, m) ; i++) {
        for (int k = 0; k < m; k++) {
            if (i < X[k].size()) {
                out << std::setw(30) << X[k][i]
                    << std::setw(30) << V[k][i];
            } else {
                // Write empty colummns if there is no data
                out << std::setw(30) << 0.0
                    << std::setw(30) << 0.0;
            }
        }
        out << "\n";
    }

    out.close();

    return 0;
}