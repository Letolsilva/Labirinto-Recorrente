#include "arquivo.hpp"

Matriz::Matriz() : viaj()
{
   this->tam = 0;
   this->profundidade = 0;
}
void Matriz::setTam(short int tam)
{
   this->tam = tam;
}
short int Matriz::getTam()
{
   return this->tam;
}

void Matriz::setProfundidade(short int profundidade)
{
   this->profundidade = profundidade;
}
short int Matriz::getProfundidade()
{
   return this->profundidade;
}

void Matriz::le_arquivo()
{
   ifstream arq;
   arq.open("dataset/input.data");
   if (!(arq.is_open()))
   {
      printf("ERRO ao abrir arquivo");
      exit(-1);
   }
   string leitura;
   string ss, nome_bool;
   arq >> leitura >> leitura;
   setTam(stoi(leitura));
   arq >> leitura;
   setProfundidade(stoi(leitura));

   int produndidadeMatriz = 0, newLine = getProfundidade() - 1;
   while (!arq.eof() && newLine != ((getTam() * getProfundidade()) + getProfundidade() - 1))
   {
      this->mat = new string *[getTam()];
      this->matrix = new bool *[getTam()];
      for (int i = 0; i < getTam(); i++)
      {
         this->mat[i] = new string[getTam()];
         this->matrix[i] = new bool[getTam()];
         for (int j = 0; j < getTam(); j++)
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
      for (int i = 0; i < getTam(); i++)
      {
         for (int j = 0; j < getTam(); j++)
         {
            outputFile << this->mat[i][j] << " ";
            file_bool << 0 << " ";
         }
         outputFile << endl;
         file_bool << endl;
      }
      outputFile.close();
      file_bool.close();
      // cout << produndidadeMatriz << endl;
      produndidadeMatriz++;
   }
   arq.close();
   walkmatrix(&ss, &nome_bool);
}

void Matriz::imprimir(int num_matrizes)
{
   cout << "\n MAPA " << num_matrizes << endl;
   for (int i = 0; i < getTam(); i++)
   {
      for (int j = 0; j < getTam(); j++)
      {
         cout << "\t" << this->mat[i][j];
      }
      cout << endl;
   }
   cout << endl;
}

void Matriz::walkmatrix(string *ss, string *nome_bool)
{
   int error = 0, aleatorio, i = 0, j = 0, val, initial_lin = 0, initial_col = 0;
   bool allNonZero = true, mudou_mat = true;
   
   *ss = "dataset/matriz" + to_string(0) + ".data"; // iniciar com a 0
   *nome_bool = "dataset/matrizbool" + to_string(0) + ".data";
   nova_matriz(getTam(), this->mat, ss, this->matrix, nome_bool);
   cout << " \t O primeiro mapa a ser explorado sera : " << endl;
   imprimir(this->num_matrizes);
   do
   {
      error = 0;
      cout << " \n Seja bem vindo viajante! \n Por onde você deseja começar? (x,y)" << endl;
      cin >> initial_lin >> initial_col;
      if ((this->mat[initial_lin][initial_col] == "#") || initial_lin < 0 || initial_lin > getTam() - 1 || initial_col < 0 || initial_col > getTam() - 1 )
      {
         cout << "Digite uma posição valida" << endl;
         error = 1;
         cin.clear();
      }
   } while (error == 1);
   i = initial_lin;
   j = initial_col;

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
      cout << "Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
      this->matrix[i][j] = 1;
      this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
   }
   cout << "\t MAPA ATUALIZADO " << endl;
   imprimir(this->num_matrizes);
   srand(time(NULL));

   while (this->viaj.getVida() > 0)
   {
      if(verificaParede(vetor)==false){
         cout<<"O viajante esta encurralado por paredes, não é possivel passar!"<<endl;
         break;
      }
     
      if (checkIfIsZero(i, j, &num_matrizes, initial_lin, initial_col, &allNonZero, &mudou_mat) == false)
      {
         salvar_matriz(getTam(), this->mat, ss, this->matrix, nome_bool);
         break;
      }
      aleatorio = rand() % 8 + 1;
      
       //aleatorio = 8;
      cout << "\n Número gerado: " << aleatorio << endl;
      switch (aleatorio)
      {
      case 1:
         cout << " CIMA " << endl;
         if ((i == 0) && (this->num_matrizes != getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if (((i) == 0) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         i--;
         if (this->mat[i][j] == "*")
         {
            Funcs_padroes(0, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            break;
         }
         if (this->mat[i][j] == "#")
         {
            i++;
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            this->vetor[0]=true;
            break;
         }
         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            vetor[0]=false;
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for(int i=0; i<8; i++){
              this-> vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;
      case 2:
         cout << " BAIXO " << endl;
         if ((i == getTam() - 1) && (this->num_matrizes != getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if ((i == getTam() - 1) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            this->vetor[1]=true;
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
             for(int i=0; i<8; i++){
               this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;

      case 3:
         cout << " ESQUERDA " << endl;
         if ((j == 0) && (this->num_matrizes != getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if ((j == 0) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            this->vetor[2]=true;
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
             for(int i=0; i<8; i++){
               this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;

      case 4:
         cout << " DIREITA " << endl;
         if ((j == getTam() - 1) && (this->num_matrizes != getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if ((j == getTam() - 1) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            this->vetor[3]=true;
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
             for(int i=0; i<8; i++){
               this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;
      case 5:
         cout << "DIAGONAL DIREITA " << endl;
         if (((i == getTam() - 1) || (j == getTam() - 1)) && !(this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if (((i == getTam() - 1) || (j == getTam() - 1)) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            this->vetor[4]=true;
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            break;
         }
         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
             for(int i=0; i<8; i++){
            this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;
      case 6:
         cout << " DIAGONAL ESQUERDA " << endl;
         if (((j == 0) || (i == getTam() - 1)) && !(this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if (((j == 0) || (i == getTam() - 1)) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            this->vetor[5]=true;
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
             for(int i=0; i<8; i++){
               this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;
      case 7:
         cout << " DIAGONAL CIMA DIREITA " << endl;
         if (((i == 0) || (j == getTam() - 1)) && !(this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if (((i == 0) || (j == getTam() - 1)) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            this->vetor[6]=true;
            cout << "\t (#) Havia uma parede não é possivel ir para esta posição";
            break;
         }

         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
             for(int i=0; i<8; i++){
             this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;
      case 8:
         cout << " DIAGONAL CIMA ESQUERDA " << endl;
         if (((i == 0) || (j == 0)) && !(this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(1, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
            break;
         }
         else if (((i == 0) || (j == 0)) && (this->num_matrizes == getProfundidade() - 1))
         {
            changeDimension(2, &i, &j, this->mat, &this->num_matrizes, viaj, &val, ss, getTam(), &mudou_mat, &allNonZero, this->matrix, nome_bool, initial_lin, initial_col, this->vetor);
            imprimir(this->num_matrizes);
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
            this->vetor[7]=true;
            cout << "\t (#)  Havia uma parede não é possivel ir para esta posição";
            break;
         }
         if (stoi(this->mat[i][j]) > 0 && this->mat[i][j] != "*" && this->mat[i][j] != "#")
         {
            Funcs_padroes(1, &i, &j, viaj, &val, this->mat, &allNonZero, this->matrix, this->vetor);
            imprimir(this->num_matrizes);
         }
         else
         {
            cout << "\t Itens esgotados nesta posição quem sabe terá mais sorte na próxima!" << endl;
            this->matrix[i][j] = 1;
            this->viaj.setQtd_andada(this->viaj.getQtd_andada() + 1);
            for(int i=0; i<8; i++){
               this->vetor[i]=false;
            }
            imprimir(this->num_matrizes);
         }
         break;
      default:
         break;
      }
   }
   this->num_matrizes = 0;
   salvar_matriz(getTam(), this->mat, ss, this->matrix, nome_bool);
   if (viaj.getVida() == 0)
   {
      cout << "\t (*) O animal era mais forte do que você esperava e você acabou morrendo " << endl;
      cout << "\t\t ----------------\t\t" << endl;
      cout << "\t\t   DADOS FINAIS " << endl;
      cout << "\t\t    Vidas: " << viaj.getVida() << endl;
      cout << "\t\t   Poçoes: " << viaj.getPocoes() << endl;
      cout << "\t\t ---------------- \t\t" << endl;
      cout << "\t\t \n FIM DO JOGO " << endl;
   }
   Output(this->matrix, nome_bool, this->mat, ss, getProfundidade(), getTam(), this->positionsNoaccessed, &this->num_matrizes, this->positionsAccessed, viaj);
}
