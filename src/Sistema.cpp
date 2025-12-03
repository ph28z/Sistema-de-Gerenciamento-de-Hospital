#include "../include/Sistema.h"
#include <iostream>
#include <limits>
#include <filesystem>

namespace fs = std::filesystem;

// --- FUNÇÃO AUXILIAR CORRIGIDA (Busca pelo CMakeLists.txt) ---
std::string obterCaminhoData() {
    fs::path caminhoAtual = fs::current_path();

    // Tenta subir até 5 níveis procurando a RAIZ do projeto
    // Usamos "CMakeLists.txt" como âncora, pois ele só existe na raiz
    for (int i = 0; i < 5; ++i) {
        if (fs::exists(caminhoAtual / "CMakeLists.txt")) {
            // ACHAMOS A RAIZ! Agora montamos o caminho para /data
            fs::path caminhoData = caminhoAtual / "data";

            // Se a pasta data não existir lá na raiz, cria agora
            if (!fs::exists(caminhoData)) {
                fs::create_directory(caminhoData);
            }
            return caminhoData.string();
        }

        // Sobe um nível (ex: sai de cmake-build-debug para a raiz)
        if (caminhoAtual.has_parent_path()) {
            caminhoAtual = caminhoAtual.parent_path();
        } else {
            break;
        }
    }

    // Fallback de segurança (usa local atual se falhar tudo)
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
    return "data";
}

// --- CONSTRUTOR ---
Sistema::Sistema() {
    carregarDados();
}

// --- DESTRUTOR ---
Sistema::~Sistema() {
    salvarDados();
    for (auto p : pacientes) delete p;
    for (auto m : medicos) delete m;
    pacientes.clear();
    medicos.clear();
}

// --- MENU PRINCIPAL ---
void Sistema::iniciar() {
    int opcao = 0;
    do {
        exibirMenuPrincipal();
        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        } else {
            cin.ignore();
        }

        switch (opcao) {
            case 1: exibirMenuPacientes(); break;
            case 2: exibirMenuMedicos(); break;
            case 3: exibirEstatisticas(); break;
            case 0: cout << "Saindo e salvando dados..." << endl; break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

void Sistema::exibirMenuPrincipal() {
    cout << "\n=== SISTEMA DE GESTAO HOSPITALAR ===" << endl;
    cout << "1. Gestao de Pacientes" << endl;
    cout << "2. Gestao de Medicos" << endl;
    cout << "3. Estatisticas Gerais" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

// --- GESTÃO DE PACIENTES ---

void Sistema::exibirMenuPacientes() {
    int opcao = 0;
    do {
        cout << "\n--- MENU PACIENTES ---" << endl;
        cout << "1. Cadastrar Paciente" << endl;
        cout << "2. Listar Pacientes" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: listarPacientes(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

void Sistema::cadastrarPaciente() {
    string nome, endereco, telefone;
    int idade;

    cout << "Nome: "; getline(cin, nome);
    cout << "Endereco: "; getline(cin, endereco);
    cout << "Telefone: "; getline(cin, telefone);
    cout << "Idade: "; cin >> idade;

    Paciente* p = new Paciente(nome, endereco, telefone, idade);
    pacientes.push_back(p);
    cout << "Paciente cadastrado com sucesso! ID: " << p->getId() << endl;
}

void Sistema::listarPacientes() {
    if (pacientes.empty()) {
        cout << "Nenhum paciente cadastrado." << endl;
        return;
    }
    cout << "\n--- LISTA DE PACIENTES ---" << endl;
    for (const auto& p : pacientes) {
        p->exibirResumo();
    }
}

// --- GESTÃO DE MÉDICOS ---

void Sistema::exibirMenuMedicos() {
    int opcao = 0;
    do {
        cout << "\n--- MENU MEDICOS ---" << endl;
        cout << "1. Cadastrar Medico" << endl;
        cout << "2. Listar Medicos" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: cadastrarMedico(); break;
            case 2: listarMedicos(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

void Sistema::cadastrarMedico() {
    string nome, endereco, telefone, especialidade, crm;

    cout << "Nome: "; getline(cin, nome);
    cout << "Endereco: "; getline(cin, endereco);
    cout << "Telefone: "; getline(cin, telefone);
    cout << "Especialidade: "; getline(cin, especialidade);
    cout << "CRM: "; getline(cin, crm);

    Medico* m = new Medico(nome, endereco, telefone, especialidade, crm);
    medicos.push_back(m);
    cout << "Medico cadastrado com sucesso! ID: " << m->getId() << endl;
}

void Sistema::listarMedicos() {
    if (medicos.empty()) {
        cout << "Nenhum medico cadastrado." << endl;
        return;
    }
    cout << "\n--- LISTA DE MEDICOS ---" << endl;
    for (const auto& m : medicos) {
        m->exibirResumo();
    }
}

// --- ESTATÍSTICAS ---

void Sistema::exibirEstatisticas() {
    cout << "\n=== ESTATISTICAS DO SISTEMA ===" << endl;
    cout << "Total de Pacientes: " << pacientes.size() << endl;
    cout << "Total de Medicos: " << medicos.size() << endl;
    cout << "===============================" << endl;
}

// --- PERSISTÊNCIA ---

void Sistema::salvarDados() {
    string caminhoBase = obterCaminhoData();

    // Debug: Mostra onde está salvando
    cout << "[DEBUG] Salvando em: " << caminhoBase << endl;

    // Salvar Pacientes
    string pathPac = caminhoBase + "/pacientes.txt";
    ofstream arqPac(pathPac);
    if (arqPac.is_open()) {
        arqPac << pacientes.size() << endl;
        for (const auto& p : pacientes) {
            arqPac << p->getId() << endl;
            arqPac << p->getNome() << endl;
            arqPac << p->getEndereco() << endl;
            arqPac << p->getTelefone() << endl;
            arqPac << p->getIdade() << endl;
        }
        arqPac.close();
    } else {
        cerr << "Erro fatal: Nao foi possivel criar: " << pathPac << endl;
    }

    // Salvar Médicos
    string pathMed = caminhoBase + "/medicos.txt";
    ofstream arqMed(pathMed);
    if (arqMed.is_open()) {
        arqMed << medicos.size() << endl;
        for (const auto& m : medicos) {
            arqMed << m->getId() << endl;
            arqMed << m->getNome() << endl;
            arqMed << m->getEndereco() << endl;
            arqMed << m->getTelefone() << endl;
            arqMed << m->getEspecialidade() << endl;
            arqMed << m->getCrm() << endl;
        }
        arqMed.close();
    }

    cout << "Dados salvos com sucesso." << endl;
}

void Sistema::carregarDados() {
    string caminhoBase = obterCaminhoData();

    // Carregar Pacientes
    ifstream arqPac(caminhoBase + "/pacientes.txt");
    if (arqPac.is_open()) {
        int qtd;
        if (arqPac >> qtd) { // Verifica se leu a quantidade corretamente
            arqPac.ignore();
            for (int i = 0; i < qtd; i++) {
                int id, idade;
                string nome, endereco, telefone;

                arqPac >> id; arqPac.ignore();
                getline(arqPac, nome);
                getline(arqPac, endereco);
                getline(arqPac, telefone);
                arqPac >> idade; arqPac.ignore();

                Paciente* p = new Paciente(nome, endereco, telefone, idade);
                p->setId(id);
                pacientes.push_back(p);
                Paciente::atualizarUltimoID(id);
            }
            cout << qtd << " pacientes carregados." << endl;
        }
        arqPac.close();
    }

    // Carregar Médicos
    ifstream arqMed(caminhoBase + "/medicos.txt");
    if (arqMed.is_open()) {
        int qtd;
        if (arqMed >> qtd) {
            arqMed.ignore();
            for (int i = 0; i < qtd; i++) {
                int id;
                string nome, endereco, telefone, especialidade, crm;

                arqMed >> id; arqMed.ignore();
                getline(arqMed, nome);
                getline(arqMed, endereco);
                getline(arqMed, telefone);
                getline(arqMed, especialidade);
                getline(arqMed, crm);

                Medico* m = new Medico(nome, endereco, telefone, especialidade, crm);
                m->setId(id);
                medicos.push_back(m);
                Medico::atualizarUltimoID(id);
            }
            cout << qtd << " medicos carregados." << endl;
        }
        arqMed.close();
    }
}