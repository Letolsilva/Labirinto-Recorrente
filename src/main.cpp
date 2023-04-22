#include "arquivo.hpp"
using namespace std;
int main()
{
    clock_t inicio = clock();
    double tempo;
    Matriz m;
    m.le_arquivo();
    clock_t fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    cout<<"\n Tempo de execução: "<< tempo << " segundos. "<<endl;
    return 0;
}
