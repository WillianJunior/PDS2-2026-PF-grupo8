#include "../include/Relatorio.hpp"
#include <stdexcept>
#include<ctime>

Relatorio::Relatorio() {}
Relatorio::~Relatorio() {}

void Relatorio::registraTempMaxMin(std::shared_ptr<const Maquina> m) {
    if (!m) {
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraTempMaxMin.");
    }
    
    std::ofstream arquivo("relatorio_temperatura.txt", std::ios::app);
    if(!arquivo.is_open()){throw std::runtime_error("ERRO AO ABRIR ARQUIVO");}
    Sensor* tempSensor = m->getSensorTemp();
    if (tempSensor && !tempSensor->getHistoricoVazio()) {
        try {
            arquivo << "Máquina: " << m->getId() 
                    << " | Temperatura Mínima: " << tempSensor->calcularMinRegistrado() 
                    << "°C | Temperatura Máxima: " << tempSensor->calcularMaxRegistrado() << "°C" 
                    << std::endl;
        } catch (const std::runtime_error& e) {
            arquivo << "Máquina: " << m->getId() << " | Erro ao ler histórico: " << e.what() << std::endl;
        }
    } else {
        arquivo << "Máquina: " << m->getId() << " | Sem histórico de temperatura disponível." << std::endl;
    }
    
    arquivo.close();
    
};

void Relatorio::registraRpmMaxMin(std::shared_ptr<const Maquina> m) {
    if (!m) {
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraRpmMaxMin.");
    }
    std::ofstream arquivo("relatorio_rpm.txt", std::ios::app);
    if(!arquivo.is_open()){throw std::runtime_error("ERRO AO ABRIR ARQUIVO");}
    Sensor* rpmSensor = m->getSensorRpm();
    if (rpmSensor && !rpmSensor->getHistoricoVazio()) {
        try {
            arquivo << "Máquina: " << m->getId() 
                    << " | RPM Mínimo: " << (int)rpmSensor->calcularMinRegistrado() 
                    << " | RPM Máximo: " << (int)rpmSensor->calcularMaxRegistrado() 
                    << std::endl;
        } catch (const std::runtime_error& e) {
            arquivo << "Máquina: " << m->getId() << " | Erro ao ler histórico: " << e.what() << std::endl;
        }
    } else {
        arquivo << "Máquina: " << m->getId() << " | Sem histórico de RPM disponível." << std::endl;
    }
    
    arquivo.close();
}

void Relatorio::registraAnomalia(std::shared_ptr<const Maquina> m) {
    if (!m) {
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraAnomalia.");
    }
    if (m->getStatus() == Maquina::QUEBRADA) {
        std::ofstream arquivo("anomalias.txt", std::ios::app);
        if(!arquivo.is_open()){throw std::runtime_error("ERRO AO ABRIR ARQUIVO DE HISTORICO");}       
        arquivo << "Alerta: Maquina com status QUEBRADA detectada." << std::endl;
        arquivo.close();
        
    }
}

void Relatorio::gerarResumo(const std::vector<std::shared_ptr<Maquina>>& maquinas) {
    std::cout << "--- RESUMO DO DIA ---" << std::endl;
    for (size_t i = 0; i < maquinas.size(); i++) {
        if (!maquinas[i]) {throw std::runtime_error("Maquina nula encontrada ao pedir resumo");};;
        maquinas[i]->exibir();
    }
}

void Relatorio::registrarDesligamentoAlerta(std::shared_ptr<const Maquina> m){
    if(!m){
        throw std::invalid_argument("Erro: Ponteiro de maquina nulo em registraAnomalia.");
    }
    if(m->getStatus() == Maquina::DESLIGADA && m->getCiclos() >= 2){
        time_t agora = time(nullptr);
        std::string dataHora = ctime(&agora);
        std::ofstream arquivo("anomalias.txt", std::ios::app);
        if(!arquivo.is_open()){throw std::runtime_error("ERRO AO ABRIR ARQUIVO DE HISTORICO");}       
        arquivo << " Maquina "<< m->getId() <<" desligada por comportamento irregular D/M/A/H: " << dataHora;
        arquivo.close();
    }
    
}
    
