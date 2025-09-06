#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib> 
#include <vector>

double f(double x) {
    return 100.0*std::exp(-10.0*x);  // Definition of the f(x) function, right part of the Poisson equation.
}

double v_start=0.0;  // Boundary condition u(0)=0
double v_end=0.0;  // Boundary condition u(1)=0

int main() {
    int n=1; // Initialize number of steps for discretization. This value will change for each case n=10, n=100, n=1000 ...

    std::string filename = "data2.txt";  // Data file containig the values to be ploted
    std::ofstream out;  
    out.open(filename);
    out << std::scientific << std::setprecision(4);  // Formating parameters for the putùt data

    // Create vectors containing vectors to store x and v for different n steps values
    std::vector<std::vector<double>> X(4);
    std::vector<std::vector<double>> V(4);

    for (int j=0; j<=3; j++) {  // Each 'for' loop corresponds to a certain n value
        
        n = n*10;  // Number of discretization points 
        double h=1.0/(n-1.0); // Discretization interval

        std::vector<double> a(n-2, -1); // subdiagonal of matrix A
        a[0]=0;
        std::vector<double> b(n-2, 2);      // diagonal of matrix A
        std::vector<double> c(n-2, -1); // superdiagonal of matrix A
        c[n-3]=0;
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
        b2[0]=b[0];
        g2[0]=g[0];

        for (int i=1; i<n-2; i++) {
            double m=a[i]/b2[i-1];
            b2[i]=b[i]-m*c[i-1];
            g2[i]=g[i]-m*g2[i-1];
        }

        // BACK SUBSTITUTION 
        v[n-2]=g2[n-3]/b2[n-3];

        for (int i=n-3; i>0; i--) {
            v[i]=(g2[i-1]-c[i-1]*v[i+1])/b2[i-1];
        }

        // Establish boundary conditions for x and v vectors.
        x[0]=0.0;
        x[n-1]=1.0;
        v[0]=v_start;
        v[n-1]=v_end;

        X[j]=x;
        V[j]=v;

    }

    // Now we write all the data in 'data2.txt' file
    for (size_t i = 0; i < 10000 ; i++) {
        for (int k = 0; k < 4; k++) {
            if (i < X[k].size()) {
                out << std::setw(15) << X[k][i]
                    << std::setw(15) << V[k][i];
            } else {
                // Write empty colummns if there is no data
                out << std::setw(15) << 0.0
                    << std::setw(15) << 0.0;
            }
        }
        out << "\n";
    }

    out.close();

    return 0;
}