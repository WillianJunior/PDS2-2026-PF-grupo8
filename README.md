# Sistema de Monitoramento e Tolerância a Falhas

## Grupo 8 - PDS II

- **Arthur Ryan Barbosa Teodoro**
- **Emilly Rayssa Sarah da Silva**
- **Gustavo Alberto Nunes Martins**

---

## 1. O Problema

Em fábricas e linhas de produção, quando uma máquina para de funcionar do nada, o prejuízo é alto e pode haver riscos de segurança. Monitorar tudo na mão é difícil e lento, o que impede de notar rápido quando a temperatura sobe demais ou o RPM (rotações por minuto) fica instável.

Este projeto é um sistema de monitoramento para automatizar esse processo. Ele lê dados de sensores, avisa se algo estiver errado conforme a gravidade e ativa protocolos de segurança sozinhos (como em casos de queda de energia), garantindo que a produção não saia das margens de segurança.

## 2. Objetivos

- **Monitoramento Real-Time:** Ler dados de RPM e Temperatura e mostrar no terminal com cores que indicam o nível de urgência.
- **Protocolo de Marcha:** Um sistema que estabiliza e iguala as máquinas automaticamente se faltar energia.
- **Gestão da Operação:** Controlar o início e fim das sessões, vincular operadores às máquinas e travar o uso de equipamentos que apresentarem defeitos.
- **Histórico e Relatórios:** Salvar os dados lidos e gerar um resumo com médias, máximos e mínimos ao final do turno.

## 3. Motivação

Escolhemos esse tema porque sistemas industriais exigem que o código seja muito confiável e saiba lidar com erros sem travar tudo (tolerância a falhas). É um cenário perfeito para usar Programação Orientada a Objetos (POO) na prática, aplicando conceitos de C++ como encapsulamento para proteger os dados das máquinas e polimorfismo para gerenciar diferentes tipos de alertas.

Além da parte técnica, o projeto simula uma situação real de engenharia. O desafio é organizar como as diferentes partes da fábrica (sensores, máquinas e o sistema de controle) se comunicam de forma eficiente, garantindo que o programa continue funcionando bem mesmo que o número de máquinas monitoradas aumente.

## 4. Organização do Sistema (Modelo CRC)

O sistema foi dividido em classes para facilitar a manutenção:

- **Maquina e Sensor:** Representam os equipamentos e a coleta de dados (RPM/Temperatura).
- **AlertaManager:** Cuida da lógica de classificar os problemas em Baixo, Médio ou Crítico.
- **ProtocoloMarcha:** Entra em ação em emergências para sincronizar as máquinas.
- **SistemaMonitor:** É o "cérebro" que roda o ciclo principal e interage com o usuário.
- **Sessao e Relatorio:** Guardam os dados temporais e geram o fechamento do dia.

## 5. Como Rodar

O projeto usa um `Makefile` para compilar tudo de uma vez e **Doxygen** para a documentação técnica.

**Compilar:**

```bash
make
```
