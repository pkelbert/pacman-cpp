/******************************************************************
	
    Alunos:
	
    Acacio Lopes			58441
    Gustavo Carvalho		58449
    Lucas Ferrari			58438
    Phellipe Kelbert		58428
    Renan Dezan				58455
	
******************************************************************/

#include "base.h"
#include "main.h"

/*
	handle das figuras
*/
int numFigBola1;		
int	numFigBola2;		
int	numFigTijolo;
int	numFigFundo;
int numFigPacmanClosed;
int numFigGetReady;
int numFigFinish;

int mapa[X_BOUND][Y_BOUND];	// mapa do jogo
int score = 0;			// pontuação
int totalScore = 0;		// total de pontos distribuídos no mapa
int hWndMain;			// handle da janela principal
int ciclo = 1;			// guarda o estado de animacao
int waitFor = 10;		// ciclos de executar a serem esperados no início do jogo
int waitCount = 0;		// total de ciclos executar

bool executarStarted = false;
bool finished = false;

char scoreText[20];		// texto a ser exibido na janela de pontuação

point padding;			// margens do mapa

character pacman;
character ghost[GHOST_BOUND];
point lastGhostPos[GHOST_BOUND];

picHandles pH_pacman;
picHandles pH_ghost[GHOST_BOUND];

void iniciar() {
    
    int			i, j;
    char		vetor[X_BOUND];	// linha temporária do mapa
    ifstream	arq;			// arquivo contendo o mapa
	
    cout << "Iniciando aplicacao..." << endl;
    
	// inicia modo aleatório
	srand(time(0));
	
	/* 
		carrega figuras de arquivos.
		os numeros das figuras sao armazenados, para ser possivel
		desenha-las na funcao "executar"
	*/
	
	numFigBola1 = carregaFiguraDeArquivo("Resources\\pictures\\food_normal.jpg");
	numFigBola2 = carregaFiguraDeArquivo("Resources\\pictures\\food_special.jpg");
    numFigFundo = carregaFiguraDeArquivo("Resources\\pictures\\fundo.jpg");
    numFigTijolo = carregaFiguraDeArquivo("Resources\\pictures\\tijolo.jpg");
	numFigPacmanClosed = carregaFiguraDeArquivo("Resources\\pictures\\pacman_closedMouth_any.jpg");
	
	pH_pacman.right = carregaFiguraDeArquivo("Resources\\pictures\\pacman_openMouth_right.jpg");
	pH_pacman.up = carregaFiguraDeArquivo("Resources\\pictures\\pacman_openMouth_up.jpg");
	pH_pacman.left = carregaFiguraDeArquivo("Resources\\pictures\\pacman_openMouth_left.jpg");
	pH_pacman.down = carregaFiguraDeArquivo("Resources\\pictures\\pacman_openMouth_down.jpg");
	
	pH_ghost[0].right = carregaFiguraDeArquivo("Resources\\pictures\\ghost_red_right.jpg");
	pH_ghost[0].left = carregaFiguraDeArquivo("Resources\\pictures\\ghost_red_left.jpg");
	pH_ghost[0].up = carregaFiguraDeArquivo("Resources\\pictures\\ghost_red_up.jpg");
	pH_ghost[0].down = carregaFiguraDeArquivo("Resources\\pictures\\ghost_red_down.jpg");
	
	pH_ghost[1].right = carregaFiguraDeArquivo("Resources\\pictures\\ghost_blue_right.jpg");
	pH_ghost[1].left = carregaFiguraDeArquivo("Resources\\pictures\\ghost_blue_left.jpg");
	pH_ghost[1].up = carregaFiguraDeArquivo("Resources\\pictures\\ghost_blue_up.jpg");
	pH_ghost[1].down = carregaFiguraDeArquivo("Resources\\pictures\\ghost_blue_down.jpg");
	
	pH_ghost[2].right = carregaFiguraDeArquivo("Resources\\pictures\\ghost_green_right.jpg");
	pH_ghost[2].left = carregaFiguraDeArquivo("Resources\\pictures\\ghost_green_left.jpg");
	pH_ghost[2].up = carregaFiguraDeArquivo("Resources\\pictures\\ghost_green_up.jpg");
	pH_ghost[2].down = carregaFiguraDeArquivo("Resources\\pictures\\ghost_green_down.jpg");
	
	pH_ghost[3].right = carregaFiguraDeArquivo("Resources\\pictures\\ghost_purple_right.jpg");
	pH_ghost[3].left = carregaFiguraDeArquivo("Resources\\pictures\\ghost_purple_left.jpg");
	pH_ghost[3].up = carregaFiguraDeArquivo("Resources\\pictures\\ghost_purple_up.jpg");
	pH_ghost[3].down = carregaFiguraDeArquivo("Resources\\pictures\\ghost_purple_down.jpg");
	
	/*
		carrega janelas e controles visuais
	*/
	
	defineScoreText();
	hWndMain = criaSubjanela(scoreText, W_WIDTH - 110, W_HEIGHT - 35, 100, 25, true);
	
    /*
		carrega o mapa
	*/
	
    arq.open("mapa.txt");    
    for(j = 0; j < Y_BOUND; j++) {
		
        arq >> vetor;
		
        for(i = 0; i < X_BOUND; i++)
			mapa[i][j] = vetor[i];
		
    }
    
	/*
		carrega a posicao do pacman
	*/
	
	arq >> pacman.position.x 
		>> pacman.position.y;
	
	/*
		carrega a posição dos fantasmas
	*/
	
	for(i = 0; i < GHOST_BOUND; i++) {
		
		arq >> ghost[i].position.x
			>> ghost[i].position.y;
		
		lastGhostPos[i] = ghost[i].position;
		
	}
	
	/*
		converte o caracter para o seu numero representado em inteiro
	*/
	
    for(j = 0; j < Y_BOUND; j++)
		for(i = 0; i < X_BOUND; i++) {
			
            mapa[i][j] -= 48;
			
			switch (mapa[i][j]) {
				case FOOD_1:
					totalScore += VALUE_FOOD_1;
					break;
				case FOOD_2:
					totalScore += VALUE_FOOD_2;
					break;
			}
			
		}
    
    /*
		centraliza o mapa
	*/
	
    padding.x = (W_WIDTH - (X_BOUND * SIZE)) / 2;
    padding.y = (W_HEIGHT - (Y_BOUND * SIZE)) / 2;
	
	
	pacman.going = dir_right;
	
}

void executar() {
    
    int i, j;
    point pos, p, q;
	
	
	if (!finished) {
		
		/*
			verifica a ultima entrada
		*/
		if (pacman.wish != dir_inercian) {
			if(getVizinho(&pacman.position, pacman.wish) != BLOCK) {
				pacman.going = pacman.wish;
				pacman.wish = dir_inercian;
			}
		}	
		
		/*
			verifica se o jogo acabou
		*/
		
		if (score == totalScore) {
			finishWin();
		}
		else {
			
			for(i = 0; i < GHOST_BOUND; i++) {
				
				p = getPoint(&pacman.position, pacman.going);
				q = getPoint(&ghost[i].position, ghost[i].going);
				
				if (samePoint(&p, &ghost[i].position) || samePoint(&q, &pacman.position) ||
					samePoint(&pacman.position, &ghost[i].position)
				   ) {
					finishLose();
				}
				
			}
			
		}
		
		if (waitCount >= waitFor) {

			/*
				move o pacman
			*/
			
			if(getVizinho(&pacman.position, pacman.going) != BLOCK) {
				
				/*
					aumenta a pontuacao quando passa por uma bolinha
				*/
				switch (getVizinho(&pacman.position, pacman.going)) {
					case FOOD_1:
						score += VALUE_FOOD_1;
						break;
					case FOOD_2:
						score += VALUE_FOOD_2;
						break;
				}
				
				setVizinho(&pacman.position, EMPTY);	// espaco EMPTY
				
				/*
					modifica a posicao do pacman	
				*/
				switch (pacman.going) {
					case dir_up:
					case dir_down:
						pacman.position.y = posicaoVizinho(&pacman.position, pacman.going);
						break;
						
					case dir_left:
					case dir_right:
						pacman.position.x = posicaoVizinho(&pacman.position, pacman.going);
						break;
						
				}
				
			}
			
			animacao(pacman.going);
			
			if (ciclo == 1) {
				
				/*
					move os fantasmas
				*/
				
				for (i = 0; i < GHOST_BOUND; i++) {
					
					if (i%2==0)
						ghost[i].going = smartDirection(&ghost[i].position, &lastGhostPos[i]);
					else
						ghost[i].going = randomDirection(&ghost[i].position, &lastGhostPos[i]);
					
					if (executarStarted)
						lastGhostPos[i] = ghost[i].position;
					
					/*
						modifica a posição do fastasma
					*/
					switch (ghost[i].going) {
						case dir_inercian:
							ghost[i].position = lastGhostPos[i];
							break;
						case dir_up:
						case dir_down:
							ghost[i].position.y = posicaoVizinho(&ghost[i].position, ghost[i].going);
							break;
							
						case dir_left:
						case dir_right:
							ghost[i].position.x = posicaoVizinho(&ghost[i].position, ghost[i].going);
							break;
							
					}
					
					/*
						modifica a figura do fantasma
					*/
					switch (ghost[i].going) {
						case dir_up:
							ghost[i].pic = pH_ghost[i].up;
							break;
						case dir_down:
							ghost[i].pic = pH_ghost[i].down;
							break;
						case dir_right:
							ghost[i].pic = pH_ghost[i].right;
							break;
						case dir_left:
							ghost[i].pic = pH_ghost[i].left;
							break;
					}
					
				}
				
			}
			
		}
		
		/*
			atualiza o score
		*/
		
		defineScoreText();
		redefineSubjanela(hWndMain, scoreText, W_WIDTH - 110, W_HEIGHT - 35, 100, 25);
		
	}
	
    /*
		desenha o mapa
	*/
	
	pos.y = padding.y;
    pos.x = padding.x; 
   	
    for(j = 0 ; j < Y_BOUND; j++) {
		
        for(i = 0; i < X_BOUND; i++) {
			
            switch (mapa[i][j]) {
				case BLOCK:
					desenhaFigura(numFigTijolo, pos.x, pos.y);
					break;
				case FOOD_1:
					desenhaFigura(numFigBola1, pos.x, pos.y);
					break;
				case FOOD_2:
					desenhaFigura(numFigBola2, pos.x, pos.y);
					break;
				case EMPTY:
					desenhaFigura(numFigFundo, pos.x, pos.y);
					break;
			}
			
            pos.x += SIZE;
			
        }
		
        pos.y += SIZE;
        pos.x = padding.x;
		
    }
	
	/*
		desenha os personagens
	*/
	
	desenhaFigura(pacman.pic, 
		          pacman.position.x * SIZE + padding.x,
				  pacman.position.y * SIZE + padding.y
				 );
	
	for (i = 0; i < GHOST_BOUND; i++) {
		
		desenhaFigura(ghost[i].pic, 
					  ghost[i].position.x * SIZE + padding.x,
					  ghost[i].position.y * SIZE + padding.y
					 );
		
	}	
	
	
	if (waitCount < waitFor) {
		
		if (!numFigGetReady)
			numFigGetReady = carregaFiguraDeArquivo("Resources\\pictures\\getReady.png");
		
		desenhaFigura(numFigGetReady, padding.x, padding.y);
		waitCount++;
		
	}
	
	if (finished)
		desenhaFigura(numFigFinish, padding.x, padding.y);
	
	executarStarted = true;
	
}

void eventoTeclado (int tipoEvento, int tecla) {         
	
	switch (tecla) {
		case TECLA_LEFT:
			pacman.wish = dir_left;
			break;
		case TECLA_RIGHT:
			pacman.wish = dir_right;
			break;
		case TECLA_UP:
			pacman.wish = dir_up;
			break;
		case TECLA_DOWN:
			pacman.wish = dir_down;
			break;
    }
    
}

void eventoMouse(int tipoEvento, int botao, int x, int y) {
	// a declaração da função é obrigatória
}

int inExtremity(int pos, int eixo) {
	switch (eixo) {
		case 0:
			if (pos <= 0)
				return -1;
			else if( pos >= X_BOUND - 1 )
				return 1;
			else
				return 0;
		case 1:
			if ( pos <= 0 ) 
				return -1;
			else if ( pos >= Y_BOUND - 1 )
				return 1;
			else
				return 0;
	}
}

int posicaoVizinho(point *p, dir vizinho) {
	
	int ext;
	
	switch (vizinho) {
		
		case dir_left:
			
			ext = inExtremity(p->x, 0);

			switch (ext) {
				case -1:
					return X_BOUND-1;
				case 0:
				case 1:
					return p->x - 1;
			}
			
		case dir_right:
			
			ext = inExtremity(p->x, 0);
			
			switch (ext) {
				case 1:
					return 0;
				case -1:
				case 0:
					return p->x + 1;
			}
			
		case dir_up:

			ext = inExtremity(p->y, 1);

			switch (ext) {
				case -1:
					return Y_BOUND-1;
				case 1:
				case 0:
					return p->y - 1;
			}
			
		case dir_down:
			
			ext = inExtremity(p->y, 1);
			
			switch (ext) {
				case 1:
					return 0;
				case -1:
				case 0:
					return p->y + 1;
			}
			
	}
	
}

char getVizinho(point *p, dir vizinho) {
	
	switch (vizinho) {
		
		case dir_up:
		case dir_down:
			return mapa[p->x][posicaoVizinho(p, vizinho)];
			
		case dir_left:
		case dir_right:
			return mapa[posicaoVizinho(p, vizinho)][p->y];
			
		case dir_inercian:
			return mapa[p->x][p->y];
			
	}

}

void setVizinho(point *p, char vizinho) {
	mapa[p->x][p->y] = vizinho;
}

void animacao(dir direcao)
{
	
	if (ciclo == 1) {

		switch(direcao)	{
			case dir_up:
				pacman.pic = pH_pacman.up;
				break;
				
			case dir_down:
				pacman.pic = pH_pacman.down;
				break;
				
			case dir_left:
				pacman.pic = pH_pacman.left;
				break;
				
			case dir_right:
				pacman.pic = pH_pacman.right;
				break;
		}
		
	}
	else pacman.pic = numFigPacmanClosed;
	
	ciclo *= -1;
	
}

void defineScoreText() {
	
	int	 i, temp;
	char t;
	
	strcpy(scoreText, "Score: ");
	i = 7;
	
	/*
		quebra cada valor absoluto do score em um 
		caracter
	*/
	temp = score;
	while(temp>=10)
	{
		scoreText[i] = (temp % 10) + 48;
		temp = temp/10;
		i++;
	}
	scoreText[i] = temp + 48;
	
	/*
		como a quebra é feita inversamente ao sentido
		de leitura do valor, corrige a apresentação no label
	*/
	for(int a = 0; a < ((i + 1) - 7) / 2; a++) {
		t = scoreText[7+a];
		scoreText[7+a] = scoreText[i-a];
		scoreText[i-a] = t;
	}
	
}

dir intToDir(int i) {
	switch (i) {
		case 1:
			return dir_up;
		case 2:
			return dir_right;
		case 3:
			return dir_down;
		case 4:
			return dir_left;
	}
}

bool validVizinho(int vizinho) {
	return (vizinho != BLOCK);
}

bool checkGhost(point *p) {
	
	int count = 0;
	
	for (int i = 0; i < GHOST_BOUND; i++)
		if (samePoint(&ghost[i].position, p))
			count++;
	
	return count > 0;
	
}

dir randomDirection(point *p, point *q) {
	
	dir	  r;
	point t;
	int   i = 0;
	bool  P;
	bool  Q;
	bool  R;
	
	do {
		
		r = intToDir(rand()%4+1);
		t = getPoint(p, r);
		
		i++;
		
		P = i < 4;
		Q = validVizinho(getVizinho(p, r));
		R = samePoint(&t, q);
		
	} while (!( (P && Q && !R) ||
		        (!P && Q && R) || 
				(!P && Q && !R)
			  )
			);
	
	t = getPoint(p, r);
	if (checkGhost(&t))
		r = dir_inercian;
	
	return r;
	
}

dir smartDirection(point *p, point *q) {
	
	dir   r;
	point t;
	int	  i = 0;
	
	/*
		avalia se a diferença em x é menor que a diferença em y;
		caso seja, move em x.
		se um dos eixos for igual, move no outro eixo.
	*/
	
	if (p->y < pacman.position.y) {
		
		if (validVizinho(getVizinho(p, dir_down))) {
			
			t = getPoint(p, dir_down);
			
			if (checkGhost(&t))
				r = dir_inercian;
			else
				r = dir_down;
			
		}
		else
			r = randomDirection(p, q);
		
	} else if (p->y > pacman.position.y) {
		
		if (validVizinho(getVizinho(p, dir_up))) {
			
			t = getPoint(p, dir_up);
			
			if (checkGhost(&t))
				r = dir_inercian;
			else
				r = dir_up;
			
		}
		else
			r = randomDirection(p, q);
		
	} else if (p->x < pacman.position.x) {
		
		if (validVizinho(getVizinho(p, dir_right))) {
			
			t = getPoint(p, dir_right);
			
			if (checkGhost(&t))
				r = dir_inercian;
			else
				r = dir_right;
			
		}
		else
			r = randomDirection(p, q);
		
	} else if (p->x > pacman.position.x) {
		
		if (validVizinho(getVizinho(p, dir_left))) {
			
			t = getPoint(p, dir_left);
			
			if (checkGhost(&t))
				r = dir_inercian;
			else
				r = dir_left;
			
		} else
			r = randomDirection(p, q);
		
	}
	
	t = getPoint(p, r);
	
	while (samePoint(&t, q) && i < 4) {
		
		r = randomDirection(p, q);
		t = getPoint(p, r);
		
		i++;
		
	}
	
	return r;
	
}

point getPoint(point *p, dir d) {
	
	point r;
	
	r = *p;
	
	switch (d) {
		
		case dir_up:
		case dir_down:
			r.y = posicaoVizinho(p, d);
			break;
			
		case dir_left:
		case dir_right:
			r.x = posicaoVizinho(p, d);
			break;
			
	}
	
	return r;
	
}

bool samePoint(point *p, point *q) {
	return p->x == q->x && p->y == q->y;
}

void finishWin() {
	
	numFigFinish = carregaFiguraDeArquivo("Resources\\pictures\\finishWin.png");
	finished = true;
	
}

void finishLose() {
	
	numFigFinish = carregaFiguraDeArquivo("Resources\\pictures\\finishLose.png");
	finished = true;
	
}
