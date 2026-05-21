#include "../include/Sensor.hpp"
#include <algorithm>

using std::string;
using std::vector;

Sensor::Sensor(string id, string tipo, double limMax, double limMin)
    : id(id), tipo(tipo), limMax(limMax), limMin(limMin), atual(0.0) {}

double Sensor::calcularMaxRegistrado() const {
    if (historico.empty()) return 0.0;
    return *std::max_element(historico.begin(), historico.end());
};

double Sensor::calcularMinRegistrado() const {
    if (historico.empty()) return 0.0;
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
    return this->atual > this->limMax || this->atual < this->limMin;
};
