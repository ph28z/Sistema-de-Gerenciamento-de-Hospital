
#ifndef SISTEMAHOSPITALAR_CONSULTA_H
#define SISTEMAHOSPITALAR_CONSULTA_H

#include <string>
#include <iostream>
#include "Paciente.h"
#include "Medico.h"

using namespace std;

class Consulta {
protected:
    int id;
    static int proximoID;
    
    // Associação com Paciente e Médico (ponteiros)
    Paciente* paciente;
    Medico* medico;
    
    string data;      
    string hora;      
    int duracao;      
    string status;   

public:
    // Construtor
    Consulta(Paciente* pac, Medico* med, const string& data, 
             const string& hora, int duracao);
    
    // Destrutor virtual (importante para polimorfismo)
    virtual ~Consulta();
    
    // Getters
    int getId() const { return id; }
    Paciente* getPaciente() const { return paciente; }
    Medico* getMedico() const { return medico; }
    string getData() const { return data; }
    string getHora() const { return hora; }
    int getDuracao() const { return duracao; }
    string getStatus() const { return status; }
    
    // Setters
    void setData(const string& d);
    void setHora(const string& h);
    void setStatus(const string& s) { status = s; }
    
    // Métodos virtuais puros (polimorfismo)
    virtual double calcularValor() const = 0;
    virtual string getTipo() const = 0;
    virtual int getPrioridade() const = 0;
    
    // Método virtual (pode ser sobrescrito)
    virtual void imprimirDetalhes() const;
    void exibirResumo() const;
    
    // Validação de data e hora
    static bool validarData(const string& data);
    static bool validarHora(const string& hora);
    
    // Para persistência
    void setId(int i) { id = i; }
    static void atualizarUltimoID(int id);
};



class ConsultaNormal : public Consulta {
private:
    static const double VALOR_BASE;
    string motivoConsulta;

public:
    ConsultaNormal(Paciente* pac, Medico* med, const string& data, 
                   const string& hora, const string& motivo = "")
        : Consulta(pac, med, data, hora, 30), motivoConsulta(motivo) {}
    
    ~ConsultaNormal() {}
    
    // Implementação dos métodos virtuais puros
    double calcularValor() const override { return 200.0; }
    string getTipo() const override { return "Consulta Normal"; }
    int getPrioridade() const override { return 3; }
    
    // Métodos específicos
    string getMotivoConsulta() const { return motivoConsulta; }
    void setMotivoConsulta(const string& motivo) { motivoConsulta = motivo; }
    
    void imprimirDetalhes() const override;
};


class Emergencia : public Consulta {
private:
    static const double VALOR_BASE;
    static const double TAXA_EMERGENCIA;
    int nivelGravidade; 
    string descricaoEmergencia;

public:
    Emergencia(Paciente* pac, Medico* med, const string& data, 
               const string& hora, int nivelGrav, const string& descricao = "")
        : Consulta(pac, med, data, hora, 60), 
          nivelGravidade(nivelGrav), descricaoEmergencia(descricao) {
        if (nivelGrav < 1 || nivelGrav > 5) {
            nivelGravidade = 3; 
        }
    }
    
    ~Emergencia() {}
    
    // Implementação dos métodos virtuais puros
    double calcularValor() const override { 
        return 200.0 + (150.0 * nivelGravidade); 
    }
    
    string getTipo() const override { return "Emergencia"; }
    
    int getPrioridade() const override { 
        return 10 - nivelGravidade;
    }
    
    // Métodos específicos
    int getNivelGravidade() const { return nivelGravidade; }
    void setNivelGravidade(int nivel) { 
        if (nivel >= 1 && nivel <= 5) nivelGravidade = nivel; 
    }
    string getDescricaoEmergencia() const { return descricaoEmergencia; }
    void setDescricaoEmergencia(const string& desc) { descricaoEmergencia = desc; }
    
    void imprimirDetalhes() const override;
};

class Retorno : public Consulta {
private:
    static const double VALOR_BASE;
    static const double DESCONTO_RETORNO;
    int idConsultaOriginal;  // Referência à consulta anterior
    string observacoes;

public:
    Retorno(Paciente* pac, Medico* med, const string& data, 
            const string& hora, int idOriginal, const string& obs = "")
        : Consulta(pac, med, data, hora, 20), 
          idConsultaOriginal(idOriginal), observacoes(obs) {}
    
    ~Retorno() {}
    
    // Implementação dos métodos virtuais puros
    double calcularValor() const override { 
        return 200.0 * 0.5; // 50% de desconto
    }
    
    string getTipo() const override { return "Retorno"; }
    int getPrioridade() const override { return 4; }
    
    // Métodos específicos
    int getIdConsultaOriginal() const { return idConsultaOriginal; }
    string getObservacoes() const { return observacoes; }
    void setObservacoes(const string& obs) { observacoes = obs; }
    
    void imprimirDetalhes() const override;
};

#endif
