#ifndef SISTEMAHOSPITALAR_SISTEMA_H
#define SISTEMAHOSPITALAR_SISTEMA_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Paciente.h"
#include "Medico.h"
#include "Consulta.h"

using namespace std;

class Sistema {
private:
    vector<Paciente*> pacientes;
    vector<Medico*> medicos;
    vector<Consulta*> consultas;

public:
    Sistema();
    ~Sistema();

    // Menus e Controle
    void iniciar();
    void exibirMenuPrincipal();
    void exibirMenuPacientes();
    void exibirMenuMedicos();
    void exibirMenuConsultas();
    void exibirEstatisticas();

    // Gestão de Pacientes
    void cadastrarPaciente();
    void listarPacientes();
    void visualizarPaciente();
    void editarPaciente();
    void removerPaciente();

    // Gestão de Médicos
    void cadastrarMedico();
    void listarMedicos();
    void buscarMedicosPorEspecializacao();

    // Gestão de Consultas
    void agendarConsulta();
    void listarConsultas();
    void listarConsultasPorPaciente();
    void listarConsultasPorMedico();
    void modificarConsulta();
    void cancelarConsulta();

    // Auxiliares
    Paciente* buscarPacientePorId(int id);
    Medico* buscarMedicoPorId(int id);
    Consulta* buscarConsultaPorId(int id);
    bool verificarConflitoHorario(Medico* medico, const string& data, const string& hora);

    // Persistência Completa
    void salvarDados();
    void carregarDados();
    void salvarConsultas();
    void carregarConsultas();
    void salvarProntuarios();
    void carregarProntuarios();
};

#endif //SISTEMAHOSPITALAR_SISTEMA_H