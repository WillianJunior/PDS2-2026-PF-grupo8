#ifndef RELATORIO_H
#define RELATORIO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "Maquina.hpp"

class Relatorio {
public:
    Relatorio();
    ~Relatorio();

    void registraTempMaxMin(std::shared_ptr<const Maquina> m);
    void registraRpmMaxMin(std::shared_ptr<const Maquina> m);
    void registraAnomalia(std::shared_ptr<const Maquina> m);
    void gerarResumo(const std::vector<std::shared_ptr<Maquina>>& maquinas);
    void registrarDesligamentoAlerta(std::shared_ptr<const Maquina> m);
};

#endif