<div align = "center" >
<h1> Labirinto-Recorrente </h1>
<img src="https://user-images.githubusercontent.com/109817570/232165764-1f993a40-61d9-491a-83ff-d45b118b11b2.jpg" width="14%">

![C++](https://img.shields.io/badge/Linguagem-C++-green.svg)
![Make](https://img.shields.io/badge/Compilacao-Make-orange)
![VSCode](https://img.shields.io/badge/IDE-VSCode-informational)
</div>

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
- Movimentação: A movimentação na matriz é realizada de forma aleatória, por meio da geração de números randômicos que variam de 1 a 8. Esses números representam as direções nas quais o caminhamento deve ser realizado, são eles:
  * Número 1: Saltar para linha de cima (Cima);
  * Número 2: Saltar para a linha de baixo (Baixo);
  * Número 3: Retroceder para coluna anterior (Esquerda);
  * Número 4: Avançar para a próxima coluna (Direita);
  * Número 5: Ir em diagonal para baixo sentido direita (Diagonal direita);
  * Número 6: Ir em diagonal para baixo sentido esquerda (Diagonal esquerda);
  * Número 7: Ir em diagonal para cima sentido direita (Diagonal direita cima);
  * Número 8: Ir em diagonal para cima sentido esquerda (Diagonal esquerda cima);

<h4> Condição de parada </h4>
Para passar por tudo isso, existem um objetivo, sendo ele sair deste labirinto, mas para encontrar a saída ele tem que encontrar muitos itens, o suficiente para zerar todas as posições do caminho que ele passou, explorar pelo ao menos uma vez todos os mapas e retornar a sua posição de inicial ou ser derrotado pelos animais selvagens e não acabar sobrevivendo (Vida 0).
</p>

<h2> Lógica do código </h2>
<p align="justify">
A implementação lógica foi desenvolvida com o objetivo de evitar falhas no programa ou no sistema operacional, como o "estouro de memória", que pode ocorrer quando a quantidade ou tamanho das matrizes excede a capacidade de memória disponível no sistema. Para resolver isso, o programa lê as matrizes do arquivo "dataset/input.data", reescreve e armazena cada uma em arquivos separados, nomeados como "dataset/matriz(K).data". O valor "K" representa o número da matriz atualmente lida e é incrementado a cada iteração do processo, até o fim das matrizes presentes no arquivo "input.data". Essa mesma lógica se aplica ao arquivo de matrizes booleanas, que começa com valores da matriz zerados e é atualizado para 1 nas posições (i, j) que são acessadas durante o caminhamento nas matrizes, com o nome do arquivo sendo "dataset/matrizbool(K).data".Estes arquivos são atualizados no decorrer do programa.
 <br>  <br>
O código está dividido em sete arquivos(exceto os de leitura): Main.cpp, viajante.hpp, viajante.cpp, functions.hpp, functions.cpp, arquivo.hpp e arquivo.cpp. Vamos abordar cada um deles:

* ```main.cpp```: Tudo se inicia na main, sendo chamada a função le_arquivo.
* ```viajante.hpp```: Classe do viajante com seus atributos.
* ```viajante.cpp```: Implementação dos atributos definidos nas declarações do arquivo hpp.
* ```functions.hpp```: Contém as declarações das funções.
* ```functions.cpp```: Implementação das funções, sendo elas salvar_matriz, nova_matriz, Funcs_padroes, changeDimension, checkIfIsZero e output. 
 
  * salvar_matriz: A função "salvar_matriz" é responsável por atualizar os arquivos das matrizes de string e booleanas. Durante o percurso na matriz, a função acessa as posições da matriz e subtrai os valores dessas posições. Como resultado, a matriz sofre alterações em seus valores. A função mantém os arquivos atualizados, registrando essas alterações a cada mudança de dimenssão ou final do jogo.
 
  * nova_matriz: A função "nova_matriz" é responsável por ler o arquivo que contém a próxima matriz e salvá-la na matriz local para ser percorrida. Essa operação ocorre quando há mudanças de dimensões, seja na transição de uma matriz K para K+1, ou no retorno da matriz K-1 para a matriz 0.

  * Funcs_padroes: A função "Funcs_padroes" utiliza a variável inteira "tag" como parâmetro para acessar o caso correspondente no switch case em que a função está. Quando a tag é igual a 0 significa que um perigo é encontrado na posição atual, a função subtrai uma vida, adiciona a quantidade de perigos enfrentados e de posições percorridas, e atribui o valor booleano 1 à posição correspondente na matriz booleana. Quando a variável "tag" recebe o valor 1, isso indica que há um número inteiro maior que zero na posição atual. Nesse caso, a função subtrai um da posição, adiciona um às poções encontradas, ao total de itens encontrados e às posições percorridas. Além disso, ela atribui o valor booleano 1 à posição correspondente na matriz booleana. A função também realiza verificações para determinar se a quantidade de poções encontradas é igual a 4. Se isso acontecer e a vida for menor do que 10, as quatro poções são subtraídas e uma vida é adicionada. Caso a vida já esteja em 10, a poção é considerada como encontrada, mas não é adicionada à mochila.
 
   * changeDimension: A função "changeDimension" é acionada sempre que uma das matrizes atinge seu limite. Ela recebe duas variações: uma com a tag 1, que indica a transição para as matrizes posteriores, e outra com a tag 2, que indica o retorno da última matriz para a primeira (matriz 0). Essa função é responsável por permitir que o viajante explore todas as matrizes várias vezes, salvando a matriz anterior, carregando a próxima e determinando a posição do viajante na nova matriz. Geralmente, quando o viajante vai para uma próxima matriz, ele permanece na mesma coluna e vai para a primeira linha, ao retornar, ele vai para a última linha. No entanto, se houver uma barreira, é gerada uma nova posição (i, j). A função também realiza as ações necessárias na nova posição, utilizando se da função ```Funcs_padroes ```. 
 
  * checkIfIsZero: A função "checkIfIsZero" tem como objetivo verificar se todo o caminho percorrido pelo viajante é composto apenas por valores iguais a zero. Para isso, a função utiliza duas variáveis booleanas: "allNonZero" e "mudou_mat". A variável "allNonZero" é inicializada como true e alterada para false se a função encontrar um valor diferente de zero. A variável "mudou_mat" é inicializada como true e alterada para false toda vez que o viajante muda de dimensão, garantindo que todas as matrizes foram visitadas pelo menos uma vez. A função continua verificando se "mudou_mat" é false e "allNonZero" é true até que o viajante retorne à posição inicial, neste momento se "mudou_mat" for false, ele verifica se "allNonZero" é verdadeiro, caso seja todo o caminho percorrido é zero, Se não for, ela redefine "mudou_mat" e "allNonZero" como true e continua a percorrer um novo caminho. Essa verificação ocorre repetidamente até que o viajante retorne à posição inicial, "mudou_mat" se torne false e "allNonZero" seja true, indicando que todo o caminho percorrido é zero.
 
  * output: A função "output" tem como propósito exibir os resultados finais do programa. Durante a execução dessa função, é realizada a leitura da matriz booleana para contabilizar o número de casas acessadas e não acessadas. Além disso, são apresentados os dados finais, tais como os números de passos realizados, casas não visitadas, perigos enfrentados, itens encontrados, vidas, poções e também os de casas descobertas e não descobertas. Ele também realiza a leitura de todas as matrizes de string e as guarda em um único arquivo de saída.
  
* ```arquivo.hpp```: Contém as declarações das classes, funções, variáveis e constantes que são usadas no programa, referente as matrizes. 
* ```arquivo.hpp```: Implementação das funções, sendo elas le_arquivo e walkmatriz.
  * le_arquivo:  A função "le_arquivo" é responsável por ler o arquivo "dataset/input.data", o que possibilita a determinar da quantidade de matrizes e seus tamanhos, que serão utilizados posteriormente para armazenar os valores. Dentro do comando "while", a função cria uma matriz de ponteiros de tamanho "N" para armazenar os valores das matrizes de string e booleana, com base nos dois primeiros números lidos anteriormente. Em seguida, é executado um loop que percorre os valores da matriz e armazena os endereços de memória correspondentes aos índices da matriz na matriz de ponteiros. Na matriz booleana, todos os seus elementos são inicializados com zero.Dessa forma, é alocada memória suficiente para a quantidade de inteiros lidos e armazenados na matriz. Durante a execução da função, as matrizes são escritas em novos arquivos, conforme a lógica já explicada anteriormente no começo deste tópico. Ao fim, é chamada a função walkmatriz que vai nos permitir andar pelas matrizes lidas.
  
  * walkmatrix: Essa função permite ao jogador caminhar e alcançar os objetivos do jogo. Ela começa no mapa 0, que é a primeira matriz do jogo, e as matrizes de strings e booleanas sempre permanecem as mesmas. Isso significa que, se o jogador está na primeira matriz de strings, ele também está na primeira matriz booleana.No início da função, o usuário escolhe a posição em que deseja iniciar. Se a posição escolhida pelo usuário for uma parede, a função solicita que ele escolha uma nova posição válida para iniciar o jogo. Mesmo na primeira posição escolhida, o jogador já está sujeito a sofrer danos, encontrar itens ou não encontrar nenhuma poção durante sua jornada. Após escolher a posição inicial, o jogo começa e as posições seguintes são geradas aleatoriamente, seguindo a lógica explicada no tópico objetivos. Elas são implementadas em um switch case, onde entram na condição do número sorteado e realizam as operações correspondentes. Por exemplo, verificar se estão em uma borda e querem ultrapassar para trocar de dimensão, utilizando a função  ``` changeDimension```, mover para a posição gerada e realizar as ações correspondentes a ela usando a função  ``` Funcs_padroes``` e verificar se o item na posição é igual a zero. Após cada iteração, é verificado se a vida do viajante é maior que zero e se o caminho percorrido é igual a zero, utilizando a função  ``` checkIfIsZero```. Quanado alguma das condições de paradas for alcançada, a função  ``` salvar_matriz``` é chamada para salvar as alterações na matriz e, em seguida, a função  ``` output``` chamada para mostrar os dados finais e gerar o arquivo de saída com as matrizes alteradas. 
  </p>
  
 <h2> Compilação e Execução </h2>

Esse código possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Após temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
