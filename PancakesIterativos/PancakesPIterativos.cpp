#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

const string OBJETIVO = "ABCDEFGHI";

int TAM = 9;
int MaxProf;
int TamMejorSolucion;
vector<char> MejorSolucion;
vector<char> SolucionActual;
int TamSolucion;
int Nodos;

string shuffle(string s) {
    random_shuffle(s.begin(), s.end());
    return s;
}

void BusqProfIterativa(string s);

void BusqProf(string s, int n_ant) {
    Nodos++;

    if (s == OBJETIVO) {
        if (TamSolucion < TamMejorSolucion) {
            TamMejorSolucion = TamSolucion;
            MejorSolucion = vector<char>(SolucionActual.begin(), SolucionActual.begin() + TamMejorSolucion);
        }
        return;
    }
    if (MaxProf <= TamSolucion) {
        return;
    }

    for (int i = 2; i <= TAM; i++) {
        if (i == n_ant) {
            continue;
        }
        string s1 = s.substr(0, i);
        reverse(s1.begin(), s1.end());
        s1 += s.substr(i);
        SolucionActual[TamSolucion++] = ('A' + i - 1);
        BusqProf(s1, i);
        TamSolucion--;
    }
}

void BusqProfIterativa(string s) {
    for (int maxProf = 0; maxProf <= TAM; maxProf++) {
        MaxProf = maxProf;
        BusqProf(s, 0);
    }
}

int main() {
    srand(time(NULL));

    string s = shuffle(OBJETIVO);

    MaxProf = TAM;
    TamMejorSolucion = TAM + 1;
    MejorSolucion = vector<char>(TAM);
    SolucionActual = vector<char>(TAM);
    TamSolucion = 0;
    Nodos = 0;

    auto start = chrono::high_resolution_clock::now();
    BusqProfIterativa(s);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Numeros aleatorios " << s << endl;
    cout << "Nodos visitados: " << Nodos << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
    cout << "Mejor solución: ";
    for (char c : MejorSolucion) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
