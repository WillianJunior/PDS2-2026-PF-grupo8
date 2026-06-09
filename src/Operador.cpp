#include "../include/Operador.hpp"
#include "../include/Maquina.hpp"

Operador::Operador(std::string nome, std::string turno) 
    : nome(nome), turno(turno), m(nullptr) {}

Operador::~Operador() {}

void Operador::alocarMaquina(Maquina *m) {
    this->m = m;
}

void Operador::realocarMaquina(Operador* opAtual,Maquina *m) {
    
   opAtual->desatribuirMaquina(m);
   this->m = m;
}

void Operador::desatribuirMaquina(Maquina *m) {
    if (this->m == m) {
        this->m = nullptr;
    }
}

string Operador::getNome() const{

    return this->nome;
}