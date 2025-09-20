#include <armadillo>
#include <cmath>
#include <cassert>

void Jacobi_rotation(arma::mat& A, arma::mat& R, int p, int q)
{
    assert(A.is_square() && A.n_rows > 1);
    assert(R.n_rows==A.n_rows && R.n_cols==A.n_cols);

    const int N=A.n_rows;
    double app=A(p,p);
    double aqq=A(q,q);
    double apq=A(p,q);

    double c=1.0, s=0.0;            // defaults if apq == 0
    if (std::abs(apq)>0.0) {
        double tau=(aqq-app)/(2.0*apq);
        double root=std::sqrt(1.0+tau*tau);
        double t1=-tau+root;
        double t2=-tau-root;
        double t=std::min(t1,t2);   // choose smaller magnitude (more stable)
        c=1.0/std::sqrt(1.0+t*t);
        s=c*t;
    }

    // Update A (only rows/columns p and q change)
    for (int i=0; i<N ; ++i) {
        if (i!=p && i!=q) {
            double aip=A(i,p), aiq=A(i,q);
            double aip_new=c*aip-s*aiq;
            double aiq_new=s*aip+c*aiq;

            A(i,p)=A(p,i)=aip_new;  // keep symmetry
            A(i,q)=A(q,i)=aiq_new;
        }
    }
    // Diagonal block update and zero the (p,q)
    double app_new=c*c*app-2.0*c*s*apq+s*s*aqq;
    double aqq_new=s*s*app+2.0*c*s*apq+c*c*aqq;
    A(p,p)=app_new;
    A(q,q)=aqq_new;
    A(p,q)=A(q,p)=0.0;

    // Update eigenvector accumulator R
    for (int i=0; i<N; ++i) {
        double rip=R(i,p), riq=R(i,q);
        R(i,p)=c*rip-s*riq;
        R(i,q)=s*rip+c*riq;
    }

}