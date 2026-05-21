#include "../include/Operador.hpp"
#include "../include/Maquina.hpp"

Operador::Operador(string nome, string turno) 
    : nome(nome), turno(turno), m(nullptr) {}

Operador::~Operador() {}

void Operador::alocarMaquina(Maquina *m) {
    this->m = m;
}

void Operador::realocarMaquina(Maquina *m) {
    this->m = m;
}

void Operador::desatribuirMaquina(Maquina *m) {
    if (this->m == m) {
        this->m = nullptr;
    }
}