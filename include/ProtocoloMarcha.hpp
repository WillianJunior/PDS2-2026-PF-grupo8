#ifndef PROTOCOLOMARCHA_H
#define PROTOCOLOMARCHA_H

#include <iostream>
#include <vector>
#include <memory>
#include "Maquina.hpp"

class ProtocoloMarcha {
public:
    ProtocoloMarcha();
    ~ProtocoloMarcha();

    void quedaEnergia(const std::vector<std::shared_ptr<Maquina>>& maquinas);
    void equalizarRPM(const std::vector<std::shared_ptr<Maquina>>& maquinas);
    void modoNormal(const std::vector<std::shared_ptr<Maquina>>& maquinas);
};

#endif