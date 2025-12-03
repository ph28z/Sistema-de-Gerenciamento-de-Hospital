#ifndef SISTEMAHOSPITALAR_SISTEMA_H
#define SISTEMAHOSPITALAR_SISTEMA_H

#include <vector>
#include <iostream>
#include <fstream> // Para arquivos
#include "Paciente.h"
#include "Medico.h"

using namespace std;

class Sistema {
private:
    vector<Paciente*> pacientes;
    vector<Medico*> medicos;

public:
    Sistema();
    ~Sistema(); // Destrutor para limpar memória

    // Menus
    void iniciar();
    void exibirMenuPrincipal();
    void exibirMenuPacientes();
    void exibirMenuMedicos();
    void exibirEstatisticas();

    // Gestão de Pacientes
    void cadastrarPaciente();
    void listarPacientes();
    void editarPaciente();
    void removerPaciente();

    // Gestão de Médicos
    void cadastrarMedico();
    void listarMedicos();

    // Persistência
    void salvarDados();
    void carregarDados();
};

#endif //SISTEMAHOSPITALAR_SISTEMA_H