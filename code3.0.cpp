#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm> //For max element

using namespace std;

// ODE: dy/dt = f(t,y)

double f(double t, double y) {
    return -2*y + exp(-t);
}

// exact solution
double exact(double t) {
    return exp(-2*t) + 0.5*exp(-t);
}

// RK4 single step
double RK4_step(double t, double y, double h) {
    double k1 = f(t, y);
    double k2 = f(t + h/2, y + h/2 * k1);
    double k3 = f(t + h/2, y + h/2 * k2);
    double k4 = f(t + h, y + h * k3);
    return y + h/6*(k1 + 2*k2 + 2*k3 + k4);
}

// adams-bashforth 2step


// adams bashforth 3 step
vector<double> AB3(double h, int n) {
    vector<double> y(n+1), t(n+1);
    y[0] = 1.0; t[0] = 0.0;
    y[1] = RK4_step(t[0], y[0], h); t[1] = t[0] + h;
    y[2] = RK4_step(t[1], y[1], h); t[2] = t[1] + h;

    for(int i=2; i<n; ++i) {
        t[i+1] = t[i] + h;
        y[i+1] = y[i] + h/12*(23*f(t[i],y[i]) - 16*f(t[i-1],y[i-1]) + 5*f(t[i-2],y[i-2]));
    }
    return y;
}

// adams-multon 2 step Predictor Corrector (AM2)
vector<double> AM2_PC(double h, int n) {
    vector<double> y(n+1), t(n+1);
    y[0] = 1.0; t[0] = 0.0;
    y[1] = RK4_step(t[0], y[0], h); t[1] = t[0] + h;

    for(int i=1; i<n; ++i) {
        t[i+1] = t[i] + h;
        // predictor- AB2
        double y_pred = y[i] + h/2*(3*f(t[i], y[i]) - f(t[i-1], y[i-1]));
        // corrector- AM2
        y[i+1] = y[i] + h/2*(f(t[i+1], y_pred) + f(t[i], y[i]));
    }
    return y;
}

// compute errors
vector<double> compute_error(const vector<double>& y, const vector<double>& t) {
    vector<double> err(y.size());
    for(size_t i=0; i<y.size(); ++i)
        err[i] = fabs(y[i] - exact(t[i]));
    return err;
}

        // find max error
  double max_error(const vector<double>& err) {
    return *max_element(err.begin(), err.end());
    }

   int main() {
    // change h to 0.1 (accurate) or 1.0 (show instability)
    double h = 1.0; // Large step to show stability issues
    double T = 5.0;
    int n = int(T/h);

    vector<double> t(n+1);
    for(int i=0; i<=n; ++i) t[i] = i*h;

    // solve all methods
    vector<double> y_RK(n+1), y_AB2, y_AB3, y_AM2;
    y_RK[0] = 1.0;
    for(int i=0; i<n; ++i)
        y_RK[i+1] = RK4_step(t[i], y_RK[i], h);

    y_AB2 = AB2(h, n);
    y_AB3 = AB3(h, n);
    y_AM2 = AM2_PC(h, n);

    // Compute errors
    vector<double> err_RK = compute_error(y_RK, t);
    vector<double> err_AB2 = compute_error(y_AB2, t);
    vector<double> err_AB3 = compute_error(y_AB3, t);
    vector<double> err_AM2 = compute_error(y_AM2, t);

    // Print max errors for all methods
    cout << "Step size h = " << h << "\n";
    cout << "Max Error RK4:   " << max_error(err_RK) << "\n";
    cout << "Max Error AB2:   " << max_error(err_AB2) << "\n";
    cout << "Max Error AB3:   " << max_error(err_AB3) << "\n";
    cout << "Max Error AM2:   " << max_error(err_AM2) << "\n";

      //save result to CSV file
    ofstream file("multistep_results.csv");
    file << "t,Exact,RK4,AB2,AB3,AM2,Err_RK,Err_AB2,Err_AB3,Err_AM2\n";
    for(int i=0; i<=n; ++i)
        file << t[i] << "," << exact(t[i]) << "," << y_RK[i] << ","
             << y_AB2[i] << "," << y_AB3[i] << "," << y_AM2[i] << ","
             << err_RK[i] << "," << err_AB2[i] << "," << err_AB3[i] << "," << err_AM2[i] << "\n";
    file.close();




    cout << "Results saved to multistep_results.csv\n";
    cout << "Run with h = 0.1 for accuracy and h = 1.0 to see stability issues.\n";

   return 0;



   }









