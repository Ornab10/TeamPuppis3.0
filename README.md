# TeamPuppis3.0
## Key Features

* Implements *single-step and multistep numerical methods* for solving first-order ordinary differential equations (ODEs).
* Supported methods:

  * *Runge–Kutta 4th Order (RK4)*
  * *Adams–Bashforth 2-step (AB2)*
  * *Adams–Bashforth 3-step (AB3)*
  * *Adams–Moulton 2-step Predictor–Corrector (AM2-PC)*
* Uses *RK4 for initialization* of multistep methods to ensure accuracy.
* Computes the *exact analytical solution* for error comparison.
* Calculates:

  * Pointwise absolute error
  * Maximum error over the interval
* Demonstrates *stability behavior* by allowing different step sizes:

  * Small step size → stable and accurate
  * Large step size → instability in explicit multistep methods
* Exports numerical results and errors to a *CSV file* for plotting and further analysis.


## Results

* The program prints the *maximum error* for each numerical method over the time interval.
* When using a *small step size (e.g., h = 0.1)*:

  * All methods show good agreement with the exact solution.
  * RK4 produces the smallest error.
* When using a *large step size (e.g., h = 1.0)*:

  * Adams–Bashforth methods exhibit noticeable *stability issues*.
  * The Adams–Moulton predictor–corrector method remains more stable than explicit methods.
* A file named multistep_results.csv is generated containing:
* ## Technologies Used

* *Programming Language:* C++
* *Numerical Methods:*

  * Runge–Kutta (RK4)
  * Adams–Bashforth methods
  * Adams–Moulton predictor–corrector method
* *Standard Libraries:*

  * <iostream> for input/output
  * <vector> for dynamic arrays
  * <cmath> for mathematical functions
  * <fstream> for file handling
  * <algorithm> for error analysis

  * Time values
  * Exact solution
  * Numerical solutions from all methods
  * Corresponding absolute errors

This file can be used to generate error curves and stability plots.


## How to Run

1. * Run this code into c++ compiler*
     
2. *Change step size*

   * Open the source file and modify:

     cpp
     double h = 0.1;   // for accuracy
     // or
     double h = 1.0;   // to demonstrate stability issues
     

3. *View Results*

   * Console output shows maximum errors for each method.
   * Open multistep_results.csv/xlsx in Excel for plot:

     * Numerical solutions vs exact solution 
     * Error curves and graph
     * Stability behavior 
