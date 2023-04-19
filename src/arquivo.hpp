#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include <sstream>
#include "functions.hpp"
#include "viajante.hpp"
using namespace std;
class Matriz
{
private:
    short int tam; // tamanho das matrizes
    short int numMatriz; // quantas matrizes
    short int num_matrizes=0; // usar para mover o personagem entre as dimensões, qual matriz estou
    bool **matrix; // matriz boolena para verificar caminhos
    string **mat; // matriz percorrida
    short int positionsNoaccessed=0, positionsAccessed=0, qtd_andadas=0;
    bool vetor[8]; //verificar se ao redor é parede
    viajante viaj; //atributos do viajante
    
public:
    Matriz();
    short int getTam();
    void setTam(short int tam);

    short int getNumMatriz();
    void setNumMatriz(short int numMatriz);
    
    short int getNum_matrizes();
    void setNum_matrizes(short int num_matrizes);

    string ***getMatriz();
    void setMatriz(string ***mat);

    void imprimir(short int index);
    void le_arquivo();
    void walkmatrix(string *ss, string *nome_bool);

};
#endif