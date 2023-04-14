<h1> Labirinto-Recorrente </h1>
<!-- IMAGEM LABIRINTO-->
<p align="justify">
Programa para disciplina de Algoritmo de Estrutura de Dados I, desenvolvido na linguagem C++.<br>
Neste algoritmo, se encontra a seguinte indagação: como encontrar a saída de um labirinto? Desta forma, o objetivo deste programa é encontrar uma saída para um labirinto virtual (representado por matrizes), partindo de um local definido pelo usuário na primeira matriz, durante o caminhamento existirá inumeros desafios que serão enfrentados pelo "Viajante". Portanto, este sistema trabalha o conceito de caminhamento em matrizes e entre matrizes de forma <b>aleatória</b>, objetivando utilizar execuções mais elaboradas e ao final <b>analisar o custo computacional</b> de todo o processo.<br>  
Em resumo, deve-se criar um algoritmo no qual o personagem caminhe de forma aleatória por todas as matrizes, enquanto ele sobreviver ou concluir todos os critérios para chegar a saída.
</p>

<h2> Objetivos </h2>
<p align="justify">
Executar apartir das K matrizes quadradas no tamanho NxN, escritas no arquivo "dataset/input.data", estas matrizes e o padrão do arquivo que será lido são geradas pelo programa <a href="https://github.com/mpiress/GenerateDataToMaze.git">GenerateDataToMaze</a>. Iniciando na primeira matriz, começando a percorre-lá na posição escolhida pelo usuário e continuar enquanto não encontrar a saída do labirinto. Importante resaltar novamente que este caminhamento é gerado por um randômico, isto é de maneira aleatório.
<h4>Condições do jogo</h4>
Neste jogo temos o Viajante perdido em um labirinto, ele tem consigo:

- Vida: ele se inícia com 10 de vida, podendo ser perdida ao enfrentar um perigo e ganhar quando encontrar 4 poções.
- Mochila: A mochila é onde ele armazena as poções encontradas, quatro delas podem ser trocadas por uma vida, mas se a mochila estiver cheia (conter quatro itens) e sua vida também (dez vidas), ele não consiguira armazenar mais itens, ele os pega mas, os passa para seu companheiro de viagem.

Ele percorre os mapas (matrizes), nestes existem alguns desafios, sendo eles:

- Perigos selvagens (*): Estes perigos são representados por '*' (asterisco), ele dão um de dano no viajante.
- Barreiras (#): As barreiras não permitem o prsonagem entrar naquela determinada posição, sendo assim, ele terá que desviar e continuar o caminho, logo é gerado nova posição i,j caso ele se depare com alguma.
- Mapas: Os mapas são compostos de números que representam a quantidade de poções existentes naquela posição, cada vez que se passa por uma é extraido 1 daquele local, até chegar em 0, o que significa que não terá mais itens para serem pegos ali, essas posições continuam sendo utilizadas normalmente.
<!-- IMAGEM DEMONSTRANDO COMO É OS MAPAS -->
- Mudança de dimensão: Essas mudanças ocorrem caso ele tente quebrar os limites do mapa, isto vale para qualquer um dos lados da matriz, logo ele consegue abrir um portal que o levrá para outro mapa, isto por K matrizes que existem no arquivo, caso ele chegue na última, ele retorna a matriz 0 (primeira matriz).
<!-- COLOCAR IMAGEM MUDANÇA DE DIMENSÃO -->

<h4> Condição de parada </h4>
Para passar por tudo isso, existem um objetivo, sendo ele sair deste labirinto, mas para encontrar a saída ele tem que encontrar muitos itens, o suficiente para zerar todas as posições do caminho que ele passou, explorar pelo ao menos uma vez todos os mapas e retornar a sua posição de inicial ou ser derrotado pelos animais selvagens e não acabar sobrevivendo (Vida 0).
</p>

<h2> Lógica do código </h2>
A implementação lógica foi desenvolvida com o objetivo de evitar falhas no programa ou no sistema operacional, como o "estouro de memória", que pode ocorrer quando a quantidade ou tamanho das matrizes excede a capacidade de memória disponível no sistema. Para resolver isso, o programa lê as matrizes do arquivo "dataset/input.data", reescreve e armazena cada uma em arquivos separados, nomeados como "dataset/matriz(K).data". O valor "K" representa o número da matriz atualmente lida e é incrementado a cada iteração do processo, até o fim das matrizes presentes no arquivo "input.data". Essa mesma lógica se aplica ao arquivo de matrizes booleanas, que começa com valores da matriz zerados e é atualizado para 1 nas posições (i, j) que são acessadas durante o caminhamento nas matrizes, com o nome do arquivo sendo "dataset/matrizbool(K).data".Estes arquivos são atualizados no decorrer do programa.
 <br>  <br>
O código está dividido em sete arquivos(exceto os de leitura): Main.cpp, viajante.hpp, viajante.cpp, functions.hpp, functions.cpp, arquivo.hpp e arquivo.cpp. Vamos abordar cada um deles:

* ```main.cpp```: Tudo se inicia na main, sendo chamada a função le_arquivo.
* ```viajante.hpp```: Classe do viajante com seus atributos.
* ```viajante.cpp```: Implementação dos atributos definidos nas declarações do arquivo hpp.
* ```functions.hpp```: Contém as declarações das funções.
* ```functions.cpp```: Implementação das funções, sendo elas salvar_matriz, nova_matriz,changeDimension, Funcs_padroes, checkIfIsZero e outout. 
* ```arquivo.hpp```: Contém as declarações das classes, funções, variáveis e constantes que são usadas no programa, referente as matrizes. 
* ```arquivo.hpp```:


