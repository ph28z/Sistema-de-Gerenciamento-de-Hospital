#include "../include/Registro.h"

Registro::Registro(const string& data, const string& nomeMedico, const string& descricao, const string& prescricao)
    : data(data), nomeMedico(nomeMedico), descricao(descricao), prescricao(prescricao) {}

void Registro::imprimir() const {
    cout << "Data: " << data << " | Medico: " << nomeMedico << endl;
    cout << "Descricao: " << descricao << endl;
    if (!prescricao.empty()) {
        cout << "Prescricao: " << prescricao << endl;
    }
    cout << "-----------------------------------" << endl;
}

string Registro::getData() const { return data; }
string Registro::getMedico() const { return nomeMedico; }
string Registro::getDescricao() const { return descricao; }
string Registro::getPrescricao() const { return prescricao; }