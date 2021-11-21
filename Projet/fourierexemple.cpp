#include <complex>
#include <iostream>
#include <valarray>

using namespace std;

const double PI = 3.141592653589793238460;
 
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void printCArray(CArray& in){
    cout << "| ";
    for(auto iter = begin(in) ; iter != end(in) ; iter++){
        cout << *iter << " | ";
    }
    cout << endl;
}

void fft(CArray& x){
    const size_t N = x.size();
    if (N <= 1){
        return;
    }
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        cout << "itération n°" << k << endl;
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
    printCArray(x);
    cout << "--------------------------" << endl;
}

// ------- MAIN

int main(){

    CArray in{1.0, 1.0, 2.0, 3.0};
    cout << "-----\nfft de :\t" ;
    printCArray(in);
    fft(in);
    cout << "-----\nSortie :\t" ;
    printCArray(in);

    return 0;
}