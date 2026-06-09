#include "../include/Maquina.hpp"
#include "../include/AlertaManager.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    Sensor temperatura("temp01", "temperatura");
    Sensor rpm("rpm01", "rpm");

    std::cout << "sensores criados" << std::endl;

    Maquina m("maquina01", &temperatura, &rpm);
    std::cout << "maquina criada" << std::endl;

    m.ligarDesligar(true);
    std::cout << "maquina ligada" << std::endl;

    while(true) {
    system("clear");
    m.simulVar();
    m.atualizarEstado();
    m.exibir();
    if (m.getStatus() == Maquina::QUEBRADA) break;
    sleep(1);; // espera 1 segundo
}

    return 0;
}