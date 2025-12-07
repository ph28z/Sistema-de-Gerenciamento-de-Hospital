#ifndef SISTEMAHOSPITALAR_SISTEMA_H
#define SISTEMAHOSPITALAR_SISTEMA_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Paciente.h"
#include "Medico.h"
#include "Consulta.h"

using namespace std;

class Sistema {
private:
    // Vetores que armazenam todos os dados do sistema
    vector<Paciente*> pacientes;
    vector<Medico*> medicos;
    vector<Consulta*> consultas;

public:
    // Construtor e Destrutor
    Sistema();
    ~Sistema();

    // --- MENUS ---
    void iniciar();
    void exibirMenuPrincipal();
    void exibirMenuPacientes();
    void exibirMenuMedicos();
    void exibirMenuConsultas();
    void exibirEstatisticas();

    // --- GESTÃO DE PACIENTES ---
    void cadastrarPaciente();
    void listarPacientes();
    void visualizarPaciente();
    void editarPaciente();
    void removerPaciente();

    // --- GESTÃO DE MÉDICOS ---
    void cadastrarMedico();
    void listarMedicos();
    void buscarMedicosPorEspecializacao();

    // --- GESTÃO DE CONSULTAS ---
    void agendarConsulta();
    void listarConsultas();
    void listarConsultasPorPaciente();
    void listarConsultasPorMedico();
    void modificarConsulta();
    void cancelarConsulta();

    // --- MÉTODOS AUXILIARES (Busca e Validação) ---
    Paciente* buscarPacientePorId(int id);
    Medico* buscarMedicoPorId(int id);
    Consulta* buscarConsultaPorId(int id);
    bool verificarConflitoHorario(Medico* medico, const string& data, const string& hora);

    // --- PERSISTÊNCIA DE DADOS (Salvar/Carregar) ---
    void salvarDados();         // Salva Pacientes e Médicos
    void carregarDados();       // Carrega Pacientes e Médicos

    void salvarConsultas();     // Salva Consultas
    void carregarConsultas();   // Carrega Consultas

    void salvarProntuarios();   // Salva Histórico Médico
    void carregarProntuarios(); // Carrega Histórico Médico
};

#endif // SISTEMAHOSPITALAR_SISTEMA_H