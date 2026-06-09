#include "../include/ProtocoloMarcha.hpp"

using std::vector;

ProtocoloMarcha::ProtocoloMarcha() {};
ProtocoloMarcha::~ProtocoloMarcha() {};

void ProtocoloMarcha::quedaEnergia(const vector<Maquina*>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        maquinas[i]->ligarDesligar(false);
    }
};

void ProtocoloMarcha::equalizarRPM(const vector<Maquina*>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        maquinas[i]->modoMarcha();
    }
};

void ProtocoloMarcha::modoNormal(const vector<Maquina*>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        maquinas[i]->ligarDesligar(true);
    }
};