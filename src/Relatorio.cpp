#include "../include/Relatorio.hpp"

using std::vector;
Relatorio::Relatorio() {}
Relatorio::~Relatorio() {}

void Relatorio::registraTempMaxMin(const Maquina *m) {
    std::ofstream arquivo("relatorio_temperatura.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "Registrando temperaturas da maquina." << std::endl;
        arquivo.close();
    }
}

void Relatorio::registraRpmMaxMin(const Maquina *m) {
    std::ofstream arquivo("relatorio_rpm.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "Registrando RPM da maquina." << std::endl;
        arquivo.close();
    }
}

void Relatorio::registraAnomalia(const Maquina* m) {
    if (m->getStatus() == Maquina::QUEBRADA) {
        std::ofstream arquivo("anomalias.txt", std::ios::app);
        if (arquivo.is_open()) {
            arquivo << "Alerta: Maquina com status QUEBRADA detectada." << std::endl;
            arquivo.close();
        }
    }
}

void Relatorio::gerarResumo(const vector<Maquina*>& maquinas) {
    std::cout << "--- RESUMO DO DIA ---" << std::endl;
    for (size_t i = 0; i < maquinas.size(); i++) {
        maquinas[i]->exibir();
    }
}