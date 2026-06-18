#include "../include/AlertaManager.hpp"
#include<fstream>
#include<ctime>

using std::string;
using std::vector;

AlertaManager::AlertaManager() {

};
AlertaManager::~AlertaManager() {

};

void AlertaManager::receberAlertas(Sensor *s) {
    if(s == nullptr){throw std::invalid_argument("SENSOR INEXISTENTE!");}
    if (s->alerta()) {
        ativos.push_back(classificarSeveridade(s));
    }
};

string AlertaManager::classificarSeveridade(Sensor *s) {
    if(s == nullptr){throw std::invalid_argument("SENSOR INEXISTENTE!");}
    double excesso = 0.0;

    if (s->retornaAtual() > s->getLimMax()){
        excesso = (s->retornaAtual() - s->getLimMax()) / s->getLimMax();
    }
    else if (s->retornaAtual() < s->getLimMin()){
        excesso = (s->getLimMin() - s->retornaAtual()) / s->getLimMin();
    }
    if (excesso > 0.2){
        return s->getId() + " CRITICO";
    }
    else 
        return s->getId() + " LEVE";
        
}
void AlertaManager::manterFilas(Sensor *s) {
    if(s == nullptr){throw std::invalid_argument("SENSOR INEXISTENTE!");}
    for (auto it = ativos.begin(); it != ativos.end(); ++it) {

        if(!s->alerta() && it->find(s->getId()) != string::npos){

            resolvidos.push_back(*it);
            ativos.erase(it);
            it--;
        }
    }

};

void AlertaManager::registrarHistóricos(Sensor *s) {
    if(s == nullptr){throw std::invalid_argument("SENSOR INEXISTENTE!");}
    time_t agora = time(nullptr);
    string dataHora = ctime(&agora);
    std::ofstream arquivo("historico.txt", std::ios::app);
    if(!arquivo.is_open()){throw std::runtime_error("ERRO AO ABRIR ARQUIVO DE HISTORICO");}
    arquivo << dataHora << " | " << s->getId() << " | " << s->retornaAtual() << std::endl;
    arquivo.close();
};

const vector<string>& AlertaManager::getAtivos() const {
    return this->ativos;
};

const vector<string>& AlertaManager::getResolvidos() const {
    return this->resolvidos;
};