#include "viajante.hpp"

viajante::viajante()
{
   this->vida = 10;
   this->pocoes = 0;
   this->itens_totais=0;
   this->perigos_passados=0;
   this->qtd_andada=0;
   this->itensNaoPegos=0;
}
void viajante::setVida(int vida)
{
   this->vida = vida;
}
int viajante::getVida()
{
   return this->vida;
}
void viajante::setPocoes(int pocoes)
{
   this->pocoes= pocoes;
}
int viajante::getPocoes()
{
   return this->pocoes;
}
void viajante::setPerigos_passados(int perigos_passados)
{
   this->perigos_passados= perigos_passados;
}
int viajante::getPerigos_passados()
{
   return this->perigos_passados;
}
void viajante::setItens_totais(int itens_totais)
{
   this->itens_totais= itens_totais;
}
int viajante::getItens_totais()
{
   return this->itens_totais;
}
void viajante::setQtd_andada(int qtd_andada)
{
   this->qtd_andada= qtd_andada;
}
int viajante::getQtd_andada()
{
   return this->qtd_andada;
}
void viajante::setItensNaoPegos(int itensNaoPegos)
{
   this->itensNaoPegos= itensNaoPegos;
}
int viajante::getItensNaoPegos()
{
   return this->itensNaoPegos;
}

