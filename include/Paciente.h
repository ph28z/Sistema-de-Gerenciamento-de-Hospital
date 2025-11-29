#ifndef PACIENTE_H
#define PACIENTE_H

#include "Pessoa.h"
#include <vector>
#include <string>

using namespace std;

class Paciente : public Pessoa {
private:
    int id;
    int idade;
    static int proximoID;
    vector<int> consultasAgendadas; 

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
};

#endif 
