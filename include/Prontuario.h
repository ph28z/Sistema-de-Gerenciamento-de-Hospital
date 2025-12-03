#ifndef SISTEMAHOSPITALAR_PRONTUARIO_H
#define SISTEMAHOSPITALAR_PRONTUARIO_H

#include <vector>
#include "Registro.h"

using namespace std;

//Esta classe gerencia a lista de registros.
class Prontuario {
private:
    vector<Registro> registros;

public:
    // Não precisamos de construtor complexo, o vetor inicia vazio
    Prontuario() = default;

    void adicionarRegistro(const string& data, const string& nomeMedico, const string& descricao, const string& prescricao = "");

    void exibirHistorico() const;
};

#endif //SISTEMAHOSPITALAR_PRONTUARIO_H