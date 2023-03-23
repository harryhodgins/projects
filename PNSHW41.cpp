#include <iostream>
#include <cmath>
#include "Fieldhw4.h"
#include "rng.h"
using std::cout;


Ran r(4949939);

//FUNCTION TO FIND ACTION FOR A GIVEN SPIN AT POINT x,y
double action(Field<int>& phi, int x, int y, int spin)
{
	double action = 0.0;

	//COUNTING NUMBER OF FRUSTRATED BONDS
	if (spin != phi(x + 1, y)) 
	{
		action += 1; 
	}
	if (spin != phi(x, y + 1)) 
	{
		action += 1; 
	}
	if (spin != phi(x - 1, y)) 
	{ 
		action += 1; 
	}
	if (spin != phi(x, y - 1)) 
	{ 
		action += 1; 
	}

	return action;
}

//FUNCTION TO FIND MAGNETISATION EXPECTATION VALUE USING METROPOLIS ALGORITHM
double magnetisation(double q,double beta)
{
	Field<int> phi(20, 20); //CREATES 20X20 GRID
	Field<int> phi_old(20, 20);

	//INITIALISING VARIABLES
	
	//ACTION
	double action_old = 0.0;
	double action_new = 0.0;
	double d_action = 0.0;

	
	//COUNTING VARIABLES
	double count_1 = 0.0;
	double count_2 = 0.0;
	double count_3 = 0.0;
	double count_4 = 0.0;
	double count_5 = 0.0;

	
	double site_fraction = 0.0; //FRACTION OF SITES WITH A CERTAIN SPIN
	double m_frac = 0.0; //FRACTIONAL MAGNETISATION
	double m_expectation = 0.0; //EXPECTATION VALUE OF MAGNETISATION


	//CREATING INTIAL SPIN DISTRIBUTION FOR GRID
	for (int y = 0.0; y < 21; y++)
	{
		for (int x = 0.0; x < 21; x++)
		{
			phi_old(x, y) = int(r * q) + 1;
		}
	}


	//METROPOLIS ALGORITHM
	for (int k = 0; k < 3000; k++) //NUMBER OF ITERATIONS
	{
		for (int y = 0.0; y < 21; y++)
		{
			for (int x = 0.0; x < 21; x++)
			{
				//COMPUTE 'OLD' ACTION
				double sigma_old = phi_old(x, y);
				action_old = action(phi, x, y, sigma_old);


				//STEP 1 - PROPOSAL
				int sigma_new = int(r * q) + 1; //PROPOSED CANDIDATE
				phi(x, y) = sigma_new;


				//STEP 2 - ACCEPT/REJECT

				//CALCULATE ACCEPTANCE PROBABILITY - delta of the action is the difference in the action before and after the proposal
				
				//COMPUTE 'NEW' ACTION
				action_new = action(phi, x, y, sigma_new);

				d_action = action_new - action_old; //delta of the action


				//ACCEPTANCE PROBABILITY
				double p_acc = 0.0;
				if (exp(-1.0 * beta * d_action) < 1.0)
				{
					p_acc = exp(-1.0 * beta * d_action);
				}
				else
				{
					p_acc = 1.0;
				}


				//ACCEPT/REJECT PROPOSED CANDIDATE
				//generate a random number u in [0,1]
				double u = r;
				if (u <= p_acc)
				{
					phi(x, y) = sigma_new; //ACCEPT
					phi_old(x, y) = sigma_new;
				}
				else
				{
					phi(x, y) = phi_old(x, y); //REJECT
				}
			}

			//RESET ACTION
			action_new = 0.0;
			action_old = 0.0;
			d_action = 0.0;
		}

		//FINDING MOST FREQUENTLY OCCURING SPIN
		//we count how many times each spin value appears on the grid and find which count is the greatest

		site_fraction = 0.0;

		//HOW MANY TIMES DOES EACH SPIN VALUE APPEAR ON THE GRID
		for (int y = 0.0; y < 21; y++)
		{
			for (int x = 0.0; x < 21; x++)
			{
				if (phi_old(x, y) == 1.0)
				{
					count_1 += 1.0;
				}

				if (phi_old(x, y) == 2.0)
				{
					count_2 += 1.0;
				}

				if (phi_old(x, y) == 3.0)
				{
					count_3 += 1.0;
				}

				if (phi_old(x, y) == 4.0)
				{
					count_4 += 1.0;
				}

				if (phi_old(x, y) == 5.0)
				{
					count_5 += 1.0;
				}
			}
		}

		//WHICH COUNT IS THE GREATEST
		if ((count_1 > count_2) && (count_1 > count_3) && (count_1 > count_4) && (count_1 > count_5))
		{
			site_fraction = count_1 / double(400);
		}

		if ((count_2 > count_1) && (count_2 > count_3) && (count_2 > count_4) && (count_2 > count_5))
		{
			site_fraction = count_2 / double(400);
		}

		if ((count_3 > count_1) && (count_3 > count_2) && (count_3 > count_4) && (count_3 > count_5))
		{
			site_fraction = count_3 / double(400);
		}

		if ((count_4 > count_1) && (count_4 > count_2) && (count_4 > count_3) && (count_4 > count_5))
		{
			site_fraction = count_4 / double(400);
		}

		if ((count_5 > count_1) && (count_5 > count_2) && (count_5 > count_3) && (count_5 > count_4))
		{
			site_fraction = count_5 / double(400);
		}


		//CALCULATING FRACTIONAL MAGNETISATION
		
		m_frac += ((q * site_fraction) - 1) / (q - 1);


		//RESETTING COUNTS
		count_1 = 0, count_2 = 0, count_3 = 0, count_4 = 0, count_5 = 0;
	}
	
	//EXPECTATION VALUE
	m_expectation = m_frac / double(3000);


	cout << beta << " " << m_expectation << "\n";
	return 0;
}

int main()
{
	//3-STATE POTTS MODEL 
	for (int i = 50; i < 151; i++)
	{
		magnetisation(3, 0.01 * i);
	}

	//5-STATE POTTS MODEL
	for (int i = 50; i < 151; i++)
	{
		magnetisation(5, 0.01 * i);
	}
}