#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>
#include <stdlib.h>

// single-valued constants
double g = 9.80665;                                                             // Gravitational acceleration at sea level              [m/s^2]
double M = 0.0289644;                                                           // Molar mass of earths air                             [kg/mol]
double Ru = 8.3144598;                                                          // Universal gas constant                               [J/(mol*K)]
double Rs = 287.058;                                                            // Specific gas constant                                [J/(kg*K)]

// multi-valued constants
double atm_temp;                                                                // Temperature at altitude                              [K]
double atm_pres_Pa;                                                             // Pressure at altitude                                 [Pa]
double atm_pres_rho;                                                            // Density at altitude                                  [kg/m^3]
double dyn_pres_Pa;                                                             // Dynamic pressure                                     [Pa]

// Atmospheric Subscripts
double P[7] = { 101325,22632.10,5474.89,868.02,110.91,66.94,3.96 };             // Static pressure at bottom of atmospheric layer       [Pa]
double T[7] = { 288.15,216.65,216.65,228.65,270.65,270.65,214.65 };             // Standard temperature at bottom of atmospheric layer  [K]
double L[7] = { -0.0065,0,0.001,0.0028,0,-0.0028,-0.002 };                      // Standard temperature lapse rate                      [K/m]
double h[7] = { 0,11000,20000,32000,47000,51000,71000 };                        // Altitude at bottom of atmospheric layer              [m]

struct Timer;
double atm_pres_model(double alt);
double atm_temp_model(double alt);
double dyn_pres_model(double vel, double alt);
void read_csv(std::string Input_file);
void write_csv(std::string Output_file);