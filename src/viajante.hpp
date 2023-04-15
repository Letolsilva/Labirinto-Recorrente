#ifndef VIAJANTE_HPP
#define VIAJANTE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include <sstream>
using namespace std;

class viajante
{
private:
    int vida, pocoes, perigos_passados, itens_totais, qtd_andada, itensNaoPegos;
public:
    viajante();
    int getVida();
    void setVida(int Vida);

    int getPocoes();
    void setPocoes(int pocoes);

    int getPerigos_passados();
    void setPerigos_passados(int perigos_passados);

    int getItens_totais();
    void setItens_totais(int itens_totais);

    int getQtd_andada();
    void setQtd_andada(int qtd_andada);

     int getItensNaoPegos();
     void setItensNaoPegos(int itensNaoPeos);
};
#endif