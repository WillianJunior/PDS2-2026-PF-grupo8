#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <stdexcept>
#include "../include/tela.hpp"
#include "../include/SistemaMonitor.hpp"
#include "../include/Sensor.hpp"
#include "../include/Maquina.hpp"
#include "../include/Operador.hpp"
#include "../include/Relatorio.hpp"
#include "../include/Sessao.hpp"
#include "../include/ProtocoloMarcha.hpp"

int main() {
    Tela tela;
    SistemaMonitor sistema;
    Relatorio geradorRelatorio;
    ProtocoloMarcha ritmo;
    Sessao controlSessao;

    std::vector<std::shared_ptr<Sensor>> sensoresAtivos;
    std::vector<std::shared_ptr<Operador>> operadoresAtivos;
    controlSessao.carregarSessao(sistema, sensoresAtivos);
    
    

    
    auto temp1 = std::make_shared<Sensor>("TEMP-01", "temperatura");
    auto rpm1 = std::make_shared<Sensor>("RPM-01", "rpm");
    
    sensoresAtivos.push_back(temp1);
    sensoresAtivos.push_back(rpm1);

    auto m1 = std::make_shared<Maquina>("MAQ-01", temp1.get(), rpm1.get());
    m1->ligarDesligar(true); 
    sistema.adicionarMaquinas(m1);
    

    srand(time(nullptr)); 

    std::atomic<bool> rodando(true);
    std::atomic<bool> pausarTela(false); 

    
    std::thread inputThread([&](){
        char c;
        while(rodando){
            std::cin >> c;
            
            if(c == 'q') {
                rodando = false;
            } 
            else if(c == 'm') {
                sistema.protocoloMarcha();
            } 
            else if(c == 'r') {
                pausarTela = true; 
                std::cout << "\n--- RELATORIO DE DADOS DO SISTEMA ---\n";
                sistema.exibirDados();
                
                std::cout << "\nDigite [v] e aperte Enter para voltar a tela: ";
                char temp;
                std::cin >> temp;
                pausarTela = false; 
            } 
            else if(c == 'a') {
                pausarTela = true; 
                
                std::string idStr;
                std::cout << "\n--- ADICIONAR NOVA MAQUINA ---\n";
                std::cout << "Digite o ID (ex: MAQ-02) e pressione Enter: ";
                std::cin >> idStr;

                auto newTemp = std::make_shared<Sensor>(idStr + "-T", "temperatura");
                auto newRpm = std::make_shared<Sensor>(idStr + "-R", "rpm");
                
                sensoresAtivos.push_back(newTemp);
                sensoresAtivos.push_back(newRpm);

                auto novaMaq = std::make_shared<Maquina>(idStr, newTemp.get(), newRpm.get());
                novaMaq->ligarDesligar(true); 
                
                sistema.adicionarMaquinas(novaMaq);
                
                std::cout << "Maquina " << idStr << " adicionada com sucesso!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2)); 
                pausarTela = false; 
            }
            else if (c == 'o') {
                pausarTela = true;
                std::string idMaq, nomeOp, turnoOp;
                std::cout << "\n--- DESIGNAR OPERADOR ---\n";
                std::cout << "ID da maquina (ex: MAQ-01): ";
                std::cin >> idMaq;

                std::shared_ptr<Maquina> maqAlvo = nullptr;
                for(auto& m : sistema.getMaquinas()){
                    if(m->getId() == idMaq) { maqAlvo = m; break; }
                }

                if(maqAlvo){
                    std::cout << "Nome do Operador (sem espacos): ";
                    std::cin >> nomeOp;
                    std::cout << "Turno (MANHA/TARDE/NOITE): ";
                    std::cin >> turnoOp;

                    try {
                        auto novoOp = std::make_shared<Operador>(nomeOp, turnoOp);
                        operadoresAtivos.push_back(novoOp); 
                        
                        novoOp->alocarMaquina(maqAlvo.get());
                        maqAlvo->refOp(novoOp.get());
                        
                        std::cout << "Operador " << nomeOp << " designado com sucesso!\n";
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Erro ao criar operador: " << e.what() << "\n";
                    }
                } else {
                    std::cout << "Erro: Maquina nao encontrada!\n";
                }
                
                std::this_thread::sleep_for(std::chrono::seconds(2));
                pausarTela = false;
            }
            else if (c == 'x') {
                pausarTela = true;
                std::string idMaq;
                std::cout << "\n--- REMOVER OPERADOR ---\n";
                std::cout << "ID da maquina para desvincular operador: ";
                std::cin >> idMaq;

                std::shared_ptr<Maquina> maqAlvo = nullptr;
                for(auto& m : sistema.getMaquinas()){
                    if(m->getId() == idMaq) { maqAlvo = m; break; }
                }

                if(maqAlvo && maqAlvo->getOp() != nullptr){
                    Operador* opAtual = maqAlvo->getOp();
                    opAtual->desatribuirMaquina(maqAlvo.get());
                    maqAlvo->refOp(nullptr);
                    std::cout << "Operador removido da " << idMaq << " com sucesso!\n";
                } else {
                    std::cout << "Erro: Maquina nao encontrada ou ja esta sem operador.\n";
                }
                
                std::this_thread::sleep_for(std::chrono::seconds(2));
                pausarTela = false;
            }
            else if (c == 'g') {
                pausarTela = true;
                std::cout << "\n--- GERANDO RELATORIOS TXT ---\n";
                
                for(auto& m : sistema.getMaquinas()){
                    geradorRelatorio.registraTempMaxMin(m);
                    geradorRelatorio.registraRpmMaxMin(m);
                    geradorRelatorio.registraAnomalia(m);
                }
                
                std::cout << "Arquivos de relatorio atualizados com sucesso!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                pausarTela = false;
            }
        }
    });    
    while(rodando){
             sistema.cicloMonitoramento();       
        if (!pausarTela) {
            tela.limparTela();
            tela.exibirCabecalho();
            tela.exibirMaquinas(sistema.getMaquinas());
            tela.exibirRodape();
        }                
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if(inputThread.joinable()){
        inputThread.join();
    }
    controlSessao.salvarSessao(sistema.getMaquinas());
    return 0;
}