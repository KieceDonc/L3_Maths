#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

float PI = 3.14159265359;

using namespace std;



// ------- AFFICHAGE DES VECTEURS DANS LA CONSOLE

void printVector1D(vector<complex<float>> in){
    for(int x = 0 ; x < in.size() ; x++)
        cout << in[x] << " ";
    cout << endl;
}


void printVector2D(vector<vector<complex<float>>> in){
    for(int y = 0 ; y < in.size() ; y++)
        printVector1D(in[y]);
}



// ------- TRANSFORMEES DE FOURIER 1D

// Transformée de Fourier 1D brutale : si bool true -> transformée inverse
vector<complex<float>> TF1DB(vector<complex<float>>& in, bool inverse){
    int N = in.size();                              // Taille du vecteur en entrée
    vector<complex<float>> out(in.size(),0.0f);     // Vecteur sortie
    
    // Formule : in[u] = somme de 0 à N-1 des in[x] * exp(-2*i*PI*u*x)
    for(int u = 0 ; u < N ; u++){
        complex<float> result = 0.0f;


        for(int x = 0 ; x < N ; x++){
            complex<float> theta = (2.0i*PI*u*x)/N;
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


// ------- MAIN

int main(){

    vector<complex<float>> vecIn{1.0f,2.0f,3.0f,4.0f,5.0f};
    vector<complex<float>> vecIn2{0.0f,4.0f,8.0f,16.0f,32.0f,64.0f,128.0f};

    //vector<vector<complex>> machin{vector<float>{1.0f,2.0f},vector<float>{3.0f,4.0f}};
    //TF1DB(truc0,false);
    vector<complex<float>> vecOut = TF1DB(vecIn2,false);
    vector<complex<float>> vecOut2 = TF1DB(vecOut,true);
    printVector1D(vecIn2);
    printVector1D(vecOut);
    printVector1D(vecOut2);



    return 0;
}