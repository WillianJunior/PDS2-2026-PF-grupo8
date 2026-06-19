#include "../include/Maquina.hpp"
#include "../include/Operador.hpp"
#include<cstdlib>
#include<ctime>

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
};

Maquina::~Maquina() {}

void Maquina::atualizarEstado() {
    
    if((s[0] != nullptr && !s[0]->getHistoricoVazio() && s[0]->alerta()) ||(s[1] != nullptr && !s[1]->getHistoricoVazio() && s[1]->alerta())){
        
        status = QUEBRADA;
    } else if(status == QUEBRADA) {
        
        status = DESLIGADA;  
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

void Maquina::exibir() {

    string statusStr;
    if(s[1] == nullptr){throw std::runtime_error("ERRO SENSOR DE ROTACAO NULO");}
    if(s[0] == nullptr){throw std::runtime_error("ERRO SENSOR DE TEMPERATURA NULO");}
    std::cout<<"ID..........: "<<this->id<<std::endl;
    if(this->op != nullptr){
    std::cout<<"OPERADOR....: "<<op->getNome()<<std::endl;
    } else {
        std::cout<<"OPERADOR....: sem operador!"<<std::endl;
    }
    std::cout<<"RPM.........: "<<s[1]->retornaAtual()<<std::endl;
    std::cout<<"TEMPERATURA.: "<<s[0]->retornaAtual()<<std::endl;
    if (status == ATIVA) statusStr = "ATIVA";
    else if (status == QUEBRADA) statusStr = "QUEBRADA";
    else if (status == MARCHA) statusStr = "MARCHA";
    else statusStr = "DESLIGADA";

std::cout << "STATUS......: " << statusStr << std::endl;

};
void Maquina::simulVar() {

    srand(time(nullptr));
    double minVal;
    double maxVal;

    if(s[0]->getTipo() == "temperatura"){
        minVal = s[0]->getLimMin() * 0.8;
        maxVal = s[0]->getLimMax() * 1.2;
    }   

    double valor = minVal + (rand() % (int)(maxVal - minVal));
    s[0]->registraHist(valor);

    if(s[1]->getTipo() == "rpm"){

        minVal = s[1]->getLimMin() - 2000;
        maxVal = s[1]->getLimMax() + 5000;
    }

    double valor2 = minVal + (rand() % (int)(maxVal - minVal));
    s[1]->registraHist(valor2);
};

Maquina::Status Maquina::getStatus() const {
    return this->status;
};

string Maquina::getId() const{
    return this->id;
}