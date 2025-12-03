#include "../include/Paciente.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Inicialização da variável estática
int Paciente::proximoID = 1;

// Construtor
Paciente::Paciente(const string& nome, const string& endereco, const string& telefone, int idade)
    : Pessoa(nome, endereco, telefone), idade(idade) {
    this->id = proximoID++;
}

// Destrutor
Paciente::~Paciente() {
    consultasAgendadas.clear();
}

// Getters
int Paciente::getId() const {
    return id;
}

int Paciente::getIdade() const {
    return idade;
}

int Paciente::getNumConsultas() const {
    return consultasAgendadas.size();
}

// Setter
void Paciente::setIdade(int i) {
    if (i > 0) {
        idade = i;
    }
}

// Gerenciamento de consultas
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

// Implementação do método virtual puro de Pessoa
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
            cout << consultasAgendadas[i];
            if (i < consultasAgendadas.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    cout << "=======================================" << endl;
}

// Método adicional para exibir resumo em lista
void Paciente::exibirResumo() const {
    cout << "ID: " << id 
         << " | Nome: " << getNome() 
         << " | Idade: " << idade 
         << " | Consultas: " << consultasAgendadas.size() << endl;
}

// Novos métodos do Prontuário
void Paciente::adicionarRegistroMedico(const string& data, const string& medico, const string& descricao, const string& prescricao) {
    prontuario.adicionarRegistro(data, medico, descricao, prescricao);
}

void Paciente::visualizarProntuario() const {
    cout << "Prontuario do Paciente: " << getNome() << endl;
    prontuario.exibirHistorico();
}
