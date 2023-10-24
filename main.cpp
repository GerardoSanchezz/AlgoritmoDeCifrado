#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

int FIRST_ASCII_VALUE = 32;
int LAST_ASCII_VALUE = 128;  // Se ha cambiado a 128
int NUMBER_OF_CHARACTERS = LAST_ASCII_VALUE - FIRST_ASCII_VALUE + 1;


char** vigenereTable();
void deleteTable(char**, int);
void exportTable(char**, int);
map<char, int> mixedAscii();
int generateNewAsciiValue(char);
int Fibonacci(int);
char*** textMatrix(string&, int&);
void textFormat();
char move(char&, char&);
char** shiftMatrixCharacters(char matrix[4][4]);
void deleteMatrix(char**);


int main(){
    textFormat();
    char** viegnere = vigenereTable();
    map<char, int> newAscii = mixedAscii();

    // string text = "EJEMPLOOOO JIJI JAJA XD";

    // int numRows;
    // char*** result = textMatrix(text, numRows);

    // // Imprimir todas las matrices resultantes
    // for (int i = 0; i < numRows; i++) { // Imprimir todas las matrices resultantes
    //     for (int j = 0; j < 4; j++) { // Imprimir cada fila de la matriz 
    //         for (int k = 0; k < 4; k++) { // Imprimir cada columna de la matriz
    //             cout << result[i][j][k] << " "; 
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    char myMatrix[4][4] = {
        {'E', 'J', 'E', 'M'},
        {'P', 'L', 'O', 'O'},
        {'O', 'O', 'C', 'J'},
        {'I', 'B', 'A', 'X'}
        
    };

    cout << "Original Matrix:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << myMatrix[i][j] << " ";
        }
        cout << endl;
    }

    char** shiftedMatrix = shiftMatrixCharacters(myMatrix);

    cout << "Shifted Matrixx:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << shiftedMatrix[i][j] << " ";
        }
        cout << endl;
    }

    deleteMatrix(shiftedMatrix);

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
    char** table = new char*[NUMBER_OF_CHARACTERS];
    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        table[i] = new char[NUMBER_OF_CHARACTERS];
        for (int j = 0; j < NUMBER_OF_CHARACTERS; j++) {
            table[i][j] = char(i + j + FIRST_ASCII_VALUE);
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
    int* fib = new int[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i -2];
    }

    return fib[n];
}

char*** textMatrix(string& text, int& numRows) {
    int n = text.length();
    int nMatrices = (n + 15) / 16;  //El +15 es pa redondear hacia arriba
    numRows = nMatrices * 4;  // 4 filas por matriz
    char*** matrices = new char**[nMatrices]; // Array de matrices

    for (int i = 0; i < nMatrices; i++) { // Se crea cada matriz
        matrices[i] = new char*[4]; 
        for (int j = 0; j < 4; j++) { 
            matrices[i][j] = new char[4];
        }
    }

    int index = 0;
    for (int matrixIndex = 0; matrixIndex < nMatrices; matrixIndex++) { // Se llena cada matriz
        for (int i = 0; i < 4; i++) { 
            for (int j = 0; j < 4; j++) {
                if (index < n) { 
                    matrices[matrixIndex][i][j] = text[index++]; 
                } else { // Si ya se acabó el texto, se llena con espacios
                    matrices[matrixIndex][i][j] = ' '; 
                }
            }
        }
    }

    return matrices;
}

void textFormat() {
    // Abrir el archivo de texto
    ifstream file("texto.txt");
    
    if (!file.is_open()) {
        cerr << "Cannot open file" << endl;
        return;
    }

    // Leer el archivo en un solo string
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();

    // Calcular el número de caracteres en el texto
    int n = text.length();

    // Completar con espacios si no es múltiplo de 16
    int nSpaces = 16 - (n % 16);
    for (int i = 0; i < nSpaces; i++) {
        text += " ";
    }

    // Sobrescribir el archivo con el texto modificado
    ofstream newFile("texto.txt");
    newFile << text;

    // Cerrar los archivos
    file.close();
    newFile.close();

    cout << n << endl;
}

char move(char& a, char& b) {
    char temp = a;
    a = b;
    return temp;
}

char** shiftMatrixCharacters(char matrix[4][4]) {
    char** newMatrix = new char*[4];
    for (int i = 0; i < 4; i++) {
        newMatrix[i] = new char[4];
    }

    char prev = matrix[0][0];
    char last = matrix[3][3];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char temp = matrix[i][j];
            newMatrix[i][j] = move(prev, temp);
            prev = temp;
        }
    }
    newMatrix[0][0] = last;

    return newMatrix;
}

void deleteMatrix(char** matrix) {
    for (int i = 0; i < 4; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}