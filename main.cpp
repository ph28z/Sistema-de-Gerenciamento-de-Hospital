#include <iostream>
#include "include/Paciente.h"
#include "include/Medico.h"
#include "include/Sistema.h"

using namespace std;

// --- Testes Anteriores (Mantidos) ---

void testarPaciente() {
    cout << "\n===== TESTANDO CLASSE PACIENTE =====" << endl;
    Paciente p1("Joao Silva", "Rua A, 123", "(16) 99999-1111", 35);
    p1.adicionarConsulta(101);
    p1.exibirResumo();
    p1.imprimirDados();
}

void testarMedico() {
    cout << "\n\n===== TESTANDO CLASSE MEDICO =====" << endl;
    Medico m1("Dr. Carlos Mendes", "Av. Central, 100", "(16) 3333-4444", "Cardiologia", "CRM-SP 123456");
    m1.adicionarConsulta(101);
    m1.exibirResumo();
    m1.imprimirDados();
}

void testarPolimorfismo() {
    cout << "\n\n===== TESTANDO POLIMORFISMO =====" << endl;
    Pessoa* pessoas[2];
    pessoas[0] = new Paciente("Paciente Teste", "End 1", "Tel 1", 30);
    pessoas[1] = new Medico("Medico Teste", "End 2", "Tel 2", "Clínica", "CRM 000");

    for (int i = 0; i < 2; i++) {
        pessoas[i]->imprimirDados();
        cout << endl;
    }

    for (int i = 0; i < 2; i++) delete pessoas[i];
}

// --- NOVO TESTE: PRONTUÁRIO (COMPOSIÇÃO) ---

void testarProntuario() {
    cout << "\n\n===== TESTANDO PRONTUARIO (COMPOSICAO) =====" << endl;

    // 1. Instanciação do Paciente
    // O Prontuário é criado automaticamente dentro dele (construtor padrão do Prontuario)
    cout << "Criando paciente Lucas..." << endl;
    Paciente p("Lucas Silva", "Rua das Flores, 123", "(11) 98888-7777", 25);

    // 2. Adicionando Registros Médicos
    // Note que não acessamos o prontuário diretamente, usamos o método do Paciente (Encapsulamento)
    cout << "Adicionando registros ao prontuario..." << endl;

    p.adicionarRegistroMedico(
        "10/01/2025",
        "Dr. Carlos Mendes",
        "Paciente queixa-se de dores de cabeca frequentes.",
        "Dipirona 500mg de 6/6h se houver dor."
    );

    p.adicionarRegistroMedico(
        "15/02/2025",
        "Dra. Ana Paula",
        "Retorno. Paciente relata melhora significativa.",
        "Manter observacao."
    );

    // 3. Visualização
    // O Paciente delega a impressão para o objeto Prontuario interno
    cout << "\n--- Visualizando Prontuario Completo ---" << endl;
    p.visualizarProntuario();

    // 4. Teste de Ciclo de Vida (Composição)
    cout << "\n[INFO] Ao final desta funcao, o objeto 'p' (Paciente) sera destruido." << endl;
    cout << "[INFO] Como a relacao e de COMPOSICAO, o Prontuario sera destruido junto." << endl;
}

// --- MAIN PRINCIPAL ---

int main() {
    // O construtor do Sistema já carrega os dados
    Sistema sistema;

    // Inicia o loop do menu
    sistema.iniciar();

    // O destrutor do Sistema salvará os dados ao sair
    return 0;
}