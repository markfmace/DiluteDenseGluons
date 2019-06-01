// FFT.h is adapted from the IP-Glasma solver.
// Copyright (C) 2018 Bjoern Schenke.
// Reproduced with permission by Mark Mace 2019 for Dilute-Dense gluon solver

#ifndef FFT_H
#define FFT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include <complex>
#include <math.h>
#include "Matrix.h"
#include <vector>
#include <algorithm>
#include <functional>

#include <fftw3.h>

using namespace std;


template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
    //assert(a.size() == b.size());
    
    std::vector<T> result;
    result.reserve(a.size());
    
    std::transform(a.begin(), a.end(), b.begin(),
                   std::back_inserter(result), std::plus<T>());
    return result;
}

template <typename T>
std::vector<T> operator*(const std::vector<T>& a, const std::complex<double>& b)
{
    std::vector<T> result;
    result = a;
    int size = a.size();
    for (int i = 0; i<size; i++)
    {
        result.at(i)=b*a.at(i);
    }
    return result;
}

template <typename T>
std::vector<T> operator / (const std::vector<T>& a, const double b)
{
    std::vector<T> result;
    result = a;
    int size = a.size();
    for (int i = 0; i<size; i++)
    {
        result.at(i)=a.at(i)/b;
    }
    return result;
}


class FFT
{
    private:
    fftw_complex *input, *output;
    fftw_complex *inputMany, *outputMany;
    fftw_plan p, pback, pmany, pmanyback;
    
    public:
    
    // Constructor.
    FFT(const int nn[])
    {
        input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nn[0] * nn[1]);
        output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nn[0] * nn[1]);
        p = fftw_plan_dft_2d(nn[0], nn[1], input, output, FFTW_FORWARD, FFTW_MEASURE);
        pback = fftw_plan_dft_2d(nn[0], nn[1], input, output, FFTW_BACKWARD, FFTW_MEASURE);
        inputMany = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nn[0] * nn[1] * 9);
        outputMany = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nn[0] * nn[1] * 9);
        pmany = fftw_plan_many_dft(2, nn, 9, input, nn, 1, nn[0]*nn[1], output, nn, 1, nn[0]*nn[1], FFTW_FORWARD, FFTW_MEASURE);
        pmanyback = fftw_plan_many_dft(2, nn, 9, input, nn, 1, nn[0]*nn[1], output, nn, 1, nn[0]*nn[1], FFTW_BACKWARD, FFTW_MEASURE);
    };
    // Destructor.
    ~FFT()
    {
        fftw_destroy_plan(pmany);
        fftw_destroy_plan(pmanyback);
        fftw_destroy_plan(p);
        fftw_destroy_plan(pback);
        fftw_free(input); fftw_free(output);
    };
    void fftnVector(vector<complex<double> > **data, vector<complex<double> > **outdata, const int nn[], const int ndim, const int isign);
    void fftnArray(complex<double> **data, complex<double> **outdata, const int nn[], const int ndim, const int isign, const int mDim);
    
    template<class T>
    void fftn(T **data, T **outdata, const int nn[], const int ndim, const int isign);
    template <class T>
    void fftnMany(T **data, T **outdata, const int nn[], const int ndim, const int isign);
    
    void fftnComplex(complex<double> *data, complex<double> *outdata, const int nn[], const int ndim, const int isign);
    //  void fftnComplex(complex<double> **data, const int nn[], const int ndim, const int isign);
    
};

#endif // FFT_H
