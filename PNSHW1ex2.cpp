#include <iostream> 
#include <cmath> 
#include <vector>
#include <iomanip>
using std::cout;

//EXERCISE 2
    

//SYSTEM OF FIRST ORDER ODEs

double a(double x, double y1, double y2, double y3)
{
	return y2;
} 

double b(double x, double y1, double y2, double y3)
{
	return y3;
}

double c(double x, double y1 , double y2, double y3) 
{
	return   -(0.3) * x * (y1 * y1 * y1) - 5.0 * y2;
}
 
int main()
{
    int n = 30000;
    double h = 30.0 / double (n);     //STEP SIZE


    //RUNGE-KUTTA COEFFICIENTS 
    double k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0; 
    double l1 = 0.0, l2 = 0.0, l3 = 0.0, l4 = 0.0;
    double m1 = 0.0, m2 = 0.0, m3 = 0.0, m4 = 0.0;


    //INITIAL CONDITIONS 
    double y1 = 1.0, y2 =0.0 , y3=0.0 , x = 0.0;


    //RUNGE-KUTTA ALGORITHM
    for (int i = 0.0; i < n; i++)
    {
        k1 = h * a(x, y1, y2, y3); //Same as ex1 but order matters, need to keep the order ki , li , mi.
        l1 = h * b(x, y1, y2, y3);
        m1 = h * c(x, y1, y2, y3);

        k2 = h * a(x + (h / 2.0), y1 + (k1 / 2.0) , y2 + (l1 / 2.0), y3 + (m1 / 2.0));
        l2 = h * b(x + (h / 2.0), y1 + (k1 / 2.0), y2 + (l1 / 2.0), y3 + (m1 / 2.0));
        m2 = h * c(x + (h / 2.0), y1 + (k1 / 2.0), y2 + (l1 / 2.0) , y3 + (m1 / 2.0));

        k3 = h * a(x + (h / 2.0), y1 + (k2 / 2.0), y2 + (l2 / 2.0), y3 + (m2 / 2.0));
        l3 = h * b(x + (h / 2.0), y1 + (k2 / 2.0), y2 + (l2 / 2.0), y3 + (m2 / 2.0));
        m3 = h * c(x + (h / 2.0), y1 + (k2 / 2.0), y2 + (l2 / 2.0), y3 + (m2 / 2.0));

        k4 = h * a(x + h, y1 + k3, y2 + l3, y3 + m3);
        l4 = h * b(x + h, y1 + k3, y2 + l3, y3 + m3);
        m4 = h * c(x + h, y1 + k3, y2 + l3, y3 + m3);


        x  +=  h;
        y1 += (k1 + (2.0 * k2) + (2.0 * k3) + k4) * (1.0 / 6.0);
        y2 += (l1 + (2.0 * l2) + (2.0 * l3) + l4) * (1.0 / 6.0);
        y3 += (m1 + (2.0 * m2) + (2.0 * m3) + m4) * (1.0 / 6.0);

    }

    cout << "The solution is y(30) = " << y1 << " for step size h = " << h << "\n";
    return 0;
}