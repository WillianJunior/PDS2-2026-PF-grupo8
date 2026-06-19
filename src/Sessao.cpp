#include "../include/Sessao.hpp"
#include <stdexcept>

Sessao::Sessao() {}
Sessao::~Sessao() {}

void Sessao::inicializarMaquinas(std::vector<std::shared_ptr<Maquina>>& maquinas) {
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) {
            throw std::runtime_error("Erro: Tentativa de inicializar maquina inexistente.");
        }
        maquinas[i]->ligarDesligar(true);
        maquinas[i]->atualizarEstado();
    }
}

void Sessao::relatorioSessao() {
    std::cout << "Fim do expediente: Relatorio emitido." << std::endl;
}

void Sessao::contarMaquinasAtivas(const std::vector<std::shared_ptr<Maquina>>& maquinas) const {
    int ativas = 0;
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) {throw std::runtime_error("Erro ao tentar contar maquina nula");};
        if (maquinas[i]->getStatus() == Maquina::ATIVA || maquinas[i]->getStatus() == Maquina::MARCHA) {
            ativas++;
        }
    }
    std::cout << "Total de maquinas ativas: " << ativas << std::endl;
}