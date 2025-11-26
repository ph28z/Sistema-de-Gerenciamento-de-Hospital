#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>

using namespace std;

class Pessoa {
private:
    // Informações de contato, privadas
    string nome;
    string endereco;
    string telefone;

public:
    // Construtor
    // Usamos const string& para evitar cópias desnecessárias de texto na memória
    Pessoa(const string& nome, const string& endereco, const string& telefone);

    // Destrutor Virtual
    // Obrigatório, pois se não fosse virtual ocorreria um Memory Leak
    virtual ~Pessoa();

    // Métodos Getters (Para ler os dados)
    string getNome() const;
    string getEndereco() const;
    string getTelefone() const;

    // Métodos Setters (Para alterar os dados - requisito de edição de paciente)
    void setNome(const string& nome);
    void setEndereco(const string& endereco);
    void setTelefone(const string& telefone);

    // Método Virtual Puro
    /*
        1. 'virtual': Prepara para Polimorfismo (cada filho terá sua versão).
        2. '= 0': Diz que Pessoa NÃO tem implementação disso.
        3. Consequência: Obriga Medico e Paciente a criarem o método 'imprimirDados'.
     */
    virtual void imprimirDados() const = 0;
};

#endif // PESSOA_H