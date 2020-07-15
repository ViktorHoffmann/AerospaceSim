#pragma once

#ifndef HEADER_H_
#define HEADER_H_

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <stdlib.h>


struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer() :start(), end(), duration()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "timing: " << ms << " ms\n";
	}
};

double atm_pres_model(double alt);
double atm_temp_model(double alt);
double dyn_pres_model(double vel, double alt);
void read_csv(std::string Input_file);
void write_csv(std::string Output_file);

#endif // !HEADER_H_