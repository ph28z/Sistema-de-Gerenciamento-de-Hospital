#ifndef SISTEMAHOSPITALAR_REGISTRO_H
#define SISTEMAHOSPITALAR_REGISTRO_H

#include <string>
#include <iostream>

using namespace std;

class Registro {
private:
    string data;
    string nomeMedico; // Guardamos o nome para histórico
    string descricao;
    string prescricao;

public:
    // Construtor
    Registro(const string& data, const string& nomeMedico, const string& descricao, const string& prescricao = "");

    void imprimir() const;

    // Getters para futura persistência em arquivo
    string getData() const;
    string getMedico() const;
    string getDescricao() const;
    string getPrescricao() const;
};

#endif //SISTEMAHOSPITALAR_REGISTRO_H