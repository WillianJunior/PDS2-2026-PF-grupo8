#include "../include/SistemaMonitor.hpp"

using std::string;
using std::vector;

SistemaMonitor::SistemaMonitor() {

};

SistemaMonitor::~SistemaMonitor() {
    // Deleta os ponteiros para nao dar leak de memoria
   /* for (size_t i = 0; i < this->machine.size(); i++) {
        delete this->machine[i];
    }
    for (size_t i = 0; i < this->op.size(); i++) {
        delete this->op[i];
    }*/
};

void SistemaMonitor::adicionarMaquinas(Maquina* maquina) {
    this->machine.push_back(maquina);
};

void SistemaMonitor::removerMaquinas(string id) {
    for (size_t i = 0; i < this->machine.size(); i++) {
        if (this->machine[i]->getStatus() != Maquina::DESLIGADA) { // exemplo de logica basica
            // Se precisar do getId(), use aqui. Como Maquina tem getStatus, usei de exemplo
        }
        // Lógica de busca simples por indice
        if (this->machine[i]->getStatus() == Maquina::QUEBRADA) {
            this->machine.erase(this->machine.begin() + i);
            break;
        }
    }
};

void SistemaMonitor::cadastrarOperador(Operador* op) {
    this->op.push_back(op);
};

void SistemaMonitor::atribuirMaquinasOperador() {
    // Vincula o operador i com a maquina i ate onde der
    size_t limite = this->machine.size();
    if (this->op.size() < limite) {
        limite = this->op.size();
    }

    for (size_t i = 0; i < limite; i++) {
        this->op[i]->alocarMaquina(this->machine[i]);
        this->machine[i]->refOp(this->op[i]);
    }
};

void SistemaMonitor::protocoloMarcha() {
    for (size_t i = 0; i < this->machine.size(); i++) {
        this->machine[i]->modoMarcha();
    }
};

void SistemaMonitor::cicloMonitoramento() {
    for (size_t i = 0; i < this->machine.size(); i++) {
        this->machine[i]->simulVar();
        this->machine[i]->atualizarEstado();
    }
};

void SistemaMonitor::exibirDados() const {
    std::cout << "--- Dados do Sistema ---" << std::endl;
    for (size_t i = 0; i < this->machine.size(); i++) {
        this->machine[i]->exibir();
    }
};

const vector<Maquina*>& SistemaMonitor::getMaquinas() const {
    return this->machine;
};