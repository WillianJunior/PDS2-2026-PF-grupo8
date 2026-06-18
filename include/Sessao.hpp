#ifndef SESSAO_H
#define SESSAO_H

#include <iostream>
#include <vector>
#include <memory>
#include "Maquina.hpp"
#include "Relatorio.hpp"

class Sessao {
public:
    Sessao();
    ~Sessao();

    void inicializarMaquinas(std::vector<std::shared_ptr<Maquina>>& maquinas);
    void relatorioSessao();
    void contarMaquinasAtivas(const std::vector<std::shared_ptr<Maquina>>& maquinas) const;
};

#endif