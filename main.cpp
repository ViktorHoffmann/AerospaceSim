/*
main
*/
#include "Header.h"

int main() {
	// TODO Multithreading

	std::string Output_file = "aerodynamics.csv";
	std::string Input_file = "ascend_pattern.csv";

	read_csv(Input_file);
	write_csv(Output_file);

	system("pause");
	return 0;
}