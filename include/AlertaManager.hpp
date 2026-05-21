#ifndef ALERTAMANAGER_H
#define ALERTAMANAGER_H

#include<iostream>
#include<string>
#include<vector>
#include"Sensor.hpp"

using std::string;

/**
 * @file AlertaManager.hpp
 * @brief Definição da classe AlertaManager para monitorar alertas.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * monitorar os alertas a depender dos dados do sensor de uma máquina.
 */
class AlertaManager{
private:
    vector<string> ativos;
    vector<string> resolvidos;

public:
    AlertaManager();
    ~AlertaManager();
    /**
     * @brief recebe os alertas de um sensor
     */
    void receberAlertas(Sensor *s);
    /**
     * @brief classifica a severidade de acordo com os dados do sensor
     * @param s é um sensor
     * @return indicador de severidade
     */
    string classificarSeveridade(Sensor *s);
    /**
     * @brief organiza os alertas ativos
     */
    void manterFilas(Sensor *s);
    /**
     * @brief documenta alertas ativos
     */
    void registrarHistóricos(Sensor *s);

    const vector<string>& getAtivos() const;
    const vector<string>& getResolvidos() const;
};

#endif