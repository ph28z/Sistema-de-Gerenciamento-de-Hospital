#ifndef SISTEMAHOSPITALAR_MEDICO_H
#define SISTEMAHOSPITALAR_MEDICO_H

#include "Pessoa.h"
#include <vector>
#include <string>

using namespace std;

class Medico : public Pessoa {
private:
    int id;
    string especialidade;
    string crm;
    static int proximoID;
    vector<int> consultasAgendadas;

public:
    // Construtor
    Medico(const string& nome, const string& endereco, const string& telefone, 
           const string& especialidade, const string& crm);
    
    // Destrutor
    ~Medico();
    
    // Getters
    int getId() const;
    string getEspecialidade() const;
    string getCrm() const;
    int getNumConsultas() const;
    
    // Setters
    void setEspecialidade(const string& esp);
    void setCrm(const string& c);
    
    // Gerenciamento de consultas
    void adicionarConsulta(int idConsulta);
    void removerConsulta(int idConsulta);
    bool temConsultasAgendadas() const;
    
    // Implementação do método virtual puro de Pessoa
    void imprimirDados() const override;
    
    // Método adicional para exibir resumo em lista
    void exibirResumo() const;
};

#endif //SISTEMAHOSPITALAR_MEDICO_H
