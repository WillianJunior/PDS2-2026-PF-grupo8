#ifndef PROTOCOLOMARCHA_H
#define PROTOCOLOMARCHA_H

#include<iostream>
#include<vector>
#include"Maquina.hpp"

/**
 * @file ProtocoloMarcha.hpp
 * @brief Definição da classe ProtocoloMarcha para ativar modos de energia e gerenciar desempenho das maquinas.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * ativar modos específicos de funcionamento.
 */
class ProtocoloMarcha{

private: 
    vector<Maquina*> machine;

public:

    ProtocoloMarcha();
    ~ProtocoloMarcha();
    /**
     * @brief informa queda de energia
     */
    void quedaEnergia();
    /**
     * @brief equaliza o RPM de todas as maquinas para operar no modo queda de energia
     */
    void equalizarRPM();
    /**
     * @brief ativa modo normal
     */
    void modoNormal();
};


#endif