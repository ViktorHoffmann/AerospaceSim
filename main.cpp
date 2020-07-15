/*
This file is the aerodynamics simulation
which takes the ascend pattern input as a .csv
and outputs the simulation results into another .csv
*/
#include "Header.h"

// single-valued constants
double g = 9.80665;                                                             // Gravitational acceleration at sea level              [m/s^2]
double M = 0.0289644;                                                           // Molar mass of earths air                             [kg/mol]
double Ru = 8.3144598;                                                          // Universal gas constant                               [J/(mol*K)]
double Rs = 287.058;                                                            // Specific gas constant                                [J/(kg*K)]

// multi-valued constants
double P[7] = { 101325,22632.10,5474.89,868.02,110.91,66.94,3.96 };             // Static pressure at bottom of atmospheric layer       [Pa]
double T[7] = { 288.15,216.65,216.65,228.65,270.65,270.65,214.65 };             // Standard temperature at bottom of atmospheric layer  [K]
double L[7] = { -0.0065,0,0.001,0.0028,0,-0.0028,-0.002 };                      // Standard temperature lapse rate                      [K/m]
double h[7] = { 0,11000,20000,32000,47000,51000,71000 };                        // Altitude at bottom of atmospheric layer              [m]

std::vector<double> alt;		                                                // Altitude        [m]
std::vector<double> vel;                                                        // Velocity        [m/s]

double atm_pres_model(double alt) {
	// Using barometric formula,
	// this absolute atmospheric pressure model
	// returns pressure and density approximation in
	// pascal and rho for given altitude.

	double atm_pres; //Pa
	if (alt >= h[0] && alt < h[1])
	{
		int i = 0;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[1] && alt < h[2])
	{
		// Temperature lapse rate is zero
		int i = 1;
		return atm_pres = P[i] * exp((((g * (-1)) * M * (alt - h[i])) / (Ru * T[i])));
	}
	if (alt >= h[2] && alt < h[3])
	{
		int i = 2;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[3] && alt < h[4])
	{
		int i = 3;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[4] && alt < h[5])
	{
		// Temperature lapse rate is zero
		int i = 4;
		return atm_pres = P[i] * exp((((g * (-1)) * M * (alt - h[i])) / (Ru * T[i])));
	}
	if (alt >= h[5] && alt < h[6])
	{
		int i = 5;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[6])
	{
		int i = 6;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	else if (alt < h[0])
	{
		std::cout << "Altitude must be positive\n";
		return 0;
	}
	else
	{
		std::cout << "error\n";
		return 0;
	}
}

double atm_temp_model(double alt) {
	// The function uses the Standard temperature
	// and temperature lapse rate to model the
	// absolute atmospheric temperature as linear functions

	double atm_temp; //K
	if (alt >= h[0] && alt < h[1])
	{
		int i = 0;
		return atm_temp = T[i] + (alt * L[i]);
	}
	if (alt >= h[1] && alt < h[2])
	{
		int i = 1;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[2] && alt < h[3])
	{
		int i = 2;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[3] && alt < h[4])
	{
		int i = 3;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[4] && alt < h[5])
	{
		int i = 4;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[5] && alt < h[6])
	{
		int i = 5;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[6])
	{
		int i = 6;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	else if (alt < h[0])
	{
		std::cout << "Altitude must be positive\n";
	}
	else
	{
		std::cout << "error\n";
		return 0;
	}
}

double atm_dens_model(double alt) {
	// Calculation of atmospheric density

	double atm_dens; //rho
	return atm_dens = (atm_pres_model(alt) / (Rs * atm_temp_model(alt)));
}

double dyn_pres_model(double vel, double alt) {
	// This function calculates the dynamic pressure
	// with velocity and atmospheric density

	double dyn_pres; //Pa
	return dyn_pres = ((atm_dens_model(alt) * pow(vel, 2)) / 2);
}

void read_csv(std::string Input_file) {
	// This function anticipates
	// that the input csv only has two columns
	// which is the standard and iterates the input csv
	// to parse the data into two strings.

	Timer timer;
	std::cout << "Reading csv...\n";

	std::ifstream Infile;
	Infile.open("ascend_pattern.csv");

	int i = 0; int j = 0;
	while (Infile.good()) {
		std::string line;
		// Read whole line
		while (getline(Infile, line))
		{
			std::istringstream iline(line);
			// Seperate line by the delimiter
			while (getline(iline, line, ';'))
			{
				if (j == 1)
				{
					// Column 2: velocity
					vel.push_back(strtod(line.c_str(), NULL));
					i++; j--;
				}
				else if (j == 0)
				{
					// Column 1: altitude
					alt.push_back(strtod(line.c_str(), NULL));
					i++; j++;
				}
			}
		}
	}
	std::cout << (alt.size() * (vel.size() <= alt.size()) + (vel.size() * (vel.size() > alt.size()))) << " elements parsed\n";

	std::cout << "Reading done\n";
}

void write_csv(std::string Output_file) {
	// This function runs the simulation loop
	// and parses the solutions to the output .csv file.

	Timer timer;
	std::cout << "Printing to csv...\n";

	std::ofstream Outfile;
	Outfile.open(Output_file);

	Outfile << "Altitude [m]" << ";" << "Velocity [m/s]" << ";" << "Temperature [K]"
		<< ";" << "Static Pressure [Pa]" << ";" << "Static Density [kg/m^3]" << ";" << "Dynamic Pressure [Pa]" << "\n";

	//Simulation loop
	for (int i = 0; i < (alt.size() * (vel.size() <= alt.size()) + (vel.size() * (vel.size() > alt.size()))); i++)
	{
		Outfile << alt[i] << ";" << vel[i] << ";" << atm_temp_model(alt[i]) << ";" << atm_pres_model(alt[i]) << ";" << atm_dens_model(alt[i]) << ";" << dyn_pres_model(vel[i], alt[i]) << "\n";
	}
	Outfile.close();

	std::cout << "Printing done\n";
}

int main() {
	std::string Output_file = "aerodynamics.csv";
	std::string Input_file = "ascend_pattern.csv";

	read_csv(Input_file);
	write_csv(Output_file);

	system("pause");
	return 0;
}