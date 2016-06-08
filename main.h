/*-------------------------------------------------------------------

	Este arquivo descreve funcoes usadas para a execucao do pacman	

	Programadores: 

    Acacio Lopes			58441
    Gustavo Carvalho		58449
    Lucas Ferrari			58438
    Phellipe Kelbert		58428
    Renan Dezan				58455

	Data: 16/07/2007

-------------------------------------------------------------------*/


#ifndef __Main_h
#define __Main_h

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#define SIZE			25	// unidade em pixel
#define X_BOUND			19	// limite horizontal da matriz
#define Y_BOUND			21	// limite vertical da matriz
#define BLOCK			0	// representa parede
#define FOOD_1			1	// representa a bolinha normal
#define FOOD_2			2	// representa a bolinha especial
#define VALUE_FOOD_1	10	// valor da bolinha normal
#define VALUE_FOOD_2	20	// valor da bolinha especial
#define EMPTY			9	// caracter que representa espaço vazio
#define GHOST_BOUND		4	// número de fantasmas

enum dir {
	dir_inercian,
	dir_up,
	dir_down,
	dir_right,
	dir_left
};

struct point {
	int x;
	int y;
};

struct character {
	point	position;	// posição atual do personagem
	dir		going;		// direção atual do personagem
	dir		wish;		// direção para onde o personagem quer ir
	int		pic;		// handle da figura do personagem
};

struct picHandles {
	int		up;
	int		right;
	int		down;
	int		left;
};

/*--------------------------------------------------------------------------------
     Funcao que trata da amimacao(mudanca de estado) do pacman
     Reveza entre estado aberto(animar=1) e estado fechado(animar=-1)
--------------------------------------------------------------------------------*/
void animacao(dir direcao);

/*--------------------------------------------------------------------------------
     Funcao que determina o texto com a pontuacao do pacman na forma "Score: xxx"
--------------------------------------------------------------------------------*/
void defineScoreText();

/*--------------------------------------------------------------------------------
	Retorna o desenho vizinho
--------------------------------------------------------------------------------*/
char getVizinho(point *p, dir vizinho);

/*--------------------------------------------------------------------------------
	Retorna se a posicao está em um dos extremos do eixo.
	Retorna 0 case não esteja em nenhum extremo, negativo caso esteja no 
	extremo inferior e positivo se etiver no extremo superior.
--------------------------------------------------------------------------------*/
int inExtremity(int pos, int eixo);

/*--------------------------------------------------------------------------------
	Retorna a posicao do bloco vizinho no eixo indicado
--------------------------------------------------------------------------------*/
int posicaoVizinho(point *p, dir vizinho);

/*--------------------------------------------------------------------------------
	Define o desenho vizinho
--------------------------------------------------------------------------------*/
void setVizinho(point *p, char vizinho);

/*--------------------------------------------------------------------------------
    Funcao que retorna se duas posições são iguais
--------------------------------------------------------------------------------*/
bool samePoint(point *p, point *q);

/*--------------------------------------------------------------------------------
    Retorna se existe um fantasma na posição
--------------------------------------------------------------------------------*/
bool checkGhost(point *p);

/*--------------------------------------------------------------------------------
     Funcao que retorna uma direção aleatória válida que aponte para uma
	 posição diferente da de origem
--------------------------------------------------------------------------------*/
dir randomDirection(point *p, point *q);

/*--------------------------------------------------------------------------------
     Funcao que retorna uma direção válida mais próxima possível do
	 pacman ou uma aleatória caso seja inválida
--------------------------------------------------------------------------------*/
dir smartDirection(point *p, point *q);

/*--------------------------------------------------------------------------------
    Funcao que retorna a posição apontada pela direção a ´partir
	do ponto de origem 
--------------------------------------------------------------------------------*/
point getPoint(point *p, dir);

/*--------------------------------------------------------------------------------
     Funcao que retorna direção baseada em inteiro
--------------------------------------------------------------------------------*/
dir intToDir(int i);

/*--------------------------------------------------------------------------------
     Funcao que retorna se uma posição é válida para movimentação
--------------------------------------------------------------------------------*/
bool validVizinho(int vizinho);

/*--------------------------------------------------------------------------------
    Funcao que sinaliza que o jogador ganhou
--------------------------------------------------------------------------------*/
void finishWin();

/*--------------------------------------------------------------------------------
    Funcao que sinaliza que o jogador perdeu
--------------------------------------------------------------------------------*/
void finishLose();

#endif
