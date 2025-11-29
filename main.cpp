#include <iostream>
#include "include/Paciente.h"
#include "include/Medico.h"

using namespace std;

void testarPaciente() {
    cout << "\n===== TESTANDO CLASSE PACIENTE =====" << endl;
    
    // Criar pacientes
    Paciente p1("João Silva", "Rua A, 123", "(16) 99999-1111", 35);
    Paciente p2("Maria Santos", "Rua B, 456", "(16) 99999-2222", 28);
    Paciente p3("Pedro Costa", "Rua C, 789", "(16) 99999-3333", 42);
    
    // Adicionar consultas
    p1.adicionarConsulta(101);
    p1.adicionarConsulta(102);
    p2.adicionarConsulta(103);
    
    // Exibir resumo
    cout << "\n--- Lista de Pacientes ---" << endl;
    p1.exibirResumo();
    p2.exibirResumo();
    p3.exibirResumo();
    
    // Exibir dados completos
    cout << "\n--- Dados Completos do Paciente 1 ---" << endl;
    p1.imprimirDados();
    
    // Testar edição
    cout << "\n--- Editando dados do Paciente 2 ---" << endl;
    p2.setNome("Maria Santos Oliveira");
    p2.setIdade(29);
    p2.imprimirDados();
    
    // Testar remoção de consulta
    cout << "\n--- Removendo consulta do Paciente 1 ---" << endl;
    p1.removerConsulta(101);
    p1.imprimirDados();
    
    // Verificar se tem consultas
    cout << "\n--- Verificando consultas ---" << endl;
    cout << "Paciente 1 tem consultas? " << (p1.temConsultasAgendadas() ? "Sim" : "Não") << endl;
    cout << "Paciente 3 tem consultas? " << (p3.temConsultasAgendadas() ? "Sim" : "Não") << endl;
}

void testarMedico() {
    cout << "\n\n===== TESTANDO CLASSE MEDICO =====" << endl;
    
    // Criar médicos
    Medico m1("Dr. Carlos Mendes", "Av. Central, 100", "(16) 3333-4444", "Cardiologia", "CRM-SP 123456");
    Medico m2("Dra. Ana Paula", "Av. Principal, 200", "(16) 3333-5555", "Pediatria", "CRM-SP 789012");
    Medico m3("Dr. Roberto Lima", "Av. Norte, 300", "(16) 3333-6666", "Ortopedia", "CRM-SP 345678");
    
    // Adicionar consultas
    m1.adicionarConsulta(101);
    m1.adicionarConsulta(102);
    m1.adicionarConsulta(103);
    m2.adicionarConsulta(104);
    
    // Exibir resumo
    cout << "\n--- Lista de Médicos ---" << endl;
    m1.exibirResumo();
    m2.exibirResumo();
    m3.exibirResumo();
    
    // Exibir dados completos
    cout << "\n--- Dados Completos do Médico 1 ---" << endl;
    m1.imprimirDados();
    
    // Testar edição
    cout << "\n--- Editando dados do Médico 2 ---" << endl;
    m2.setEspecialidade("Pediatria e Neonatologia");
    m2.setTelefone("(16) 3333-7777");
    m2.imprimirDados();
    
    // Testar remoção de consulta
    cout << "\n--- Removendo consulta do Médico 1 ---" << endl;
    m1.removerConsulta(102);
    m1.imprimirDados();
}

void testarPolimorfismo() {
    cout << "\n\n===== TESTANDO POLIMORFISMO =====" << endl;
    
    // Criar vetor de ponteiros para Pessoa
    Pessoa* pessoas[4];
    
    pessoas[0] = new Paciente("Teste Paciente 1", "End 1", "Tel 1", 30);
    pessoas[1] = new Medico("Teste Medico 1", "End 2", "Tel 2", "Clínica Geral", "CRM 111");
    pessoas[2] = new Paciente("Teste Paciente 2", "End 3", "Tel 3", 25);
    pessoas[3] = new Medico("Teste Medico 2", "End 4", "Tel 4", "Dermatologia", "CRM 222");
    
    cout << "\n--- Imprimindo dados usando polimorfismo ---" << endl;
    for (int i = 0; i < 4; i++) {
        pessoas[i]->imprimirDados();
        cout << endl;
    }
    
    // Liberar memória
    for (int i = 0; i < 4; i++) {
        delete pessoas[i];
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "   SISTEMA HOSPITALAR - TESTE         " << endl;
    cout << "========================================" << endl;
    
    // Executar testes
    testarPaciente();
    testarMedico();
    testarPolimorfismo();
    
    cout << "\n========================================" << endl;
    cout << "   TESTES CONCLUÍDOS COM SUCESSO!     " << endl;
    cout << "========================================" << endl;
    
    return 0;
}
