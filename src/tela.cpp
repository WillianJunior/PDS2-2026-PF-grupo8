#include<iostream>
#include<cstdlib>
#include"tela.hpp"
#include"cores.hpp"
using namespace Cores;


Tela::Tela(){};
void Tela::limparTela(){
    system("clear");
};

void Tela::exibirCabecalho(){

    std::cout << GRAY << BLACK;
    std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║             SISTEMA DE MONITORAMENTO DE MÁQUINAS             ║\n";
    std::cout << "║                                                              ║\n";
    std::cout << "╠══════════════════════════════════════════════════════════════╣\n";
    std::cout << RESET;
};

void Tela::exibirRodape(){
    
    std::cout << GRAY << BLACK;
    // Linha 1 de comandos
    std::cout<< "║ [r] Relatório   [a] Add Máq   [m] Trocar Modo   [q] Sair     ║\n";
    // Linha 2 com os novos comandos adicionados
    std::cout<< "║ [o] Designar Op [x] Remover Op [g] Gerar TXT                 ║\n";
    std::cout<< "╚══════════════════════════════════════════════════════════════╝\n";
    std::cout<<RESET;

}

void Tela::exibirMaquinas(const std::vector<std::shared_ptr<Maquina>>& maquinas){
    const int largura = 20;
    
    auto pad = [&](std::string s) -> std::string {
        if(s.size() >= largura) return s.substr(0, largura);
        return s + std::string(largura - s.size(), ' ');
    };

    for(size_t i = 0; i < maquinas.size(); i += 4){
        size_t fim = std::min(i + 4, maquinas.size());
        
        
        for(size_t j = i; j < fim; j++)
            std::cout << GRAY << BLACK << "| ID: " << pad(maquinas[j]->getId()) << " ";
        std::cout << "|\n";

        
        for(size_t j = i; j < fim; j++){
            std::string op = maquinas[j]->getOp() ? maquinas[j]->getOp()->getNome() : "sem operador";
            std::cout << GRAY << BLACK << "| OP: " << pad(op) << " ";
        }
        std::cout << "|\n";

        
        for(size_t j = i; j < fim; j++)
            std::cout << GRAY << BLACK << "| RPM: " << pad(std::to_string((int)maquinas[j]->getSensorRpm()->retornaAtual())) << " ";
        std::cout << "|\n";

        
        for(size_t j = i; j < fim; j++)
            std::cout << GRAY << BLACK << "| TMP: " << pad(std::to_string((int)maquinas[j]->getSensorTemp()->retornaAtual())) << " ";
        std::cout << "|\n";

        
        for(size_t j = i; j < fim; j++){
            std::string corStatus, statusStr;
            if(maquinas[j]->getStatus() == Maquina::ATIVA){ corStatus = GREEN; statusStr = "ATIVA"; }
            else if(maquinas[j]->getStatus() == Maquina::QUEBRADA){ 
                corStatus = RED; 
                statusStr = "QUEBRADA"; 
            }
            else if(maquinas[j]->getStatus() == Maquina::ALERTA)
            { 
                corStatus = YELLOW; 
                statusStr = "ALERTA"; 
            }
            else if(maquinas[j]->getStatus() == Maquina::MARCHA){ 
                corStatus = BLUE; 
                statusStr = "MARCHA";
            }
            else { 
                corStatus = BLACK; 
                statusStr = "DESLIGADA"; 
            }
            std::cout << GRAY << BLACK << "| ST: " << corStatus << pad(statusStr) << GRAY << BLACK << " ";
        };
        std::cout << RESET << "|\n\n";
    };
};