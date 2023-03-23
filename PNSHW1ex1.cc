#include <iostream> 
#include <cmath> 
#include <vector>
#include <iomanip>
using std::cout;  

//EXERCISE 1

//EQUATION WE WANT TO SOLVE
double f(double x, double t)
{ 
  return (1-t)*(5-2*t)*(sqrt (1-x));
} 
   

//ANALYTICAL SOLUTION
double s(double v)
{
    return -0.75 + (((static_cast<double>(1) / 144) * v) * (30 + v * (-21 + 4 * v))) * (12 * sqrt(7) + v * (-30 + (21 - 4 * v) * v));
}


int main() 
{ 
// Defining and initialising variables

  int n=15; 
  double h = 3 / double(n);     //STEP SIZE
  double k1 = 0.0, k2 = 0.0 ,k3 = 0.0, k4 = 0.0; //RUNGE-KUTTA COEFFICIENTS 
  double x=-0.75,t=0.0;
  double analytical = s(3);  //ANALYTICAL SOLUTION AT t = 3
  

  cout << t << " " << x << "\n";


  //RUNGE-KUTTA ALGORITHM FOR STEP-SIZE h=0.2
  for (int k=0.0; k<n; k++) 
  {  
    k1 = h * f(x,t);
    k2 = h * f(x + (k1 / 2), t + (h / 2));
    k3 = h * f(x + (k2 / 2), t + (h / 2));
    k4 = h * f(x + k3, t + h);
    x += (k1 + (2 * k2) + (2 * k3) + k4)/6;
    t += h; 
    cout << t << " " << x << "\n"; 
  } 


  //COMPARING ANALYTICAL AND NUMERICAL SOLUTION FOR VARIOUS STEP-SIZES
  std::vector<int> steps = { 15,30,45,60,75,100,150,300 }; //VARIOUS STEP-SIZES
  double t1 = 0.0, x1 = -0.75;
  double k11 = 0.0, k22 = 0.0, k33 = 0.0, k44 = 0.0;

  for (int j = 0.0; j < steps.size(); j++)
  {
      double step_size = static_cast<double>(3) / steps[j];
      int step = steps[j];

      for (int i = 0.0; i < step; i++) //RUNGE-KUTTA METHOD
      {
          k11 = step_size * f(x1, t1);
          k22 = step_size * f(x1 + (k11 / 2), t1 + (step_size / 2));
          k33 = step_size * f(x1 + (k22 / 2), t1 + (step_size / 2));
          k44 = step_size * f(x1 + k33, t1 + step_size);
          x1 += (k11 + (2 * k22) + (2 * k33) + k44) / 6;
          t1 += step_size;
      }

      //OUTPUTTING EASILY READABLE RESULTS
      double error = analytical - x1;
      cout << "numerical solution at t = 3 for step-size h = " << step_size << " : " << std::setprecision(8) << x1 << "\n";
      cout << "analytical solution at t = 3 : " << std::setprecision(8) << analytical << "\n";
      cout << "The discrepancy is : " << error << "\n";
      x1 = -0.75; //resetting x1 and t1 after each iteration
      t1 = 0.0;
  }

 

   
   }
   