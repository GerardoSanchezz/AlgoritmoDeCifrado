#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

char** vigenereTable(char*, int);
void deleteTable(char**, int);
void exportTable(char**);
map<char, int> mixedAscii(char*, int);
int generateNewAsciiValue(char);

int main(){
    
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char** viegnere = vigenereTable(alphabet, 26);
    map<char, int> newAscii = mixedAscii(alphabet, 26);
   
    
    deleteTable(viegnere, 26);

    return 0;
}

void deleteTable(char** table, int n) {
    for (int i = 0; i < n; i++) {
        delete[] table[i];
    }
    delete[] table;
}

char** vigenereTable(char* alphabet, int size) {
    char** table = new char*[size];

    for (int i = 0; i < size; i++) {
        table[i] = new char[25];
        for (int j = 0; j < 25; j++) {
            table[i][j] = (alphabet[(i + j) % size]);
        }
    }

    return table;
}

map<char, int> mixedAscii(char* alphabet, int size) {
    map<char, int> newAscii;
    for (int i = 0; i < size; i++) {
        newAscii[alphabet[i]] = generateNewAsciiValue(alphabet[i]);
    }
    return newAscii;
}

int generateNewAsciiValue(char character) {
    int offset = 3;
    return (character + offset) % 127;
}

void exportTable(char** tabla) {
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