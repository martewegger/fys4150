// class file
// This is where all functions are specified.

#include "Ising2D.hpp"
using namespace std;


// Function initializing variables, initializeren min
Ising2D::Ising2D(double T, int L, string initial_state){
  m_E = 0;
  m_dE = 0;
  m_M = 0; //ønsker vi å fylle opp etterpå, heltall, kan bare være -1 eller 1
  m_dM = 0;
  m_E_mean = 0;
  m_M_mean = 0;
  m_E_mean_squared = 0;
  m_M_mean_squared = 0;
  m_L = L; //om jeg har flere dimensjoner
  m_L2 = L*L; //lemngde av spin array
  m_spin_array = new int[m_L2]; //int av strl dim, hvdrt element, så lang
  m_idx = new int[m_L+2];
  init_spin_matrix(initial_state);
  m_T = T;
  m_beta = 1./m_T;
  for (int i=-8; i<=8; i+=4){ //da hopper den med steg på 4
    m_Boltzmann[i+8] = exp(i*(-m_beta)); //boltzmann faktorene mine
  }
}



//Initialize spin matrix:
void Ising2D::init_spin_matrix(string initial_state){
  int index;
  if (initial_state!="random"){ //ha ordered, at alle begynner spin up
    for (int i=0; i<m_L2; i++){
      m_spin_array[i] = 1; //printer tydeligvis adressen når jeg bare printer m_spin_array
      m_M += m_spin_array[i]; //da er jo summen av alle lik alle som peker opp
    }
  }

  if (initial_state=="random"){ //ha uordered,random spin opp og ned
    uniform_int_distribution<int> RandomNumberGenerator(0,1);
    for (int i=0; i<m_L2; i++){
      ran_nr = RandomNumberGenerator(generator);
      m_spin_array[i] = 2*ran_nr -1;
      m_M += m_spin_array[i]; //blir altså pluss eller minus 1, oppdaterer M
    }
  }

  //then we calculate the initial energy:
  for (int i=1; i<=m_L; i++){ //skal denne gå fra 1 til L
    m_idx[i] = i-1; //finding index
  }
  m_idx[0] = m_idx[m_L];
  m_idx[m_L+2] = m_idx[1];

  for (int i=1; i<=m_L; i++){
    for (int j=1; j<=m_L; j++){
      m_E -= m_spin_array[ m_idx[i]*m_L + m_idx[j] ] * (m_spin_array[m_idx[i]*m_L + m_idx[j+1]] + m_spin_array[m_idx[i+1]*m_L + m_idx[j]]);
    }
  }

}

void Ising2D::Monte_Carlo(int MC, int n){  //n er number of spins?
  uniform_int_distribution<int> int_dist(1, m_L);

  int x, y;
  //Burn in period
  for (int i = 0; i < n; i++){
    x = int_dist(generator);
    y = int_dist(generator);
    Metropolis_algo(x, y);
  }


  m_energies = new double[MC];
  m_magnetisation = new double[MC];
  for (int i = 0; i < MC; i++){
    x = int_dist(generator);
    y = int_dist(generator);
    Metropolis_algo(x, y);
    m_energies[i] = m_E;
    m_magnetisation[i] = abs(m_M);
    //m_E_mean += m_E;
    //m_M_mean += m_M;
    //m_E_mean_squared += m_E*m_E;
    //m_M_mean_squared += m_M*m_M;
  }

  //m_E_mean *= (1./MC); //her finner vi mean verdi til E, <E>
  //m_M_mean *= (1./MC); //her finner vi mean verdi til M, <M>
  //m_E_mean_squared *= (1./MC); //<E^2>
  //m_M_mean_squared *= (1./MC); //<M^2>

  //file2.open("data.txt");
  //file2 << setw(15) << setprecision(8) << m_E_mean;
  //ile2 << setw(15) << setprecision(8) <<  m_M_mean;
  //file2 << setw(15) << setprecision(8) <<  m_E_mean_squared;
  //file2 << setw(15) << setprecision(8) <<  m_M_mean_squared;

  //cout << m_M_mean << endl;

  //Write energies to file here
  //writing to file:
  file2.open("magnetisation.txt");
  myfile.open("Energy.txt");
  for (int i = 0; i < MC; i++){
    myfile << m_energies[i] << endl;
    file2 << m_magnetisation[i]<< endl;
  }
  myfile.close();
  file2.close();

  delete[] m_energies; //slette den her etterpå, trenger den ikke, tar bare opp minne.
  delete[] m_magnetisation;

}



//finding burn-in period
void Ising2D::Metropolis_algo(int i, int j){ //de jeg vil sende inn, sample i,j{1,...,L}
  m_dE = 2*m_spin_array[m_idx[i]*m_L + m_idx[j]]*( m_spin_array[m_idx[i+1]*m_L + m_idx[j]] + m_spin_array[m_idx[i-1]*m_L + m_idx[j]] + m_spin_array[m_idx[i]*m_L + m_idx[j+1]] + m_spin_array[m_idx[i]*m_L + m_idx[j-1]]);

  if(m_dE < 0){ //accept flip
    m_spin_array[m_idx[i]*m_L + m_idx[j]] *= (-1);
    m_dM = 2*m_spin_array[m_idx[i]*m_L + m_idx[j]];
  }
  else if(uniform_dist(generator) < m_Boltzmann[m_dE+8]){ //accept flip
    m_spin_array[m_idx[i]*m_L + m_idx[j]] *= (-1);
    m_dM = 2*m_spin_array[m_idx[i]*m_L + m_idx[j]];
  }
  else{ //reject flip
    m_dE = 0;
    m_dM = 0;
  }
  m_E += m_dE;
  m_M += m_dM;


}






  //Etter skrevet til fil, så kan vi plotte og finne min?? Finne der den er stabil, i termisk likevekt.?
  //Så hente den verdien og kalle den N_burn. Men hva er det som gjør at den er N_burn


  //Må vel skrive disse her til en fil så jeg får plotta?
  //Så jeg kan finne N_burn
