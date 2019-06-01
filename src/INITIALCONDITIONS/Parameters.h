// Parameters.h is adapted from the IP-Glasma solver.
// Copyright (C) 2018 Bjoern Schenke.
// Reproduced with permission by Mark Mace 2019 for Dilute-Dense gluon solver

#ifndef Parameters_H
#define Parameters_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class Parameters
{
    private:
    // switches:
    int initMethod;
    
    double myPI;
    double myhbarc;
    
    int A;       // number of nucleons;
    int locNc;      // number of colors (SU(Nc))
    int size;    // the length of the lattice (make it 2^n, with n integer)
    int runningCoupling; // switch to decide if alpha_s should run (0 constant alpha_s, 1 running coupling)
    double R;
    int useTimeForSeed; // decide if the system time should be used to generate a seed (1) or not (0)
    int useSeedList; // read random seeds from a file if set to (1) - this overwrites the 'use time for seed' setting
    unsigned long long int seed;    // random seed that's added to the current time to generate the full seed (or the full seed, depending on the value of getUseTimeforSeed())
    double g2mu; // g^2 mu
    double Qs;   // Q_s, to be dynamically determined
    int runWithQs; // set whether alpha_s should run with the maximum(2), average (1) or minimum(0) of Q_s from nucleus A and B
    int runWithkt; // set whether alpha_s should run kt (1) or not (0) - if this is set it overwrites any running with Q_s
    int runWithLocalQs; // set whether alpha_s should run with the local Q_s from nucleus A and B (1) or the average (0), both use settings from runWithQs
    double runWithThisFactorTimesQs; // set the factor in front of Q_s under the log in alpha_s
    double mu0;  // cutoff to avoid the Landau pole in the 1-loop running coupling expression
    double g; // coupling g needed in the initU3 where g^2mu does not scale out
    double Jacobianm; // mass term in GeV in the Jacobian going from y to eta
    double QsmuRatio; // ratio between Qs and mu: Q_s = QsmuRatio * g^2 mu for nucleus A
    double QsmuRatioB; // ratio between Qs and mu: Q_s = QsmuRatio * g^2 mu for nucleus B
    double rapidity; // rapidity to use when getting Q_s from IPSat. Basically to pick x for now
    int usePseudoRapidity; // if selected (1) the variable 'rapidity' will contain the pseudorapidity and the right conversion will be done (incl. Jacobian)
    double averageQs; // the average Q_s (maximum of nucleus A and B) used as scale for running coupling
    double averageQsAvg; // the average Q_s (average of nucleus A and B) used as scale for running coupling
    double averageQsmin; // the average Q_s (minimum of nucleus A and B) used as scale for running coupling
    double alphas; // the alpha_s computed at the scale given by the average Q_s
    double xExponent; // - exponent with which Q_s grows with x (usually 0.31 in IP-Sat for nuclei)
    unsigned long long int randomSeed; // stores the random seed used (so the event can be reproduced)
    string NucleusQsTableFileName; // the file name for the table containing Qs^2 as a function of Y and Qs^2(Y=0)
    double BG; // the width of the Gaussian describing the shape of the proton in GeV^(-2)
    double BGq; // the width of the Gaussian describing the shape of a constituent quark in GeV^(-2)
    double muZero; // mu_0 in the running coupling (makes it infrared finite)
    double c; // determines how smooth the cutoff in the running coupling is
    double roots; // square root of s: center of mass energy of the collision in GeV
    int useFluctuatingx; // switch to determine if the rapidity value in the input file should always be used (0) or if x should fluctuate as the local Q_s
    // x = Q_s*beta/roots (1). the value of roots is only used when this is set to 1.
    double xFromThisFactorTimesQs; // set the factor beta in x = Q_s*beta/roots
    double Tpp; // This is the convolution of two T_p's to be used in the weight for different impact parameters
    // T_pp (b_T) = \sum \delta^2 x_T T_p(x_T) T_p(x_T-b_T)
    //Glauber parameters:
    double SigmaNN;   // nucleon-nucleon cross section
    double b;         // impact parameter
    double bmin;      // minimum impact parameter to sample from
    double bmax;      // maximum impact parameter to sample to
    int linearb;      // sample b from a linear distribution if 1, uniform distribution otherwise
    string Target;    // target nucleus' name
    string Projectile;// projectile nucleus' name
    double L;         // lattice size in fm
    int useNucleus;   // use nuclei (1) or a constant g^2mu distribution over the lattice (0) or constant g^2mu target (2)
    int Npart;        // Number of participants
    int averageOverNuclei; // average over this many nuclei to get a smooth(er) distribution
    int nucleonPositionsFromFile; // switch to determine whether to sample nucleon positions (0) or read them from a file (1)
    int A1FromFile;    // if nuclei are read from file, store A value here
    int A2FromFile;    // if nuclei are read from file, store A value here
    int useFixedNpart; // if 0 do not demand a given N_part, if >1 sample the initial configuration until the given N_part is reached
    double rnp;        // distance between proton and neutron in the transverse projection of the deuteron
    int smearQs;       // decide whether to smear Q_s using a Poisson distribution around its mean at every x_T (1) or not (0)
    double smearingWidth; // width of the Gaussian smearing around the mean g^2mu^2
    int gaussianWounding; // use hard sphere profile (0) or Gaussian cross section (1) to determine whether a nucleon is wounded
    //int MPIrank; // MPI rank
    //int MPIsize; // MPI number of cores
    int success; // no collision happened (0) or collision happened (1) - used to restart if there was no collision
    double rmax; // radius at which we cut distribution for each nucleon (in fm)
    double protonAnisotropy; //anisotropy of the proton thickness function: xi in Exp[-(x^2 + xi y^2)/2/B]/2/Pi/B Sqrt[xi] - as a first test
    int useConstituentQuarkProton; // if 1 use a proton made up of 3 constituent quarks.
    
    public:
    
    // constructor:
    Parameters()
    {
        setPi(3.141592654);       //pi
        sethbarc(0.1973269631);   //hbar c in GeV*fm
    }
    
    // functions to access the private variables:
    void setPi(double x){myPI=x;}
    double getPi(){return myPI;}
    void sethbarc(double x){myhbarc=x;}
    double gethbarc(){return myhbarc;}
    void setSeed(unsigned long long int x) {seed=x;}
    unsigned long long int getSeed() {return seed;}
    void setA(int x) {A=x;}
    int getA() {return A;}
    void setNc(int x) {locNc=x;}
    int getNc() {return locNc;}
    void setSize(int x) {size=x;}
    int getSize() {return size;}
    void setProtonAnisotropy(double x) {protonAnisotropy=x;}
    double getProtonAnisotropy() {return protonAnisotropy;}
    
    void setAverageOverNuclei(int x) {averageOverNuclei=x;}
    int getAverageOverNuclei() {return averageOverNuclei;}
    void setR(double x) {R=x;}
    double getR() {return R;}
    void setg2mu(double x) {g2mu=x;}
    double getg2mu() {return g2mu;}
    void setQs(double x) {Qs=x;}
    double getQs() {return Qs;}
    void setRunningCoupling(int x) {runningCoupling=x;};
    int getRunningCoupling() {return runningCoupling;}
    void setMu0(double x) {mu0=x;}
    double getMu0() {return mu0;}
    void setg(double x) {g=x;}
    double getg() {return g;}
    void setSigmaNN(double x) {SigmaNN=x;}
    double getSigmaNN() {return SigmaNN;}
    void setb(double x) {b=x;}
    double getb() {return b;}
    void setbmin(double x) {bmin=x;}
    double getbmin() {return bmin;}
    void setbmax(double x) {bmax=x;}
    double getbmax() {return bmax;}
    void setTarget(string x){Target=x;}
    string getTarget(){return Target;}
    void setProjectile(string x){Projectile=x;}
    string getProjectile(){return Projectile;}
    void setL(double x) {L=x;}
    double getL() {return L;}
    void setJacobianm(double x) {Jacobianm=x;}
    double getJacobianm() {return Jacobianm;}
    void setQsmuRatio(double x) {QsmuRatio=x;}
    double getQsmuRatio() {return QsmuRatio;}
    void setQsmuRatioB(double x) {QsmuRatioB=x;}
    double getQsmuRatioB() {return QsmuRatioB;}
    void setRapidity(double x) {rapidity=x;}
    double getRapidity() {return rapidity;}
    void setNpart(int x) {Npart=x;};
    int getNpart() {return Npart;}
    void setAverageQs(double x) {averageQs=x;}
    double getAverageQs() {return averageQs;}
    void setAverageQsAvg(double x) {averageQsAvg=x;}
    double getAverageQsAvg() {return averageQsAvg;}
    void setAverageQsmin(double x) {averageQsmin=x;}
    double getAverageQsmin() {return averageQsmin;}
    void setalphas(double x) {alphas=x;}
    double getalphas() {return alphas;}
    void setxExponent(double x) {xExponent=x;}
    double getxExponent() {return xExponent;}
    void setRandomSeed(unsigned long long int x) {randomSeed=x;};
    unsigned long long int getRandomSeed() {return randomSeed;}
    void setUseTimeForSeed(int x) {useTimeForSeed=x;};
    int getUseTimeForSeed() {return useTimeForSeed;}
    void setUseSeedList(int x) {useSeedList=x;};
    int getUseSeedList() {return useSeedList;}
    void setNucleusQsTableFileName(string x){NucleusQsTableFileName=x;}
    string getNucleusQsTableFileName(){return NucleusQsTableFileName;}
    void setA1FromFile(int x) {A1FromFile=x;}
    int getA1FromFile() {return A1FromFile;}
    void setA2FromFile(int x) {A2FromFile=x;}
    int getA2FromFile() {return A2FromFile;}
    void setBG(double x) {BG=x;}
    double getBG() {return BG;}
    void setBGq(double x) {BGq=x;}
    double getBGq() {return BGq;}
    void setMuZero(double x) {muZero=x;}
    double getMuZero() {return muZero;}
    void setc(double x) {c=x;}
    double getc() {return c;}
    void setRoots(double x) {roots=x;}
    double getRoots() {return roots;}
    void setUseFluctuatingx(int x) {useFluctuatingx=x;}
    int getUseFluctuatingx() {return useFluctuatingx;}
    void setRunWithThisFactorTimesQs(double x) {runWithThisFactorTimesQs=x;};
    double getRunWithThisFactorTimesQs() {return runWithThisFactorTimesQs;}
    void setxFromThisFactorTimesQs(double x) {xFromThisFactorTimesQs=x;};
    double getxFromThisFactorTimesQs() {return xFromThisFactorTimesQs;}
    void setTpp(double x) {Tpp=x;}
    double getTpp() {return Tpp;}
    void setUseFixedNpart(int x) {useFixedNpart=x;}
    int getUseFixedNpart() {return useFixedNpart;}
    void setRnp(double x) {rnp=x;}
    double getRnp() {return rnp;}
    void setSmearingWidth(double x) {smearingWidth=x;}
    double getSmearingWidth() {return smearingWidth;}
    void setSuccess(int x) {success=x;}
    int getSuccess() {return success;}
    void setRmax(double x) {rmax=x;}
    double getRmax() {return rmax;}
    
    
    // switches:
    void setInitMethod(int x) {initMethod=x;}
    int getInitMethod() {return initMethod;}
    void setUseNucleus(int x) {useNucleus=x;};
    int getUseNucleus() {return useNucleus;}
    void setRunWithQs(int x) {runWithQs=x;};
    int getRunWithQs() {return runWithQs;}
    void setRunWithkt(int x) {runWithkt=x;};
    int getRunWithkt() {return runWithkt;}
    void setRunWithLocalQs(int x) {runWithLocalQs=x;};
    int getRunWithLocalQs() {return runWithLocalQs;}
    void setLinearb(int x) {linearb=x;};
    int getLinearb() {return linearb;}
    void setNucleonPositionsFromFile(int x) {nucleonPositionsFromFile=x;}
    int getNucleonPositionsFromFile() {return nucleonPositionsFromFile;}
    void setSmearQs(int x) {smearQs=x;}
    int getSmearQs() {return smearQs;}
    void setGaussianWounding(int x) {gaussianWounding=x;}
    int getGaussianWounding() {return gaussianWounding;}
    void setUsePseudoRapidity(int x) {usePseudoRapidity=x;}
    int getUsePseudoRapidity() {return usePseudoRapidity;}
    void setUseConstituentQuarkProton(int x) {useConstituentQuarkProton=x;}
    int getUseConstituentQuarkProton() {return useConstituentQuarkProton;}
};
#endif // Parameters_H
