#ifndef SENSOR_H
#define SENSOR_H

#include<iostream>
#include<string>
#include<vector>

using std::string;
using std::vector;
/**
 * @file Sensor.hpp
 * @brief Definição da classe Sensor para monitoriar dados da maquina.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * armazenar limites, registar o histórico de leituras e validar estados de alerta.
 */
class Sensor{
private:
    string id;
    string tipo;
    double limMax;
    double limMin;
    double atual;
    vector<double> historico;

public:
    Sensor(string id, string tipo, double limMax, double limMin);
    ~Sensor(){};
    /**
     * @brief guarda o valor maximo registrado
     */
    double calcularMaxRegistrado() const;
    /**
     * @brief guarda o valor minimo registrado
     */
    double calcularMinRegistrado() const;
    /**
     * @brief conferir valor do sensor em determinado momento
     * @return retorna o valor do sensor no momento da chamada
     */
    double retornaAtual() const;
    /**
     * @brief registra a leitura atual no histórico
     * 
     */
    void registraHist(double valorLido);
/**
 * @brief Verifica se o sensor está em estado de alerta.
 * @return true se o valor atual ultrapassar os limites, false caso contrário.
 */
    bool alerta() const;


};


#endif