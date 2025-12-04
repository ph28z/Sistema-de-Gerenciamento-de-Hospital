
#include "../include/Consulta.h"
#include "../include/ExcecaoConsulta.h"
#include <sstream>
#include <iomanip>

// Inicialização da variável estática
int Consulta::proximoID = 1;

// Construtor
Consulta::Consulta(Paciente* pac, Medico* med, const string& data, 
                   const string& hora, int duracao)
    : paciente(pac), medico(med), data(data), hora(hora), 
      duracao(duracao), status("Agendada") {
    
    // Validações com tratamento de exceção
    if (!validarData(data)) {
        throw ExcecaoConsulta("Data invalida: " + data, ExcecaoConsulta::DATA_INVALIDA);
    }
    
    if (!validarHora(hora)) {
        throw ExcecaoConsulta("Hora invalida: " + hora, ExcecaoConsulta::HORA_INVALIDA);
    }
    
    if (pac == nullptr) {
        throw ExcecaoConsulta("Paciente inexistente", ExcecaoConsulta::PACIENTE_INEXISTENTE);
    }
    
    if (med == nullptr) {
        throw ExcecaoConsulta("Medico inexistente", ExcecaoConsulta::MEDICO_INEXISTENTE);
    }
    
    this->id = proximoID++;
    
    // Adiciona a consulta nas listas do paciente e médico
    paciente->adicionarConsulta(this->id);
    medico->adicionarConsulta(this->id);
}

// Destrutor
Consulta::~Consulta() {
    // Remove a consulta das listas (se ainda existirem)
    if (paciente != nullptr) {
        paciente->removerConsulta(this->id);
    }
    if (medico != nullptr) {
        medico->removerConsulta(this->id);
    }
}

// Setters com validação
void Consulta::setData(const string& d) {
    if (!validarData(d)) {
        throw ExcecaoConsulta("Data invalida: " + d, ExcecaoConsulta::DATA_INVALIDA);
    }
    data = d;
}

void Consulta::setHora(const string& h) {
    if (!validarHora(h)) {
        throw ExcecaoConsulta("Hora invalida: " + h, ExcecaoConsulta::HORA_INVALIDA);
    }
    hora = h;
}

// Método virtual
void Consulta::imprimirDetalhes() const {
    cout << "\n========== DETALHES DA CONSULTA ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Tipo: " << getTipo() << endl;
    cout << "Data: " << data << " - Hora: " << hora << endl;
    cout << "Duracao: " << duracao << " minutos" << endl;
    cout << "Status: " << status << endl;
    cout << "Prioridade: " << getPrioridade() << endl;
    cout << "Valor: R$ " << fixed << setprecision(2) << calcularValor() << endl;
    cout << "\nPaciente: " << paciente->getNome() << " (ID: " << paciente->getId() << ")" << endl;
    cout << "Medico: " << medico->getNome() << " (CRM: " << medico->getCrm() << ")" << endl;
    cout << "==========================================" << endl;
}

void Consulta::exibirResumo() const {
    cout << "ID: " << setw(3) << id 
         << " | " << setw(15) << left << getTipo()
         << " | Data: " << data 
         << " | Hora: " << hora
         << " | Paciente: " << setw(20) << left << paciente->getNome()
         << " | Medico: " << setw(20) << left << medico->getNome()
         << " | Status: " << status << endl;
}

bool Consulta::validarData(const string& data) {
    if (data.length() != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    
    try {
        int dia = stoi(data.substr(0, 2));
        int mes = stoi(data.substr(3, 2));
        int ano = stoi(data.substr(6, 4));
        
        if (mes < 1 || mes > 12) return false;
        if (dia < 1 || dia > 31) return false;
        if (ano < 2024 || ano > 2100) return false;
        
        if (mes == 2 && dia > 29) return false;
        if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

bool Consulta::validarHora(const string& hora) {
    if (hora.length() != 5) return false;
    if (hora[2] != ':') return false;
    
    try {
        int hh = stoi(hora.substr(0, 2));
        int mm = stoi(hora.substr(3, 2));
        
        if (hh < 0 || hh > 23) return false;
        if (mm < 0 || mm > 59) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

void Consulta::atualizarUltimoID(int id) {
    if (id >= proximoID) {
        proximoID = id + 1;
    }
}


void ConsultaNormal::imprimirDetalhes() const {
    Consulta::imprimirDetalhes(); 
    
    if (!motivoConsulta.empty()) {
        cout << "\nMotivo da Consulta: " << motivoConsulta << endl;
    }
    cout << "==========================================" << endl;
}

void Emergencia::imprimirDetalhes() const {
    Consulta::imprimirDetalhes();
    
    cout << "\n*** EMERGENCIA ***" << endl;
    cout << "Nivel de Gravidade: " << nivelGravidade << "/5";
    
    string nivelTexto;
    switch(nivelGravidade) {
        case 1: nivelTexto = "Muito Baixo"; break;
        case 2: nivelTexto = "Baixo"; break;
        case 3: nivelTexto = "Medio"; break;
        case 4: nivelTexto = "Alto"; break;
        case 5: nivelTexto = "CRITICO"; break;
        default: nivelTexto = "Indefinido";
    }
    cout << " (" << nivelTexto << ")" << endl;
    
    if (!descricaoEmergencia.empty()) {
        cout << "Descricao: " << descricaoEmergencia << endl;
    }
    cout << "==========================================" << endl;
}

void Retorno::imprimirDetalhes() const {
    Consulta::imprimirDetalhes(); 
    
    cout << "\n*** CONSULTA DE RETORNO ***" << endl;
    cout << "ID da Consulta Original: " << idConsultaOriginal << endl;
    cout << "Desconto Aplicado: 50%" << endl;
    
    if (!observacoes.empty()) {
        cout << "Observacoes: " << observacoes << endl;
    }
    cout << "==========================================" << endl;
}
