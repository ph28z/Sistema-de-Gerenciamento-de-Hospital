#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib> // Para system()
#include <limits>  // Para numeric_limits

using namespace std;

// Limpa o console
inline void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa a execução para o usuário ler a mensagem
inline void pausar() {
    cout << "\n\n[Pressione ENTER para continuar...]";
    // Garante que o buffer esteja limpo antes de esperar o enter
    if (cin.rdbuf()->in_avail() > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
}

#endif // UTILS_H