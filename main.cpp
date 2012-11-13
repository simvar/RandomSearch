#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime> // time() - grąžina sekundžių skaičių nuo 1970 m. sausio 1 d.
using namespace std;
static int n = 2; // Uzdavinio dimensija

// Generuoja atsitiktini realu skaiciu tarp dLow and dHigh
double GetRandomNumber(double dLow, double dHigh){
    return static_cast<double>(rand())/RAND_MAX*(dHigh-dLow) + dLow;
}
// Apskaiciuoja Six-hump Camel Back funkcijos reiksme taske x
double SixHumpCamelBack(double *x){
    return (4-2.1*x[0]*x[0]+x[0]*x[0]*x[0]*x[0]/3)*x[0]*x[0] + x[0]*x[1] +
    (-4+4*x[1]*x[1])*x[1]*x[1];
}
void RezultatuIsvedimas(int nCount, double dGlobF, double *dX){
    cout << nCount << " band. : \n";
    cout << "globF = " << dGlobF << endl;
    for(int i = 0; i < n; ++i)
        cout << "x[" << i << "] = " << dX[i] << endl;
    cout << endl;
}
int main(){
    int N = 1000; // Iteraciju skaitiklis
    int pN = 100; // Rodykliu masyvo dydis
    int count = 1;
    int stopingRule = 1; // 0: FOR N zingsniu; 1: WHILE > eps
    int p = 0; // Rodykliu masyvo indeksas
    double x[n];
    double **xAll = new double*[pN];
    double f;
    double **fAll = new double*[pN];
    xAll[p] = new double[N*n];
    fAll[p] = new double[N];
    double globF = 1000000;
    double globX[n];
    double globMinimum = -1.031628453;
    double region[] = {-1.9, 1.9, -1.1, 1.1};
    double eps = 0.01;
  
    srand(time(0)); // Naudoja vis kita seed'a
    if (stopingRule == 0){
        for (count=0; count < N; count++)
        {
            for(int i = 0; i < n; ++i){
                x[i] = GetRandomNumber(region[2*i], region[2*i+1]);
                xAll[p][count*n+i] = x[i];
            }
            f = SixHumpCamelBack(&x[0]);
            fAll[p][count] = f;
            if (f < globF){
                globF = f;
                for(int i = 0; i < n; ++i) globX[i] = x[i];
                RezultatuIsvedimas(p*N+count, globF, &globX[0]);
            }
        }
    } else {
        while (globF - globMinimum > eps)
        {
            for(int i = 0; i < n; ++i){
                x[i] = GetRandomNumber(region[2*i], region[2*i+1]);
                xAll[p][count*n+i] = x[i];
            }
            f = SixHumpCamelBack(&x[0]);
            fAll[p][count] = f;
            if (f < globF){
                globF = f;
                for(int i = 0; i < n; ++i) globX[i] = x[i];
                RezultatuIsvedimas(p*N+count, globF, &globX[0]);
            }
            count++;
            if (count >= N){
                p++;
                xAll[p] = new double[N*n];
                fAll[p] = new double[N];
                count = 0;
            }
        }
        
    }
    // Isvalome atminty (HEAP'a)
    for(int i = 0; i < p; ++i){
        delete [] xAll[i];
        delete [] fAll[i];
    }
    delete [] xAll;
    delete [] fAll;

    cout << "RANDOM SEARCH REZULTATAS: \nPo ";
    RezultatuIsvedimas(p*N+count-1, globF, &globX[0]);
}
