#include "../include/Operador.hpp"
#include "../include/Maquina.hpp"


Operador::Operador(std::string nome, std::string turno) 
    : nome(nome), turno(turno), m(nullptr) {
        if(nome.empty()){throw std::invalid_argument("OPERADOR SEM NOME!");}
        if(turno != "MANHA" && turno!= "TARDE" && turno != "NOITE"){throw std::invalid_argument("TURNO INVALIDO");}
    }

Operador::~Operador() {}

void Operador::alocarMaquina(Maquina *m) {
    if(m == nullptr){throw std::invalid_argument("MAQUINA INEXISTENTE!");}
    if(m->getStatus() == m->QUEBRADA){throw std::invalid_argument("MAQUINA QUEBRADA!");}
    this->m = m;
}

void Operador::realocarMaquina(Operador* opAtual,Maquina *m) {
    if(m == nullptr){throw std::invalid_argument("MAQUINA INEXISTENTE!");}
    if(opAtual == nullptr){throw std::invalid_argument("OPERADOR INEXISTENTE!");}
   opAtual->desatribuirMaquina(m);
   this->m = m;
}

void Operador::desatribuirMaquina(Maquina *m) {
    if(m == nullptr){throw std::invalid_argument("MAQUINA INEXISTENTE!");}
    if (this->m == m) {
        this->m = nullptr;
    }
}

std::string Operador::getNome() const{

    return this->nome;
}