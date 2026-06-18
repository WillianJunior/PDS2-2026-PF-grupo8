#ifndef SISTEMAMONITOR_H
#define SISTEMAMONITOR_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Maquina.hpp"
#include "Operador.hpp"

class SistemaMonitor {
private:
    std::vector<std::shared_ptr<Maquina>> machine;
    std::vector<std::shared_ptr<Operador>> op;

public:
    SistemaMonitor();
    ~SistemaMonitor();

    void adicionarMaquinas(std::shared_ptr<Maquina> maquina);
    void removerMaquinas(std::string id);
    void cadastrarOperador(std::shared_ptr<Operador> op);
    void atribuirMaquinasOperador();
    void protocoloMarcha();
    void cicloMonitoramento();
    void exibirDados() const;

    const std::vector<std::shared_ptr<Maquina>>& getMaquinas() const;
};

#endif