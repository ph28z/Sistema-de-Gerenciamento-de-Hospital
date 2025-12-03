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

    // COMPOSIÇÃO: O Paciente TEM um prontuário dentro dele.
    // Quando o Paciente for destruído, este objeto também será.
    Prontuario prontuario;

public:
    // Construtor
    Paciente(const string& nome, const string& endereco, const string& telefone, int idade);
    
    // Destrutor
    ~Paciente();
    
    // Getters
    int getId() const;
    int getIdade() const;
    int getNumConsultas() const;
    
    // Setter
    void setIdade(int i);
    
    // Gerenciamento de consultas
    void adicionarConsulta(int idConsulta);
    void removerConsulta(int idConsulta);
    bool temConsultasAgendadas() const;
    
    // Implementação do método virtual puro de Pessoa
    void imprimirDados() const override;
    
    // Método adicional para exibir resumo em lista
    void exibirResumo() const;

    // Métodos para delegar ações ao prontuário
    void adicionarRegistroMedico(const string& data, const string& medico, const string& descricao, const string& prescricao = "");
    void visualizarProntuario() const;

    void setId(int id); // Para carregar do arquivo
    static void atualizarUltimoID(int id); // Para evitar duplicidade após carregar
};

#endif 
