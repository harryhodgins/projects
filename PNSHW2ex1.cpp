#include <iostream> 
#include <cmath> 
#include <vector>
#include <iomanip>
#include <fstream>
using std::cout;
using namespace std;


//EXERCISE 1

//WRITING SECOND ORDER ODE AS SYSTEM OF FIRST ORDER ODEs

double a(double t,double x1, double x2) 
{
	return x2;
}

double b(double t,double x1, double x2)
{
	return  ( (- 30.0 * x1) / (2 + t*t * x1*x1) );
}


//RUNGE-KUTTA FUNCTION
double F(double x2) 
{
    
           int n = 1000;
           double h = 10.0 / double(n);     //STEP SIZE


           //RUNGE-KUTTA COEFFICIENTS 
           double k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0;
           double l1 = 0.0, l2 = 0.0, l3 = 0.0, l4 = 0.0;


           //INITIALISING VARIABLES
           double t = 0.0, x1 = 0.75;


           //RUNGE-KUTTA ALGORITHM
           for (int i = 0.0; i < n; i++)
           {
               k1 = h * a(t, x1, x2);
               l1 = h * b(t, x1, x2);


               k2 = h * a(t + (h / 2.0), x1 + (k1 / 2.0), x2 + (l1 / 2.0));
               l2 = h * b(t + (h / 2.0), x1 + (k1 / 2.0), x2 + (l1 / 2.0));

               k3 = h * a(t + (h / 2.0), x1 + (k2 / 2.0), x2 + (l2 / 2.0));
               l3 = h * b(t + (h / 2.0), x1 + (k2 / 2.0), x2 + (l2 / 2.0));

               k4 = h * a(t + h, x1 + k3, x2 + l3);
               l4 = h * b(t + h, x1 + k3, x2 + l3);


               t += h;
               x1 += (k1 + (2.0 * k2) + (2.0 * k3) + k4) * (1.0 / 6.0);
               x2 += (l1 + (2.0 * l2) + (2.0 * l3) + l4) * (1.0 / 6.0);
               
           }
           return x1 +1 ;
}


//BISECTION METHOD FOR FINDING ROOTS OF F(c)
double bisect(double c_lo, double c_hi)
{
    double b_lo = F(c_lo);
    double b_hi = F(c_hi);
    double c_mid;

    do
    {
        c_mid = 0.5 * (c_hi + c_lo);
        double b_mid = F(c_mid);
        if (b_mid * b_lo > 0.0) // does b_mid have same sign as b_lo? 
        {
            c_lo = c_mid; b_lo = b_mid;
        }
        else
        {
            c_hi = c_mid; b_hi = b_mid;
        }
        //cout << c_lo << " - " << c_mid << " - " << c_hi << "\n";
    } while (c_hi - c_lo > 1.0e-10);
    return 0.5 * (c_hi + c_lo);
}

std::vector<double> solutions;

int main()
{
    double stepsize = 0.01;
    double tvalue = 0.0;

    /*for (double j = -30.0; j < 30; j++)
    {
        cout << rk4(j) << " " << j << "\n";
    }*/

    //finding dx/dt (t=0) values. A suitable range for the bisection method is found by inspecting the graph of F(c)

    solutions.push_back(bisect(-20, -15));
    solutions.push_back(bisect(-10, -5));
    solutions.push_back(bisect(-4, -2));
    solutions.push_back(bisect(1, 3));
    solutions.push_back(bisect(3, 5));
    solutions.push_back(bisect(7, 9));
    solutions.push_back(bisect(20, 25));

    for (int i = 0.0; i < solutions.size(); i++)
    {
        cout << "solution " << i + 1 << " : " << "dx/dt = " << solutions[i] << "\n";
    }


    //creating a text file to store the time and x values for plotting the differnet solutions
    ofstream file;
    file.open("HW2sols.txt", std::ios::app);
    file.close();

    //RUNGE-KUTTA FOR PLOTTING
    for (int j = 0.0; j < solutions.size(); j++)
    {
        double x22 = solutions[j]; //finding the solution for each dx/dt value we found


        int n = 1000;
        double h = 10.0 / double(n);     //STEP SIZE


        //RUNGE-KUTTA COEFFICIENTS 
        double k11 = 0.0, k22 = 0.0, k33 = 0.0, k44 = 0.0;
        double l11 = 0.0, l22 = 0.0, l33 = 0.0, l44 = 0.0;


        //INITIALISING VARIABLES
        double t1 = 0.0, x11 = 0.75;

       
        file.open("HW2sols.txt", std::ios::app);

        //RUNGE-KUTTA ALGORITHM
        for (int i = 0.0; i < n; i++)
        {
            k11 = h * a(t1, x11, x22);
            l11 = h * b(t1, x11, x22);


            k22 = h * a(t1 + (h / 2.0), x11 + (k11 / 2.0), x22 + (l11 / 2.0));
            l22 = h * b(t1 + (h / 2.0), x11 + (k11 / 2.0), x22 + (l11 / 2.0));

            k33 = h * a(t1 + (h / 2.0), x11 + (k22 / 2.0), x22 + (l22 / 2.0));
            l33 = h * b(t1 + (h / 2.0), x11 + (k22 / 2.0), x22 + (l22 / 2.0));

            k44 = h * a(t1 + h, x11 + k33, x22 + l33);
            l44 = h * b(t1 + h, x11 + k33, x22 + l33);


            t1 += h;
            x11 += (k11 + (2.0 * k22) + (2.0 * k33) + k44) * (1.0 / 6.0);
            x22 += (l11 + (2.0 * l22) + (2.0 * l33) + l44) * (1.0 / 6.0);

            
            //cout << t1 << " " << x11 << "\n";
            
            file << t1 << " " << x11 << "\n"; //adding the data to the text file



        }
        file.close();
        
        //cout << "NEW SOLUTION" << j+1 <<"\n"; //making it easier to read when a new solution begins in the output 
        
        //commented out the cout statements because it was clogging up the terminal 
    }
   
}
