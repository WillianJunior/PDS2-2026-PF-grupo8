#include "../include/Relatorio.hpp"
#include <stdexcept>

Relatorio::Relatorio() {}
Relatorio::~Relatorio() {}

void Relatorio::registraTempMaxMin(std::shared_ptr<const Maquina> m) {
    if (!m) {
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraTempMaxMin.");
    }
    std::ofstream arquivo("relatorio_temperatura.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "Registrando temperaturas da maquina." << std::endl;
        arquivo.close();
    }
}

void Relatorio::registraRpmMaxMin(std::shared_ptr<const Maquina> m) {
    if (!m) {
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraRpmMaxMin.");
    }
    std::ofstream arquivo("relatorio_rpm.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "Registrando RPM da maquina." << std::endl;
        arquivo.close();
    }
}

void Relatorio::registraAnomalia(std::shared_ptr<const Maquina> m) {
    if (!m) {
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraAnomalia.");
    }
    if (m->getStatus() == Maquina::QUEBRADA) {
        std::ofstream arquivo("anomalias.txt", std::ios::app);
        if (arquivo.is_open()) {
            arquivo << "Alerta: Maquina com status QUEBRADA detectada." << std::endl;
            arquivo.close();
        }
    }
}

void Relatorio::gerarResumo(const std::vector<std::shared_ptr<Maquina>>& maquinas) {
    std::cout << "--- RESUMO DO DIA ---" << std::endl;
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) continue;
        maquinas[i]->exibir();
    }
}