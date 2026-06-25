#ifndef SESSAO_H
#define SESSAO_H

#include <iostream>
#include <vector>
#include <memory>
#include "Maquina.hpp"
#include "Relatorio.hpp"
#include"SistemaMonitor.hpp"

class Sessao {
public:
    Sessao();
    ~Sessao();

    void inicializarMaquinas(std::vector<std::shared_ptr<Maquina>>& maquinas);
    void relatorioSessao();
    void contarMaquinasAtivas(const std::vector<std::shared_ptr<Maquina>>& maquinas) const;
    void salvarSessao(const std::vector<std::shared_ptr<Maquina>>& maquinas) const;
    void carregarSessao(SistemaMonitor& sistema, std::vector<std::shared_ptr<Sensor>>& sensoresAtivos) const;
};

#endif