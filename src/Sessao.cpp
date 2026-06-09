#include "../include/Sessao.hpp"

Sessao::Sessao() {}
Sessao::~Sessao() {}

void Sessao::inicializarMaquinas(vector<Maquina*>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        maquinas[i]->ligarDesligar(true);
        maquinas[i]->atualizarEstado();
    }
}

void Sessao::relatorioSessao() {
    std::cout << "Fim do expediente: Relatorio emitido." << std::endl;
}

void Sessao::contarMaquinasAtivas(const vector<Maquina*>& maquinas) const {
    int ativas = 0;
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (maquinas[i]->getStatus() == Maquina::ATIVA || maquinas[i]->getStatus() == Maquina::MARCHA) {
            ativas++;
        }
    }
    std::cout << "Total de maquinas ativas: " << ativas << std::endl;
}