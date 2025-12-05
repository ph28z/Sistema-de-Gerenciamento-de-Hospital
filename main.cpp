#include "include/Sistema.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Sistema sistema;
        sistema.iniciar();
    } catch (const exception& e) {
        cerr << "ERRO: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
