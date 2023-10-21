#include <iostream>
#include <string>
#include <fstream>
using namespace std;

char** tablaVigenere();
void deleteTablaVigenere(char** tabla);
void exportarTablaVigenere(char** tabla);

int main(){
    char** viegnere = tablaVigenere();
    // Exportar la tabla al archivo de texto
    exportarTablaVigenere(viegnere);

    // Eliminar la tabla de memoria
    deleteTablaVigenere(viegnere);

    return 0;
}

void deleteTablaVigenere(char** tabla) {
    for (int i = 0; i < 26; i++) {
        delete[] tabla[i];
    }
    delete[] tabla;
}

char** tablaVigenere() {
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
    // Exportar la tabla al archivo de texto
    std::ofstream archivo("tabla_vigenere.txt");

    if (archivo.is_open()) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 25; j++) { // 25 en lugar de 26 para omitir la última columna
                archivo << tabla[i][j] << " ";
            }
            archivo << "\n"; // Nueva línea después de cada fila
        }
        archivo.close();
        std::cout << "Tabla de Vigenère generada y exportada exitosamente a tabla_vigenere.txt" << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
    }
}