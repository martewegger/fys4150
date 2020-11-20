// Header file
// This is where we declare the class, its variables and functions/methods.

#ifndef ISING2D_HPP
#define ISING2D_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <random>

using namespace std;


class Ising2D{
private: //åpne for alle metoder INNI klassen.
    double m_T, m_k, m_J, m_beta, ran_nr, *m_energies, *m_magnetisation;
    int m_L, m_L2, m_M, m_E, m_dE, m_dM, m_E_mean, m_M_mean, m_E_mean_squared, m_M_mean_squared;
    int *m_spin_array, *m_idx; //Pointer to spin array and index array
    double m_Boltzmann[17]; //Look up table for Boltzmann distribution, extract probability through m_Boltzmann[dE+8]
    string m_filename;
    int idx(int i, int j); //indexer i E
    void init_spin_matrix(string initial_state);
    ofstream myfile;
    ofstream file2;

    //default_random_engine generator;
    mt19937_64 generator;
    uniform_real_distribution<double> uniform_dist;


public: //metoder jeg vil kalle på i main, utenfor klassen
    Ising2D(double T, int L, string initial_state);
    void Monte_Carlo(int MC, int n);
    int Write_to_file();
    void Metropolis_algo(int i, int j);
};
#endif
