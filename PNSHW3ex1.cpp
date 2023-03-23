#include <iostream> 
#include <cmath> 
#include <vector>
#include <iomanip>
#include <fstream>
using std::cout;

#include "headerhw3.h"


//SOR METHOD
void sor(double w, int n, double l, Field& phi)
{
	int m = 10 * n; //SCALING FACTOR

	//cout << "Grid size is " << phi.nx() << " x " << phi.ny() << "\n";

	for (int k = 0.0; k < l; k++)
	{
		for (int y = 1; y < m; y++)
		{
			for (int x = 1; x < m; x++)
			{

				phi(x, y) = (1 - w) * phi(x, y) + (w / 4.0) * (phi(x - 1, y) + phi(x, y - 1) + phi(x + 1, y) + phi(x, y + 1));


				//KEEP OBSTACLES CONSTANT
				//LINE 'B'
				if ((x == 8 * n) && (1 * n <= y && y <= 5 * n))
				{
					phi(x, y) = -1;
				}


				if ((6 * n <= x && x <= 8 * n) && (y == 5 * n))
				{
					phi(x, y) = -1;
				}

				//BOX 'A'
				if ((2 * n <= x && x <= 6 * n) && (y == 9 * n))
				{
					phi(x, y) = 1;
				}

				if ((2 * n <= x && x <= 6 * n) && (y == 7 * n))
				{
					phi(x, y) = 1;
				}

				if ((x == 2 * n) && (7 * n <= y && y <= 9 * n))
				{
					phi(x, y) = 1;
				}

				if ((x == 6 * n) && (7 * n <= y && y <= 9 * n))
				{
					phi(x, y) = 1;
				}

				//TOP AND RIGHT EDGE
				if ((y == 10 * n) && (0.0 <= x && x <= 10 * n))
				{
					phi(x, y) = x / double(m);
				}

				if ((x == 10 * n) && (0.0 <= y && y <= 10 * n))
				{
					phi(x, y) = y / double(m);
				}

				//LEFT AND BOTTOM EDGE
				if ((y == 0) && (0.0 <= x && x <= 10 * n))
				{
					phi(x, y) = 0.0;
				}

				if ((x == 0) && (0 <= y && y <= 10 * n))
				{
					phi(x, y) = 0.0;
				}

			}
		}
	}
	

}

int main()
{
	double o = 0.0; //RELAXATION PARAMETER
	double iterations = 0.0; //# ITERATIONS
	double sum = 0.0; //SUM OF ALL VALUES OF phi(x,y)
	std::vector<double> grid_dimension = {10, 50,100,200,500};

	//####UNCOMMENT COUT STATEMENTS FOR DATA####


	//!!COMMENTED OUT THIS BIT BELOW TO SAVE COMPUTATION TIME - I USED IT TO PLOT A GRAPH FOR TESTING!! 
	
	//COMPUTING SUM OF ALL VALUES OF FIELD AT EVERY POINT TO CHECK GLOBAL CONVERGENCE FOR DIFFERENT GRIDS
	/* for (int j = 0.0; j < grid_dimension.size(); j++)
	{
		int s = grid_dimension[j]; //GRID SIZE
		int scale = s / 10;
		Field phi(s, s); //sxs GRID 
		//cout << "Grid Dimension  " << s << "x" << s << " :" << "\n";
		for (int i = 0.0; i < 20; i++)
		{
			double sum = 0.0;
			iterations += 50;
			sor(o, scale, iterations, phi);
			for (int y = 1.0; y < s; y++) //leaving out edges because they stay constant, saves unecessary calculation.
			{
				for (int x = 1.0; x < s; x++)
				{
					sum += phi(x, y);
				}
			}

			//cout << std::setprecision(8) << "for " << iterations << " iterations sum = " << sum << "\n";
			//cout << iterations << " " << sum << "\n";
		}
		double sum = 0.0;
		iterations = 0.0;
	} */
	

	//TUNING RELAXATION PARAMETER
	for (int j = 0.0; j < 1; j++) //change range of j to adjust omega range
	{
		o += 0.1;
		//cout << "omega = " << o << " :" << "\n";
		
		
		for (int i = 0.0; i < 40; i++)
		{
			int s = 100;
			int scale = s / 10;
			Field phi(s, s);
			double sum = 0.0;
			iterations += 10;
			sor(o, 10, iterations, phi);
			for (int y = 1; y < s; y++) //leaving out edges because they stay constant, saves unecessary calculation.
			{
				for (int x = 1; x < s; x++)
				{
					sum += phi(x, y);
				}
			}

			//cout << std::setprecision(8) << "for " << iterations << " iterations sum = " << sum << "\n";
			//cout << sum << "\n";
		}
		
		sum = 0.0;
		iterations = 0.0;
	}
	

	////CONTOUR PLOT DATA
	Field phi(100, 100);
	sor(1.9, 10, 1000, phi);
	for (int y = 1; y < 100; y++) //leaving out edges because they stay constant, saves unecessary calculation.
	{
		for (int x = 1; x < 100; x++)
		{
			//cout << x/100.0 << " " << y/100.0 << " " << phi(x, y)<< "\n";
		}
	}

	//DERIVATIVE BY CENTRAL DIFFERENCE METHOD -  !!TAKES 2-3 MINUTES TO RUN ON MY SYSTEM!!
	for (int j = 0.0; j < grid_dimension.size(); j++)
	{
		int s = grid_dimension[j];
		Field phi(s,s);
		int scale = s / 10;
		sor(1.91, scale, 5000, phi);
		cout << s << " x " << s << " Grid : " << "dphi/dy = " << (phi(3 * scale, (5 * scale) + 1) - phi(3 * scale, (5 * scale) - 1)) / (2.0 / grid_dimension[j]) << "\n";
	}

}