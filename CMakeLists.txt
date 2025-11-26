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
        include/Medico.h
        src/Medico.cpp
        include/Pessoa.h
        src/Pessoa.cpp
)