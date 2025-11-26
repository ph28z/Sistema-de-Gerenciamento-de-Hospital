# Sistema de Gerenciamento de Hospital

## Sobre o Projeto
Este projeto visa desenvolver um sistema simplificado de gestão hospitalar via console, permitindo o cadastro de pacientes, médicos, agendamentos e prontuários médicos.
O sistema utiliza persistência de dados em arquivos.

**Disciplina:** Programação Orientada a Objetos  
**Data de Entrega:** 08/12/2025 

## Objetivos do Projeto
Para ver o detalhamento do que já foi feito e o que falta, acesse nossa:
👉 [Lista de Progressão e Tarefas](TASKS.md)

![Progresso](https://img.shields.io/badge/Progresso-5%25-brightgreen)

## Funcionalidades Implementadas
### 1. Gestão de Pacientes
- Cadastro (ID único automático) e visualização.
- Edição de dados demográficos.
- Remoção (com validação de dependência).

### 2. Gestão de Médicos
- Cadastro (CRM, Especialização) e listagem.
- Busca por especialização.

### 3. Agendamento de Consultas
- Agendamento com validação de data/hora.
- Polimorfismo em tipos de consulta: Normal, Emergência, Retorno.
- Cancelamento e listagem.

### 4. Prontuários Médicos
- Histórico de registros médicos por paciente.
- Composição: O prontuário pertence exclusivamente ao paciente.

### 5. Estatísticas
- Relatórios quantitativos de pacientes, médicos e consultas.

