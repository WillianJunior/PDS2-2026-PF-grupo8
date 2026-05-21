#include "../include/AlertaManager.hpp"

using std::string;
using std::vector;

AlertaManager::AlertaManager() {

};
AlertaManager::~AlertaManager() {

};

void AlertaManager::receberAlertas(Sensor *s) {
    if (s->alerta()) {
        ativos.push_back(classificarSeveridade(s));
    }
};

string AlertaManager::classificarSeveridade(Sensor *s) {
    return "CRÍTICO";
};

void AlertaManager::manterFilas(Sensor *s) {}

void AlertaManager::registrarHistóricos(Sensor *s) {}

const vector<string>& AlertaManager::getAtivos() const {
    return this->ativos;
};

const vector<string>& AlertaManager::getResolvidos() const {
    return this->resolvidos;
};