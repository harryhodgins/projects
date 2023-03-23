#include <iostream> 
#include <cmath> 
#include <vector>
#include <iomanip>
#include <fstream>
using std::cout;

class Planet
{
  private:
    double m_;
  public: //parameters 
    double pos[2];
    double vel[2];
    double acc[2];  

// Constructor
    Planet(double m, double x0, double x1, double v0, double v1,double a0,double a1)
    {
      m_ = m;
      pos[0] = x0; pos[1] = x1; 
      vel[0] = v0; vel[1] = v1; 
      acc[0] = a0; acc[1] = a1;
    }
    double mass() const { return m_; } 
};

//INGREDIENTS FOR LEAP-FROG INTEGRATOR

//STEP 1 : UPDATE POSITION AT TIME t
void update_position(double h, Planet& p)
{
  for (int a=0;a<2;a++) p.pos[a] += h * p.vel[a]; 
}

void update_position(double h, std::vector<Planet>& solar_system)
{
  int n=solar_system.size(); 
  for (int i=0;i<n;i++) update_position(h, solar_system[i]);
}

//STEP 2 : CALCULATE ACCELERATION AND UPDATE VELOCITY

//make a function which takes two planets as inputs, calculates the force between the two planets.


void acc(Planet& p1, Planet& p2) 
{
    //angle between planets
    double theta = atan2((p2.pos[1] - p1.pos[1]) , (p2.pos[0] - p1.pos[0])); 

    //Newton's law of gravitation
    double f = (p1.mass() * p2.mass()) /((p2.pos[0] - p1.pos[0]) * (p2.pos[0] - p1.pos[0]) + (p2.pos[1] - p1.pos[1]) * (p2.pos[1] - p1.pos[1]));

    //acceleration from F = ma, we use += to get the RESULTANT accleration due to the 3 other planets 
    p1.acc[0] += (f * cos(theta)) / p1.mass();
    p1.acc[1] += (f * sin(theta)) / p1.mass();
    
    p2.acc[0] += -(f * cos(theta)) / p2.mass(); //the second planet experiences an acceleration in the OPPOSITE direction
    p2.acc[1] += -(f * sin(theta)) / p2.mass();
}

//UPDATE VELOCITY
void update_velocity(double h, Planet& p)
{
    for (int a = 0.0; a < 2; a ++) p.vel[a] += h * p.acc[a];
}


int main()
{
 //CREATING PLANETS
  std::vector<Planet> my_solar_system; 

  my_solar_system.push_back(Planet(2.2,-0.50,0.10,-0.84,0.65,0.0,0.0)) ;
  my_solar_system.push_back(Planet(0.8,-0.60,-0.20,1.86,0.70,0.0,0.0)) ;
  my_solar_system.push_back(Planet(0.9,0.50,0.10,-0.44,-1.50,0.0,0.0)) ;
  my_solar_system.push_back(Planet(0.4, 0.50, 0.40, 1.15, -1.60,0.0,0.0));
  

  int n = 100000;
  double h = 5.0 / double(n); //STEP-SIZE
  double t = 0.0;

  //LEAP FROG INTEGRATOR
  for (int i = 0.0; i < n; i++)
  {
      for (int j = 0.0; j < my_solar_system.size(); j++) //STEP 1 - UPDATE POSITION
      {
          update_position((h/2.0), my_solar_system[j]);
      }

      //CALCULATE ACCELERATION between each pair of planets
      acc(my_solar_system[0], my_solar_system[1]);
      acc(my_solar_system[0], my_solar_system[2]);
      acc(my_solar_system[0], my_solar_system[3]);
      acc(my_solar_system[1], my_solar_system[2]);
      acc(my_solar_system[1], my_solar_system[3]);
      acc(my_solar_system[2], my_solar_system[3]);

      

      for (int k = 0.0; k < my_solar_system.size(); k++) //STEP 2 - UPDATE VELOCITY
      {
          update_velocity(h, my_solar_system[k]);
      }

      for (int m = 0.0; m < my_solar_system.size(); m++) //STEP 3 - UPDATE POSITION AGAIN
      {
          update_position((h/2.0), my_solar_system[m]);
      } 

      t += h;
      //RESET ACCELERATION 
      for (int l = 0.0; l < my_solar_system.size(); l++) 
      {
          my_solar_system[l].acc[0] = 0.0;
          my_solar_system[l].acc[1] = 0.0;
      }

  }

  //OUTPUTTING POSITIONS AT t = 5 
  for (int i = 0.0; i < my_solar_system.size(); i++) 
  {
      cout << std::setprecision(3) << "Planet " << i + 1 << " has position" << " x0 = " << my_solar_system[i].pos[0] << " ," << " x1 = " << my_solar_system[i].pos[1] << "\n";
  }
   
}