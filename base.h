
/*-------------------------------------------------------------------

	Este arquivo descreve funcoes que podem ser usadas para
	criacao de jogos com elementos graficos. Essas funcoes executam
	chamadas a servicos da biblioteca Clanlib.

	Programador: Vladimir Oliveira Di Iorio
	Data: 02/06/2005

-------------------------------------------------------------------*/


#ifndef __BaseParaJogo_h
#define __BaseParaJogo_h
#define W_WIDTH 600		// largura do formulario principal
#define W_HEIGHT 600	// altura do formulario principal


/*-------------------------------------------------------------------

	Um projeto que utilizar a interface para Clanlib construida
	em "BaseParaJogo" nao deve definir uma funcao "main", pois ela
	ja esta definida. Mas deve OBRIGATORIAMENTE definir algumas funcoes
	especificas, em algum ponto do seu codigo.
	
	Os cabecalhos de funcoes a seguir sao divididos em 2 grupos.
	O primeiro grupo eh formado por funcoes que devem ser definidas
	OBRIGATORIAMENTE PELA APLICACAO CLIENTE, ou seja, por um programador
	que usar A interface "BaseParaJogo".
	O segundo grupo eh formado por funcoes cujo codigo reside no arquivo
	"BaseParaJogo.cpp" e podem ser usadas por aplicacoes cliente.

-------------------------------------------------------------------*/


/*-------------------------------------------------------------------

	PRIMEIRO GRUPO:
	FUNCOES QUE DEVEM SER DEFINIDAS OBRIGATORIAMENTE
	PELA APLICACAO CLIENTE.

-------------------------------------------------------------------*/


/*
Esta funcao eh chamada apenas uma vez pela aplicacao, logo apos
a criacao da janela principal.
Coloque aqui inicializacoes do seu programa, incluindo a definicao
de subjanelas internas para a aplicacao, carregamento de figuras
a partir de arquivos etc.
*/
void iniciar();

/*
Esta funcao eh chamada continuamente pela aplicacao, ate que
o usuario pressione a tecla "ESC".
Coloque aqui codigo para atualizar a janela, especialmente
codigo para desenhar figuras que foram previamente carregadas.
A aplicacao "limpa" a tela e chama a funcao "executar", facilitando
a producao de animacao.
*/
void executar();

/*
Esta funcao eh chamada pela aplicacao quando alguma tecla for
pressionada ou liberada.
O primeiro parametro recebido eh o tipo do evento, que pode ser
TECLA_FOI_PRESSIONADA ou TECLA_FOI_LIBERADA.
O segundo parametro eh o codigo da tecla associada ao evento
(ver codigos de teclas mais abaixo, neste mesmo arquivo).
*/
void eventoTeclado(int tipoEvento, int tecla);

/*
Esta funcao eh chamada pela aplicacao quando um botao do mouse
for pressionado ou liberado.
O primeiro parametro recebido eh o tipo do evento, que pode ser
BOTAO_FOI_PRESSIONADO ou BOTAO_FOI_LIBERADO.
O segundo parametro eh o codigo do botao associada ao evento,
que pode ser BOTAO_ESQUERDO ou BOTAO_DIREITO.
O terceiro e quarto parametro definem a posicao do cursor quando
o evento ocorreu.
*/
void eventoMouse(int tipoEvento, int botao, int x, int y);


/*-------------------------------------------------------------------

	SEGUNDO GRUPO:
	FUNCOES QUE PODEM SER UTILIZADAS NA APLICACAO CLIENTE.
-------------------------------------------------------------------*/


/*
Redefine a janela principal da aplicacao.
Podem ser alterados: o titulo da janela, a posicao (x,y),
a largura e a altura da janela.
*/
void redefineJanelaPrincipal(const char * titulo, int x, int y,
														 int largura, int altura);

/*
Cria uma subjanela para a aplicacao, representada por uma janela
flutuante, interna aa janela da aplicacao.
Devem ser definidos: o titulo da subjanela, a posicao (x,y),
a largura e a altura da subjanela.
Adicionalmente, pode ser definido um parametro "nuncaFecha" que,
se true, a janela nunca podera ser fechada.
Esta funcao retorna um numero inteiro que identifica unicamente
a subjanela criada. Esse numero podera ser usado em outras funcoes
que precisam de identificar uma subjanela.
Por exemplo, para inserir um botao em uma subjanela, eh preciso
fornecer o numero da subjanela onde quer se inserir o botao.
*/
int criaSubjanela (const char * titulo, int x, int y,
									 int largura, int altura, bool nuncaFecha = false);

/*
Modifica uma subjanela.
Podem ser alterados: o titulo da subjanela, a posicao (x,y),
a largura e a altura da subjanela.
O primeiro parametro eh um numero inteiro que identifica
unicamente a subjanela a ser modificado.
*/
void redefineSubjanela (int numSubjanela, const char * titulo,
												int x, int y, int largura, int altura);

/*
Torna uma subjanela visivel ou invisivel.
Devem ser fornecidos um numero inteiro que identifica
unicamente a subjanela e um parametro booleano, onde true significa
visivel e false significa invisivel.
*/
void setVisibilidadeSubjanela (int numSubjanela, bool visivel);

/*
Cria um botao em uma subjanela.
Devem ser especificados:
- um numero inteiro que identifica unicamente a subjanela;
- o texto do botao, alem da posicao (x,y) dentro da subjanela, sua
largura e altura;
- o nome de uma funcao que sera executada quando o botao for pressionado
(esse funcao nao deve receber paramentros nem retornar nenhum valor).
Esta funcao retorna um numero inteiro que identifica unicamente o botao
criado.
*/
int criaBotao (int numSubjanela, const char * texto, int x, int y,
							 int largura, int altura, void func());

/*
Modifica um botao.
Podem ser alterados: o texto do botao, a posicao (x,y),
a largura e a altura.
O primeiro parametro eh um numero inteiro que identifica
unicamente o botao a ser modificado.
*/
void redefineBotao (int numBotao, const char * texto,
										int x, int y, int largura, int altura);

/*
Cria um rotulo (texto) em uma subjanela.
Devem ser especificados:
- um numero inteiro que identifica unicamente a subjanela;
- o texto do rotulo, alem da posicao (x,y) dentro da subjanela, sua
largura e altura.
Esta funcao retorna um numero inteiro que identifica unicamente o rotulo
criado.
*/
int criaRotulo (int numSubjanela, const char * texto, int x, int y,
								int largura, int altura);

/*
Modifica um rotulo.
Podem ser alterados: o texto do rotulo, a posicao (x,y),
a largura e a altura.
O primeiro parametro eh um numero inteiro que identifica
unicamente o rotulo a ser modificado.
*/
void redefineRotulo (int numRotulo, const char *texto,
										 int x, int y, int largura, int altura);

/*
Cria uma caixa de edicao em uma subjanela.
Devem ser especificados:
- um numero inteiro que identifica unicamente a subjanela;
- o texto inicial da caixa de edicao, alem da posicao (x,y) dentro
da subjanela, sua largura e altura.
Esta funcao retorna um numero inteiro que identifica unicamente
a caixa de edicao criada.
*/
int criaCaixaEdicao (int numSubjanela, const char *texto,
										 int x, int y, int largura, int altura);

/*
Modifica uma caixa de edicao.
Podem ser alterados: o texto da caixa de edicao, a posicao (x,y),
a largura e a altura.
O primeiro parametro eh um numero inteiro que identifica
unicamente a caixa de edicao a ser modificada.
*/
void redefineCaixaEdicao (int numCaixaEdicao, const char *texto, 
													int x, int y, int largura, int altura);

/*
Obtem o texto atual de uma caixa de edicao (que pode ter sido
alterado pelo usuario).
O parametro esperado eh um numero inteiro que identifica
unicamente a caixa de edicao verificada.
*/
const char * obtemTextoCaixaEdicao (int numCaixaEdicao);

/*
Carrega uma figura de um arquivo.
Alguns formatos permitidos sao JPG e PNG.
Esta funcao retorna um numero inteiro que identifica unicamente a figura
carregada.
*/
int carregaFiguraDeArquivo (const char * nomeArq);

/*
Desenha uma figura em uma posicao (x,y) da janela da aplicacao.
O primeiro parametro eh um numero inteiro que identifica
unicamente a fugura a ser desenhada.
*/
void desenhaFigura (int numFig, int x, int y);

/*
As constantes a seguir servem para identificar se um botao de mouse
foi pressionado ou liberado, na funcao de tratamento de evento
de mouse.
*/

const int BOTAO_FOI_PRESSIONADO = 0;
const int BOTAO_FOI_LIBERADO = 1;

/*
As constantes a seguir podem ser usadas para identificar qual botao
do mouse foi pressionado ou liberado.
*/

const int BOTAO_ESQUERDO = 0;
const int BOTAO_DIREITO = 1;

/*
Habilita / desabilita o evento de mouse em subjanelas.
O default é desabilitado.
*/
void habilitaMouseSubjanela (bool b);


/*
As constantes a seguir servem para identificar se uma tecla
foi pressionada ou liberada, na funcao de tratamento de evento
de teclado.
*/

const int TECLA_FOI_PRESSIONADA = 0;
const int TECLA_FOI_LIBERADA = 1;

/*
As constantes a seguir podem ser usadas para identificar qual tecla
foi pressionada ou liberada.
*/

#define TECLA_ESCAPE         0x1B
#define TECLA_CONVERT        0x1C
#define TECLA_NONCONVERT     0x1D
#define TECLA_ACCEPT         0x1E
#define TECLA_MODECHANGE     0x1F
#define TECLA_SPACE          0x20
#define TECLA_PRIOR          0x21
#define TECLA_NEXT           0x22
#define TECLA_END            0x23
#define TECLA_HOME           0x24
#define TECLA_LEFT           0x25
#define TECLA_UP             0x26
#define TECLA_RIGHT          0x27
#define TECLA_DOWN           0x28
#define TECLA_SELECT         0x29
#define TECLA_PRINT          0x2A
#define TECLA_EXECUTE        0x2B
#define TECLA_SNAPSHOT       0x2C
#define TECLA_INSERT         0x2D
#define TECLA_DELETE         0x2E
#define TECLA_HELP           0x2F
#define TECLA_0 '0'
#define TECLA_1 '1'
#define TECLA_2 '2'
#define TECLA_3 '3'
#define TECLA_4 '4'
#define TECLA_5 '5'
#define TECLA_6 '6'
#define TECLA_7 '7'
#define TECLA_8 '8'
#define TECLA_9 '9'
#define TECLA_A 'A'
#define TECLA_B 'B'
#define TECLA_C 'C'
#define TECLA_D 'D'
#define TECLA_E 'E'
#define TECLA_F 'F'
#define TECLA_G 'G'
#define TECLA_H 'H'
#define TECLA_I 'I'
#define TECLA_J 'J'
#define TECLA_K 'K'
#define TECLA_L 'L'
#define TECLA_M 'M'
#define TECLA_N 'N'
#define TECLA_O 'O'
#define TECLA_P 'P'
#define TECLA_Q 'Q'
#define TECLA_R 'R'
#define TECLA_S 'S'
#define TECLA_T 'T'
#define TECLA_U 'U'
#define TECLA_V 'V'
#define TECLA_W 'W'
#define TECLA_X 'X'
#define TECLA_Y 'Y'
#define TECLA_Z 'Z'


#endif
