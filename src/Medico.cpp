#include "../include/Medico.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Inicialização da variável estática
int Medico::proximoID = 1;

// Construtor
Medico::Medico(const string& nome, const string& endereco, const string& telefone,
               const string& especialidade, const string& crm)
    : Pessoa(nome, endereco, telefone), especialidade(especialidade), crm(crm) {
    this->id = proximoID++;
}

// Destrutor
Medico::~Medico() {
    consultasAgendadas.clear();
}

// Getters
int Medico::getId() const {
    return id;
}

string Medico::getEspecialidade() const {
    return especialidade;
}

string Medico::getCrm() const {
    return crm;
}

int Medico::getNumConsultas() const {
    return consultasAgendadas.size();
}

// Setters
void Medico::setEspecialidade(const string& esp) {
    if (!esp.empty()) {
        especialidade = esp;
    }
}

void Medico::setCrm(const string& c) {
    if (!c.empty()) {
        crm = c;
    }
}

// Gerenciamento de consultas
void Medico::adicionarConsulta(int idConsulta) {
    consultasAgendadas.push_back(idConsulta);
}

void Medico::removerConsulta(int idConsulta) {
    auto it = find(consultasAgendadas.begin(), consultasAgendadas.end(), idConsulta);
    if (it != consultasAgendadas.end()) {
        consultasAgendadas.erase(it);
    }
}

bool Medico::temConsultasAgendadas() const {
    return !consultasAgendadas.empty();
}

// Implementação do método virtual puro de Pessoa
void Medico::imprimirDados() const {
    cout << "========== DADOS DO MEDICO ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "CRM: " << crm << endl;
    cout << "Especialidade: " << especialidade << endl;
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
    cout << "=====================================" << endl;
}

// Método adicional para exibir resumo em lista
void Medico::exibirResumo() const {
    cout << "ID: " << id 
         << " | Nome: " << getNome() 
         << " | CRM: " << crm 
         << " | Especialidade: " << especialidade 
         << " | Consultas: " << consultasAgendadas.size() << endl;
}

void Medico::setId(int i) {
    id = i;
}

void Medico::atualizarUltimoID(int id) {
    if (id >= proximoID) {
        proximoID = id + 1;
    }
}
