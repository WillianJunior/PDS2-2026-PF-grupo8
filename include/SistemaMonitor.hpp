#ifndef SISTEMAMONITOR_H
#define SISTEMAMONITOR_H

#include<iostream>
#include<vector>
#include"Maquina.hpp"
#include"Operador.hpp"

/**
 * @file SistemaMonitor.hpp
 * @brief Definição da classe SistemaMonitor para gerenciar operações.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * adicionar/remover maquinas à operação, cadastrar operadores, atribuir operadores às máquinas, ativar protocolos inicializar ciclo de monitoramento, exibir os dados dos sensores das maquinas em "tempo real".
 */
class SistemaMonitor{

private:
    vector<Maquina*> machine;
    vector<Operador*> op;
public:
    SistemaMonitor();
    ~SistemaMonitor();
    /**
     * @brief adiciona maquinas à rotina
     */
    void adicionarMaquinas(Maquina* maquina);
    /**
     * @brief remove maquinas à rotina
     */
    void removerMaquinas(string id);
    /**
     * @brief cadastra operador instanciado
     */
    void cadastrarOperador(Operador* op);
    /**
     * @brief atribui maquina a um operador especifico
     */
    void atribuirMaquinasOperador();
    /**
     * @brief aciona protocolo de marcha lenta
     */
    void protocoloMarcha();
    /**
     * @brief inicializa ciclo de monitoramento
     */
    void cicloMonitoramento();
    /**
     * @brief exibe os dados de todas as maquinas em tempo real
     */
    void exibirDados() const;

    const vector<Maquina*>& getMaquinas() const;

};

#endif