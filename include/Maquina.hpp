#ifndef MAQUINA_H
#define MAQUINA_H

#include<iostream>
#include<string>
#include "Sensor.hpp"
#include"Operador.hpp"
#include"cores.hpp"


/**
 * @file Maquina.hpp
 * @brief Definição da classe Maquina, objeto central do projeto.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * criar maquinas, ligar, desligar, ativar modos de energia baixa, cadastrar operador, simular variaveis, exibir dados.
 */
class Maquina{

public:
    enum Status {ATIVA, QUEBRADA, MARCHA, DESLIGADA, ALERTA};
private:
    std::string id;
    Sensor *s[2];
    Status status;
    Operador *op;
    int alertaCiclos;

public:  
    Maquina(std::string id, Sensor *temperatura, Sensor*velocidade);
    ~Maquina();
    /**
     * @brief opera o status da maquina
     */
    void atualizarEstado();
    /**
     * @brief liga/desliga a maquina
     */
    void ligarDesligar(bool x);
    /**
     * @brief ativa modo marcha lenta
     * @return true para ativado e false para não ativado
     */
    bool modoMarcha();
    /**
     * @brief relaciona determinada maquina a um operador
     */
    void refOp(Operador *op);
    /**
     * @brief exibe a maquina
     */
    void exibir() const;
    /**
     * @brief simula os valores do sensor
     */
    void simulVar();
    
    Status getStatus() const;

    std::string getId() const;
    Sensor* getSensorTemp() const;
    Sensor* getSensorRpm() const;
    Operador* getOp() const;
    int getCiclos() const;
    
};
#endif