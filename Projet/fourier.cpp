#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <valarray>

float PI = 3.14159265359;

using namespace std;

typedef std::complex<float> Complex;
typedef std::vector<Complex> CVector;
typedef std::vector<CVector> CVector2D;

// ------- AFFICHAGE DES VECTEURS DANS LA CONSOLE

void printVector1D(CVector in){
    for(int x = 0 ; x < in.size() ; x++)
        cout << in[x] << " ";
    cout << endl;
}


void printVector2D(CVector2D in){
    for(int y = 0 ; y < in.size() ; y++)
        printVector1D(in[y]);
}



// ------- TRANSFORMEES DE FOURIER 1D

// Transformée de Fourier 1D brutale : si bool true -> transformée inverse
CVector TF1DB(CVector& in, bool inverse){
    int N = in.size();                              // Taille du vecteur en entrée
    CVector out(in.size(),0.0f);                    // Vecteur sortie rempli de 0
    
    // Formule : in[u] = somme de 0 à N-1 des in[x] * exp(-2*i*PI*u*x)
    for(int u = 0 ; u < N ; u++){
        Complex result = 0.0f;


        for(int x = 0 ; x < N ; x++){
            Complex theta = (2.0fi*PI*u*x)/N;
            if(inverse){
                theta*=-1;
            }
            result += in[x] * exp(theta);
        }

        out[u] = result;
        if(inverse){
            out[u] = out[u] / (N*1.0f);
        } 
    }

    return out;
}

// Transformée de Fourier 1D rapide 

CVector TF1DR(CVector& in, bool inverse){
    int N = in.size();                              // Taille du vecteur en entrée
    CVector out(in.size(),0.0f);                    // Vecteur sortie rempli de 0



    return out;
}

/*
t0 = [ 0 1 2 3 ]
-----------
fft(t0)
t1e [ 0 2 ]
t1o [ 1 3 ]

fft(t1e = [0 2])
-----------
t2e [ 0 ]
t2o [ 2 ]

A

fft(t2e = [ 0 ])
N <= 1 donc
return

fft(t2o = [2])
N <= 1 donc 
return

fft(t1o = [1 3])
-----------
t2e [ 1 ]
t2o [ 3 ]

fft(t2e = [ 1 ])
N <= 1 donc
return

fft(t10 = [ 3 ])
N <= 1 donc 
return

--------------

A





*/


// ------- MAIN

int main(){

    CVector vecIn{1.0f,2.0f,3.0f,4.0f,5.0f};
    CVector vecIn2{0.0f,4.0f,8.0f,16.0f,32.0f,64.0f,128.0f};
    CVector vecIn3{1.0f,3.0f};

    //CVector2D machin{vector<float>{1.0f,2.0f},vector<float>{3.0f,4.0f}};
    //TF1DB(truc0,false);
    CVector vecOut = TF1DB(vecIn3,false);

    CVector vecOut2 = TF1DB(vecOut,true);
    cout << "Vecteur entrée :\t"; 
    printVector1D(vecIn3);
    cout << "TF :\t\t\t"; 
    printVector1D(vecOut);
    cout << "TFI :\t\t\t";
    printVector1D(vecOut2);



    return 0;
}
