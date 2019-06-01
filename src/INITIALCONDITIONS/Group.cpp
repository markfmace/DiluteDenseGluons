// Group.cpp is adapted from the IP-Glasma solver.
// Copyright (C) 2018 Bjoern Schenke.
// Reproduced with permission by Mark Mace 2019 for Dilute-Dense gluon solver

#include "Group.h"

Group::Group(int N){
    
    //std::cerr << "# INITIALIZING GROUP SU(" << N << ") ... ";
    locNc = N;
    t = new Matrix*[locNc*locNc-1]; // 3 generators for SU(2), 8 for SU(3)
    for (int i=0; i<locNc*locNc-1; i++)
    {
        t[i] = new Matrix(locNc); // 2x2 for SU(2), 3x3 for SU(3)
    }
    tA = new Matrix*[locNc*locNc-1]; // 3 generators for SU(2), 8 for SU(3) in the adjoint representation
    for (int i=0; i<locNc*locNc-1; i++)
    {
        tA[i] = new Matrix(locNc*locNc-1,0.); // 3x3 for SU(2), 8x8 for SU(3)
    }
    //   it = new Matrix*[Nc*Nc-1]; // i times generators
    //   for (int i=0; i<Nc*Nc-1; i++)
    //     {
    //       it[i] = new Matrix(Nc); // 2x2 for SU(2), 3x3 for SU(3)
    //     }
    if(locNc==2)
    {
        // fundamental rep.
        t[0]->set(0,0,0.);                       t[0]->set(0,1,0.5);
        t[0]->set(1,0,0.5);                      t[0]->set(1,1,0.);
        
        t[1]->set(0,0,0.);                       t[1]->set(0,1,complex<double>(0.,-0.5));
        t[1]->set(1,0,complex<double>(0.,0.5));  t[1]->set(1,1,0.);
        
        t[2]->set(0,0,0.5);                      t[2]->set(0,1,0.);
        t[2]->set(1,0,0.);                       t[2]->set(1,1,-0.5);
        
        // adjoint rep.
        tA[0]->set(0,0,0.);                      tA[0]->set(0,1,0.);                      tA[0]->set(0,2,0.);
        tA[0]->set(1,0,0.);                      tA[0]->set(1,1,0.);                      tA[0]->set(1,2,complex<double>(0.,-1.));
        tA[0]->set(2,0,0.);                      tA[0]->set(2,1,complex<double>(0.,1.));  tA[0]->set(2,2,0.);
        
        tA[1]->set(0,0,0.);                      tA[1]->set(0,1,0.);                      tA[1]->set(0,2,complex<double>(0.,1.));
        tA[1]->set(1,0,0.);                      tA[1]->set(1,1,0.);                      tA[1]->set(1,2,0.);
        tA[1]->set(2,0,complex<double>(0.,-1.)); tA[1]->set(2,1,0.);                      tA[1]->set(2,2,0.);
        
        tA[2]->set(0,0,0.);                      tA[2]->set(0,1,complex<double>(0.,-1.)); tA[2]->set(0,2,0.);
        tA[2]->set(1,0,complex<double>(0.,1.));  tA[2]->set(1,1,0.);                      tA[2]->set(1,2,0.);
        tA[2]->set(2,0,0.);                      tA[2]->set(2,1,0.);                      tA[2]->set(2,2,0.);
        
        
        //       // fund. times i (not needed, really...)
        //       it[0]->set(0,0,0.);                      it[0]->set(0,1,complex<double>(0.,0.5));
        //       it[0]->set(1,0,complex<double>(0.,0.5)); it[0]->set(1,1,0.);
        
        //       it[1]->set(0,0,0.);                      it[1]->set(0,1,0.5);
        //       it[1]->set(1,0,-0.5);                    it[1]->set(1,1,0.);
        
        //       it[2]->set(0,0,complex<double>(0.,0.5)); it[2]->set(0,1,0.);
        //       it[2]->set(1,0,0.);                      it[2]->set(1,1,complex<double>(0.,-0.5));
        
        //cerr << "SU(" << Nc << ") generators:" << endl;
        //cerr << endl << *t[0] << endl << endl << *t[1] << endl << endl << *t[2] << endl << endl;
    }
    else if(locNc==3)
    {
        // fundamental rep.
        t[0]->set(0,0,0.);                      t[0]->set(0,1,0.5);                      t[0]->set(0,2,0.);
        t[0]->set(1,0,0.5);                     t[0]->set(1,1,0.);                       t[0]->set(1,2,0.);
        t[0]->set(2,0,0.);                      t[0]->set(2,1,0.);                       t[0]->set(2,2,0.);
        
        t[1]->set(0,0,0.);                      t[1]->set(0,1,complex<double>(0.,-0.5)); t[1]->set(0,2,0.);
        t[1]->set(1,0,complex<double>(0.,0.5)); t[1]->set(1,1,0.);                       t[1]->set(1,2,0.);
        t[1]->set(2,0,0.);                      t[1]->set(2,1,0.);                       t[1]->set(2,2,0.);
        
        t[2]->set(0,0,0.5);                     t[2]->set(0,1,0.);                       t[2]->set(0,2,0.);
        t[2]->set(1,0,0.);                      t[2]->set(1,1,-0.5);                     t[2]->set(1,2,0.);
        t[2]->set(2,0,0.);                      t[2]->set(2,1,0.);                       t[2]->set(2,2,0.);
        
        t[3]->set(0,0,0.);                      t[3]->set(0,1,0.);                       t[3]->set(0,2,0.5);
        t[3]->set(1,0,0.);                      t[3]->set(1,1,0.);                       t[3]->set(1,2,0.);
        t[3]->set(2,0,0.5);                     t[3]->set(2,1,0.);                       t[3]->set(2,2,0.);
        
        t[4]->set(0,0,0.);                      t[4]->set(0,1,0.);                       t[4]->set(0,2,complex<double>(0.,-0.5));
        t[4]->set(1,0,0.);                      t[4]->set(1,1,0.);                       t[4]->set(1,2,0.);
        t[4]->set(2,0,complex<double>(0.,0.5)); t[4]->set(2,1,0.);                       t[4]->set(2,2,0.);
        
        t[5]->set(0,0,0.);                      t[5]->set(0,1,0.);                       t[5]->set(0,2,0.);
        t[5]->set(1,0,0.);                      t[5]->set(1,1,0.);                       t[5]->set(1,2,0.5);
        t[5]->set(2,0,0.);                      t[5]->set(2,1,0.5);                      t[5]->set(2,2,0.);
        
        t[6]->set(0,0,0.);                      t[6]->set(0,1,0.);                       t[6]->set(0,2,0.);
        t[6]->set(1,0,0.);                      t[6]->set(1,1,0.);                       t[6]->set(1,2,complex<double>(0.,-0.5));
        t[6]->set(2,0,0.);                      t[6]->set(2,1,complex<double>(0.,0.5));  t[6]->set(2,2,0.);
        
        t[7]->set(0,0,1./(2.*sqrt(3.)));        t[7]->set(0,1,0.);                       t[7]->set(0,2,0.);
        t[7]->set(1,0,0.);                      t[7]->set(1,1,1./(2.*sqrt(3.)));         t[7]->set(1,2,0.);
        t[7]->set(2,0,0.);                      t[7]->set(2,1,0.);                       t[7]->set(2,2,-1./(sqrt(3.)));
        
        
        // adjoint rep.
        // all components are set to zero by default  - now just set those that aren't zero:
        
        //tA1
        tA[0]->set(1,2,complex<double>(0.,-1.));
        tA[0]->set(2,1,complex<double>(0.,1.));
        tA[0]->set(3,6,complex<double>(0.,-0.5));
        tA[0]->set(4,5,complex<double>(0.,0.5));
        tA[0]->set(5,4,complex<double>(0.,-0.5));
        tA[0]->set(6,3,complex<double>(0.,0.5));
        
        //tA2
        tA[1]->set(0,2,complex<double>(0.,1.));
        tA[1]->set(2,0,complex<double>(0.,-1.));
        tA[1]->set(3,5,complex<double>(0.,-0.5));
        tA[1]->set(4,6,complex<double>(0.,-0.5));
        tA[1]->set(5,3,complex<double>(0.,0.5));
        tA[1]->set(6,4,complex<double>(0.,0.5));
        
        //tA3
        tA[2]->set(0,1,complex<double>(0.,-1.));
        tA[2]->set(1,0,complex<double>(0.,1.));
        tA[2]->set(3,4,complex<double>(0.,-0.5));
        tA[2]->set(4,3,complex<double>(0.,0.5));
        tA[2]->set(5,6,complex<double>(0.,0.5));
        tA[2]->set(6,5,complex<double>(0.,-0.5));
        
        //tA4
        tA[3]->set(0,6,complex<double>(0.,0.5));
        tA[3]->set(1,5,complex<double>(0.,0.5));
        tA[3]->set(2,4,complex<double>(0.,0.5));
        tA[3]->set(4,2,complex<double>(0.,-0.5));
        tA[3]->set(4,7,complex<double>(0.,-0.8660254037844386)); // sqrt(3)/2=0.8660254037844386
        tA[3]->set(5,1,complex<double>(0.,-0.5));
        tA[3]->set(6,0,complex<double>(0.,-0.5));
        tA[3]->set(7,4,complex<double>(0.,0.8660254037844386));
        
        //tA5
        tA[4]->set(0,5,complex<double>(0.,-0.5));
        tA[4]->set(1,6,complex<double>(0.,0.5));
        tA[4]->set(2,3,complex<double>(0.,-0.5));
        tA[4]->set(3,2,complex<double>(0.,0.5));
        tA[4]->set(3,7,complex<double>(0.,0.8660254037844386));
        tA[4]->set(5,0,complex<double>(0.,0.5));
        tA[4]->set(6,1,complex<double>(0.,-0.5));
        tA[4]->set(7,3,complex<double>(0.,-0.8660254037844386));
        
        //tA6
        tA[5]->set(0,4,complex<double>(0.,0.5));
        tA[5]->set(1,3,complex<double>(0.,-0.5));
        tA[5]->set(2,6,complex<double>(0.,-0.5));
        tA[5]->set(3,1,complex<double>(0.,0.5));
        tA[5]->set(4,0,complex<double>(0.,-0.5));
        tA[5]->set(6,2,complex<double>(0.,0.5));
        tA[5]->set(6,7,complex<double>(0.,-0.8660254037844386));
        tA[5]->set(7,6,complex<double>(0.,0.8660254037844386));
        
        //tA7
        tA[6]->set(0,3,complex<double>(0.,-0.5));
        tA[6]->set(1,4,complex<double>(0.,-0.5));
        tA[6]->set(2,5,complex<double>(0.,0.5));
        tA[6]->set(3,0,complex<double>(0.,0.5));
        tA[6]->set(4,1,complex<double>(0.,0.5));
        tA[6]->set(5,2,complex<double>(0.,-0.5));
        tA[6]->set(5,7,complex<double>(0.,0.8660254037844386));
        tA[6]->set(7,5,complex<double>(0.,-0.8660254037844386));
        
        //tA8
        tA[7]->set(3,4,complex<double>(0.,-0.8660254037844386));
        tA[7]->set(4,3,complex<double>(0.,0.8660254037844386));
        tA[7]->set(5,6,complex<double>(0.,-0.8660254037844386));
        tA[7]->set(6,5,complex<double>(0.,0.8660254037844386));
        
        //cerr << "SU(" << Nc << ") generators:" << endl;
        //cerr << endl << *t[0] << endl << endl << *t[1] << endl << endl << *t[2] << endl
        //	   << endl << *t[3] << endl << endl << *t[4] << endl << endl << *t[5] << endl
        //	   << endl << *t[6] << endl << endl << *t[7] << endl << endl; 
    }
    else
    {
        std::cerr << "# this program only works for SU(2) and SU(3). You gave me SU(" << locNc << "). I can't do that. Write your own program. Exiting." << endl;
        exit(1);
    }
    
    
    //std::cerr << "done." << endl;
    
}

Group::~Group()
{
    for (int i=0; i<locNc*locNc-1; i++)
    {
        delete t[i];
        delete tA[i];
    }
    delete [] t;
    delete [] tA;
}
