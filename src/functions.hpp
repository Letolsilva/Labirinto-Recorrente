#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <algorithm>
#include "viajante.hpp"
using namespace std;

void changeDimension(int tag, int *i, int *j, string **mat, int *num_matrizes, viajante &viaj, int *val, string *ss, int tam, bool *mudou_mat, bool *allNonZero, bool **matrix, string *nomebool);
void salvar_matriz(int tam, string **mat, string *ss, bool **matrix, string *nomebool);
void nova_matriz(int tam, string **mat, string *ss, bool **matrix, string *nomebool);
bool checkIfIsZero(int i, int j, int *num_matrizes, int inital_i, int initial_j, bool *allNonZero, bool *mudou_mat);
void Funcs_padroes(int tag, int *i, int *j, viajante &viaj, int *val, string **mat, bool *allNonZero, bool **matrix);
void Output(bool **matrix, string *nomebool, string **mat, string *ss, int total_mat, int tam, short int positionsNoaccessed, int *num_matrizes, short int positionsAccessed, viajante &viaj);
#endif