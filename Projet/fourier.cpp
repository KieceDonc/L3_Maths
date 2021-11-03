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
    for(int x = 0 ; x < in.size() ; x++){
        cout << in[x] << " ";
    }
    cout << endl;
}


void printVector2D(CVector2D in){
    for(int y = 0 ; y < in.size() ; y++){
        printVector1D(in[y]);
    }
}



// ------- TRANSFORMEES DE FOURIER 1D

// Transformée de Fourier 1D brutale : si bool true -> transformée inverse
CVector TF1DB(CVector& in, bool inverse){
    int N = in.size();                              // Taille du vecteur en entrée
    CVector out(N,0.0f);                    // Vecteur sortie rempli de 0
    
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
            //out[u] = out[u] / (N*N*1.0f);
        } 
    }

    return out;
}

// ------- TRANSFORMEES DE FOURIER 2D

// Transformée de Fourier 2D brutale : si bool true -> transformée inverse
CVector2D TF2DB(CVector2D& in, bool inverse){
    int N = in.size();
    CVector2D out(N,CVector(N));
    for(int u = 0 ; u < N ; u++){
        for(int v = 0 ; v < N; v++){
            Complex result = 0.0f;


            for(int x = 0 ; x < N ; x++){
                for(int y = 0 ; y < N ; y++){
                    Complex theta = 2.0fi*PI*((u*x*1.0f)/N+(v*y*1.0f)/N);
                    if(inverse){
                        theta*=-1;
                    }
                    result += in[x][y] * exp(theta);
                }
            }

            out[u][v] = result;
            if(inverse){
                out[u][v] = out[u][v] / (N*N*1.0f);
            }
        } 
    }
    return out;
}


// ------- MAIN

int main(){

    CVector vecIn{1.0f,2.0f,3.0f,4.0f,5.0f};
    CVector vecIn2{0.0f,4.0f,8.0f,16.0f,32.0f,64.0f,128.0f};
    CVector vecIn3{1.0f,3.0f};

    CVector vecOut = TF1DB(vecIn3,false);
    CVector vecOut2 = TF1DB(vecOut,true);
    cout << "Vecteur entrée :\t"; 
    printVector1D(vecIn3);
    cout << "TF :\t\t\t"; 
    printVector1D(vecOut);
    cout << "TFI :\t\t\t";
    printVector1D(vecOut2);


    CVector2D vecIn2D{{50.0f,3.0f},{4.0f,5.0f}};

    CVector2D vecOut2D = TF2DB(vecIn2D,false);
    CVector2D vecOut2D_2 = TF2DB(vecOut2D,true);
    cout << "Vecteur entrée :" << endl ; 
    printVector2D(vecIn2D);
    cout << "TF :" << endl; 
    printVector2D(vecOut2D);
    cout << "TFI :" << endl;
    printVector2D(vecOut2D_2);


    return 0;
}
