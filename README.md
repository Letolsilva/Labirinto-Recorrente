# Labirinto-Recorrente

<p align="justify">
Programa para disciplina de Algoritmo de Estrutura de Dados I, desenvolvido na linguagem C++.<br>
Neste algoritmo, se encontra a seguinte indagação: como encontrar a saída de um labirinto? Desta forma, o objetivo deste programa é encontrar uma saída para um labirinto virtual (representado por matrizes), partindo de um local definido pelo usuário na primeira matriz, durante o caminhamento existirá inumeros desafios que serão enfrentados pelo "Viajante". Portanto, este sistema trabalha o conceito de caminhamento em matrizes e entre matrizes de forma <b>aleatória</b>, objetivando utilizar execuções mais elaboradas e ao final <b>analisar o custo computacional</b> de todo o processo.<br>  
Em resumo, deve-se criar um algoritmo no qual o personagem caminhe de forma aleatória por todas as matrizes, enquanto ele sobreviver ou concluir todos os critérios para chegar a saída.
</p>

# Objetivos
<p align="justify">
O sistema se executa apartir das K matrizes quadradas no tamanho NxN, escritas no arquivo "dataset/input.data", estas matrizes e o padrão do arquivo que será lido são geradas pelo programa <a href="https://github.com/mpiress/GenerateDataToMaze.git">GenerateDataToMaze</a>. Ele se inicia na primeira matriz, começando a percorre-lá na posição escolhida pelo usuário e continua enquanto não encontrar a saída do labirindo, ou seja, retornar a posição de inicio, todo o caminho percorrido por ele ser zero e ter acessado pelo ao menos uma vez todas as matrizes ou ele não sobreviver, importante resaltar novamente que este caminhamento será gerado por um randômico, isto é de maneira aleatório.</p>
