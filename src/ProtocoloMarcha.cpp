#include "../include/ProtocoloMarcha.hpp"
#include <stdexcept>

ProtocoloMarcha::ProtocoloMarcha() {}
ProtocoloMarcha::~ProtocoloMarcha() {}

void ProtocoloMarcha::quedaEnergia(const std::vector<std::shared_ptr<Maquina>>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) continue;
        maquinas[i]->ligarDesligar(false);
    }
}

void ProtocoloMarcha::equalizarRPM(const std::vector<std::shared_ptr<Maquina>>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) {
            throw std::runtime_error("Erro de sincronia: Maquina nula encontrada ao equalizar RPM.");
        }
        maquinas[i]->modoMarcha();
    }
}

void ProtocoloMarcha::modoNormal(const std::vector<std::shared_ptr<Maquina>>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) continue;
        maquinas[i]->ligarDesligar(true);
    }
}