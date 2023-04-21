#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "viajante.hpp"
using namespace std;

void changeDimension(short int tag, short int *i, short int *j, string **mat,  short int *num_matrizes, viajante &viaj, short int *val, string *ss, short int tam, bool *mudou_mat, bool *allNonZero, bool **matrix, string *nomebool,short int initialLinha, short int initialColuna, bool vetor[8]);
void salvar_matriz(short int tam, string **mat, string *ss, bool **matrix, string *nomebool);
void nova_matriz(short int tam, string **mat, string *ss, bool **matrix, string *nomebool);
bool checkIfIsZero(short int i, short int j, short int *num_matrizes, short int inital_i, short int initial_j, bool *allNonZero, bool *mudou_mat);
void Funcs_padroes(short int tag, short int *i, short int *j, viajante &viaj, short int *val, string **mat, bool *allNonZero, bool **matrix, bool vetor[8]);
void Output(bool **matrix, string *nomebool, string **mat, string *ss, short int total_mat, short int tam, short int positionsNoaccessed, short int *num_matrizes, short int positionsAccessed, viajante &viaj);
bool verificaParede(bool vetor[8]);
void removeFile(string *nomebool, string *ss,  short int total_mat, short int *num_matrizes);
#endif