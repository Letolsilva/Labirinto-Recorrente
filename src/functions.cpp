#include "functions.hpp"

// função é chamada nas condicionais de troca de dimensão.
/*      params:
    tag=index de direção do traveller
    i, j, k=index de posição do traveller (definidos como ponteiros para alterar as variaveis no escopo da classe Matriz)
*/
void nova_matriz(int tam, string **mat, string *ss, bool **matrix, string *nomebool)
{
   ifstream arq;
   ifstream arqbool;
   arq.open(*ss);
   arqbool.open(*nomebool);
   if (!(arq.is_open()) || !(arqbool.is_open()))
   {
      printf("Erro ao abrir arquivo de nova matriz");
      exit(-1);
   }
   for (int i = 0; i < tam; i++)
   {
      for (int j = 0; j < tam; j++)
      {
         arq >> mat[i][j];
         arqbool >> matrix[i][j];
      }
   }
   arq.close();
   arqbool.close();
}
void salvar_matriz(int tam, string **mat, string *ss, bool **matrix, string *nomebool)
{
   ofstream file(*ss);
   ofstream file_bool(*nomebool);
   for (int i = 0; i < tam; i++)
   {
      for (int j = 0; j < tam; j++)
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

void changeDimension(int tag, int *i, int *j, string **mat, int *num_matrizes, viajante &viaj, int *val, string *ss, int tam, bool *mudou_mat, bool *allNonZero, bool **matrix, string *nomebool)
{

   switch (tag)
   {
   case 1:
      salvar_matriz(tam, mat, ss, matrix, nomebool);
      *ss = "dataset/matriz" + to_string(*num_matrizes + 1) + ".data";
      *nomebool = "dataset/matrizbool" + to_string(*num_matrizes + 1) + ".data";
      (*num_matrizes)++;
      *mudou_mat = false;
      *i = 0;
      nova_matriz(tam, mat, ss, matrix, nomebool);
      while (mat[*i][*j] == "#" )
      {
         *i = rand() % (tam - 1);
         *j = rand() % (tam - 1);
         cout << "\t (#) Você tentou abrir o portal mas havia uma barreira, faça o feitiço mais uma vez para destrui-la!" << endl;
      }
      cout << "\t Você conseguiu abrir um portal e acessar o mundo: " << *num_matrizes << " aproveite para explora-lo!" << endl;
      cout << "\t Você iniciou na nova dimensão em : [" << *i << "]"
           << "[" << *j << "]" << endl;
      if (mat[*i][*j] == "*")
      {
         Funcs_padroes(0, i, j, viaj, val, mat, allNonZero, matrix);
         return;
      }
      else if (stoi(mat[*i][*j]) > 0 && mat[*i][*j] != "*" && mat[*i][*j] != "#")
      {
         Funcs_padroes(1, i, j, viaj, val, mat, allNonZero, matrix);
         return;
      }
      else
      {
         cout << "\t (int) Poxa, todas as poções ja foram resgatadas nesta posição, quem sabe terá mais sorte na próxima!" << endl;
         matrix[*i][*j] = 1;
         viaj.setQtd_andada(viaj.getQtd_andada() + 1);
         return;
      }

      break;
   case 2:
      cout << " \t Você explorou todas as dimensões vamos retornar ao inicio!" << endl;
      salvar_matriz(tam, mat, ss, matrix, nomebool);
      *ss = "dataset/matriz" + to_string(0) + ".data";
      *nomebool = "dataset/matrizbool" + to_string(0) + ".data";
      *num_matrizes = 0;
      *i = (tam - 1);
      nova_matriz(tam, mat, ss, matrix, nomebool);

      while (mat[*i][*j] == "#" )
      {
         *i = rand() % (tam - 1);
         *j = rand() % (tam - 1);
         cout << "\t (#) Você tentou abrir o portal mas havia uma barreira, faça o feitiço mais uma vez para destrui-la!" << endl;
      }

      cout << "\t Você conseguiu abrir um portal para voltar para o mundo: " << *num_matrizes << " aproveite para explora-lo!" << endl;
      cout << "\t Você iniciou na nova dimensão em : [" << *i << "]"
           << "[" << *j << "]" << endl;

      if (mat[*i][*j] == "*")
      {
         Funcs_padroes(0, i, j, viaj, val, mat, allNonZero, matrix);
         return;
      }
      else if (stoi(mat[*i][*j]) > 0 && mat[*i][*j] != "*" && mat[*i][*j] != "#")
      {
         Funcs_padroes(1, i, j, viaj, val, mat, allNonZero, matrix);
         return;
      }
      else
      {
         cout << "\t (int) Poxa, todas as poções ja foram resgatadas nesta posição, quem sabe terá mais sorte na próxima!" << endl;
         matrix[*i][*j] = 1;
         viaj.setQtd_andada(viaj.getQtd_andada() + 1);
         return;
      }
      break;
   default:
      break;
   }
}

void Funcs_padroes(int tag, int *i, int *j, viajante &viaj, int *val, string **mat, bool *allNonZero, bool **matrix)
{
   switch (tag)
   {
   case 0:
      matrix[*i][*j] = 1;
      viaj.setVida(viaj.getVida() - 1);
      viaj.setPerigos_passados(viaj.getPerigos_passados() + 1);
      viaj.setQtd_andada(viaj.getQtd_andada() + 1);
      cout << "\t (*) Você tentou enfrentar um animal selvagem e acabou se machucando " << endl;
      cout << "\t\t ----------------\t\t" << endl;
      cout << "\t\t   Vidas: " << viaj.getVida() << endl;
      cout << "\t\t ---------------- \t\t" << endl;
      break;
   case 1:
      matrix[*i][*j] = 1;
      *allNonZero = false;
      *val = stoi(mat[*i][*j]);
      (*val) -= 1;
      mat[*i][*j] = to_string(*val);
      viaj.setPocoes(viaj.getPocoes() + 1);
      viaj.setItens_totais(viaj.getItens_totais() + 1);
      viaj.setQtd_andada(viaj.getQtd_andada() + 1);
      cout << "\t (int) Você encontrou uma poção " << endl;
      cout << "\t\t ----------------\t\t" << endl;
      cout << "\t\t    Poçoes: " << viaj.getPocoes() << endl;
      cout << "\t\t ----------------\t\t" << endl;
      if (viaj.getPocoes() == 4)
      {
         if (viaj.getVida() < 10)
         {
            cout << "\t Você encontrou 4 poções, elas serão trocadas por uma vida." << endl;
            viaj.setPocoes(viaj.getPocoes() - 4);
            viaj.setVida(viaj.getVida() + 1);
            cout << "\t Você recebeu um ponto de vida!" << endl;
            cout << "\t\t ----------------\t\t" << endl;
            cout << "\t\t    Vidas: " << viaj.getVida() << endl;
            cout << "\t\t   Poçoes: " << viaj.getPocoes() << endl;
            cout << "\t\t ---------------- \t\t" << endl;
         }
         else
         {
            cout << "\t Sua mochila está muito pesada, você não poderar comprar mais vidas!" << endl;
            cout << "\t Você não poderá pegar mais itens!" << endl;
            viaj.setPocoes(viaj.getPocoes() - 1);
            viaj.setItens_totais(viaj.getItens_totais() - 1);
            viaj.setItensNaoPegos(viaj.getItensNaoPegos()+1);
         }
      }
      break;
   default:
      break;
   }
}
bool checkIfIsZero(int i, int j, int *num_matrizes, int inital_i, int initial_j, bool *allNonZero, bool *mudou_mat)
{
   if ((i == inital_i) && (j == initial_j) && (*num_matrizes == 0) && !(*mudou_mat))
   {
      if (*allNonZero == true)
      {
         cout << "Todo o caminho percorrido é zero! \n FIM DO JOGO" << endl;
         return false;
      }
      *mudou_mat = true;
      *allNonZero = true;
   }
   return true;
}

void Output(bool **matrix, string *nomebool, string **mat, string *ss, int total_mat, int tam, short int positionsNoaccessed, int *num_matrizes, short int positionsAccessed, viajante &viaj)
{
   string Output;
   ofstream ArqCaminho;
   ArqCaminho.open("dataset/output.data", ios::app);
   ArqCaminho << "\tOUTPUT- CAMINHOS DESCOBERTOS\t" << endl;
   for (int k = 0; k < total_mat; k++)
   {
      ifstream arqbool;
      ifstream outputFile;
      *nomebool = "dataset/matrizbool" + to_string(*num_matrizes) + ".data";
      *ss = "dataset/matriz" + to_string(*num_matrizes) + ".data";
      arqbool.open(*nomebool);
      outputFile.open(*ss);
      if (!(arqbool.is_open()) || !outputFile.is_open())
      {
         printf("Erro ao abrir arquivo Output");
         exit(-1);
      }
      for (int i = 0; i < tam; i++)
      {
         for (int j = 0; j < tam; j++)
         {
            arqbool >> matrix[i][j];
            outputFile >> mat[i][j];
            if (matrix[i][j] == false)
            {
               positionsNoaccessed++;
            }
            if (matrix[i][j] == true)
            {
               positionsAccessed++;
            }
         }
      }
      (*num_matrizes)++;

      if (!ArqCaminho.is_open())
      {
         cout << "Error ao escrever no arquivo Output!" << endl;
         return;
      }
      for (int i = 0; i < tam; i++)
      {
         for (int j = 0; j < tam; j++)
         {
            ArqCaminho << mat[i][j] << " ";
         }
         ArqCaminho << endl;
      }
      ArqCaminho << endl;
      arqbool.close();
      outputFile.close();
   }
   ArqCaminho.close();

   cout << " \t\t DADOS FINAIS \t\t" << endl;
   cout << "\t\t --------------------------------------------------------\t\t" << endl;
   cout << "\t Numero de casas não exploradas: " << positionsNoaccessed << endl;
   cout << "\t Numero de casas descobertas: " << positionsAccessed << endl;
   cout << "\t Numero de passos: " << viaj.getQtd_andada() << endl;
   cout << "\t Perigos enfrentados: " << viaj.getPerigos_passados() << endl;
   cout << "\t Itens totais que foram colocados na mochila: " << viaj.getItens_totais() << endl;
   cout<<"\t Itens que foram encontrados "<<((viaj.getItensNaoPegos()) + (viaj.getItens_totais()))<<endl;
   cout << "\t Vidas: " << viaj.getVida() << endl;
   cout << "\t Poções: " << viaj.getPocoes() << endl;
   cout << "\t\t --------------------------------------------------------\t\t" << endl;
}
