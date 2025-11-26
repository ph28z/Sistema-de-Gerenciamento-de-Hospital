# Lista de Tarefas - Sistema de Gerenciamento Hospitalar

> **Disciplina:** Programação Orientada a Objetos  
> **Entrega:** 08/12/2025  
> **Status:** 🚧 Em Desenvolvimento

---

## 1. Configuração e Arquitetura Base
Fase inicial para estruturar o projeto e as classes principais.

- [X] **Configuração do Ambiente**
    - [X] Criar repositório Git e configurar `.gitignore` (ignorar binários e arquivos temporários).
    - [X] Configurar `CMakeLists.txt` para compilação.
    - [X] Criar estrutura de pastas: `src/`, `include/`, `data/`.
- [ ] **Classe Abstrata `Pessoa`**
    - [ ] Criar classe com atributos comuns: Nome e Contato/Endereço.
    - [ ] Definir atributos como `protected` ou `private` com getters/setters (Encapsulamento).

## 2. Gestão de Pacientes
Requisitos focados no módulo de pacientes.

- [ ] **Classe `Paciente` (Herança de Pessoa)** 
    - [ ] Implementar herança de `Pessoa`.
    - [ ] Criar atributo estático (`static`) para geração automática de ID único.
    - [ ] Implementar construtor e destrutor.
- [ ] **Funcionalidades de Paciente**
    - [ ] Cadastro de novos pacientes (com ID automático).
    - [ ] Visualização de dados do paciente.
    - [ ] Edição de dados demográficos (nome, idade, endereço, contato).
    - [ ] Listagem de todos os pacientes cadastrados
    - [ ] Remoção de paciente (Validar: só permitir se **não** tiver consultas agendadas).

## 3. Gestão de Médicos
Requisitos focados no módulo de equipe médica.

- [ ] **Classe `Medico` (Herança de Pessoa)** 
    - [ ] Implementar herança de `Pessoa`.
    - [ ] Adicionar atributos: CRM e Especialização.
- [ ] **Funcionalidades de Médico**
    - [ ] Cadastro de médicos com IDs únicos
    - [ ] Listagem de todos os médicos.
    - [ ] Busca de médicos por especialização.

## 4. Agendamento de Consultas (Polimorfismo & Associação)
Core do sistema: relacionamento entre médico e paciente.

- [ ] **Classe Base `Consulta` (Abstrata)**
    - [ ] Criar associação entre `Paciente` e `Medico` (ponteiros/referências).
    - [ ] Atributos: Data, Hora, Duracao (ou Valor).
    - [ ] Método virtual puro para sobrescrita (ex: `calcularValor()` ou `getPrioridade()`).
- [ ] **Subclasses de Consulta (Polimorfismo)**
    - [ ] Implementar `ConsultaNormal` (sobrescrever método virtual).
    - [ ] Implementar `Emergencia` (sobrescrever método virtual).
    - [ ] Implementar `Retorno` ou `Acompanhamento`.
- [ ] **Funcionalidades de Agendamento**
    - [ ] Agendar nova consulta.
    - [ ] **Tratamento de Exceção:** Validar datas/horas inválidas e conflitos.
    - [ ] **Tratamento de Exceção:** Impedir agendamento para IDs inexistentes.
    - [ ] Modificação e cancelamento de consultas.
    - [ ] Listagem de consultas (Geral ou filtrada por Médico/Paciente).

## 5. Prontuários Médicos (Composição)
Relação forte onde o prontuário pertence ao paciente.

- [ ] **Estrutura do Prontuário**
    - [ ] Criar classe `Registro` (Data, Médico, Descrição, Prescrição).
    - [ ] Criar classe `Prontuario` contendo uma lista/vetor de Registros.
    - [ ] Implementar **Composição**: O Prontuário deve ser instanciado dentro do Paciente e destruído junto com ele.
- [ ] **Funcionalidades de Prontuário**
    - [ ] Adicionar novo registro médico (após consulta concluída).
    - [ ] Visualizar histórico completo de um paciente.

## 6. Sistema, Persistência e Estatísticas
Interface e salvamento de dados.

- [ ] **Sistema Principal (Menu/Console)** 
    - [ ] Criar menus de navegação para todas as funcionalidades acima.
    - [ ] Classe controladora `SistemaHospitalar` ou `GerenteHospitalar`.
- [ ] **Persistência de Dados (Arquivos)** 
    - [ ] Salvar/Carregar lista de Pacientes em arquivo (`.txt` ou binário).
    - [ ] Salvar/Carregar lista de Médicos.
    - [ ] Salvar/Carregar Consultas.
    - [ ] Salvar/Carregar Prontuários Médicos.
- [ ] **Estatísticas e Relatórios** 
    - [ ] Total de pacientes cadastrados.
    - [ ] Total de médicos cadastrados.
    - [ ] Total de consultas realizadas.
    - [ ] Contagem de consultas por especialização.

## 7. Entregáveis e Finalização
Preparação para o envio.

- [ ] **Testes Finais**
    - [ ] Verificar tratamento de exceções em todo o sistema.
    - [ ] Verificar vazamento de memória (destrutores corretos).
- [ ] **Relatório do Projeto** 
    - [ ] Demonstrar criação de pacientes e médicos.
    - [ ] Demonstrar agendamento e polimorfismo.
    - [ ] Demonstrar persistência (fechar e abrir o programa mantendo dados).