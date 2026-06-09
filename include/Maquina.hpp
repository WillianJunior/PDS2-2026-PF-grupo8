#ifndef MAQUINA_H
#define MAQUINA_H

#include<iostream>
#include<string>
#include "Sensor.hpp"
#include"Operador.hpp"

using std::string;

/**
 * @file Maquina.hpp
 * @brief Definição da classe Maquina, objeto central do projeto.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * criar maquinas, ligar, desligar, ativar modos de energia baixa, cadastrar operador, simular variaveis, exibir dados.
 */
class Maquina{

private:
    string id;
    Sensor *s[2];
    enum Status {ATIVA, QUEBRADA, MARCHA, DESLIGADA};
    Status status;
    Operador *op;

public:
   
    
    Maquina(string id, Sensor *temperatura, Sensor*velocidade);
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
    void exibir();
    /**
     * @brief simula os valores do sensor
     */
    void simulVar();

    Status getStatus() const;
};
#endif