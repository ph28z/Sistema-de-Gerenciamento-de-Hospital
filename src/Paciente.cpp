#include "../include/Paciente.h"
#include <iostream>
#include <algorithm>

using namespace std;

int Paciente::proximoID = 1;

Paciente::Paciente(const string& nome, const string& endereco, const string& telefone, int idade)
    : Pessoa(nome, endereco, telefone), idade(idade) {
    this->id = proximoID++;
}

Paciente::~Paciente() {
    consultasAgendadas.clear();
}

int Paciente::getId() const { return id; }
int Paciente::getIdade() const { return idade; }
int Paciente::getNumConsultas() const { return consultasAgendadas.size(); }

void Paciente::setIdade(int i) {
    if (i > 0) idade = i;
}

void Paciente::adicionarConsulta(int idConsulta) {
    consultasAgendadas.push_back(idConsulta);
}

void Paciente::removerConsulta(int idConsulta) {
    auto it = find(consultasAgendadas.begin(), consultasAgendadas.end(), idConsulta);
    if (it != consultasAgendadas.end()) {
        consultasAgendadas.erase(it);
    }
}

bool Paciente::temConsultasAgendadas() const {
    return !consultasAgendadas.empty();
}

void Paciente::imprimirDados() const {
    cout << "========== DADOS DO PACIENTE ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "Idade: " << idade << " anos" << endl;
    cout << "Endereco: " << getEndereco() << endl;
    cout << "Telefone: " << getTelefone() << endl;
    cout << "Consultas agendadas: " << consultasAgendadas.size() << endl;

    if (!consultasAgendadas.empty()) {
        cout << "IDs das consultas: ";
        for (size_t i = 0; i < consultasAgendadas.size(); i++) {
            cout << consultasAgendadas[i] << (i < consultasAgendadas.size() - 1 ? ", " : "");
        }
        cout << endl;
    }
    cout << "=======================================" << endl;
}

void Paciente::exibirResumo() const {
    cout << "ID: " << id << " | Nome: " << getNome() << " | Idade: " << idade << endl;
}

void Paciente::adicionarRegistroMedico(const string& data, const string& medico, const string& descricao, const string& prescricao) {
    prontuario.adicionarRegistro(data, medico, descricao, prescricao);
}

void Paciente::visualizarProntuario() const {
    cout << "Prontuario do Paciente: " << getNome() << endl;
    prontuario.exibirHistorico();
}

void Paciente::setId(int i) { id = i; }

void Paciente::atualizarUltimoID(int id) {
    if (id >= proximoID) proximoID = id + 1;
}

const Prontuario& Paciente::getProntuario() const {
    return prontuario;
}

Prontuario& Paciente::getProntuarioModificavel() {
    return prontuario;
}