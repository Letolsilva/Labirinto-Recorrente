#include "arquivo.hpp"
using namespace std;
int main()
{
    clock_t start = clock();
    Matriz m;
    m.le_arquivo();
    clock_t end = clock();
    double durations = (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"\n Tempo de execução: "<< durations << " segundos. "<<endl;
    return 0;
}
