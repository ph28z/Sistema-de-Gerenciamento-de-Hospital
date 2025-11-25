# Sistema de Gerenciamento de Hospital

## Sobre o Projeto
Este projeto visa desenvolver um sistema simplificado de gestão hospitalar via console, permitindo o cadastro de pacientes, médicos, agendamentos e prontuários médicos.
O sistema utiliza persistência de dados em arquivos.

**Disciplina:** Programação Orientada a Objetos  
**Data de Entrega:** 08/12/2025 

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
- [cite_start]Polimorfismo em tipos de consulta: Normal, Emergência, Retorno[cite: 32].
- Cancelamento e listagem.

### 4. Prontuários Médicos
- Histórico de registros médicos por paciente.
- [cite_start]Composição: O prontuário pertence exclusivamente ao paciente[cite: 40].

### 5. Estatísticas
- Relatórios quantitativos de pacientes, médicos e consultas.

