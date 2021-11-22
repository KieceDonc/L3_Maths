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

// ------- FONCTION D'AIDE POUR DÉCOUPER DES VECTEURS

CVector slice1D(CVector in, int start, int size, int increment){
    CVector out(size);
    int outIndex=0;
    for(int inIndex = start;inIndex<=size;inIndex+=increment){
        out[outIndex]=in[inIndex];
        outIndex+=1;
    }
    return out;
}



// ------- AFFICHAGE DES VECTEURS DANS LA CONSOLE

void printVector1D(CVector in){
    cout << "\t\t\t";
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

// Transformée de Fourier 1D discrete directe et inverse : si bool true -> transformée inverse
CVector TF1D(CVector& in, bool inverse){
    int N = in.size();                              // Taille du vecteur en entrée
    CVector out(in.size(),0.0f);                    // Vecteur sortie rempli de 0
    Complex root;                                   // Contenu de l'exponentielle (racine de l'unité a.k.a root of unity)
    Complex sum;                                    // Calcul de la somme (calcul de chaque index du vecteur sortie)
    
    // Formule : in[u] = somme de 0 à N-1 des in[x] * exp(-2*i*PI*k*x) pour k de 0 à N-1
    for(int k = 0 ; k < N ; k++){
        sum = 0.0f;

        //Boucle des k de 0 à N-1
        for(int x = 0 ; x < N ; x++){
            root = (2.0fi*PI*k*x)/N;    
            if(inverse)
                root*=-1;
            sum += in[x] * exp(root);
        }

        out[k] = sum;
        if(inverse)
            out[k] = out[k] / (N*1.0f);
    }

    return out;
}

// Transformée de Fourier 1D rapide 
CVector TF1FFT(CVector in){
    int N = in.size();
    if (N <= 1){
        return CVector{in[0]};
    }
 
    // divide
    CVector even = slice1D(in,0,N/2, 2);
    CVector odd = slice1D(in,1,N/2, 2);
    
    // conquer
    TF1FFT(even);
    TF1FFT(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k){
        Complex t = std::polar(1.0f, -2 * PI * k / N) * odd[k];
        in[k    ] = even[k] + t;
        in[k+N/2] = even[k] - t;
    }

    return in;
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

    //CVector2D machin{vector<float>{1.0f,2.0f},vector<float>{3.0f,4.0f}};
    //TF1DB(truc0,false);
    CVector vecOut = TF1D(vecIn3,false);

    CVector vecOut2 = TF1D(vecOut,true);
    cout << "Vecteur entrée :\t"; 
    printVector1D(vecIn3);
    cout << "TF :"; 
    printVector1D(vecOut);
    cout << "TFI :";
    printVector1D(vecOut2);

    CVector vecOutFFT = TF1FFT(vecIn3);
    CVector vecOutFFT2 = TF1FFT(vecOutFFT);
    cout << "Vecteur entrée :"; 
    printVector1D(vecIn3);
    cout << "TF :"; 
    printVector1D(vecOutFFT);
    cout << "TFI :";
    printVector1D(vecOutFFT2);

    CVector2D vecIn2D{{50.0f,3.0f},{4.0f,5.0f}};

    CVector2D vecOut2D = TF2DB(vecIn2D,false);
    CVector2D vecOut2D_2 = TF2DB(vecOut2D,true);
    cout << "Vecteur entrée :"; 
    printVector2D(vecIn2D);
    cout << "TF :"; 
    printVector2D(vecOut2D);
    cout << "TFI :";
    printVector2D(vecOut2D_2);


    return 0;
}
