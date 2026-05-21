#include "../include/Maquina.hpp"
#include "../include/Operador.hpp"

using std::string;

Maquina::Maquina(string id, Sensor *temperatura, Sensor *velocidade) {
    this->id = id;
    this->s[0] = temperatura;
    this->s[1] = velocidade;
    this->status = DESLIGADA;
    this->op = nullptr;
}

Maquina::~Maquina() {}

void Maquina::atualizarEstado() {}

void Maquina::ligarDesligar(bool x) {
    this->status = x ? ATIVA : DESLIGADA;
}

bool Maquina::modoMarcha() {
    if (this->status == ATIVA) {
        this->status = MARCHA;
        return true;
    }
    return false;
}

void Maquina::refOp(Operador *op) {
    this->op = op;
}

void Maquina::exibir() {}
void Maquina::simulVar() {}

Maquina::Status Maquina::getStatus() const {
    return this->status;
}