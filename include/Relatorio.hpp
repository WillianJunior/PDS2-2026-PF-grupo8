#ifndef RELATORIO_H
#define RELATORIO_H

#include<iostream>
#include<vector>
#include<fstream>
#include"Maquina.hpp"

using std::fstream;
/**
 * @file Relatorio.hpp
 * @brief Definição da classe Relatorio para gerar relatorios de desempenho.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * registrar acontecimentos relevantes e comportamentos das máquinas.
 */
class Relatorio{

private:
    vector<Maquina*> machine;

public:
    Relatorio();
    ~Relatorio();
    /**
     * @brief registra temperatura maxima e minima do dia
     */
    void registraTempMaxMin();
    /**
     * @brief registra RPM maximo e minimo do dia
     */
    void registraRpmMaxMin();
    /**
     * @brief registra anomalias comportamentais, aquecimento, oscilação anormal no RPM e desligamentos
     */
    void registraAnomalia();
    /**
     * @brief gera resumo do dia
     */
    void gerarResumo();
    

};


#endif