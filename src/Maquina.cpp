#include "../include/Maquina.hpp"
#include "../include/Operador.hpp"
#include "../include/cores.hpp"
#include<cstdlib>
#include<ctime>
using namespace Cores;

using std::string;

Maquina::Maquina(string id, Sensor *temperatura, Sensor *velocidade) {
    if(id.empty()){throw std::invalid_argument("MAQUINA SEM IDENTIFICACAO!");}
    else if(temperatura == nullptr){throw std::invalid_argument("SENSOR DE TEMPERATURA INEXISTENTE");}
    else if (velocidade == nullptr){throw std::invalid_argument("SENSOR DE ROTACAO INEXISTENTE");}
    this->id = id;
    this->s[0] = temperatura;
    this->s[1] = velocidade;
    this->status = DESLIGADA;
    this->op = nullptr;
    alertaCiclos = 0;
    this->tempoDecorridoRPM = 60;
};

Maquina::~Maquina() {}

void Maquina::atualizarEstado() {
    if(s[0]->getHistoricoVazio() || s[1]->getHistoricoVazio()) {
        
        return;
    }
    if (this->status == MARCHA) { 
        return;
    }
    if((s[0] != nullptr && !s[0]->getHistoricoVazio() && s[0]->alerta()) ||(s[1] != nullptr && !s[1]->getHistoricoVazio() && s[1]->alerta())){
        
        status = QUEBRADA;
    } else if(status == QUEBRADA) {
        
        status = DESLIGADA;  
    } else if(s[1]->retornaAtual() > 8000 && s[1]->retornaAtual() < 13000){
        status = ATIVA;
        alertaCiclos = 0;
    } else if((s[1]->retornaAtual() > 6999 && s[1]->retornaAtual() <= 8000) || (s[1]->retornaAtual() >= 13000 && s[1]->retornaAtual() <= 14000)){
        status = ALERTA;
        alertaCiclos++;
        if(alertaCiclos == 3){
            status = DESLIGADA;
            alertaCiclos = 0;
        }
    } 
};

void Maquina::ligarDesligar(bool x) {

    this->status = x ? ATIVA : DESLIGADA;
};

bool Maquina::modoMarcha() {
    if (this->status == ATIVA) {
        this->status = MARCHA;
        return true;
    }
    return false;
};

void Maquina::refOp(Operador *op) {
    this->op = op;
};

void Maquina::exibir() const{

    string statusStr;
    string corStatus;
    if(s[1] == nullptr){throw std::runtime_error("ERRO SENSOR DE ROTACAO NULO");}
    if(s[1]->retornaAtual() < 0){throw std::runtime_error("ERRO SENSOR DE RPM NEGATIVO");}
    if(s[0] == nullptr){throw std::runtime_error("ERRO SENSOR DE TEMPERATURA NULO");}
    std::cout << GRAY << BLACK;
    std::cout<<"ID..........: "<<this->id<<std::endl;
    if(this->op != nullptr){
    std::cout<<"OPERADOR....: "<<op->getNome()<<std::endl;
    } else {
        std::cout<<"OPERADOR....: sem operador!"<<std::endl;
    }
    std::cout<<"RPM.........: "<<s[1]->retornaAtual()<<std::endl;
    std::cout<<"TEMPERATURA.: "<<s[0]->retornaAtual()<<std::endl;
    if (status == ATIVA) {       
        statusStr = "ATIVA";
        corStatus = GREEN;
    }
    else if (status == QUEBRADA) {
        statusStr = "QUEBRADA";
        corStatus = RED;
    }
    else if (status == ALERTA) {
        statusStr = "ALERTA";
        corStatus = YELLOW;
    }
    else if(status == MARCHA){
        statusStr = "MARCHA";
        corStatus = BLUE;
    }
    else {
        statusStr = "DESLIGADA";
        corStatus = BLACK;
    } 


    std::cout << "STATUS......: " << corStatus << statusStr << RESET << std::endl;;

};
void Maquina::simulVar() {

    if (this->status == MARCHA) {
        s[1]->registraHist(8000); 
               
        double minTemp = s[0]->getLimMin() + 2;
        double maxTemp = s[0]->getLimMax() - 2;
        double valorTemp = minTemp + (rand() % (int)(maxTemp - minTemp));
        s[0]->registraHist(valorTemp);
        
        return; 
    }
    
    double minVal = 0;
    double maxVal = 0;

    if(s[0]->getTipo() == "temperatura"){
        minVal = s[0]->getLimMin() + 2;
        maxVal = s[0]->getLimMax() - 2;
    } else {
        throw std::runtime_error("Erro no simulVar: s[0] nao e do tipo temperatura!");
    }

    double valor = minVal + (rand() % (int)(maxVal - minVal));
    s[0]->registraHist(valor);

    if(s[1]->getTipo() == "rpm"){
        this->tempoDecorridoRPM++;

        if (this->tempoDecorridoRPM >= 60) {
            minVal = s[1]->getLimMin() + 500;
            maxVal = s[1]->getLimMax() - 500;
            double valor2 = minVal + (rand() % (int)(maxVal - minVal));
            s[1]->registraHist(valor2);
            this->tempoDecorridoRPM = 0;
        } else {
            s[1]->registraHist(s[1]->retornaAtual());
        }
    } else {
        throw std::runtime_error("Erro no simulVar: s[1] nao e do tipo rpm!");
    }
}
Maquina::Status Maquina::getStatus() const {
    return this->status;
};

Sensor* Maquina::getSensorTemp() const{
    return this->s[0];
};

Sensor* Maquina::getSensorRpm() const{
    return this->s[1];
};
Operador* Maquina::getOp() const{
    return this->op;
};
string Maquina::getId() const{
    return this->id;
};
int Maquina::getCiclos()const{
    return this->alertaCiclos;
}