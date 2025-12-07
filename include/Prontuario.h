#ifndef SISTEMAHOSPITALAR_PRONTUARIO_H
#define SISTEMAHOSPITALAR_PRONTUARIO_H

#include <vector>
#include "Registro.h"

using namespace std;

class Prontuario {
private:
    vector<Registro> registros;

public:
    Prontuario() = default;

    void adicionarRegistro(const string& data, const string& nomeMedico, const string& descricao, const string& prescricao = "");
    void exibirHistorico() const;


    const vector<Registro>& getRegistros() const { return registros; }
};

#endif //SISTEMAHOSPITALAR_PRONTUARIO_H