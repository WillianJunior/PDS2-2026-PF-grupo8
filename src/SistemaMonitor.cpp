#include "../include/SistemaMonitor.hpp"

using std::string;
using std::vector;

SistemaMonitor::SistemaMonitor() {

};
SistemaMonitor::~SistemaMonitor() {

};

void SistemaMonitor::adicionarMaquinas(Maquina* maquina) {
    this->machine.push_back(maquina);
};

void SistemaMonitor::removerMaquinas(string id) {

};
void SistemaMonitor::cadastrarOperador(Operador* op) {

};
void SistemaMonitor::atribuirMaquinasOperador() {

};
void SistemaMonitor::protocoloMarcha() {

};
void SistemaMonitor::cicloMonitoramento() {

};
void SistemaMonitor::exibirDados() const {

};

const vector<Maquina*>& SistemaMonitor::getMaquinas() const {
    return this->machine;
};