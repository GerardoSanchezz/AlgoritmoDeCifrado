#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char** vigenereTable();
void deleteTable(char**, int);
void exportarTablaVigenere(char**);
int Fibonacci(int);

int main(){
    char** viegnere = vigenereTable();
    
    exportarTablaVigenere(viegnere);
   
    deleteTable(viegnere, 26);

    cout << "Fibonacci(8): " << Fibonacci(8) << endl;

    return 0;
}

void deleteTable(char** table, int n) {
    for (int i = 0; i < n; i++) {
        delete[] table[i];
    }
    delete[] table;
}

char** vigenereTable() {
    char valores[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char** tabla = new char*[26];

    for (int i = 0; i < 26; i++) {
        tabla[i] = new char[25];
        for (int j = 0; j < 25; j++) {
            tabla[i][j] = (valores[(i + j) % 26]);
        }
    }

    return tabla;
}

void exportarTablaVigenere(char** tabla) {
    ofstream archivo("tabla_vigenere.txt");

    if (archivo.is_open()) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 25; j++) {
                archivo << tabla[i][j] << " ";
            }
            archivo << "\n";
        }
        archivo.close();
        cout << "Tabla de Vigenère generada y exportada exitosamente a tabla_vigenere.txt" << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}

int Fibonacci(int n) {
    if (n < 2) {
        return n;
    } else {
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
}