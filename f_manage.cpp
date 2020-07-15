#include "Header.h"

std::vector<double> alt;		                                                // Altitude        [m]
std::vector<double> vel;                                                        // Velocity        [m/s]

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