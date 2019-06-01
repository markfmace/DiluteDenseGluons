// Spinor.h is adapted from of the IP-Glasma solver.
// Copyright (C) 2018 Bjoern Schenke.
// Reproduced with permission by Mark Mace 2019 for Dilute-Dense gluon solver

#ifndef Spinor_h
#define Spinor_h

#include <complex>
#include <iostream>
#include <cstdlib>

using namespace std;

class Spinor
{
    private:
    int ndim;
    int nn;
    complex<double>* e;
    
    public:
    
    //constructor(s)
    Spinor(int n);
    Spinor(int n, complex<double> a, complex<double> b); // for SU(2)
    Spinor(int n, complex<double> a, complex<double> b, complex<double> c); // for SU(3)
    
    //destructor
    ~Spinor()
    {
        delete[] e;
    }
    
    void setRe(int i, double a) {e[i]=complex<double>(a,e[i].imag());};
    void setIm(int i, double a) {e[i]=complex<double>(e[i].real(),a);};
    
    void set(int i, complex<double> a) {e[i]=a;};
    
    complex<double> get(int i) {return e[i];};
    
    double getRe(int i) {return e[i].real();};
    double getIm(int i) {return e[i].imag();};
    
    int getNDim() const {return ndim;}
    int getNN()  const {return nn;}
    
    double norm()
    {
        nn = (*this).getNN();
        complex<double> mynorm = 0.;
        for (int i=0; i<nn; i++)
        mynorm += (conj(e[i])*e[i]);
        
        return (sqrt(mynorm)).real();
        //return sqrt((conj(e[0])*e[0]+conj(e[1])*e[1]+conj(e[2])*e[2]).real());
        // cerr << e[0] << " " << e[1] << " " << e[2] << " norm=" << sqrt((conj(e[0])*e[0]+conj(e[1])*e[1]+conj(e[2])*e[2]).real()) << endl;
    }
    
    Spinor normalize();
    
    Spinor GramSchmidt(const Spinor& a);
    
    //operators:
    
    //()
    std::complex<double> operator () (const int i) const { return e[i]; }
    
    
    //=
    const Spinor& operator = (const Spinor& p)
    {
        nn = p.getNN();
        if(&p != this )
        {
            for(int i=0; i<nn; i++)
            {
                e[i] = p.e[i];
            }
        }
        return *this;
    }
    
    //==
    bool operator == (const Spinor& p) const
    {
        for(int i=0; i<nn; i++)
        if(e[i] != p.e[i]) return false;
        return true;
    }
    
    //!=
    bool operator != (const Spinor& p) const
    {
        for(int i=0; i<nn; i++)
        if(e[i] != p.e[i]) return true;
        return false;
    }
    
    //+=
    Spinor& operator += (const Spinor& a)
    {
        for(int i=0; i<nn; i++) e[i] += a.e[i];
        return *this;
    }
    
    //-=
    Spinor& operator -= (const Spinor& a)
    {
        for(int i=0; i<nn; i++) e[i] -= a.e[i];
        return *this;
    }
    
    //*=
    Spinor& operator *= (const complex<double> a)
    {
        for(int i=0; i<nn; i++) e[i] *= a;
        return *this;
    }
    
    // /=
    Spinor& operator /= (const complex<double> a)
    {
        for(int i=0; i<nn; i++) e[i] /= a;
        return *this;
    }
    
    //<<
    friend ostream& operator<<(ostream& os, const Spinor& p)
    {
        for(int i=0; i<p.getNDim();i++)
        {
            os << p(i);
            if(i<p.getNDim()-1) os << std::endl;
        }
        return os;
    }
    
    
};

Spinor  operator + (const Spinor& a, const Spinor& b);
Spinor  operator - (const Spinor& a, const Spinor& b);
Spinor  operator % (const Spinor&  a, const Spinor& b);
Spinor  operator - (const Spinor& a);
Spinor  operator / (const Spinor&  a, const Spinor& b);
Spinor  operator / (const Spinor&  a, const double b);

Spinor operator * (const double a, const Spinor& b);
Spinor operator * (const std::complex<double> a,const Spinor& b);
Spinor operator * (const Spinor& b, const std::complex<double> a);
Spinor operator * (const Spinor&  a, const double b);
complex<double> operator * (const Spinor&  a, const Spinor& b);

#endif

