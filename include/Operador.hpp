#ifndef OPERADOR_H
#define OPERADOR_H

#include<iostream>
#include<string>
class Maquina;

using std::string;
/**
 * @file Operador.hpp
 * @brief Definição da classe Operador.
 * @details Este arquivo contém as propriedades e os métodos necessários para 
 * instanciar operadores.
 */
class Operador{

private:
    string nome;
    string turno;
    Maquina *m;

public: 
    Operador(string nome, string turno);
    ~Operador();
    /**
     * @brief aloca maquina a um operador especifico
     */
    void alocarMaquina(Maquina *m);
    /**
     * @brief realoca maquina a um operador especifico
     */
    void realocarMaquina(Maquina *m);
    /**
     * @brief desatribui a maquina de um operador específico
     */
    void desatribuirMaquina(Maquina *m);
};


#endif