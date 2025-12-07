#ifndef SISTEMAHOSPITALAR_EXCECAOCONSULTA_H
#define SISTEMAHOSPITALAR_EXCECAOCONSULTA_H

#include <exception>
#include <string>

using namespace std;

class ExcecaoConsulta : public exception {
private:
    string mensagem;
    int codigoErro;

public:
    // Códigos de erro
    static const int DATA_INVALIDA = 1;
    static const int HORA_INVALIDA = 2;
    static const int CONFLITO_HORARIO = 3;
    static const int PACIENTE_INEXISTENTE = 4;
    static const int MEDICO_INEXISTENTE = 5;
    static const int CONSULTA_INEXISTENTE = 6;
    static const int PARAMETRO_INVALIDO = 7;
    static const int REMOCAO_PROIBIDA = 8; // <--- NOVO CÓDIGO ADICIONADO

    ExcecaoConsulta(const string& msg, int codigo)
        : mensagem(msg), codigoErro(codigo) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }

    int getCodigoErro() const { return codigoErro; }

    string getMensagemCompleta() const {
        return "[ERRO " + to_string(codigoErro) + "] " + mensagem;
    }
};

#endif