#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <math.h>

using namespace std;

char** vigenereTable();
void deleteTable(char**, int);
void exportTable(char**, int);
map<char, int> mixedAscii();
int newAsciiValue(char);
int Fibonacci(int);
char** stringToBlock(string);
string encryptText(string, string);
string decryptText(string, string);
string hideValues(char**, char**, int);
string revealValues(char**, char**, int);
char originalAsciiCharacter(int);
char getTextCharacter(char, char);

int FIRST_ASCII_VALUE = 32;
int LAST_ASCII_VALUE = 126;
int NUMBER_OF_CHARACTERS = LAST_ASCII_VALUE - FIRST_ASCII_VALUE;
char** vigenere = vigenereTable();
map<char, int> newAscii = mixedAscii();

int main(){
   
    string text;
    string key = "contrasenasegura";
    getline(cin, text);

    string chyper = encryptText(text, key);
    string original = decryptText(chyper, key);

    cout << chyper << endl;
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
    return (character + offset % LAST_ASCII_VALUE);
}

string encryptText(string text, string key) {
    string cypherText = text;
    int blockSize = 16;
    for(int i = 0; i < 5; i++) {
        int blockCounter = 1;
        int index = 0;
        while(index < cypherText.length()) {
            index = blockCounter * blockSize;
            char** textBlock = stringToBlock(cypherText.substr(index-blockSize, blockSize));
            char** keyBlock = stringToBlock(key.substr(index-blockSize, blockSize));
            cypherText = hideValues(textBlock, keyBlock, sqrt(blockSize));
            blockCounter++;
        }
    }
    return cypherText;
}

string decryptText(string cypherText, string key) {
    string text = cypherText;
    int blockSize = 16;
    
    for(int i = 0; i < 5; i++) {
        int blockCounter = 1;
        int index = 0;
        while(index < cypherText.length()) {
            index = blockCounter * blockSize;
            char** textBlock = stringToBlock(text.substr(index-blockSize, blockSize));
            char** keyBlock = stringToBlock(key.substr(index-blockSize, blockSize));
            text = revealValues(textBlock, keyBlock, sqrt(blockSize));
            blockCounter++;
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
    if (n < 2) {
        return n;
    } else {
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
}