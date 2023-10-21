#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

char** vigenereTable();
void deleteTable(char**, int);
void exportTable(char**, int);
map<char, int> mixedAscii();
int generateNewAsciiValue(char);
int Fibonacci(int);

int main(){
    char** viegnere = vigenereTable();
    map<char, int> newAscii = mixedAscii();

    exportTable(viegnere, 94);
    deleteTable(viegnere, 94);

    return 0;
}

void deleteTable(char** table, int n) {
    for (int i = 0; i < n; i++) {
        delete[] table[i];
    }
    delete[] table;
}

char** vigenereTable() {
    char** table = new char*[94];

    for (int i = 0; i < 94; i++) {
        table[i] = new char[94];
        for (int j = 0; j < 94; j++) {
            table[i][j] = char(((i + j) % 94) + 32);
        }
    }

    return table;
}

map<char, int> mixedAscii() {
    map<char, int> newAscii;
    for (int i = 32; i < 126; i++) {
        newAscii[char(i)] = generateNewAsciiValue(char(i));
    }
    return newAscii;
}

int generateNewAsciiValue(char character) {
    int offset = 3;
    return (character + offset % 126);
}

void exportTable(char** tabla, int size) {
    ofstream archivo("tabla_vigenere.txt");

    if (archivo.is_open()) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
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