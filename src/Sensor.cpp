#include "../include/Sensor.hpp"
#include <algorithm>
#include <stdexcept>

using std::string;
using std::vector;

Sensor::Sensor(string id, string tipo) : id(id), tipo(tipo), atual(0.0) {
    if(id.empty()){throw std::invalid_argument("SENSOR SEM IDENTIFICACAO!");}
    if (tipo == "temperatura") { limMax = 45; limMin = 30; }
    else if (tipo == "rpm") { limMax = 14000; limMin = 7000; }
    else {throw std::invalid_argument("TIPO DE SENSOR INVALIDO!");}
};

double Sensor::calcularMaxRegistrado() const {
    if (historico.empty())  {
        throw std::runtime_error("Histórico vazio");
    };
    return *std::max_element(historico.begin(), historico.end());
};

double Sensor::calcularMinRegistrado() const {
    if (historico.empty())  {
        throw std::runtime_error("Histórico vazio");
    };
    return *std::min_element(historico.begin(), historico.end());
};

double Sensor::retornaAtual() const {
    return this->atual;
};

void Sensor::registraHist(double valorLido) {
    this->atual = valorLido;
    this->historico.push_back(valorLido);
};

bool Sensor::alerta() const {
    if (historico.empty())  {
        throw std::runtime_error("Histórico vazio");
    };
    return this->atual > this->limMax || this->atual < this->limMin;
};

string Sensor::getId() const{

    return this-> id;
};

string Sensor::getTipo() const{
    
    return this->tipo;
};

bool Sensor::getHistoricoVazio() const{

   return historico.empty();

};

double Sensor::getLimMax() const{

    return this->limMax;
};

double Sensor::getLimMin() const{

    return this->limMin;
};

void Sensor::sensorStop(){
    this->atual = 0;
}