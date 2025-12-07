cmake_minimum_required(VERSION 3.20)
project(SistemaHospitalar)

set(CMAKE_CXX_STANDARD 17)

# Inclui a pasta de cabeçalhos (headers)
include_directories(include)

# Encontra todos os arquivos .cpp dentro de src
file(GLOB SOURCES "src/*.cpp")

# Cria o executável
add_executable(SistemaHospitalar main.cpp ${SOURCES}
        main.cpp

        # Classes Básicas
        include/Pessoa.h
        src/Pessoa.cpp
        include/Medico.h
        src/Medico.cpp
        include/Paciente.h
        src/Paciente.cpp

        # Prontuário
        include/Registro.h
        src/Registro.cpp
        include/Prontuario.h
        src/Prontuario.cpp

        # Sistema
        include/Sistema.h
        src/Sistema.cpp

        # Consulta
        include/Consulta.h
        src/Consulta.cpp
        include/ExcecaoConsulta.h
)