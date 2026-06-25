#ifndef TELA_H
#define TELA_H

#include<iostream>
#include<vector>
#include"Operador.hpp"
#include"Sessao.hpp"
#include"Maquina.hpp"
#include"cores.hpp"

//using std::vector;
//using std::string;

class Tela {
public:
    Tela();
    void exibirCabecalho();
    void exibirRodape();
    void exibirMaquinas(const std::vector<std::shared_ptr<Maquina>>& maquinas);   
    void limparTela();

    
};

#endif