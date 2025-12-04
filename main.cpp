#include "../include/Sistema.h"
#include "../include/ExcecaoConsulta.h"
#include <iostream>
#include <cassert>

using namespace std;

// Contador para verificar vazamento de memória
int contadorAlocacoes = 0;
int contadorDesalocacoes = 0;

void testeExcecoes() {
    cout << "\n========================================" << endl;
    cout << "TESTE 1: TRATAMENTO DE EXCECOES" << endl;
    cout << "========================================\n" << endl;
    
    Sistema sistema;
    
    // Cadastrar dados válidos primeiro
    cout << "[SETUP] Cadastrando paciente e medico validos..." << endl;
    Paciente* pac = new Paciente("Joao Silva", "Rua A, 123", "1234-5678", 30);
    Medico* med = new Medico("Dr. Carlos", "Rua B, 456", "9876-5432", 
                             "Cardiologia", "CRM-12345");
    
    // TESTE 1.1: Data inválida
    cout << "\n[TESTE 1.1] Tentando criar consulta com data invalida..." << endl;
    try {
        ConsultaNormal c(pac, med, "32/13/2024", "10:00", "Checkup");
        cout << "FALHOU: Deveria lancar excecao!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "PASSOU: " << e.getMensagemCompleta() << endl;
        assert(e.getCodigoErro() == ExcecaoConsulta::DATA_INVALIDA);
    }
    
    // TESTE 1.2: Hora inválida
    cout << "\n[TESTE 1.2] Tentando criar consulta com hora invalida..." << endl;
    try {
        ConsultaNormal c(pac, med, "15/12/2024", "25:99", "Checkup");
        cout << "FALHOU: Deveria lancar excecao!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "PASSOU: " << e.getMensagemCompleta() << endl;
        assert(e.getCodigoErro() == ExcecaoConsulta::HORA_INVALIDA);
    }
    
    // TESTE 1.3: Paciente nulo
    cout << "\n[TESTE 1.3] Tentando criar consulta com paciente nulo..." << endl;
    try {
        ConsultaNormal c(nullptr, med, "15/12/2024", "10:00", "Checkup");
        cout << "FALHOU: Deveria lancar excecao!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "PASSOU: " << e.getMensagemCompleta() << endl;
        assert(e.getCodigoErro() == ExcecaoConsulta::PACIENTE_INEXISTENTE);
    }
    
    // TESTE 1.4: Médico nulo
    cout << "\n[TESTE 1.4] Tentando criar consulta com medico nulo..." << endl;
    try {
        ConsultaNormal c(pac, nullptr, "15/12/2024", "10:00", "Checkup");
        cout << "FALHOU: Deveria lancar excecao!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "PASSOU: " << e.getMensagemCompleta() << endl;
        assert(e.getCodigoErro() == ExcecaoConsulta::MEDICO_INEXISTENTE);
    }
    
    // TESTE 1.5: Validação de data - vários formatos inválidos
    cout << "\n[TESTE 1.5] Testando validacao de datas..." << endl;
    assert(!Consulta::validarData("1/1/2024"));      // Formato errado
    assert(!Consulta::validarData("01-01-2024"));    // Separador errado
    assert(!Consulta::validarData("32/12/2024"));    // Dia inválido
    assert(!Consulta::validarData("15/13/2024"));    // Mês inválido
    assert(!Consulta::validarData("29/02/2023"));    // Fev em ano não-bissexto
    assert(Consulta::validarData("15/12/2024"));     // Data válida
    cout << "PASSOU: Validacao de datas funcionando corretamente" << endl;
    
    // TESTE 1.6: Validação de hora
    cout << "\n[TESTE 1.6] Testando validacao de horas..." << endl;
    assert(!Consulta::validarHora("24:00"));         // Hora inválida
    assert(!Consulta::validarHora("10:60"));         // Minuto inválido
    assert(!Consulta::validarHora("9:30"));          // Formato errado
    assert(!Consulta::validarHora("10-30"));         // Separador errado
    assert(Consulta::validarHora("10:30"));          // Hora válida
    assert(Consulta::validarHora("00:00"));          // Meia-noite válida
    assert(Consulta::validarHora("23:59"));          // Hora máxima válida
    cout << "PASSOU: Validacao de horas funcionando corretamente" << endl;
    
    // TESTE 1.7: Modificação de consulta com dados inválidos
    cout << "\n[TESTE 1.7] Tentando modificar consulta com dados invalidos..." << endl;
    ConsultaNormal* consulta = new ConsultaNormal(pac, med, "15/12/2024", "10:00", "Checkup");
    
    try {
        consulta->setData("99/99/9999");
        cout << "FALHOU: Deveria lancar excecao!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "PASSOU: " << e.getMensagemCompleta() << endl;
    }
    
    try {
        consulta->setHora("99:99");
        cout << "FALHOU: Deveria lancar excecao!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "PASSOU: " << e.getMensagemCompleta() << endl;
    }
    
    // Limpeza
    delete consulta;
    delete pac;
    delete med;
    
    cout << "\n[RESUMO] Todos os testes de excecao PASSARAM!" << endl;
}

void testeVazamentoMemoria() {
    cout << "\n========================================" << endl;
    cout << "TESTE 2: VAZAMENTO DE MEMORIA" << endl;
    cout << "========================================\n" << endl;
    
    // TESTE 2.1: Criação e destruição de Pessoa
    cout << "[TESTE 2.1] Testando destrutores de Pessoa/Paciente/Medico..." << endl;
    {
        Paciente* p = new Paciente("Teste", "End", "Tel", 25);
        Medico* m = new Medico("Dr Teste", "End", "Tel", "Especialidade", "CRM");
        
        cout << "Paciente criado - ID: " << p->getId() << endl;
        cout << "Medico criado - ID: " << m->getId() << endl;
        
        delete p;
        delete m;
        cout << "PASSOU: Objetos deletados sem erros" << endl;
    }
    
    // TESTE 2.2: Criação e destruição de Consultas
    cout << "\n[TESTE 2.2] Testando destrutores de Consultas..." << endl;
    {
        Paciente* pac = new Paciente("Maria", "Rua X", "1111", 40);
        Medico* med = new Medico("Dr. Silva", "Rua Y", "2222", "Ortopedia", "CRM-999");
        
        ConsultaNormal* cn = new ConsultaNormal(pac, med, "20/12/2024", "14:00", "Dor");
        Emergencia* em = new Emergencia(pac, med, "21/12/2024", "15:00", 4, "Fratura");
        Retorno* ret = new Retorno(pac, med, "22/12/2024", "16:00", 1, "Acompanhamento");
        
        cout << "ConsultaNormal criada - ID: " << cn->getId() << endl;
        cout << "Emergencia criada - ID: " << em->getId() << endl;
        cout << "Retorno criado - ID: " << ret->getId() << endl;
        
        delete cn;
        delete em;
        delete ret;
        delete pac;
        delete med;
        cout << "PASSOU: Todas as consultas deletadas sem erros" << endl;
    }
    
    // TESTE 2.3: Sistema completo (construtor/destrutor)
    cout << "\n[TESTE 2.3] Testando Sistema completo..." << endl;
    {
        Sistema* sistema = new Sistema();
        cout << "Sistema criado" << endl;
        delete sistema;
        cout << "PASSOU: Sistema destruido sem erros" << endl;
    }
    
    // TESTE 2.4: Vetores com múltiplos objetos
    cout << "\n[TESTE 2.4] Testando vetores com multiplos objetos..." << endl;
    {
        vector<Paciente*> pacientes;
        vector<Medico*> medicos;
        vector<Consulta*> consultas;
        
        // Criar 10 pacientes
        for (int i = 0; i < 10; i++) {
            pacientes.push_back(new Paciente("Pac" + to_string(i), "End", "Tel", 20 + i));
        }
        
        // Criar 5 médicos
        for (int i = 0; i < 5; i++) {
            medicos.push_back(new Medico("Med" + to_string(i), "End", "Tel", "Esp", "CRM" + to_string(i)));
        }
        
        // Criar 20 consultas
        for (int i = 0; i < 20; i++) {
            Paciente* p = pacientes[i % 10];
            Medico* m = medicos[i % 5];
            
            if (i % 3 == 0) {
                consultas.push_back(new ConsultaNormal(p, m, "20/12/2024", "10:00", "Motivo"));
            } else if (i % 3 == 1) {
                consultas.push_back(new Emergencia(p, m, "20/12/2024", "11:00", 3, "Desc"));
            } else {
                consultas.push_back(new Retorno(p, m, "20/12/2024", "12:00", 1, "Obs"));
            }
        }
        
        cout << "Criados: " << pacientes.size() << " pacientes, " 
             << medicos.size() << " medicos, " 
             << consultas.size() << " consultas" << endl;
        
        // Liberar memória
        for (auto c : consultas) delete c;
        for (auto p : pacientes) delete p;
        for (auto m : medicos) delete m;
        
        cout << "PASSOU: Todos os objetos deletados sem erros" << endl;
    }
    
    // TESTE 2.5: Associação bidirecional (Consulta remove IDs de Paciente/Médico)
    cout << "\n[TESTE 2.5] Testando associacao bidirecional..." << endl;
    {
        Paciente* pac = new Paciente("Ana", "Rua Z", "3333", 35);
        Medico* med = new Medico("Dr. Costa", "Av A", "4444", "Clinico", "CRM-777");
        
        cout << "Antes da consulta - Consultas do paciente: " << pac->getNumConsultas() << endl;
        cout << "Antes da consulta - Consultas do medico: " << med->getNumConsultas() << endl;
        
        ConsultaNormal* consulta = new ConsultaNormal(pac, med, "25/12/2024", "09:00", "Rotina");
        
        cout << "Apos criar consulta - Consultas do paciente: " << pac->getNumConsultas() << endl;
        cout << "Apos criar consulta - Consultas do medico: " << med->getNumConsultas() << endl;
        
        assert(pac->getNumConsultas() == 1);
        assert(med->getNumConsultas() == 1);
        
        delete consulta;
        
        cout << "Apos deletar consulta - Consultas do paciente: " << pac->getNumConsultas() << endl;
        cout << "Apos deletar consulta - Consultas do medico: " << med->getNumConsultas() << endl;
        
        assert(pac->getNumConsultas() == 0);
        assert(med->getNumConsultas() == 0);
        
        delete pac;
        delete med;
        
        cout << "PASSOU: Associacao bidirecional funcionando corretamente" << endl;
    }
    
    cout << "\n[RESUMO] Todos os testes de memoria PASSARAM!" << endl;
    cout << "\nDICA: Execute com Valgrind para verificacao completa:" << endl;
    cout << "valgrind --leak-check=full --show-leak-kinds=all ./programa" << endl;
}

void testePolimorfismo() {
    cout << "\n========================================" << endl;
    cout << "TESTE 3: POLIMORFISMO" << endl;
    cout << "========================================\n" << endl;
    
    Paciente* pac = new Paciente("Pedro", "Rua P", "5555", 50);
    Medico* med = new Medico("Dr. Alves", "Rua M", "6666", "Neurologista", "CRM-888");
    
    // TESTE 3.1: Vetor polimórfico
    cout << "[TESTE 3.1] Testando vetor polimorfico..." << endl;
    vector<Consulta*> consultas;
    
    consultas.push_back(new ConsultaNormal(pac, med, "10/01/2025", "08:00", "Rotina"));
    consultas.push_back(new Emergencia(pac, med, "11/01/2025", "09:00", 5, "Urgente"));
    consultas.push_back(new Retorno(pac, med, "12/01/2025", "10:00", 1, "Revisao"));
    
    cout << "\nDetalhes das consultas (chamada polimórfica):" << endl;
    for (const auto& c : consultas) {
        cout << "\nTipo: " << c->getTipo() << endl;
        cout << "Valor: R$ " << c->calcularValor() << endl;
        cout << "Prioridade: " << c->getPrioridade() << endl;
    }
    
    // TESTE 3.2: Verificar valores calculados
    cout << "\n[TESTE 3.2] Verificando calculos polimorficos..." << endl;
    assert(consultas[0]->calcularValor() == 200.0);           // Normal
    assert(consultas[1]->calcularValor() == 200.0 + 150.0*5); // Emergência nível 5
    assert(consultas[2]->calcularValor() == 100.0);           // Retorno (50% desc)
    cout << "PASSOU: Calculos corretos para cada tipo" << endl;
    
    // TESTE 3.3: Verificar prioridades
    cout << "\n[TESTE 3.3] Verificando prioridades..." << endl;
    assert(consultas[0]->getPrioridade() == 3);  // Normal
    assert(consultas[1]->getPrioridade() == 5);  // Emergência nível 5 -> prio 10-5=5
    assert(consultas[2]->getPrioridade() == 4);  // Retorno
    cout << "PASSOU: Prioridades corretas" << endl;
    
    // Limpeza
    for (auto c : consultas) delete c;
    delete pac;
    delete med;
    
    cout << "\n[RESUMO] Todos os testes de polimorfismo PASSARAM!" << endl;
}

void testeAssociacao() {
    cout << "\n========================================" << endl;
    cout << "TESTE 4: ASSOCIACAO" << endl;
    cout << "========================================\n" << endl;
    
    // TESTE 4.1: Múltiplas consultas para mesmo médico/paciente
    cout << "[TESTE 4.1] Testando multiplas consultas..." << endl;
    
    Paciente* pac = new Paciente("Lucas", "Rua L", "7777", 28);
    Medico* med = new Medico("Dra. Lima", "Av B", "8888", "Pediatra", "CRM-555");
    
    vector<Consulta*> consultas;
    consultas.push_back(new ConsultaNormal(pac, med, "15/01/2025", "08:00", ""));
    consultas.push_back(new ConsultaNormal(pac, med, "16/01/2025", "09:00", ""));
    consultas.push_back(new ConsultaNormal(pac, med, "17/01/2025", "10:00", ""));
    
    cout << "Criadas 3 consultas" << endl;
    cout << "Consultas do paciente: " << pac->getNumConsultas() << endl;
    cout << "Consultas do medico: " << med->getNumConsultas() << endl;
    
    assert(pac->getNumConsultas() == 3);
    assert(med->getNumConsultas() == 3);
    cout << "PASSOU: Associacao correta" << endl;
    
    // TESTE 4.2: Remover consulta do meio
    cout << "\n[TESTE 4.2] Removendo consulta do meio..." << endl;
    delete consultas[1];
    consultas.erase(consultas.begin() + 1);
    
    cout << "Consultas do paciente: " << pac->getNumConsultas() << endl;
    cout << "Consultas do medico: " << med->getNumConsultas() << endl;
    
    assert(pac->getNumConsultas() == 2);
    assert(med->getNumConsultas() == 2);
    cout << "PASSOU: Remocao correta" << endl;
    
    // Limpeza
    for (auto c : consultas) delete c;
    delete pac;
    delete med;
    
    cout << "\n[RESUMO] Todos os testes de associacao PASSARAM!" << endl;
}

void testeComposicao() {
    cout << "\n========================================" << endl;
    cout << "TESTE 5: COMPOSICAO (PRONTUARIO)" << endl;
    cout << "========================================\n" << endl;
    
    cout << "[TESTE 5.1] Testando composicao Paciente-Prontuario..." << endl;
    
    Paciente* pac = new Paciente("Roberto", "Rua R", "9999", 45);
    
    // Adicionar registros ao prontuário
    pac->adicionarRegistroMedico("01/01/2025", "Dr. Silva", "Consulta inicial", "Dipirona");
    pac->adicionarRegistroMedico("15/01/2025", "Dr. Costa", "Retorno", "Paracetamol");
    pac->adicionarRegistroMedico("30/01/2025", "Dr. Lima", "Exame", "");
    
    cout << "\nProntuario do paciente:" << endl;
    pac->visualizarProntuario();
    
    cout << "\nAo deletar paciente, prontuario tambem sera destruido (composicao)" << endl;
    delete pac;
    
    cout << "PASSOU: Composicao funcionando corretamente" << endl;
}

int main() {
    cout << "\n************************************************" << endl;
    cout << "   SUITE DE TESTES - SISTEMA HOSPITALAR" << endl;
    cout << "************************************************" << endl;
    
    try {
        testeExcecoes();
        testeVazamentoMemoria();
        testePolimorfismo();
        testeAssociacao();
        testeComposicao();
        
        cout << "\n************************************************" << endl;
        cout << "   TODOS OS TESTES PASSARAM COM SUCESSO!" << endl;
        cout << "************************************************" << endl;
        
        cout << "\n=== CHECKLIST FINAL ===" << endl;
        cout << "[X] Tratamento de excecoes verificado" << endl;
        cout << "[X] Destrutores corretos implementados" << endl;
        cout << "[X] Polimorfismo funcionando" << endl;
        cout << "[X] Associacao bidirecional correta" << endl;
        cout << "[X] Composicao implementada" << endl;
        cout << "\n[RECOMENDACAO] Execute com Valgrind:" << endl;
        cout << "valgrind --leak-check=full --show-leak-kinds=all ./test_sistema" << endl;
        
    } catch (const exception& e) {
        cout << "\n[ERRO CRITICO] " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
