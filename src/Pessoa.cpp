#include "../include/Pessoa.h"

// CONSTRUTOR
// Inicializa os atributos básicos herdados por Paciente e Médico
Pessoa::Pessoa(const string& nome, const string& endereco, const string& telefone)
    : nome(nome), endereco(endereco), telefone(telefone) {}

// IMPLEMENTAÇÃO DO DESTRUTOR
// Mesmo vazio, ele precisa existir para que o compilador saiba o que fazer ao destruir o objeto.
Pessoa::~Pessoa() {
}

// GETTERs
// Encapsulamento, permitindo apenas leitura.
string Pessoa::getNome() const {
    return nome;
}

string Pessoa::getEndereco() const {
    return endereco;
}

string Pessoa::getTelefone() const {
    return telefone;
}

// SETTERs
// Permitem alterar os dados privados.
void Pessoa::setNome(const string& n) {
    nome = n;
}

void Pessoa::setEndereco(const string& e) {
    endereco = e;
}

void Pessoa::setTelefone(const string& t) {
    telefone = t;
}