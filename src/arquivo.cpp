#include "arquivo.hpp"

Matriz::Matriz() : viaj()
{
   this->tam = 0;
   this->numMatriz = 0;
}
void Matriz::setTam(short int tam)
{
   this->tam = tam;
}
short int Matriz::getTam()
{
   return this->tam;
}

void Matriz::setNumMatriz(short int numMatriz)
{
   this->numMatriz = numMatriz;
}
short int Matriz::getNumMatriz()
{
   return this->numMatriz;
}

void Matriz::le_arquivo()
{
   ifstream arq;
   arq.open("dataset/input.data");
   if (!(arq.is_open()))
   {
      cout << ("Erro ao abrir arquivo dataset/input");
      exit(-1);
   }
   string leitura;
   string ss, nome_bool;
   arq >> leitura >> leitura;
   setTam(stoi(leitura));
   arq >> leitura;
   setNumMatriz(stoi(leitura));

   short int produndidadeMatriz = 0, newLine = getNumMatriz() - 1;
   while (!arq.eof() && newLine != ((getTam() * getNumMatriz()) + getNumMatriz() - 1))
   {
      this->mat = new string *[getTam()];
      this->matrix = new bool *[getTam()];
      for (short int i = 0; i < getTam(); i++)
      {
         this->mat[i] = new string[getTam()];
         this->matrix[i] = new bool[getTam()];
         for (short int j = 0; j < getTam(); j++)
         {
            arq >> this->mat[i][j];
         }
         newLine++;
      }

      ss = "dataset/matriz" + to_string(produndidadeMatriz) + ".data";
      nome_bool = "dataset/matrizbool" + to_string(produndidadeMatriz) + ".data";
      ofstream outputFile(ss);
      ofstream file_bool(nome_bool);
      if (!outputFile.is_open() || !file_bool.is_open())
      {
         cout << "Error ao escrever no arquivo!" << endl;
         return;
      }
      for (short int i = 0; i < getTam(); i++)
      {
         for (short int j = 0; j < getTam(); j++)
         {
            outputFile << this->mat[i][j] << " ";
            file_bool << 0 << " ";
         }
         outputFile << endl;
         file_bool << endl;
      }
      outputFile.close();
      file_bool.close();
      produndidadeMatriz++;
   }
   arq.close();
   walkmatrix(&ss, &nome_bool);
}

void Matriz::imprimir(short int num_matrizes)
{
   cout << "\n MAPA " << num_matrizes << endl;
   for (short int i = 0; i < getTam(); i++)
   {
      for (short int j = 0; j < getTam(); j++)
      {
         cout << "\t" << this->mat[i][j];
      }
      cout << endl;
   }
   cout << endl;
}

void Matriz::walkmatrix(string *ss, string *nome_bool)
{
   short int error = 0, aleatorio, i = 0, j = 0, val, initial_lin = 0, initial_col = 0;
   bool allNonZero = true, mudou_mat = true;

   *ss = "dataset/matriz" + to_string(0) + ".data"; // iniciar com as matrizes  0
   *nome_bool = "dataset/matrizbool" + to_string(0) + ".data";
   nova_matriz(getTam(), this->mat, ss, this->matrix, nome_bool);

   cout << " \t O primeiro mapa a ser explorado sera : " << endl;
   imprimir(this->num_matrizes);
   do
   {
      error = 0;
      cout << " \n Seja bem vindo viajante! \n Por onde você deseja começar? (x,y)" << endl;
      cin >> initial_lin >> initial_col;
      if ((this->mat[initial_lin][initial_col] == "#") || initial_lin < 0 || initial_lin > getTam() - 1 || initial_col < 0 || initial_col > getTam() - 1)
      {
         cout << "Digite uma posição valida" << endl;
         error = 1;
         cin.clear();
      }
   } while (error == 1);
   i = initial_lin;
   j = initial_col;
   // perigos iniciais
   if (this->mat[i][j] == "*")
   {
      Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
   }
   else if ((stoi(this->mat[i][j]) > 0) && !this->mat[i][j].empty())
   {
      Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
   }
   else if (stoi(this->mat[i][j]) == 0)
   {
      this->matrix[i][j] = 1;
      this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
   }
   srand(time(NULL));

   while (this->viaj.getVida() > 0)
   {
      // condiçoes de parada
      if (verificaParede(vetor) == false)
      {
         cout << "\n\t O viajante esta encurralado por paredes, não é possivel passar!" << endl;
         break;
      }

      if (checkIfIsZero(i, j, &num_matrizes, initial_lin, initial_col, &allNonZero, &mudou_mat) == false)
      {
         salvar_matriz(getTam(), this->mat, ss, this->matrix, nome_bool);
         break;
      }
      aleatorio = rand() % 8 + 1;
      // 1- cima , 2- baixo , 3- esquerda, 4 - direita , 5- diagonal direita, 6 - diagonal esquerda, 7 - diagonal cima direita, 8 - diagonal cima esquerda
      switch (aleatorio)
      {
      case 1:
         // mudança de dimensão
         if ((i == 0) && (this->num_matrizes != getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if (((i) == 0) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         // andar pela matriz
         i--;
         if (this->mat[i][j] == "*") // perigo
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#") // barreira
         {
            i++;  //para retornar para posiçao que estava 
            this->vetor[0] = true; //usado para verificar se todas as direçoes sao barreiras
            break;
         }
         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#") // short inteiro
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            vetor[0] = false;
         }
         else // valor da posição é zero, não pega item
         {
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false; //se uma não for barreira todo o vetor é false
            }
         }
         break;
      case 2:
         if ((i == getTam() - 1) && (this->num_matrizes != getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if ((i == getTam() - 1) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         i++;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            i--;

            this->vetor[1] = true;
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;

      case 3:
         if ((j == 0) && (this->num_matrizes != getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if ((j == 0) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         j--;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            j++;

            this->vetor[2] = true;
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {

            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;

      case 4:
         if ((j == getTam() - 1) && (this->num_matrizes != getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if ((j == getTam() - 1) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         j++;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            j--;
            this->vetor[3] = true;
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {

            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;
      case 5:
         if (((i == getTam() - 1) || (j == getTam() - 1)) && !(this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if (((i == getTam() - 1) || (j == getTam() - 1)) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         i++;
         j++;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            i--;
            j--;
            this->vetor[4] = true;
            break;
         }
         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {

            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;
      case 6:
         if (((j == 0) || (i == getTam() - 1)) && !(this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if (((j == 0) || (i == getTam() - 1)) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         i++;
         j--;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            i--;
            j++;
            this->vetor[5] = true;

            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {

            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;
      case 7:
         if (((i == 0) || (j == getTam() - 1)) && !(this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if (((i == 0) || (j == getTam() - 1)) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         i--;
         j++;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            i++;
            j--;
            this->vetor[6] = true;

            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {

            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;
      case 8:
         if (((i == 0) || (j == 0)) && !(this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }
         else if (((i == 0) || (j == 0)) && (this->num_matrizes == getNumMatriz() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);

            break;
         }

         i--;
         j--;

         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            i++;
            j++;
            this->vetor[7] = true;
            break;
         }
         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
         }
         else
         {

            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for (short int i = 0; i < 8; i++)
            {
               this->vetor[i] = false;
            }
         }
         break;
      default:
         break;
      }
   }
   //fim do while = fim do jogo
   this->num_matrizes = 0;
   salvar_matriz(getTam(), this->mat, ss, this->matrix, nome_bool);
   if (viaj.getVida() == 0)
   {
      cout << "\n\t (*) O animal era mais forte do que você esperava e você acabou morrendo " << endl;
   }
   Output(this->matrix, nome_bool, this->mat, ss, getNumMatriz(), getTam(), this->positionsNoaccessed, &this->num_matrizes, this->positionsAccessed, viaj);
}
