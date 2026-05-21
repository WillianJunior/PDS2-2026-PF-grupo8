#ifndef SESSAO_H
#define SESSAO_H

#include<iostream>
#include<vector>
#include"Maquina.hpp"
#include"Relatorio.hpp"

/**
 * @file Sessao.hpp
 * @brief Definição da classe Sessao para inicializar o "expediente".
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * inicializar maquinas, contar maquinas ativas e emitir relatorios no fim do expediente.
 */
class Sessao{


public:
    Sessao();
    ~Sessao();
    /**
     * @brief inicializa todas as maquinas
     */
    void inicializarMaquinas(vector<Maquina*>& maquinas);
    /**
     * @brief gera relatorio geral da sessão
     */
    void relatorioSessao();
    /**
     * @brief contagem das maquinas em funcionamento
     */
    void contarMaquinasAtivas(const vector<Maquina*>& maquinas) const;

};

#endif