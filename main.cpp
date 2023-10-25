#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;


char** vigenereTable();
void deleteTable(char**, int);
void exportTable(char**, int);
map<char, int> mixedAscii();
int newAsciiValue(char);
int Fibonacci(int);
char** stringToBlock(string);
string encrypt(string, string);
string decrypt(string, string);
string hideValues(char**, char**, int);
string revealValues(char**, char**, int);
char originalAsciiCharacter(int);
char getTextCharacter(char, char);
char*** textMatrix(string&, int&);
void textFormat();
void shiftMatrixCharactersRight(char**);
void shiftMatrixCharactersLeft(char**);
void deleteMatrix(char**);

int FIRST_ASCII_VALUE = 32;
int LAST_ASCII_VALUE = 126;
int NUMBER_OF_CHARACTERS = LAST_ASCII_VALUE - FIRST_ASCII_VALUE + 1;
int NUMBER_OF_ITERATIONS = 1;
char** vigenere = vigenereTable();
map<char, int> newAscii = mixedAscii();


int main(){

    string text;
    string key = "contrasenaseguracontrasenasegura";
    getline(cin, text);

    string chyper = encrypt(text, key);
    cout << chyper << endl;

    string original = decrypt(chyper, key);
    cout << original << endl;


    exportTable(vigenere, NUMBER_OF_CHARACTERS);
    deleteTable(vigenere, NUMBER_OF_CHARACTERS);

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
            table[i][j] = char(((i + j) % NUMBER_OF_CHARACTERS) + FIRST_ASCII_VALUE);
        }
    }

    return table;
}

map<char, int> mixedAscii() {
    map<char, int> newAscii;
    for (int i = FIRST_ASCII_VALUE; i <= LAST_ASCII_VALUE; i++) {
        newAscii[char(i)] = newAsciiValue(char(i));
    }
    return newAscii;
}

int newAsciiValue(char character) {
    int offset = 3;
    return (((int(character) + offset - FIRST_ASCII_VALUE) % NUMBER_OF_CHARACTERS) + FIRST_ASCII_VALUE);
}

string encrypt(string text, string key) {
    string cypherText = text;
    string tempCypherText;
    int blockSize = 16;
    for(int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        int blockNum = 1;
        int index = 0;
        tempCypherText = cypherText;
        cypherText = "";
        while(index < text.length()) {
            index = blockNum * blockSize;
            char** textBlock = stringToBlock(tempCypherText.substr(index-blockSize, blockSize));
            char** keyBlock = stringToBlock(key.substr(index-blockSize, blockSize));
            cypherText += hideValues(textBlock, keyBlock, sqrt(blockSize));
            blockNum++;
        }
    }
    char** block = stringToBlock(cypherText);
    shiftMatrixCharactersRight(block);
    for(int i=0; i<sqrt(cypherText.length()); i++){
        for(int j=0; j<sqrt(cypherText.length()); j++){
            cout << block[i][j] << " ";
        }
    }
    deleteTable(block, sqrt(cypherText.length()));

    
    return cypherText;
}

string decrypt(string cypherText, string key) {
    string text = cypherText;
    string tempText;
    int blockSize = 16;
    for(int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        int blockNum = 1;
        int index = 0;
        tempText = text;
        text = "";
        while(index < cypherText.length()) {
            index = blockNum * blockSize;
            char** textBlock = stringToBlock(tempText.substr(index-blockSize, blockSize));
            char** keyBlock = stringToBlock(key.substr(index-blockSize, blockSize));
            text += revealValues(textBlock, keyBlock, sqrt(blockSize));
            blockNum++;
        }
    }
    return text;
}

char** stringToBlock(string text) {
    int textIndex = 0;
    char** matrix = new char*[4];
    for (int i = 0; i < 4; i++) {
        matrix[i] = new char[4];
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = text[textIndex];
            textIndex++;
        }
    }
    return matrix;
}

string hideValues(char** textBlock, char** keyBlock, int n) {
    string newText;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int textCharacter = int(textBlock[i][j]) - FIRST_ASCII_VALUE; 
            int keyCharacter = int(keyBlock[i][j]) - FIRST_ASCII_VALUE; 
            char vigenereCharacter = vigenere[textCharacter][keyCharacter];
            newText += char(newAscii[vigenereCharacter]);
        }
    }
    return newText;
}

string revealValues(char** textBlock, char** keyBlock, int n) {
    string newText;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int hiddenValue = int(textBlock[i][j]);
            char hiddenCharacter = originalAsciiCharacter(hiddenValue);
            newText += getTextCharacter(hiddenCharacter, keyBlock[i][j]);
        }
    }
    return newText;
}

char originalAsciiCharacter(int value) {
    for (const auto pair : newAscii) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return ' ';
}

char getTextCharacter(char cypherCharacter, char keyCharacter) {
    int keyValue = int(keyCharacter) - FIRST_ASCII_VALUE;
    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        if (vigenere[i][keyValue] == cypherCharacter) {
            return vigenere[i][0];
        }
    }
    return ' ';
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

void shiftMatrixCharactersRight(char** matrix) {
    char prev = matrix[0][0];
    char last = matrix[3][3];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char temp = matrix[i][j];
            matrix[i][j] = move(prev, temp);
            prev = temp;
        }
    }
    matrix[0][0] = last;
;
}

void deleteMatrix(char** matrix) {
    for (int i = 0; i < 4; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void shiftMatrixCharactersLeft(char** matrix) {

    char prev = matrix[0][0];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char temp = matrix[i][j];
            matrix[i][j] = temp;
        }
    }

    matrix[0][0] = prev;
}