#include "../include/Sistema.h"
#include "../include/ExcecaoConsulta.h"
#include "../include/Consulta.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sys/stat.h>
#include <map>

using namespace std;

bool diretorioExiste(const string& caminho) {
    struct stat info;
    if (stat(caminho.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

void criarDiretorio(const string& caminho) {
    #ifdef _WIN32
        system(("mkdir " + caminho + " 2>nul").c_str());
    #else
        system(("mkdir -p " + caminho + " 2>/dev/null").c_str());
    #endif
}

string obterCaminhoData() {
    string caminho = "data";
    if (!diretorioExiste(caminho)) {
        criarDiretorio(caminho);
    }
    return caminho;
}

Sistema::Sistema() {
    carregarDados();
    carregarConsultas();
}

Sistema::~Sistema() {
    salvarDados();
    salvarConsultas();
    
    for (auto p : pacientes) delete p;
    for (auto m : medicos) delete m;
    for (auto c : consultas) delete c;
    
    pacientes.clear();
    medicos.clear();
    consultas.clear();
}

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
            case 3: exibirMenuConsultas(); break;
            case 4: exibirEstatisticas(); break;
            case 0: cout << "Saindo e salvando dados..." << endl; break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

void Sistema::exibirMenuPrincipal() {
    cout << "\n=== SISTEMA DE GESTAO HOSPITALAR ===" << endl;
    cout << "1. Gestao de Pacientes" << endl;
    cout << "2. Gestao de Medicos" << endl;
    cout << "3. Gestao de Consultas" << endl;
    cout << "4. Estatisticas Gerais" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

void Sistema::exibirMenuPacientes() {
    int opcao = 0;
    do {
        cout << "\n--- MENU PACIENTES ---" << endl;
        cout << "1. Cadastrar Paciente" << endl;
        cout << "2. Listar Pacientes" << endl;
        cout << "3. Visualizar Paciente" << endl;
        cout << "4. Editar Paciente" << endl;
        cout << "5. Remover Paciente" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: listarPacientes(); break;
            case 3: visualizarPaciente(); break;
            case 4: editarPaciente(); break;
            case 5: removerPaciente(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

void Sistema::visualizarPaciente() {
    int id;
    cout << "ID do Paciente: "; cin >> id;
    cin.ignore();
    
    Paciente* pac = buscarPacientePorId(id);
    if (!pac) {
        cout << "Paciente nao encontrado!" << endl;
        return;
    }
    
    pac->imprimirDados();
    
    cout << "\nDeseja visualizar o prontuario? (S/N): ";
    char opcao;
    cin >> opcao;
    cin.ignore();
    
    if (opcao == 'S' || opcao == 's') {
        pac->visualizarProntuario();
    }
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

void Sistema::editarPaciente() {
    int id;
    cout << "ID do Paciente: "; cin >> id;
    cin.ignore();
    
    Paciente* pac = buscarPacientePorId(id);
    if (!pac) {
        cout << "Paciente nao encontrado!" << endl;
        return;
    }
    
    pac->imprimirDados();
    
    cout << "\nO que deseja editar?" << endl;
    cout << "1. Nome" << endl;
    cout << "2. Endereco" << endl;
    cout << "3. Telefone" << endl;
    cout << "4. Idade" << endl;
    cout << "Opcao: ";
    
    int opcao;
    cin >> opcao;
    cin.ignore();
    
    switch (opcao) {
        case 1: {
            string novoNome;
            cout << "Novo nome: "; getline(cin, novoNome);
            pac->setNome(novoNome);
            cout << "Nome atualizado!" << endl;
            break;
        }
        case 2: {
            string novoEndereco;
            cout << "Novo endereco: "; getline(cin, novoEndereco);
            pac->setEndereco(novoEndereco);
            cout << "Endereco atualizado!" << endl;
            break;
        }
        case 3: {
            string novoTelefone;
            cout << "Novo telefone: "; getline(cin, novoTelefone);
            pac->setTelefone(novoTelefone);
            cout << "Telefone atualizado!" << endl;
            break;
        }
        case 4: {
            int novaIdade;
            cout << "Nova idade: "; cin >> novaIdade;
            pac->setIdade(novaIdade);
            cout << "Idade atualizada!" << endl;
            break;
        }
        default:
            cout << "Opcao invalida!" << endl;
    }
}

void Sistema::removerPaciente() {
    int id;
    cout << "ID do Paciente: "; cin >> id;
    
    Paciente* pac = buscarPacientePorId(id);
    if (!pac) {
        cout << "Paciente nao encontrado!" << endl;
        return;
    }
    
    if (pac->temConsultasAgendadas()) {
        cout << "ERRO: Nao e possivel remover paciente com consultas agendadas!" << endl;
        cout << "Total de consultas: " << pac->getNumConsultas() << endl;
        return;
    }
    
    pac->imprimirDados();
    
    cout << "\nTem certeza que deseja remover este paciente? (S/N): ";
    char confirmacao;
    cin >> confirmacao;
    
    if (confirmacao == 'S' || confirmacao == 's') {
        auto it = find(pacientes.begin(), pacientes.end(), pac);
        if (it != pacientes.end()) {
            delete *it;
            pacientes.erase(it);
            cout << "Paciente removido com sucesso!" << endl;
        }
    } else {
        cout << "Remocao cancelada." << endl;
    }
}

void Sistema::exibirMenuMedicos() {
    int opcao = 0;
    do {
        cout << "\n--- MENU MEDICOS ---" << endl;
        cout << "1. Cadastrar Medico" << endl;
        cout << "2. Listar Medicos" << endl;
        cout << "3. Buscar por Especializacao" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: cadastrarMedico(); break;
            case 2: listarMedicos(); break;
            case 3: buscarMedicosPorEspecializacao(); break;
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

void Sistema::buscarMedicosPorEspecializacao() {
    if (medicos.empty()) {
        cout << "Nenhum medico cadastrado." << endl;
        return;
    }
    
    string especializacao;
    cout << "Digite a especializacao: ";
    getline(cin, especializacao);
    
    transform(especializacao.begin(), especializacao.end(), 
              especializacao.begin(), ::tolower);
    
    cout << "\n--- MEDICOS DA ESPECIALIZACAO: " << especializacao << " ---" << endl;
    
    bool encontrou = false;
    for (const auto& m : medicos) {
        string espMedico = m->getEspecialidade();
        transform(espMedico.begin(), espMedico.end(), espMedico.begin(), ::tolower);
        
        if (espMedico.find(especializacao) != string::npos) {
            m->exibirResumo();
            encontrou = true;
        }
    }
    
    if (!encontrou) {
        cout << "Nenhum medico encontrado com essa especializacao." << endl;
    }
}

void Sistema::exibirMenuConsultas() {
    int opcao = 0;
    do {
        cout << "\n--- MENU CONSULTAS ---" << endl;
        cout << "1. Agendar Consulta" << endl;
        cout << "2. Listar Todas as Consultas" << endl;
        cout << "3. Listar Consultas por Paciente" << endl;
        cout << "4. Listar Consultas por Medico" << endl;
        cout << "5. Modificar Consulta" << endl;
        cout << "6. Cancelar Consulta" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: agendarConsulta(); break;
            case 2: listarConsultas(); break;
            case 3: listarConsultasPorPaciente(); break;
            case 4: listarConsultasPorMedico(); break;
            case 5: modificarConsulta(); break;
            case 6: cancelarConsulta(); break;
            case 0: break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

void Sistema::agendarConsulta() {
    try {
        int idPaciente, idMedico, tipoConsulta;
        string data, hora;
        
        cout << "\n--- AGENDAR CONSULTA ---" << endl;
        cout << "ID do Paciente: "; cin >> idPaciente;
        cout << "ID do Medico: "; cin >> idMedico;
        cin.ignore();
        
        Paciente* pac = buscarPacientePorId(idPaciente);
        Medico* med = buscarMedicoPorId(idMedico);
        
        if (!pac) {
            throw ExcecaoConsulta("Paciente nao encontrado!", 
                                ExcecaoConsulta::PACIENTE_INEXISTENTE);
        }
        
        if (!med) {
            throw ExcecaoConsulta("Medico nao encontrado!", 
                                ExcecaoConsulta::MEDICO_INEXISTENTE);
        }
        
        cout << "Data (DD/MM/AAAA): "; getline(cin, data);
        cout << "Hora (HH:MM): "; getline(cin, hora);
        
        if (verificarConflitoHorario(med, data, hora)) {
            throw ExcecaoConsulta("Conflito de horario! Medico ja tem consulta neste horario.", 
                                ExcecaoConsulta::CONFLITO_HORARIO);
        }
        
        cout << "\nTipo de Consulta:" << endl;
        cout << "1. Consulta Normal" << endl;
        cout << "2. Emergencia" << endl;
        cout << "3. Retorno" << endl;
        cout << "Opcao: "; cin >> tipoConsulta;
        cin.ignore();
        
        Consulta* consulta = nullptr;
        
        switch (tipoConsulta) {
            case 1: {
                string motivo;
                cout << "Motivo da consulta: "; getline(cin, motivo);
                consulta = new ConsultaNormal(pac, med, data, hora, motivo);
                break;
            }
            case 2: {
                int nivelGrav;
                string descricao;
                cout << "Nivel de gravidade (1-5): "; cin >> nivelGrav;
                cin.ignore();
                cout << "Descricao da emergencia: "; getline(cin, descricao);
                consulta = new Emergencia(pac, med, data, hora, nivelGrav, descricao);
                break;
            }
            case 3: {
                int idOriginal;
                string obs;
                cout << "ID da consulta original: "; cin >> idOriginal;
                cin.ignore();
                cout << "Observacoes: "; getline(cin, obs);
                consulta = new Retorno(pac, med, data, hora, idOriginal, obs);
                break;
            }
            default:
                cout << "Tipo invalido! Criando consulta normal..." << endl;
                consulta = new ConsultaNormal(pac, med, data, hora, "");
        }
        
        consultas.push_back(consulta);
        cout << "\nConsulta agendada com sucesso! ID: " << consulta->getId() << endl;
        cout << "Valor: R$ " << fixed << setprecision(2) << consulta->calcularValor() << endl;
        
    } catch (const ExcecaoConsulta& e) {
        cout << "\nERRO: " << e.getMensagemCompleta() << endl;
    } catch (const exception& e) {
        cout << "\nERRO inesperado: " << e.what() << endl;
    }
}

void Sistema::listarConsultas() {
    if (consultas.empty()) {
        cout << "Nenhuma consulta agendada." << endl;
        return;
    }
    
    cout << "\n--- TODAS AS CONSULTAS ---" << endl;
    for (const auto& c : consultas) {
        c->exibirResumo();
    }
}

void Sistema::listarConsultasPorPaciente() {
    int idPaciente;
    cout << "ID do Paciente: "; cin >> idPaciente;
    
    Paciente* pac = buscarPacientePorId(idPaciente);
    if (!pac) {
        cout << "Paciente nao encontrado!" << endl;
        return;
    }
    
    cout << "\n--- CONSULTAS DO PACIENTE: " << pac->getNome() << " ---" << endl;
    bool encontrou = false;
    
    for (const auto& c : consultas) {
        if (c->getPaciente()->getId() == idPaciente) {
            c->exibirResumo();
            encontrou = true;
        }
    }
    
    if (!encontrou) {
        cout << "Nenhuma consulta encontrada para este paciente." << endl;
    }
}

void Sistema::listarConsultasPorMedico() {
    int idMedico;
    cout << "ID do Medico: "; cin >> idMedico;
    
    Medico* med = buscarMedicoPorId(idMedico);
    if (!med) {
        cout << "Medico nao encontrado!" << endl;
        return;
    }
    
    cout << "\n--- CONSULTAS DO MEDICO: " << med->getNome() << " ---" << endl;
    bool encontrou = false;
    
    for (const auto& c : consultas) {
        if (c->getMedico()->getId() == idMedico) {
            c->exibirResumo();
            encontrou = true;
        }
    }
    
    if (!encontrou) {
        cout << "Nenhuma consulta encontrada para este medico." << endl;
    }
}

void Sistema::modificarConsulta() {
    try {
        int idConsulta;
        cout << "ID da Consulta: "; cin >> idConsulta;
        cin.ignore();
        
        Consulta* consulta = buscarConsultaPorId(idConsulta);
        if (!consulta) {
            throw ExcecaoConsulta("Consulta nao encontrada!", 
                                ExcecaoConsulta::CONSULTA_INEXISTENTE);
        }
        
        consulta->imprimirDetalhes();
        
        cout << "\nO que deseja modificar?" << endl;
        cout << "1. Data" << endl;
        cout << "2. Hora" << endl;
        cout << "3. Status" << endl;
        cout << "Opcao: ";
        
        int opcao;
        cin >> opcao;
        cin.ignore();
        
        switch (opcao) {
            case 1: {
                string novaData;
                cout << "Nova data (DD/MM/AAAA): "; getline(cin, novaData);
                consulta->setData(novaData);
                cout << "Data atualizada!" << endl;
                break;
            }
            case 2: {
                string novaHora;
                cout << "Nova hora (HH:MM): "; getline(cin, novaHora);
                
                if (verificarConflitoHorario(consulta->getMedico(), 
                                            consulta->getData(), novaHora)) {
                    throw ExcecaoConsulta("Conflito de horario!", 
                                        ExcecaoConsulta::CONFLITO_HORARIO);
                }
                
                consulta->setHora(novaHora);
                cout << "Hora atualizada!" << endl;
                break;
            }
            case 3: {
                string novoStatus;
                cout << "Novo status (Agendada/Realizada/Cancelada): ";
                getline(cin, novoStatus);
                consulta->setStatus(novoStatus);
                cout << "Status atualizado!" << endl;
                break;
            }
            default:
                cout << "Opcao invalida!" << endl;
        }
        
    } catch (const ExcecaoConsulta& e) {
        cout << "\nERRO: " << e.getMensagemCompleta() << endl;
    }
}

void Sistema::cancelarConsulta() {
    try {
        int idConsulta;
        cout << "ID da Consulta: "; cin >> idConsulta;
        
        Consulta* consulta = buscarConsultaPorId(idConsulta);
        if (!consulta) {
            throw ExcecaoConsulta("Consulta nao encontrada!", 
                                ExcecaoConsulta::CONSULTA_INEXISTENTE);
        }
        
        consulta->imprimirDetalhes();
        
        cout << "\nTem certeza que deseja cancelar? (S/N): ";
        char confirmacao;
        cin >> confirmacao;
        
        if (confirmacao == 'S' || confirmacao == 's') {
            auto it = find(consultas.begin(), consultas.end(), consulta);
            if (it != consultas.end()) {
                delete *it;
                consultas.erase(it);
                cout << "Consulta cancelada com sucesso!" << endl;
            }
        } else {
            cout << "Cancelamento abortado." << endl;
        }
        
    } catch (const ExcecaoConsulta& e) {
        cout << "\nERRO: " << e.getMensagemCompleta() << endl;
    }
}

Paciente* Sistema::buscarPacientePorId(int id) {
    for (auto p : pacientes) {
        if (p->getId() == id) return p;
    }
    return nullptr;
}

Medico* Sistema::buscarMedicoPorId(int id) {
    for (auto m : medicos) {
        if (m->getId() == id) return m;
    }
    return nullptr;
}

Consulta* Sistema::buscarConsultaPorId(int id) {
    for (auto c : consultas) {
        if (c->getId() == id) return c;
    }
    return nullptr;
}

bool Sistema::verificarConflitoHorario(Medico* medico, const string& data, const string& hora) {
    for (const auto& c : consultas) {
        if (c->getMedico()->getId() == medico->getId() &&
            c->getData() == data &&
            c->getHora() == hora &&
            c->getStatus() != "Cancelada") {
            return true;
        }
    }
    return false;
}

void Sistema::exibirEstatisticas() {
    cout << "\n=== ESTATISTICAS DO SISTEMA ===" << endl;
    cout << "Total de Pacientes: " << pacientes.size() << endl;
    cout << "Total de Medicos: " << medicos.size() << endl;
    cout << "Total de Consultas: " << consultas.size() << endl;
    
    int agendadas = 0, realizadas = 0, canceladas = 0;
    for (const auto& c : consultas) {
        if (c->getStatus() == "Agendada") agendadas++;
        else if (c->getStatus() == "Realizada") realizadas++;
        else if (c->getStatus() == "Cancelada") canceladas++;
    }
    
    cout << "  - Agendadas: " << agendadas << endl;
    cout << "  - Realizadas: " << realizadas << endl;
    cout << "  - Canceladas: " << canceladas << endl;
    
    cout << "\n--- CONSULTAS POR ESPECIALIZACAO ---" << endl;
    
    map<string, int> consultasPorEspecializacao;
    
    for (const auto& c : consultas) {
        string esp = c->getMedico()->getEspecialidade();
        consultasPorEspecializacao[esp]++;
    }
    
    if (consultasPorEspecializacao.empty()) {
        cout << "Nenhuma consulta registrada." << endl;
    } else {
        for (const auto& par : consultasPorEspecializacao) {
            cout << "  " << par.first << ": " << par.second << " consulta(s)" << endl;
        }
    }
    
    cout << "===============================" << endl;
}

void Sistema::salvarDados() {
    string caminhoBase = obterCaminhoData();
    
    ofstream arqPac(caminhoBase + "/pacientes.txt");
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
    }
    
    ofstream arqMed(caminhoBase + "/medicos.txt");
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
}

void Sistema::carregarDados() {
    string caminhoBase = obterCaminhoData();
    
    ifstream arqPac(caminhoBase + "/pacientes.txt");
    if (arqPac.is_open()) {
        int qtd;
        if (arqPac >> qtd) {
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
        }
        arqPac.close();
    }
    
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
        }
        arqMed.close();
    }
}

void Sistema::salvarConsultas() {
    string caminhoBase = obterCaminhoData();
    
    ofstream arqCon(caminhoBase + "/consultas.txt");
    if (!arqCon.is_open()) return;
    
    arqCon << consultas.size() << endl;
    
    for (const auto& c : consultas) {
        string tipo = c->getTipo();
        int tipoInt = 1;
        if (tipo == "Emergencia") tipoInt = 2;
        else if (tipo == "Retorno") tipoInt = 3;
        
        arqCon << c->getId() << endl;
        arqCon << tipoInt << endl;
        arqCon << c->getPaciente()->getId() << endl;
        arqCon << c->getMedico()->getId() << endl;
        arqCon << c->getData() << endl;
        arqCon << c->getHora() << endl;
        arqCon << c->getDuracao() << endl;
        arqCon << c->getStatus() << endl;
        
        if (tipoInt == 1) {
            ConsultaNormal* cn = dynamic_cast<ConsultaNormal*>(c);
            arqCon << (cn ? cn->getMotivoConsulta() : "") << endl;
        } else if (tipoInt == 2) {
            Emergencia* em = dynamic_cast<Emergencia*>(c);
            if (em) {
                arqCon << em->getNivelGravidade() << endl;
                arqCon << em->getDescricaoEmergencia() << endl;
            } else {
                arqCon << "3" << endl << "" << endl;
            }
        } else if (tipoInt == 3) {
            Retorno* ret = dynamic_cast<Retorno*>(c);
            if (ret) {
                arqCon << ret->getIdConsultaOriginal() << endl;
                arqCon << ret->getObservacoes() << endl;
            } else {
                arqCon << "0" << endl << "" << endl;
            }
        }
    }
    
    arqCon.close();
}

void Sistema::carregarConsultas() {
    string caminhoBase = obterCaminhoData();
    
    ifstream arqCon(caminhoBase + "/consultas.txt");
    if (!arqCon.is_open()) return;
    
    int qtd;
    if (arqCon >> qtd) {
        arqCon.ignore();
        
        for (int i = 0; i < qtd; i++) {
            int id, tipo, idPac, idMed, duracao;
            string data, hora, status;
            
            arqCon >> id; arqCon.ignore();
            arqCon >> tipo; arqCon.ignore();
            arqCon >> idPac; arqCon.ignore();
            arqCon >> idMed; arqCon.ignore();
            getline(arqCon, data);
            getline(arqCon, hora);
            arqCon >> duracao; arqCon.ignore();
            getline(arqCon, status);
            
            Paciente* pac = buscarPacientePorId(idPac);
            Medico* med = buscarMedicoPorId(idMed);
            
            if (!pac || !med) continue;
            
            Consulta* consulta = nullptr;
            
            try {
                if (tipo == 1) {
                    string motivo;
                    getline(arqCon, motivo);
                    consulta = new ConsultaNormal(pac, med, data, hora, motivo);
                } else if (tipo == 2) {
                    int nivel;
                    string desc;
                    arqCon >> nivel; arqCon.ignore();
                    getline(arqCon, desc);
                    consulta = new Emergencia(pac, med, data, hora, nivel, desc);
                } else if (tipo == 3) {
                    int idOrig;
                    string obs;
                    arqCon >> idOrig; arqCon.ignore();
                    getline(arqCon, obs);
                    consulta = new Retorno(pac, med, data, hora, idOrig, obs);
                }
                
                if (consulta) {
                    consulta->setId(id);
                    consulta->setStatus(status);
                    consultas.push_back(consulta);
                    Consulta::atualizarUltimoID(id);
                }
            } catch (...) {
                continue;
            }
        }
    }
    
    arqCon.close();
}
