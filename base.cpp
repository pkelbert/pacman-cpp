
/*-------------------------------------------------------------------

	Este arquivo contem a implementacao das funcoes
	cujos cabecalhos sao descritos no arquivo "BaseParaJogo.h".
	Consulte o arquivo "BaseParaJogo.h" para informacoes sobre
	utilizacao dessas funcoes.

	Programador: Vladimir Oliveira Di Iorio
	Data: 02/06/2005

-------------------------------------------------------------------*/

#include <ClanLib/core.h>			//Necessaria em qualquer programa que utiliza a ClanLib
#include <ClanLib/display.h>		//Necessaria para utilizacao de objetos graficos
#include <ClanLib/gl.h>				//Necessaria para utilizacao da OpenGL (biblioteca utilizada pela ClanLib para acesso a hardware)
#include <ClanLib/application.h>	//Necessaria para criacao de uma crossplataform application framework
#include <ClanLib/gui.h>			//Necessaria para criacao da interface do usuario
#include <ClanLib/guistylesilver.h>	//Necessaria para exibicao da interface no estilo padrao

#include <time.h>					//Necessaria para utilizacao da funcao time()
#include <fstream>					//Necessario para leitura de dados no disco rigido

#include <iostream>
using std::cout;
using std::endl;

#include "base.h"

#define EXEC_TIMEOUT	150

// para controlar fechamento da janela
bool fechar;

/*
	Classe principal de controle do jogo
*/
class BaseParaJogo : public CL_ClanApplication {

public:

		BaseParaJogo();						//Construtor
		~BaseParaJogo();					//Destruidor

		virtual int main(int, char **);		//Funcao main redefinida

		void handleKeyDown(const CL_InputEvent &key);
		void handleKeyUp(const CL_InputEvent &key);
		void handleMouseDown(const CL_InputEvent &key);
		void handleMouseUp(const CL_InputEvent &key);
		void handleMouseDC(const CL_InputEvent &key);

		void run();							//Funcao para execucao do jogo

		//Variaveis//
		CL_DisplayWindow *gameWindow; //Objeto para obter acesso a janela da aplicacao
		CL_GUIManager *guiManager;			//Gerenciador da GUI visivel a todo arquivo
		CL_Window *janelaGUI;				//Ponteiro para a janela do GUI visivel a todo o arquivo

	void onWindowClose() {
		fechar = true;
	}


} game;	//Cria uma instancia chamada game


void redefineJanelaPrincipal(const char * titulo, int x, int y,
										int largura, int altura) {
	CL_DisplayWindow * w = game.gameWindow;
	w->set_title(titulo);
	w->set_position(x, y);
	w->set_size(largura, altura);
}


const int MAX_SUBJANELAS = 10;
CL_Window * tabSubjanelas[MAX_SUBJANELAS];
boolean nuncaFechaSubjanelas[MAX_SUBJANELAS];
int currSubjanela = 0;

int criaSubjanela (const char * titulo, int x, int y,
									 int largura, int altura, bool nuncaFecha) {
	if (currSubjanela >= MAX_SUBJANELAS) {
		cout << "ERRO - Atingiu o numero maximo de Subjanelas!" << endl;
		return -1;
	}
	CL_Window * windowGUI = new CL_Window(CL_Rect(x, y, x+largura, y+altura),
		titulo, game.guiManager);
	tabSubjanelas[currSubjanela] = windowGUI;
	nuncaFechaSubjanelas[currSubjanela] = nuncaFecha;
	return currSubjanela++;
}

void redefineSubjanela (int numSubjanela, const char * titulo, int x, int y,
									 int largura, int altura) {
	if (numSubjanela < 0 || numSubjanela >= currSubjanela) {
		cout << "ERRO - numero de Subjanela invalido!" << endl;
		return;
	}
	CL_Window * w = tabSubjanelas[numSubjanela];
	w->set_title(titulo);
	w->set_position(x, y);
	w->set_width(largura);
	w->set_height(altura);
}

void setVisibilidadeSubjanela (int numSubjanela, bool visivel) {
	if (numSubjanela < 0 || numSubjanela >= currSubjanela) {
		cout << "ERRO - numero de Subjanela invalido!" << endl;
		return;
	}
	CL_Window * w = tabSubjanelas[numSubjanela];
	w->show(visivel);
}



const int MAX_BUTTONS = 50;
CL_Slot tabSlots[MAX_BUTTONS];
int currButton = 0;
CL_Button * tabButtons[MAX_BUTTONS];

int criaBotao (int numSubjanela, const char *texto, int x, int y,
							 int largura, int altura, void func()) {
	if (currButton >= MAX_BUTTONS) {
		cout << "ERRO - Atingiu numero maximo de botoes!" << endl;
		return -1;
	}
	if (numSubjanela < 0 || numSubjanela >= currSubjanela) {
		cout << "ERRO - numero de subjanela invalido!" << endl;
		return -1;
	}
	CL_Window * w = tabSubjanelas[numSubjanela];
	CL_Button * novoBotao = new CL_Button(texto, w);
	novoBotao->set_position(x,y);
	novoBotao->set_width(largura);
	novoBotao->set_height(altura);
	tabSlots[currButton] = novoBotao->sig_clicked().connect(func);
	tabButtons[currButton] = novoBotao;
	return currButton++;
}

void redefineBotao (int numBotao, const char * texto, int x, int y,
												int largura, int altura) {
	if (numBotao < 0 || numBotao >= MAX_BUTTONS) {
		cout << "ERRO - numero de botao invalido!" << endl;
		return;
	}
	CL_Button * botao = tabButtons[numBotao];
	botao->set_position(x,y);
	botao->set_width(largura);
	botao->set_height(altura);
	botao->set_text(texto);
}


const int MAX_LABELS = 100;
CL_Label * tabLabels[MAX_LABELS];
int currLabel = 0;

int criaRotulo (int numSubjanela, const char *texto,
								int x, int y, int largura, int altura) {
	if (currLabel >= MAX_LABELS) {
		cout << "ERRO - Atingiu numero maximo de rotulos!" << endl;
		return -1;
	}
	if (numSubjanela < 0 || numSubjanela >= currSubjanela) {
		cout << "ERRO - numero de subjanela invalido!" << endl;
		return -1;
	}
	CL_Window * w = tabSubjanelas[numSubjanela];
	CL_Label * novoRotulo = new CL_Label(w);
	novoRotulo->set_position(x,y);
	novoRotulo->set_width(largura);
	novoRotulo->set_height(altura);
	novoRotulo->set_text(texto);
	tabLabels[currLabel] = novoRotulo;
	return currLabel++;
}

void redefineRotulo (int numRotulo, const char *texto, int x, int y, int largura, int altura) {
	if (numRotulo < 0 || numRotulo >= MAX_LABELS) {
		cout << "ERRO - numero de rotulo invalido!" << endl;
		return;
	}
	CL_Label * lab = tabLabels[numRotulo];
	lab->set_position(x,y);
	lab->set_width(largura);
	lab->set_height(altura);
	lab->set_text(texto);
}


const int MAX_EDITBOXES = 100;
CL_InputBox * tabInputBoxes[MAX_EDITBOXES];
int currInputBox = 0;

int criaCaixaEdicao (int numSubjanela, const char *texto,
										 int x, int y, int largura, int altura) {
	if (currInputBox >= MAX_EDITBOXES) {
		cout << "ERRO - Atingiu numero maximo de caixas de edicao!" << endl;
		return -1;
	}
	if (numSubjanela < 0 || numSubjanela >= currSubjanela) {
		cout << "ERRO - numero de subjanela invalido!" << endl;
		return -1;
	}
	CL_Window * w = tabSubjanelas[numSubjanela];
	CL_InputBox * ip = new CL_InputBox(CL_Rect(x, y, x+largura, y+altura), w);
	ip->set_width(largura);
	ip->set_height(altura);
	ip->set_text(texto);
	tabInputBoxes[currInputBox] = ip;
	return currInputBox++;
}

void redefineCaixaEdicao (int numCaixaEdicao, const char *texto, 
													int x, int y, int largura, int altura) {
	if (numCaixaEdicao < 0 || numCaixaEdicao >= MAX_EDITBOXES) {
		cout << "ERRO - numero de caixa de edicao invalido!" << endl;
		return;
	}
	CL_InputBox * ip = tabInputBoxes[numCaixaEdicao];
	ip->set_position(x,y);
	ip->set_width(largura);
	ip->set_height(altura);
	ip->set_text(texto);
}

const char * obtemTextoCaixaEdicao (int numCaixaEdicao) {
	if (numCaixaEdicao < 0 || numCaixaEdicao >= MAX_EDITBOXES) {
		cout << "ERRO - numero de caixa de edicao invalido!" << endl;
		return NULL;
	}
	CL_InputBox * ip = tabInputBoxes[numCaixaEdicao];
	return ip->get_text().c_str();
}

const int MAX_SURFACES = 100;
CL_Surface * tabSurfaces[MAX_SURFACES];
int currSurface;

int carregaFiguraDeArquivo (const char * nomeArq) {
	if (currSurface >= MAX_SURFACES) {
		cout << "ERRO - Atingiu numero maximo de figuras carregadas!" << endl;
		return -1;
	}
	tabSurfaces[currSurface] = new CL_Surface(nomeArq);
	return currSurface++;
}

void desenhaFigura (int numFig, int x, int y) {
	if (numFig < 0 || numFig >= currSurface) {
		cout << "ERRO - Numero de figura invalido!" << endl;
		return;
	}
	tabSurfaces[numFig]->draw(x, y);
}



BaseParaJogo::BaseParaJogo() {
}


BaseParaJogo::~BaseParaJogo() {
}



void BaseParaJogo::handleKeyDown(const CL_InputEvent &key) {
	eventoTeclado(TECLA_FOI_PRESSIONADA, key.id);
}

void BaseParaJogo::handleKeyUp(const CL_InputEvent &key) {
	eventoTeclado(TECLA_FOI_LIBERADA, key.id);
}


bool mouseEmSubjanela = false;
bool prendeBotaoEsquerdo = false;
bool prendeBotaoDireito = false;

void habilitaMouseSubjanela (bool b) {
	mouseEmSubjanela = b;
}

void BaseParaJogo::handleMouseDown(const CL_InputEvent &key) {
	if (!mouseEmSubjanela) {
		for(int i = 0; i < currSubjanela; ++i) {
			CL_Window * w = tabSubjanelas[i];
			if (! w->is_visible())
				continue;
			CL_Rect r = w->get_position();
			int a = r.left, b = r.right, c = r.top, d = r.bottom;
			if (
				key.mouse_pos.x >= a &&
				key.mouse_pos.x <= b &&
				key.mouse_pos.y >= c &&
				key.mouse_pos.y <= d) {
					if (key.id == BOTAO_ESQUERDO) prendeBotaoEsquerdo = true;
					else if (key.id == BOTAO_DIREITO) prendeBotaoDireito = true;
					return;
			}
		}
	}
	eventoMouse(BOTAO_FOI_PRESSIONADO, key.id, key.mouse_pos.x, key.mouse_pos.y);
}

void BaseParaJogo::handleMouseUp(const CL_InputEvent &key) {
	if (!mouseEmSubjanela && key.id == BOTAO_ESQUERDO && prendeBotaoEsquerdo)
		prendeBotaoEsquerdo = false;
	else if (!mouseEmSubjanela && key.id == BOTAO_DIREITO && prendeBotaoDireito)
		 prendeBotaoDireito = false;
	else
		eventoMouse(BOTAO_FOI_LIBERADO, key.id, key.mouse_pos.x, key.mouse_pos.y);
}

void BaseParaJogo::handleMouseDC(const CL_InputEvent &key) {
	int i = 0;
}



//Redefinicao da funcao main
int BaseParaJogo::main(int, char **) 
{
	
	//Cria uma janela console para saida de texto
	CL_ConsoleWindow console("Main Console");

	//Redireciona a saida para o console
	console.redirect_stdio();

	//Como a chamada da biblioteca podera gerar excecoes,
	//tais comandos deverao ser colocados em blocos try/catch
	try	
	{

		/////////////////////////////
		//Inicializacao da ClanLib //
		/////////////////////////////

		//Funcoes de inicializacao da ClanLib
		//Tais inicializacoes sao necessarias para utilizacao da biblioteca
		//CL_SetupCore::init() deve ser o primeiro comando
		CL_SetupCore::init();
		CL_SetupDisplay::init();
		CL_SetupGL::init();
		CL_SetupGUI::init();

		/////////////////////////////////////////
		//Definindo a janela principal do jogo//
		/////////////////////////////////////////

		//Criando uma tela para visualizacao do jogo
		CL_DisplayWindow window("Teste", W_WIDTH, W_HEIGHT, false, true);
		gameWindow = &window;

		// Cria um gerenciador de recursos para a interface grafica do usuario usando o estilo padrao
		CL_ResourceManager guiResources("Resources/GUIStyleSilver/gui.xml");

		//Cria um gerenciador de estilos
		CL_StyleManager_Silver guiStyle(&guiResources);

		//Cria um gerenciador de interface grafica
		guiManager = new CL_GUIManager(&guiStyle);

		iniciar();

		/////////////////////////////
		//Gerenciamento de Eventos//
		/////////////////////////////

		//Conecta a captura de pressionamento de teclas a funcao handleKeyDown
		CL_Slot keyPress = CL_Keyboard::sig_key_down().connect(this, &BaseParaJogo::handleKeyDown);

		//Conecta a captura de liberacao de teclas a funcao handleKeyUp
		CL_Slot keyRelease = CL_Keyboard::sig_key_up().connect(this, &BaseParaJogo::handleKeyUp);

		//Conecta a captura de pressionamento de botao mouse a funcao handleMouseDown
		CL_Slot mouseDown = CL_Mouse::sig_key_down().connect(this, &BaseParaJogo::handleMouseDown);

		//Conecta a captura de liberacao de botao de mouse a funcao handleMouseUp
		CL_Slot mouseUp = CL_Mouse::sig_key_up().connect(this, &BaseParaJogo::handleMouseUp);

		//Conecta a captura de duplo clique de botao mouse a funcao handleMouseDown
		CL_Slot mouseDC = CL_Mouse::sig_key_dblclk().connect(this, &BaseParaJogo::handleMouseDown);

		//Conecta o sinal de fechamento a funcao onWindowClose
		CL_Slot slotQuit = window.sig_window_close().connect(this, &BaseParaJogo::onWindowClose);

		/////////////////////////////
		//Execucao do jogo		   //
		/////////////////////////////

		run();					//Executa o jogo

		/////////////////////////////
		//Finalizacao da ClanLib //
		/////////////////////////////
		
		//Funcoes de finalizacao da ClanLib
		//Tais finalizacoes sao necessarias para liberacao dos recursos alocados
		//CL_SetupCore::deinit() deve ser o ultimo comando

		CL_SetupGUI::deinit();
		CL_SetupGL::deinit();
		CL_SetupDisplay::deinit();
		CL_SetupCore::deinit();
	} 
	//Qualquer excecao gerada pela ClanLib sera do tipo Cl_Error
	catch (CL_Error err) 
	{
		//Resultado de std::cout somente sera visualizado se houver um console para exibicao de textos
		std::cout << "Ocorreu uma excecao: " << err.message.c_str() << std::endl;

		// Mostra a mensagem de fechamento no console e espera o pressionamento de uma tecla
		console.display_close_message();
	}

	//Destruindo os ponteiros alocados dinamicamente
	delete guiManager;

	return 0;
}


//A funcao run executara o jogo ate que a tecla Escape seja pressionada
void BaseParaJogo::run()  {

	int controlTempo = 0;					//Controle de velocidade de execucao
	
	CL_Display::clear(CL_Color(0, 0, 0));	//Limpa a janela

	fechar = false;

	//Loop que executa o jogo ate o pressionamento da tecla ESC ou fechamento da janela
	while (!fechar && !CL_Keyboard::get_keycode(CL_KEY_ESCAPE))  {

		for (int i = 0; i < currSubjanela; ++i) {
			if (nuncaFechaSubjanelas[i])
				tabSubjanelas[i]->show(true);
		}

		//Executa a atualizacao a cada 10 milisegundos para garantir
		//que o jogo executara na mesma velocidade em qualquer maquina.
		if(CL_System::get_time() > controlTempo + EXEC_TIMEOUT) {

			CL_Display::clear(CL_Color(0, 0, 0));	//Limpa a janela

			executar();

			guiManager->show();							//Atualiza a interface gráfica

			CL_Display::flip();							//Atualiza os buffers de display
			//Obtem o tempo em milissegundos desde o ultimo boot do sistema
			controlTempo = CL_System::get_time();
		}			

		CL_System::sleep(10);		//Permite que o sistema operacional execute outras tarefas
		CL_System::keep_alive();			//Permite que a ClanLib se atualize
	}
}
