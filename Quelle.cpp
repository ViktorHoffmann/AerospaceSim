/*
This file is the aerodynamics simulation
which takes the ascend pattern input as a .csv
and outputs the simulation results into another .csv
*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

// single-valued constants
double g = 9.80665;                                                             // Gravitational acceleration at sea level              [m/s^2]
double M = 0.0289644;                                                           // Molar mass of earths air                             [kg/mol]
double Ru = 8.3144598;                                                          // Universal gas constant                               [J/(mol*K)]
double Rs = 287.058;                                                            // Specific gas constant                                [J/(kg*K)]

// multi-valued constants
double alt;                                                                     // Altitude                                             [m]
double vel;                                                                     // Velocity                                             [m/s]
double atm_temp;                                                                // Temperature at altitude                              [K]
double atm_pres_Pa;                                                             // Pressure at altitude                                 [Pa]
double atm_pres_rho;                                                            // Density at altitude                                  [kg/m^3]
double dyn_pres_Pa;                                                             // Dynamic pressure                                     [Pa]

double P[7] = { 101325,22632.10,5474.89,868.02,110.91,66.94,3.96 };             // Static pressure at bottom of atmospheric layer       [Pa]
double T[7] = { 288.15,216.65,216.65,228.65,270.65,270.65,214.65 };             // Standard temperature at bottom of atmospheric layer  [K]
double L[7] = { -0.0065,0,0.001,0.0028,0,-0.0028,-0.002 };                      // Standard temperature lapse rate                      [K/m]
double h[7] = { 0,11000,20000,32000,47000,51000,71000 };                        // Altitude at bottom of atmospheric layer              [m]

double atm_pres_model(double alt) {
	// Using barometric formula,
	// this absolute atmospheric pressure model
	// returns pressure and density approximation in
	// pascal and rho for given altitude.

	if (alt >= h[0] && alt < h[1])
	{
		int i = 0;
		return atm_pres_Pa = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[1] && alt < h[2])
	{
		// Temperature lapse rate is zero
		int i = 1;
		return atm_pres_Pa = P[i] * exp((((g * (-1)) * M * (alt - h[i])) / (Ru * T[i])));
	}
	if (alt >= h[2] && alt < h[3])
	{
		int i = 2;
		return atm_pres_Pa = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[3] && alt < h[4])
	{
		int i = 3;
		return atm_pres_Pa = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[4] && alt < h[5])
	{
		// Temperature lapse rate is zero
		int i = 4;
		return atm_pres_Pa = P[i] * exp((((g * (-1)) * M * (alt - h[i])) / (Ru * T[i])));
	}
	if (alt >= h[5] && alt < h[6])
	{
		int i = 5;
		return atm_pres_Pa = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[6])
	{
		int i = 6;
		return atm_pres_Pa = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	else if (alt < h[0])
	{
		std::cout << "Altitude must be positive\n";
		return 0;
	}
}

double atm_temp_model(double alt) {
	// The function uses the Standard temperature
	// and temperature lapse rate to model the
	// absolute atmospheric temperature as linear functions

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
		return 0;
	}
}

double dyn_pres_model(double vel, double alt) {
	// This function calculates the dynamic pressure
	// with velocity, atmospheric density and the
	// atmospheric temperature model.

	atm_pres_rho = atm_pres_model(alt) / (Rs * atm_temp_model(alt));
	dyn_pres_Pa = ((atm_pres_rho * pow(vel, 2)) / 2);
	return dyn_pres_Pa;
}

void read_csv(std::string Input_file) {
	std::stringstream ifile(Input_file);
	std::string line;
	while (std::getline(ifile, line)) // read the current line
	{
		std::istringstream iss{ line }; // construct a string stream from line

		// read the tokens from current line separated by semiiicoLOOOON
		std::vector<std::string> tokens; // here we store the tokens
		std::string token; // current token
		while (std::getline(iss, token, ';'))
		{
			tokens.push_back(token); // add the token to the vector
		}

		// we can now process the tokens
		// first display them
		std::cout << "Tokenized line: ";
		for (const auto& elem : tokens)
			std::cout << "[" << elem << "]";
		std::cout << std::endl;

		// map the tokens into our variables, this applies to your scenario
		std::string name = tokens[0]; // first is a string, no need for further processing
		int age = std::stoi(tokens[1]); // second is an int, convert it
		int height = std::stoi(tokens[2]); // same for third
		std::cout << "Processed tokens: " << std::endl;
		std::cout << "\t Name: " << name << std::endl;
		std::cout << "\t Age: " << age << std::endl;
		std::cout << "\t Height: " << height << std::endl;
	}
}

void write_csv(std::string Output_file) {
	std::cout << "Printing to csv...\n";
	std::ofstream Outfile;
	Outfile.open(Output_file);
	Outfile << "Altitude [m]" << ";" << "Velocity [m/s]" << ";" << "Temperature [K]"
		<< ";" << "Static Pressure [Pa]" << ";" << "Static Density [kg/m^3]" << ";" << "Dynamic Pressure [Pa]" << "\n";

	//Simulation Loop
	for (alt = 0, vel = 0; alt < 100000 && vel < 100000; alt++, vel++)
	{
		Outfile << alt << ";" << vel << ";" << atm_temp
			<< ";" << atm_pres_model(alt) << ";" << atm_pres_rho << ";" << dyn_pres_model(vel, alt) << "\n";
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