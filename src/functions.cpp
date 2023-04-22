#include "functions.hpp"

void nova_matriz(short int tam, string **mat, string *ss, bool **matrix, string *nomebool) // matriz que sera percorrida
{
   ifstream arq;
   ifstream arqbool;
   arq.open(*ss);
   arqbool.open(*nomebool);
   if (!(arq.is_open()) || !(arqbool.is_open()))
   {
      cout << ("Erro ao abrir arquivo de nova matriz");
      exit(-1);
   }
   for (short int i = 0; i < tam; i++)
   {
      for (short int j = 0; j < tam; j++)
      {
         arq >> mat[i][j];
         arqbool >> matrix[i][j];
      }
   }
   arq.close();
   arqbool.close();
}
void salvar_matriz(short int tam, string **mat, string *ss, bool **matrix, string *nomebool) // salvar as alteraçoes nas matrizes
{
   ofstream file(*ss);
   ofstream file_bool(*nomebool);
   for (short int i = 0; i < tam; i++)
   {
      for (short int j = 0; j < tam; j++)
      {
         file << mat[i][j] << " ";
         file_bool << matrix[i][j] << " ";
      }
      file << endl;
      file_bool << endl;
   }
   file.close();
   file_bool.close();
}

void changeDimension(short int tag, short int *i, short int *j, string **mat, short int *num_matrizes, viajante &viaj, short int *val, string *ss, short int tam, bool *mudou_mat, bool *allNonZero, bool **matrix, string *nomebool, short int initialLinha, short int initialColuna, bool vetor[8])
{
   switch (tag)
   {
   case 1:
      salvar_matriz(tam, mat, ss, matrix, nomebool); // salvar a matriz anterior

      *ss = "dataset/matriz" + to_string(*num_matrizes + 1) + ".data";
      *nomebool = "dataset/matrizbool" + to_string(*num_matrizes + 1) + ".data";

      (*num_matrizes)++;
      *mudou_mat = false; // variavel para verificar que passou de matriz
      *i = initialLinha;  // inicia na posiçao i , j inicial
      *j = initialColuna;
      nova_matriz(tam, mat, ss, matrix, nomebool); // abrir a proxima matriz
      while (mat[*i][*j] == "#")
      {
         *i = rand() % (tam - 1);
         *j = rand() % (tam - 1);
      }

      if (mat[*i][*j] == "*")
      {
         Funcs_padroes(0, i, j, viaj, val, mat, allNonZero, matrix, vetor);
         return;
      }
      else if (stoi(mat[*i][*j]) > 0 && mat[*i][*j] != "*" && mat[*i][*j] != "#")
      {
         Funcs_padroes(1, i, j, viaj, val, mat, allNonZero, matrix, vetor);
         return;
      }
      else
      {
         matrix[*i][*j] = 1;
         viaj.setQtd_andada(viaj.getQtd_andada() + 1);
         for (short int i = 0; i < 8; i++)
         {
            vetor[i] = false;
         }
         return;
      }
      break;
   case 2:
      // Quando se esta na ultima matrix e vai retornar para inicial
      salvar_matriz(tam, mat, ss, matrix, nomebool);

      *ss = "dataset/matriz" + to_string(0) + ".data";
      *nomebool = "dataset/matrizbool" + to_string(0) + ".data";

      *num_matrizes = 0;
      *i = initialLinha;
      *j = initialColuna;
      nova_matriz(tam, mat, ss, matrix, nomebool);

      while (mat[*i][*j] == "#")
      {
         *i = rand() % (tam - 1);
         *j = rand() % (tam - 1);
      }

      if (mat[*i][*j] == "*")
      {
         Funcs_padroes(0, i, j, viaj, val, mat, allNonZero, matrix, vetor);
         return;
      }
      else if (stoi(mat[*i][*j]) > 0 && mat[*i][*j] != "*" && mat[*i][*j] != "#")
      {
         Funcs_padroes(1, i, j, viaj, val, mat, allNonZero, matrix, vetor);
         return;
      }
      else
      {
         matrix[*i][*j] = 1;
         viaj.setQtd_andada(viaj.getQtd_andada() + 1);
         for (short int i = 0; i < 8; i++)
         {
            vetor[i] = false;
         }
         return;
      }
      break;
   default:
      break;
   }
}

void Funcs_padroes(short int tag, short int *i, short int *j, viajante &viaj, short int *val, string **mat, bool *allNonZero, bool **matrix, bool vetor[8])
{
   switch (tag)
   {
   case 0:
      // entrou em um perigo
      matrix[*i][*j] = 1; // matrix booleana
      viaj.setVida(viaj.getVida() - 1);
      viaj.setPerigos_passados(viaj.getPerigos_passados() + 1);
      viaj.setQtd_andada(viaj.getQtd_andada() + 1);
      for (short int i = 0; i < 8; i++)
      {
         vetor[i] = false;
      }
      break;
   case 1:
      // entrou em uma posiçao com inteiro
      matrix[*i][*j] = 1;
      *allNonZero = false; // verificar se as posiçao sao zero, neste caso não é!
      *val = stoi(mat[*i][*j]);
      (*val) -= 1;
      mat[*i][*j] = to_string(*val); // retirar 1 da posiçao
      viaj.setPocoes(viaj.getPocoes() + 1);
      viaj.setItens_totais(viaj.getItens_totais() + 1);
      viaj.setQtd_andada(viaj.getQtd_andada() + 1);
      for (short int i = 0; i < 8; i++)
      {
         vetor[i] = false;
      }
      if (viaj.getPocoes() == 4) // receber uma vida por poçoes
      {
         if (viaj.getVida() < 10)
         {
            viaj.setPocoes(viaj.getPocoes() - 4);
            viaj.setVida(viaj.getVida() + 1);
         }
         else // caso a vida seja dez e tenha 4 poçoes
         {
            viaj.setPocoes(viaj.getPocoes() - 1);
            viaj.setItens_totais(viaj.getItens_totais() - 1);
            viaj.setItensNaoPegos(viaj.getItensNaoPegos() + 1);
         }
      }
      break;
   default:
      break;
   }
}
bool checkIfIsZero(short int i, short int j, short int *num_matrizes, short int inital_i, short int initial_j, bool *allNonZero, bool *mudou_mat)
{
   if ((i == inital_i) && (j == initial_j) && (*num_matrizes == 0) && !(*mudou_mat))
   {
      if (*allNonZero == true)
      {
         cout << "Todo o caminho percorrido é zero!" << endl;
         return false;
      }
      cout << "\n Um novo caminho se inicia!" << endl;
      *mudou_mat = true;
      *allNonZero = true;
   }
   return true;
}

void Output(bool **matrix, string *nomebool, string **mat, string *ss, short int total_mat, short int tam, short int positionsNoaccessed, short int *num_matrizes, short int positionsAccessed, viajante &viaj)
{
   ofstream ArqCaminho;
   ArqCaminho.open("dataset/output.data", ios::app);
   ArqCaminho << "\tOUTPUT- CAMINHOS DESCOBERTOS\t" << endl;
   for (short int k = 0; k < total_mat; k++) // percorre todas as matrizes
   {
      ifstream arqbool;
      ifstream outputFile;

      *nomebool = "dataset/matrizbool" + to_string(*num_matrizes) + ".data";
      *ss = "dataset/matriz" + to_string(*num_matrizes) + ".data";
      arqbool.open(*nomebool);
      outputFile.open(*ss);

      if (!(arqbool.is_open()) || !outputFile.is_open())
      {
         cout << ("Erro ao abrir arquivo Output");
         exit(-1);
      }
      for (short int i = 0; i < tam; i++)
      {
         for (short int j = 0; j < tam; j++)
         {
            arqbool >> matrix[i][j];   // passa para matriz booleana
            outputFile >> mat[i][j];   // passa para matriz de string
            if (matrix[i][j] == false) // conta quantas posiçoes foram acessadas
            {
               positionsNoaccessed++;
            }
            if (matrix[i][j] == true)
            {
               positionsAccessed++;
            }
         }
      }
      (*num_matrizes)++; // muda os arquivos que esta sendo lidos

      if (!ArqCaminho.is_open())
      {
         cout << "Error ao escrever no arquivo Output!" << endl;
         return;
      }
      for (short int i = 0; i < tam; i++)
      {
         for (short int j = 0; j < tam; j++)
         {
            ArqCaminho << mat[i][j] << " "; // juntas todas as matrizes alteradas em um so arquivo
         }
         ArqCaminho << endl;
      }
      ArqCaminho << endl;
      arqbool.close();
      outputFile.close();
   }
   ArqCaminho.close();
   cout << "\n\t\t FIM DO JOGO!\t\t" << endl;
   cout << " \t\t DADOS FINAIS \t\t" << endl;
   cout << "--------------------------------------------------------\t\t" << endl;
   cout << "\t Numero de casas não exploradas: " << positionsNoaccessed << endl;
   cout << "\t Numero de casas descobertas: " << positionsAccessed << endl;
   cout << "\t Numero de passos: " << viaj.getQtd_andada() << endl;
   cout << "\t Perigos enfrentados: " << viaj.getPerigos_passados() << endl;
   cout << "\t Itens totais que foram colocados na mochila: " << viaj.getItens_totais() << endl;
   cout << "\t Itens totais que foram encontrados " << ((viaj.getItensNaoPegos()) + (viaj.getItens_totais())) << endl;
   cout << "\t Vidas: " << viaj.getVida() << endl;
   cout << "\t Poções: " << viaj.getPocoes() << endl;
   cout << "--------------------------------------------------------\t\t" << endl;
}

bool verificaParede(bool vetor[8])
{
   short int cont = 0;
   for (short int i = 0; i < 8; i++)
   {
      if (vetor[i] == true)
      {
         cont++;
      }
   }
   if (cont == 8)
   {
      return false;
   }

   return true;
}
void removeFile(string *nomebool, string *ss, short int total_mat, short int *num_matrizes)
{
   *num_matrizes=0;
   string output = "dataset/output.data";
   for (short int k = 0; k < total_mat; k++)
   {
      *nomebool = "dataset/matrizbool" + to_string(*num_matrizes) + ".data";
      *ss = "dataset/matriz" + to_string(*num_matrizes) + ".data";
      int removendoBool = remove(nomebool->c_str());
      if (removendoBool != 0)
      {
         cout<<"Não foi possível remover o arquivo "<< nomebool->c_str()<<endl;
      }
      else
      {
         int removendoString = remove(ss->c_str());
         if (removendoString != 0)
         {
            cout<<"Não foi possível remover o arquivo "<< ss->c_str()<<endl;
         }
      }
      (*num_matrizes)++;
   }
}
