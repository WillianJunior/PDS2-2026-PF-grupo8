#include "../include/SistemaMonitor.hpp"
#include <stdexcept>

SistemaMonitor::SistemaMonitor() {}
SistemaMonitor::~SistemaMonitor() {}

void SistemaMonitor::adicionarMaquinas(std::shared_ptr<Maquina> maquina) {
    if (!maquina) {
        throw std::invalid_argument("Erro: Nao e possivel adicionar uma maquina nula ao monitor.");
    }
    this->machine.push_back(maquina);
}

void SistemaMonitor::removerMaquinas(std::string id) {
    if (id.empty()) {
        throw std::invalid_argument("Erro: ID fornecido para remocao esta vazio.");
    }
    for (size_t i = 0; i < this->machine.size(); i++) {
        if (this->machine[i]->getStatus() == Maquina::QUEBRADA) {
            this->machine.erase(this->machine.begin() + i);
            break;
        }
    }
}

void SistemaMonitor::cadastrarOperador(std::shared_ptr<Operador> operador) {
    if (!operador) {
        throw std::invalid_argument("Erro: Nao e possivel cadastrar um operador nulo.");
    }
    this->op.push_back(operador);
}

void SistemaMonitor::atribuirMaquinasOperador() {
    size_t limite = this->machine.size();
    if (this->op.size() < limite) {
        limite = this->op.size();
    }

    for (size_t i = 0; i < limite; i++) {
        this->op[i]->alocarMaquina(this->machine[i].get());
        this->machine[i]->refOp(this->op[i].get());
    }
}

void SistemaMonitor::protocoloMarcha() {
    for (size_t i = 0; i < this->machine.size(); i++) {
        this->machine[i]->modoMarcha();
    }
}

void SistemaMonitor::cicloMonitoramento() {
    for (size_t i = 0; i < this->machine.size(); i++) {
        this->machine[i]->simulVar();
        this->machine[i]->atualizarEstado();
    }
}

void SistemaMonitor::exibirDados() const {
    std::cout << "--- Dados do Sistema ---" << std::endl;
    for (size_t i = 0; i < this->machine.size(); i++) {
        this->machine[i]->exibir();
    }
}

const std::vector<std::shared_ptr<Maquina>>& SistemaMonitor::getMaquinas() const {
    return this->machine;
}