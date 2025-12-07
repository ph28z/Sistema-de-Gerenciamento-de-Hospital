#ifndef PACIENTE_H
#define PACIENTE_H

#include "Pessoa.h"
#include "Prontuario.h"
#include <vector>
#include <string>

using namespace std;

class Paciente : public Pessoa {
private:
    int id;
    int idade;
    static int proximoID;
    vector<int> consultasAgendadas; 

    // Composição: O Paciente TEM um prontuário
    Prontuario prontuario;

public:
    Paciente(const string& nome, const string& endereco, const string& telefone, int idade);
    ~Paciente();

    // Getters e Setters
    int getId() const;
    int getIdade() const;
    int getNumConsultas() const;
    void setIdade(int i);

    // Gerenciamento de consultas
    void adicionarConsulta(int idConsulta);
    void removerConsulta(int idConsulta);
    bool temConsultasAgendadas() const;

    // Métodos virtuais e auxiliares
    void imprimirDados() const override;
    void exibirResumo() const;

    // Prontuário (Lógica de Negócio)
    void adicionarRegistroMedico(const string& data, const string& medico, const string& descricao, const string& prescricao = "");
    void visualizarProntuario() const;

    // Métodos Estáticos e de Sistema
    void setId(int id);
    static void atualizarUltimoID(int id);


    const Prontuario& getProntuario() const;
    Prontuario& getProntuarioModificavel();
};

#endif