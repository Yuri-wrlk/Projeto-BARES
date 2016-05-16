## Project BARES

##### Version 1.0.0 - Monday May 16th 2016

by Thiago Cesar Morais Diniz de Lucena and Yuri Reinaldo da Silva  


Introduction
--------------------------------------------------------------------------------------

BARES, or *Basic ARithmetic Expression Evaluator based on Stacks*, is a program
made in C++, it's main purpose is to take a series of arithmetic expressions and
analyse it searching if there is any problem within the formula and if it is 
well-formed.

At the moment the program does not support algebraic or any other type of numeral 
other than integers.

Instalation and running
--------------------------------------------------------------------------------------

To install and execute the program, follow these steps: 

1. The file must be extracted from the accompanying zip folder 
  "Project_Bares.zip", it should come with all the files necessary.
2. Open your terminal and navigate to the folder where the files where extracted
   to.
3. Simply input the __make__ command.
..* Instead of make, another way to do it is by inputting the following command 
	at the terminal:
	g++ -std=c++11 -I include src/drive\_bares.cpp src/functions.cpp -o bin/drive_bares

Para executar o programa deve-se extrair o arquivo "Projeto Keno-Game.
zip", através do terminal navegar até a pasta principal (a que contém 
as pastas "bin", "data", "include" e "src") e compilar o programa 
através do seguinte comando:

	g++ -Wall -std=c++11 -I include/ src/drive_keno.cpp src/keno_func.cpp  src/keno_c.cpp -o bin/exe

Logo após basta executar o jogo usando o comando:
	
	./bin/exe /data/*nome_do_arquivo.txt*

É importante que *"nome_do_arquivo.txt"* seja substituido pelo nome do
arquivo da sua aposta no tipo ".txt" ou similar.

O arquivo da aposta deverá conter, _em linhas separadas_, o valor de 
sua aposta, o número de rodadas que se deseja jogar e os valores 
inteiros entre 1 e 80 nos quais você deseja apostar. Esses valores 
devem estar em uma única linha e devem ser separados por espaço.

Pronto! O Keno Game será executado e os resultados do jogo serão 
exibidos na tela.


Como Jogar
--------------------------------------------------------------------------------------

O Keno Game é um jogo de apostas em que são escolhidos até 15
números entre 1 e 80, logo após o jogo irá gerar um total de
20 valores no mesmo intervalo e então será calculada a quantidade
de acertos e o valor a ser recebido.

É possível apostar entre 1 e 15 números, e para cada quantidade
há uma tabela de pagamentos correspondente que será exibida.

Também é permitido que o jogador distribua seus créditos em várias
apostas. Para tal, basta aumentar o número de rodadas que os seus
créditos passarão a ser divididos igualmente para cada jogo. 


Bugs e limitações
--------------------------------------------------------------------------------------

Caso os valores de créditos, rodadas e números apostados sejam
inseridos na mesma linha, é possível que não seja feita a leitura de 
todos. Portanto, é imprescindível que estas três características 
estejam em linhas diferentes.

Números em conjunção com caracteres e outros símbolos também serão 
ignorados.

Exemplo de uma aposta padrão:

1500 - Sendo o valor apostado
4 - Quantidade de rodadas
1 2 2 4 5 6 7 8 9 10 11 23 33 50 60 - Números apostados

Exemplo de uma aposta válida:

as
das
das
dasd
1500 a a a
-2 4

1 2 2 4 -1 5 6 7 8 9 10 '11' '23' 33 50 60

