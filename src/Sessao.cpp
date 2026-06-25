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

void Sessao::salvarSessao(const std::vector<std::shared_ptr<Maquina>>& maquinas) const{

    std::ofstream arquivo("sessao_anterior.txt");
    if(!arquivo.is_open()){
        std::cerr << "Erro ao salvar o estado da sessao." << std::endl;
        return;
    }
    for(const auto& m: maquinas){
        if(m){
            arquivo<<m->getId();
        }
    }
    arquivo.close();
};

void Sessao::carregarSessao(SistemaMonitor& sistema, std::vector<std::shared_ptr<Sensor>>& sensoresAtivos) const{
    
    std::ifstream arquivo("sessao_anterior.txt");
    if(!arquivo.is_open()){
        std::cerr <<"SESSÃO ANTERIOR INEXISTENTE"<<std::endl;
        return;
    }

    std::string svId;
    while(std::getline(arquivo, svId)){
        if (svId.empty()){
            continue;
        };
        auto newTemp = std::make_shared<Sensor>(svId + "-T", "temperatura");
        auto newRpm = std::make_shared<Sensor>(svId + "-R", "rpm");
        sensoresAtivos.push_back(newTemp);
        sensoresAtivos.push_back(newRpm);
        auto novaMaq = std::make_shared<Maquina>(svId, newTemp.get(), newRpm.get());
        novaMaq->ligarDesligar(true);
        sistema.adicionarMaquinas(novaMaq);
    }
    arquivo.close();
}