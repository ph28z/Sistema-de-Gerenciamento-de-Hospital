#include "../include/Prontuario.h"
#include <iostream>

void Prontuario::adicionarRegistro(const string& data, const string& nomeMedico, const string& descricao, const string& prescricao) {
    // Cria um objeto Registro anônimo e o adiciona ao vetor
    registros.emplace_back(data, nomeMedico, descricao, prescricao);
}

void Prontuario::exibirHistorico() const {
    if (registros.empty()) {
        cout << "Nenhum registro medico encontrado." << endl;
        return;
    }

    cout << "\n=== HISTORICO MEDICO ===" << endl;
    for (const auto& reg : registros) {
        reg.imprimir();
    }
    cout << "========================" << endl;
}