#include "../include/Sistema.h"
#include "../include/ExcecaoConsulta.h"
#include "../include/Consulta.h"
#include "../include/Utilidades.h" // <--- Inclusão do novo utilitário
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sys/stat.h>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

// --- Função auxiliar para achar o caminho ---
string obterCaminhoData() {
    fs::path caminhoAtual = fs::current_path();
    for (int i = 0; i < 5; ++i) {
        if (fs::exists(caminhoAtual / "CMakeLists.txt")) {
            fs::path caminhoData = caminhoAtual / "data";
            if (!fs::exists(caminhoData)) fs::create_directory(caminhoData);
            return caminhoData.string();
        }
        if (caminhoAtual.has_parent_path()) caminhoAtual = caminhoAtual.parent_path();
        else break;
    }
    if (!fs::exists("data")) fs::create_directory("data");
    return "data";
}

// --- CONSTRUTOR / DESTRUTOR ---
Sistema::Sistema() {
    carregarDados();
    carregarConsultas();
    carregarProntuarios();
}

Sistema::~Sistema() {
    salvarDados();
    salvarConsultas();
    salvarProntuarios();

    for (auto p : pacientes) delete p;
    for (auto m : medicos) delete m;
    for (auto c : consultas) delete c;
    pacientes.clear();
    medicos.clear();
    consultas.clear();
}

// --- MENUS ---
void Sistema::iniciar() {
    int opcao = 0;
    do {
        exibirMenuPrincipal();
        cin >> opcao;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcao = -1;
        } else { cin.ignore(); }

        switch (opcao) {
            case 1: exibirMenuPacientes(); break;
            case 2: exibirMenuMedicos(); break;
            case 3: exibirMenuConsultas(); break;
            case 4: exibirEstatisticas(); break;
            case 0: cout << "\nFinalizando o sistema..." << endl; break;
            default: cout << "Opcao invalida!" << endl; pausar();
        }
    } while (opcao != 0);
}

void Sistema::exibirMenuPrincipal() {
    limparTela(); // <--- Limpeza de tela
    cout << "========================================" << endl;
    cout << "      SISTEMA DE GESTAO HOSPITALAR      " << endl;
    cout << "========================================" << endl;
    cout << "1. Gestao de Pacientes" << endl;
    cout << "2. Gestao de Medicos" << endl;
    cout << "3. Gestao de Consultas" << endl;
    cout << "4. Estatisticas Gerais" << endl;
    cout << "0. Sair" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Escolha uma opcao: ";
}

void Sistema::exibirMenuPacientes() {
    int opcao = 0;
    do {
        limparTela();
        cout << "============ MENU PACIENTES ============" << endl;
        cout << "1. Cadastrar Paciente" << endl;
        cout << "2. Listar Pacientes" << endl;
        cout << "3. Visualizar Detalhes e Prontuario" << endl;
        cout << "4. Editar Paciente" << endl;
        cout << "5. Remover Paciente" << endl;
        cout << "0. Voltar" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Opcao: ";
        cin >> opcao; cin.ignore();

        switch (opcao) {
            case 1: cadastrarPaciente(); pausar(); break;
            case 2: listarPacientes(); pausar(); break;
            case 3: visualizarPaciente(); pausar(); break;
            case 4: editarPaciente(); pausar(); break;
            case 5: removerPaciente(); pausar(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl; pausar();
        }
    } while (opcao != 0);
}

void Sistema::visualizarPaciente() {
    limparTela();
    cout << "--- VISUALIZAR PACIENTE ---" << endl;
    int id;
    cout << "Digite o ID do Paciente: "; cin >> id; cin.ignore();

    Paciente* pac = buscarPacientePorId(id);
    if (!pac) { cout << "Paciente nao encontrado!" << endl; return; }

    pac->imprimirDados();

    cout << "\nDeseja visualizar o prontuario? (S/N): ";
    char opcao; cin >> opcao; cin.ignore();
    if (opcao == 'S' || opcao == 's') {
        cout << endl;
        pac->visualizarProntuario();
    }
}

void Sistema::cadastrarPaciente() {
    limparTela();
    cout << "--- CADASTRO DE PACIENTE ---" << endl;
    string nome, endereco, telefone;
    int idade;

    cout << "Nome: "; getline(cin, nome);
    cout << "Endereco: "; getline(cin, endereco);
    cout << "Telefone: "; getline(cin, telefone);
    cout << "Idade: "; cin >> idade;

    Paciente* p = new Paciente(nome, endereco, telefone, idade);
    pacientes.push_back(p);
    cout << "\n>>> Paciente cadastrado com sucesso! ID: " << p->getId() << endl;
}

void Sistema::listarPacientes() {
    limparTela();
    if (pacientes.empty()) { cout << "Nenhum paciente cadastrado." << endl; return; }
    cout << "--- LISTA DE PACIENTES ---" << endl;
    for (const auto& p : pacientes) p->exibirResumo();
}

void Sistema::editarPaciente() {
    limparTela();
    cout << "--- EDITAR PACIENTE ---" << endl;
    int id;
    cout << "ID do Paciente: "; cin >> id; cin.ignore();
    Paciente* pac = buscarPacientePorId(id);
    if (!pac) { cout << "Paciente nao encontrado!" << endl; return; }

    cout << "O que deseja editar? (1-Nome, 2-Endereco, 3-Telefone, 4-Idade): ";
    int opcao; cin >> opcao; cin.ignore();

    if (opcao == 1) { string n; cout << "Novo nome: "; getline(cin, n); pac->setNome(n); }
    else if (opcao == 2) { string e; cout << "Novo endereco: "; getline(cin, e); pac->setEndereco(e); }
    else if (opcao == 3) { string t; cout << "Novo telefone: "; getline(cin, t); pac->setTelefone(t); }
    else if (opcao == 4) { int i; cout << "Nova idade: "; cin >> i; pac->setIdade(i); }
    else cout << "Opcao invalida!" << endl;

    cout << "Dados atualizados!" << endl;
}

void Sistema::removerPaciente() {
    limparTela();
    cout << "--- REMOVER PACIENTE ---" << endl;
    try {
        int id;
        cout << "ID do Paciente: "; cin >> id;

        Paciente* pac = buscarPacientePorId(id);
        if (!pac) throw ExcecaoConsulta("Paciente nao encontrado!", ExcecaoConsulta::PACIENTE_INEXISTENTE);

        if (pac->temConsultasAgendadas()) {
            throw ExcecaoConsulta("Nao e possivel remover: Paciente possui consultas pendentes!", ExcecaoConsulta::REMOCAO_PROIBIDA);
        }

        pac->exibirResumo();
        cout << "\nTem certeza que deseja remover este paciente? (S/N): ";
        char confirmacao; cin >> confirmacao;

        if (confirmacao == 'S' || confirmacao == 's') {
            auto it = find(pacientes.begin(), pacientes.end(), pac);
            if (it != pacientes.end()) {
                delete *it;
                pacientes.erase(it);
                cout << "\n>>> Paciente removido com sucesso!" << endl;
            }
        } else {
            cout << "Remocao cancelada." << endl;
        }
    } catch (const ExcecaoConsulta& e) {
        cout << "\nERRO: " << e.getMensagemCompleta() << endl;
    } catch (...) {
        cout << "\nERRO desconhecido." << endl;
    }
}

// --- MEDICOS ---
void Sistema::exibirMenuMedicos() {
    int opcao = 0;
    do {
        limparTela();
        cout << "============= MENU MEDICOS =============" << endl;
        cout << "1. Cadastrar Medico" << endl;
        cout << "2. Listar Medicos" << endl;
        cout << "3. Buscar por Especializacao" << endl;
        cout << "0. Voltar" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Opcao: ";
        cin >> opcao; cin.ignore();
        switch (opcao) {
            case 1: cadastrarMedico(); pausar(); break;
            case 2: listarMedicos(); pausar(); break;
            case 3: buscarMedicosPorEspecializacao(); pausar(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl; pausar();
        }
    } while (opcao != 0);
}

void Sistema::cadastrarMedico() {
    limparTela();
    cout << "--- CADASTRO DE MEDICO ---" << endl;
    string nome, endereco, telefone, especialidade, crm;
    cout << "Nome: "; getline(cin, nome);
    cout << "Endereco: "; getline(cin, endereco);
    cout << "Telefone: "; getline(cin, telefone);
    cout << "Especialidade: "; getline(cin, especialidade);
    cout << "CRM: "; getline(cin, crm);
    Medico* m = new Medico(nome, endereco, telefone, especialidade, crm);
    medicos.push_back(m);
    cout << "\n>>> Medico cadastrado com sucesso! ID: " << m->getId() << endl;
}

void Sistema::listarMedicos() {
    limparTela();
    if (medicos.empty()) { cout << "Nenhum medico cadastrado." << endl; return; }
    cout << "--- LISTA DE MEDICOS ---" << endl;
    for (const auto& m : medicos) m->exibirResumo();
}

void Sistema::buscarMedicosPorEspecializacao() {
    limparTela();
    cout << "--- BUSCA POR ESPECIALIZACAO ---" << endl;
    string esp;
    cout << "Digite a especializacao: "; getline(cin, esp);

    cout << "\nResultados:" << endl;
    bool achou = false;
    for(const auto& m : medicos) {
        string mEsp = m->getEspecialidade();
        // Busca simples (case sensitive na implementação básica)
        if(mEsp.find(esp) != string::npos) {
            m->exibirResumo(); achou = true;
        }
    }
    if(!achou) cout << "Nenhum medico encontrado com esse termo." << endl;
}

// --- CONSULTAS ---
void Sistema::exibirMenuConsultas() {
    int opcao = 0;
    do {
        limparTela();
        cout << "============ MENU CONSULTAS ============" << endl;
        cout << "1. Agendar Consulta" << endl;
        cout << "2. Listar Todas as Consultas" << endl;
        cout << "3. Listar por Paciente" << endl;
        cout << "4. Listar por Medico" << endl;
        cout << "5. Modificar Consulta" << endl;
        cout << "6. Cancelar Consulta" << endl;
        cout << "0. Voltar" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Opcao: "; cin >> opcao; cin.ignore();
        switch (opcao) {
            case 1: agendarConsulta(); pausar(); break;
            case 2: listarConsultas(); pausar(); break;
            case 3: listarConsultasPorPaciente(); pausar(); break;
            case 4: listarConsultasPorMedico(); pausar(); break;
            case 5: modificarConsulta(); pausar(); break;
            case 6: cancelarConsulta(); pausar(); break;
            case 0: break;
        }
    } while (opcao != 0);
}

void Sistema::agendarConsulta() {
    limparTela();
    cout << "--- AGENDAR CONSULTA ---" << endl;
    try {
        int idPac, idMed, tipo;
        string data, hora;
        cout << "ID Paciente: "; cin >> idPac;
        cout << "ID Medico: "; cin >> idMed; cin.ignore();

        Paciente* p = buscarPacientePorId(idPac);
        Medico* m = buscarMedicoPorId(idMed);

        if (!p) throw ExcecaoConsulta("Paciente nao encontrado", ExcecaoConsulta::PACIENTE_INEXISTENTE);
        if (!m) throw ExcecaoConsulta("Medico nao encontrado", ExcecaoConsulta::MEDICO_INEXISTENTE);

        cout << "Data (DD/MM/AAAA): "; getline(cin, data);
        cout << "Hora (HH:MM): "; getline(cin, hora);

        if (verificarConflitoHorario(m, data, hora))
            throw ExcecaoConsulta("Medico ocupado neste horario", ExcecaoConsulta::CONFLITO_HORARIO);

        cout << "\nTipo (1-Normal, 2-Emergencia, 3-Retorno): "; cin >> tipo; cin.ignore();

        Consulta* c = nullptr;
        if (tipo == 1) {
            string mot; cout << "Motivo: "; getline(cin, mot);
            c = new ConsultaNormal(p, m, data, hora, mot);
        } else if (tipo == 2) {
            int grav; string desc;
            cout << "Gravidade (1-5): "; cin >> grav; cin.ignore();
            cout << "Descricao: "; getline(cin, desc);
            c = new Emergencia(p, m, data, hora, grav, desc);
        } else {
            int idOrig; string obs;
            cout << "ID Consulta Original: "; cin >> idOrig; cin.ignore();
            cout << "Obs: "; getline(cin, obs);
            c = new Retorno(p, m, data, hora, idOrig, obs);
        }

        consultas.push_back(c);
        cout << "\n>>> Agendado com sucesso!" << endl;
        cout << "ID: " << c->getId() << " | Valor: R$ " << fixed << setprecision(2) << c->calcularValor() << endl;

    } catch (const exception& e) {
        cout << "\nERRO: " << e.what() << endl;
    }
}

void Sistema::listarConsultas() {
    limparTela();
    if (consultas.empty()) { cout << "Nenhuma consulta agendada." << endl; return; }
    cout << "--- TODAS AS CONSULTAS ---" << endl;
    for(const auto& c : consultas) c->exibirResumo();
}

void Sistema::listarConsultasPorPaciente() {
    limparTela();
    cout << "--- CONSULTAS POR PACIENTE ---" << endl;
    int id; cout << "ID Paciente: "; cin >> id;
    bool achou = false;
    for(const auto& c : consultas) {
        if(c->getPaciente()->getId() == id) {
            c->exibirResumo(); achou = true;
        }
    }
    if(!achou) cout << "Nenhuma consulta encontrada para este ID." << endl;
}

void Sistema::listarConsultasPorMedico() {
    limparTela();
    cout << "--- CONSULTAS POR MEDICO ---" << endl;
    int id; cout << "ID Medico: "; cin >> id;
    bool achou = false;
    for(const auto& c : consultas) {
        if(c->getMedico()->getId() == id) {
            c->exibirResumo(); achou = true;
        }
    }
    if(!achou) cout << "Nenhuma consulta encontrada para este ID." << endl;
}

void Sistema::modificarConsulta() {
    limparTela();
    cout << "--- MODIFICAR CONSULTA ---" << endl;
    try {
        int id; cout << "ID Consulta: "; cin >> id; cin.ignore();
        Consulta* c = buscarConsultaPorId(id);
        if(!c) throw ExcecaoConsulta("Consulta nao encontrada!", ExcecaoConsulta::CONSULTA_INEXISTENTE);

        c->imprimirDetalhes();
        string d, h;
        cout << "\nNova Data: "; getline(cin, d);
        cout << "Nova Hora: "; getline(cin, h);

        if (verificarConflitoHorario(c->getMedico(), d, h)) {
             throw ExcecaoConsulta("Conflito de horario!", ExcecaoConsulta::CONFLITO_HORARIO);
        }

        c->setData(d); c->setHora(h);
        cout << "\n>>> Consulta atualizada com sucesso!" << endl;
    } catch (const ExcecaoConsulta& e) {
        cout << "\nERRO: " << e.getMensagemCompleta() << endl;
    }
}

void Sistema::cancelarConsulta() {
    limparTela();
    cout << "--- CANCELAR CONSULTA ---" << endl;
    int id; cout << "ID Consulta: "; cin >> id;
    Consulta* c = buscarConsultaPorId(id);
    if(c) {
        c->setStatus("Cancelada");
        cout << "\n>>> Consulta marcada como CANCELADA." << endl;
    } else cout << "Nao encontrada." << endl;
}

// --- AUXILIARES ---
Paciente* Sistema::buscarPacientePorId(int id) {
    for(auto p : pacientes) if(p->getId() == id) return p;
    return nullptr;
}
Medico* Sistema::buscarMedicoPorId(int id) {
    for(auto m : medicos) if(m->getId() == id) return m;
    return nullptr;
}
Consulta* Sistema::buscarConsultaPorId(int id) {
    for(auto c : consultas) if(c->getId() == id) return c;
    return nullptr;
}
bool Sistema::verificarConflitoHorario(Medico* m, const string& data, const string& hora) {
    for(auto c : consultas)
        if(c->getMedico() == m && c->getData() == data && c->getHora() == hora && c->getStatus() != "Cancelada")
            return true;
    return false;
}

void Sistema::exibirEstatisticas() {
    limparTela();
    cout << "========== ESTATISTICAS ==========" << endl;
    cout << "Pacientes cadastrados: " << pacientes.size() << endl;
    cout << "Medicos cadastrados:   " << medicos.size() << endl;
    cout << "Total de Consultas:    " << consultas.size() << endl;
    cout << "==================================" << endl;
    pausar();
}

// --- PERSISTÊNCIA ---
void Sistema::salvarDados() {
    string base = obterCaminhoData();

    // Salvar Pacientes
    ofstream pac(base + "/pacientes.txt");
    if(pac.is_open()) {
        pac << pacientes.size() << endl;
        for(auto p : pacientes)
            pac << p->getId() << "\n" << p->getNome() << "\n" << p->getEndereco()
                << "\n" << p->getTelefone() << "\n" << p->getIdade() << endl;
        pac.close();
    }

    // Salvar Médicos
    ofstream med(base + "/medicos.txt");
    if(med.is_open()) {
        med << medicos.size() << endl;
        for(auto m : medicos)
            med << m->getId() << "\n" << m->getNome() << "\n" << m->getEndereco()
                << "\n" << m->getTelefone() << "\n" << m->getEspecialidade() << "\n" << m->getCrm() << endl;
        med.close();
    }
}

void Sistema::carregarDados() {
    string base = obterCaminhoData();

    // Carregar Pacientes
    ifstream pac(base + "/pacientes.txt");
    int qtd;
    if(pac >> qtd) {
        pac.ignore();
        for(int i=0; i<qtd; i++) {
            int id, idad; string n, e, t;
            pac >> id; pac.ignore(); getline(pac, n); getline(pac, e); getline(pac, t); pac >> idad; pac.ignore();
            Paciente* p = new Paciente(n, e, t, idad);
            p->setId(id);
            pacientes.push_back(p);
            Paciente::atualizarUltimoID(id);
        }
    }
    pac.close();

    // Carregar Médicos
    ifstream med(base + "/medicos.txt");
    if(med >> qtd) {
        med.ignore();
        for(int i=0; i<qtd; i++) {
            int id; string n, e, t, esp, crm;
            med >> id; med.ignore(); getline(med, n); getline(med, e); getline(med, t); getline(med, esp); getline(med, crm);
            Medico* m = new Medico(n, e, t, esp, crm);
            m->setId(id);
            medicos.push_back(m);
            Medico::atualizarUltimoID(id);
        }
    }
    med.close();
}

void Sistema::salvarConsultas() {
    string base = obterCaminhoData();
    ofstream arq(base + "/consultas.txt");
    if(!arq.is_open()) return;

    arq << consultas.size() << endl;
    for(auto c : consultas) {
        int tipo = (c->getTipo() == "Emergencia" ? 2 : (c->getTipo() == "Retorno" ? 3 : 1));
        arq << c->getId() << "\n" << tipo << "\n" << c->getPaciente()->getId() << "\n" << c->getMedico()->getId() << "\n"
            << c->getData() << "\n" << c->getHora() << "\n" << c->getDuracao() << "\n" << c->getStatus() << endl;

        if(tipo == 1) {
            ConsultaNormal* cn = dynamic_cast<ConsultaNormal*>(c);
            arq << (cn ? cn->getMotivoConsulta() : "") << endl;
        } else if(tipo == 2) {
            Emergencia* em = dynamic_cast<Emergencia*>(c);
            arq << (em ? em->getNivelGravidade() : 3) << "\n" << (em ? em->getDescricaoEmergencia() : "") << endl;
        } else {
            Retorno* ret = dynamic_cast<Retorno*>(c);
            arq << (ret ? ret->getIdConsultaOriginal() : 0) << "\n" << (ret ? ret->getObservacoes() : "") << endl;
        }
    }
    arq.close();
}

void Sistema::carregarConsultas() {
    string base = obterCaminhoData();
    ifstream arq(base + "/consultas.txt");
    int qtd;
    if(arq >> qtd) {
        arq.ignore();
        for(int i=0; i<qtd; i++) {
            int id, tipo, pid, mid, dur; string d, h, st;
            arq >> id >> tipo >> pid >> mid; arq.ignore(); getline(arq, d); getline(arq, h); arq >> dur; arq.ignore(); getline(arq, st);

            Paciente* p = buscarPacientePorId(pid); Medico* m = buscarMedicoPorId(mid);
            if(!p || !m) continue;

            Consulta* c = nullptr;
            if(tipo == 1) { string mot; getline(arq, mot); c = new ConsultaNormal(p, m, d, h, mot); }
            else if(tipo == 2) { int nv; string ds; arq >> nv; arq.ignore(); getline(arq, ds); c = new Emergencia(p, m, d, h, nv, ds); }
            else { int ori; string ob; arq >> ori; arq.ignore(); getline(arq, ob); c = new Retorno(p, m, d, h, ori, ob); }

            if(c) {
                c->setId(id); c->setStatus(st);
                consultas.push_back(c);
                Consulta::atualizarUltimoID(id);
            }
        }
    }
    arq.close();
}

void Sistema::salvarProntuarios() {
    string base = obterCaminhoData();
    ofstream arq(base + "/prontuarios.txt");
    if(arq.is_open()) {
        for(const auto& p : pacientes) {
            const auto& regs = p->getProntuario().getRegistros();
            for(const auto& r : regs) {
                arq << p->getId() << "\n" << r.getData() << "\n" << r.getMedico() << "\n"
                    << r.getDescricao() << "\n" << r.getPrescricao() << "\n---\n";
            }
        }
        arq.close();
    }
}

void Sistema::carregarProntuarios() {
    string base = obterCaminhoData();
    ifstream arq(base + "/prontuarios.txt");
    if(arq.is_open()) {
        int pid;
        while(arq >> pid) {
            arq.ignore();
            string d, m, desc, presc, sep;
            getline(arq, d); getline(arq, m); getline(arq, desc); getline(arq, presc); getline(arq, sep);
            Paciente* p = buscarPacientePorId(pid);
            if(p) p->getProntuarioModificavel().adicionarRegistro(d, m, desc, presc);
        }
        arq.close();
    }
}