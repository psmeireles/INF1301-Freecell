#if !defined( EspacosExtras_MOD )
#define EspacosExtras_MOD

/***************************************************************************
*
*  $MCD M�dulo de defini��o: ESPEXT Espa�os Extras
*
*  Arquivo gerado:              Espa�osExtras.h
*  Letras identificadoras:      ESPEXT
*
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: rtn
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1		  rtn	14/04/2017	In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa os Espa�os Extras do jogo Freecell.
*     Os Espa�os Extras s�o os espa�os onde podem ser armazenadas no m�ximo 4 cartas quaisquer, sendo uma em cada espa�o. 
*     Normalmente, essas cartas est�o impedindo o alcance de outras cartas e por isso precisam ser movidas.
*	  O tabuleiro do jogo tem 4 espa�os extras.
***************************************************************************/

#include "Cartas.h"
#include "LISTA.H"

/* Controle de escopo do arquivo de defini��o */
#if defined( EspacosExtras_MOD )
	#define EspacosExtras_EXT
#else
	#define EspacosExtras_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um conjunto de espa�os extras */

typedef struct ESPEXT_tagEspExt * ESPEXT_tppEspExt;

/***********************************************************************
*
*  $TC Tipo de dados: ESPEXT Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de espa�os extras
*
***********************************************************************/

typedef enum {

	ESPEXT_CondRetOK,
	/* Concluiu corretamente */

	ESPEXT_CondRetListaVazia,
	/* A lista n�o cont�m elementos */

	ESPEXT_CondRetListaNaoExiste,
	/* A lista n�o existe */

	ESPEXT_CondRetNaoAchou,
	/* N�o encontrou o valor procurado */

	ESPEXT_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento de lista */
	
	ESPEXT_CondRetImpossRetirarCarta,
	/* A carta especificada n�o pode ser removida */

	ESPEXT_CondRetImpossInserirCarta,
	/* A carta especificada n�o pode ser inserida */

	ESPEXT_CondRetImpossivelImprimir,
	/* Impossivel imprimir espa�os extras */

	ESPEXT_CondRetEspExtNaoExiste
	/* pEspExt � NULL */

} ESPEXT_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: ESPEXT  Criar os espa�os extras
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o primeiro espa�o extra.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem os espa�os extras.
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK				- se tiver criado o espa�o extra com sucesso.
*	  ESPEXT_CondRetFaltouMemoria  - se n�o tiver conseguido alocar mem�ria para 
*									 o espa�o extra.
*
***********************************************************************/
	
	ESPEXT_tpCondRet ESPEXT_CriarEspExt( ESPEXT_tppEspExt *pEspExt ) ;


/***********************************************************************
*
*  $FC Fun��o: ESPEXT  Destruir espa�os extras
*
*  $ED Descri��o da fun��o
*     Destr�i os espa�os extras fornecidos.
*     O par�metro ponteiro para o espa�o n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*
*  $EP Par�metros
*     pEspExt - ponteiro para os espa�os extras
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_DestruirEspExt( ESPEXT_tppEspExt pEspExt ) ;



/***********************************************************************
*
*  $FC Fun��o: ESPEXT  Inserir carta em espa�o extra
*
*  $ED Descri��o da fun��o
*     Insere novo elemento no primeiro espa�o extra vazio.
*     Caso os espa�os estejam vazios, insere o primeiro elemento da lista.
*	  S� podem ser inseridos at� 4 elementos.
*
*  $EP Par�metros
*     pEspExt	  - ponteiro para os espa�os extras
*     pListaCarta - ponteiro para a lista de carta a ser inserida
*				    N�o pode ser NULL
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK				   - se inseriu corretamente
*     ESPEXT_CondRetListaVazia		   - se a lista com a carta a ser inserida est� vazia
*	  ESPEXT_CondRetImpossInserirCarta - se n�o p�de inserir
*	  ESPEXT_CondRetListaNaoExiste	   - se alguma lista for NULL
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_InserirCarta(ESPEXT_tppEspExt pEspExt,  LIS_tppLista pListaCarta);

/***********************************************************************
*
*  $FC Fun��o: ESPEXT  Remover elemento dos espa�os extras
*
*  $ED Descri��o da fun��o
*     Remove o elemento especificado dos espa�os extras. 
*	  A carta removida vai ser retornada em uma lista.
*
*  $EP Par�metros
*	  pEspExt - espa�os extras
*     pCarta - carta a ser retirada dos espa�os extras
*	  pListaRemovida - lista que receber� a carta removida
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK						 - se removeu a carta com sucesso
*	  ESPEXT_CondRetFaltouMemoria			 - se faltou mem�ria ao criar a lista para a carta
*	  ESPEXT_CondRetListaVazia				 - se os espa�os extras est�o vazios
*	  ESPEXT_CondRetNaoAchou				 - se a carta a ser retirada n�o est� nos espa�os extras
*	  ESPEXT_CondRetListaNaoExiste			 - se a lista do baralho n�o existe
*	  ESPEXT_CondRetImpossRetirarCarta		 - se o baralho ou a carta n�o existem
*
***********************************************************************/

	ESPEXT_tpCondRet  ESPEXT_RemoverCarta(ESPEXT_tppEspExt pEspExt,
										  CAR_tppCarta pCarta,
										  LIS_tppLista *pListaRemovida);


/***********************************************************************
*
*  $FC Fun��o: ESPEXT  Imprimir espa�os extras
*
*  $ED Descri��o da fun��o
*     Imprime na tela as cartas nos espa�os extras. Caso um espa�o esteja vazio,
*	  ser� impresso '0'.
*
*  $EP Par�metros
*     pEspExt - ponteiro para espa�os extras a serem impressos
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK					     - se imprimiu com sucesso
*	  ESPEXT_CondRetImpossivelImprimir		 - se falhou ao imprimir alguma carta
*	  ESPEXT_CondRetEspExtNaoExiste
*	  ESPEXT_CondRetListaNaoExiste
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_ImprimeEspExt(ESPEXT_tppEspExt pEspExt) ;


/***********************************************************************
*
*  $FC Fun��o: ESPEXT  &Obter lista de cartas
*
*  $ED Descri��o da fun��o
*     Recebe uma espa�o extra e guarda em um endere�o recebido a lista de cartas
*     dos espa�os.
*
*  $EP Par�metros
*     pEspExt  - ponteiro para a sequ�ncia vis�vel
*	  pLista   - endere�o que vai receber a lista de cartas
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK	
*	  ESPEXT_CondRetEspExtNaoExiste
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_ObterListaCartas( ESPEXT_tppEspExt pEspExt, LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: ESPEXT  Obter numero de espa�os espa�os extras vazios
*
*  $ED Descri��o da fun��o
*     Obt�m n�mero de espa�os extras vazios.
*
*  $EP Par�metros
*     pEspExt   - espa�os extras
*     qtdVazios - endere�o da vari�vel que vai receber a quantidade de espa�os
*				  extras vazios.
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK
*	  ESPEXT_CondRetEspExtNaoExiste
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_ObterNumEspExtVazios( ESPEXT_tppEspExt pEspExt, int *qtdVazios ) ;

#undef EspacosExtras_EXT

/********** Fim do m�dulo de defini��o: ESPEXT  Espa�os extras **********/
#endif