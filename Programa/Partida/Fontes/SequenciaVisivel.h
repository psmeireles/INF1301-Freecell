#if !defined( SequenciaVisivel_MOD )
#define SequenciaVisivel_MOD

/***************************************************************************
*
*  $MCD M�dulo de defini��o: SEQVIS Sequ�ncia Vis�vel
*
*  Arquivo gerado:              SequenciaVisivel.h
*  Letras identificadoras:      SEQVIS
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1		  psm	13/abr/2017	In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa uma sequ�ncia vis�vel do jogo Freecell.
*     As sequ�ncias vis�veis s�o as sequ�ncias onde as cartas do jogo s�o inicialmente dispostas.
*	  O tabuleiro do jogo tem 8 sequ�ncias vis�veis.
*	  Uma sequ�ncia vis�vel � estruturada como uma lista de cartas.
***************************************************************************/

#include "Cartas.h"
#include "LISTA.H"

/* Controle de escopo do arquivo de defini��o */

#if defined( SequenciaVisivel_MOD )
	#define SequenciaVisivel_EXT
#else
	#define SequenciaVisivel_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um conjunto de sequ�ncias vis�veis */

	typedef struct SEQVIS_tagSeqVis * SEQVIS_tppSeqVis;

/***********************************************************************
*
*  $TC Tipo de dados: SEQVIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da sequ�ncia vis�vel
*
***********************************************************************/

	typedef enum {

		SEQVIS_CondRetOK,
		/* Concluiu corretamente */

		SEQVIS_CondRetListaVazia,
		/* A lista n�o cont�m elementos */

		SEQVIS_CondRetFimLista,
		/* Foi atingido o fim de lista */

		SEQVIS_CondRetNaoAchou,
		/* N�o encontrou o valor procurado */

		SEQVIS_CondRetFaltouMemoria,
		/* Faltou mem�ria ao tentar criar um elemento de lista */

		SEQVIS_CondRetImpossRetirarCarta,
		/* A carta especificada n�o pode ser removida */

		SEQVIS_CondRetImpossInserirCarta,
		/* A carta especificada n�o pode ser inserida */

		SEQVIS_CondRetListaErrada,
		/* A lista de cartas n�o obedece as restri��es do jogo Free Cell */

		SEQVIS_CondRetImpossivelImprimir,
		/* A carta especificada n�o pode ser impressa */

		SEQVIS_CondRetListaNaoExiste,
		/* pSeqVis->pLinha == NULL */

		SEQVIS_CondRetSeqVisNaoExiste
		/* pSeqVis == NULL */
	

	} SEQVIS_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Criar uma sequ�ncia vis�vel
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada
*
*  $EP Par�metros
*     pSeqVis - endere�o que vai receber a sequ�ncia vis�vel criada
*
*  $FV Valor retornado
*	  SEQVIS_CondRetOK			  - se tiver criado sem problemas
*	  SEQVIS_CondRetFaltouMemoria - se tiver faltado mem�ria
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_CriarSeqVis(SEQVIS_tppSeqVis *pSeqVis);


/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Destruir sequ�ncia vis�vel
*
*  $ED Descri��o da fun��o
*     Destr�i a sequ�ncia vis�vel fornecida.
*     O par�metro ponteiro para a sequ�ncia n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*
*  $EP Par�metros
*     pSeqVis - ponteiro para a sequ�ncia vis�vel
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_DestruirSeqVis(SEQVIS_tppSeqVis pSeqVis);


/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Inserir carta na sequ�ncia vis�vel seguindo a restri��o de naipe e n�mero
*
*  $ED Descri��o da fun��o
*     Insere uma carta, ou bloco de cartas, na �ltima posi��o da sequ�ncia vis�vel.
*     Caso a sequ�ncia esteja vazia, insere a primeira carta da lista.
*	  A inser��o da carta deve seguir os padr�es do jogo Freecell. Ou seja, a carta inserida na sequ�ncia
*	  deve ter naipe de cor diferente e s�mbolo antecessor aos da carta anterior da sequ�ncia.
*	  Essa fun��o ser� usada para movimentar as cartas durante a partida.
*
*  $EP Par�metros
*     pSeqVis	   - ponteiro para a sequ�ncia vis�vel
*     pListaCartas - ponteiro para a cabe�a da lista que cont�m as cartas a serem inseridas
*				     N�o pode ser NULL. Estragada no final.
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK			  - se o elemento inserido retirado sem problemas
*     SEQVIS_CondRetFaltouMemoria - se n�o houve espa�o suficiente na sequ�ncia vis�vel para inserir carta
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_InserirCartaRestr(SEQVIS_tppSeqVis pSeqVis,  LIS_tppLista pListaCartas);


/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Inserir carta na sequ�ncia vis�vel sem a restri��o de naipe e n�mero
*
*  $ED Descri��o da fun��o
*     Insere uma carta na �ltima posi��o da sequ�ncia vis�vel.
*     Caso a sequ�ncia esteja vazia, insere o primeiro elemento da lista.
*	  A inser��o da carta n�o deve seguir os padr�es do jogo Freecell. Ou seja, a carta inserida na sequ�ncia
*	  n�o precisa ter naipe de cor diferente e s�mbolo antecessor aos da carta anterior da sequ�ncia.
*	  Essa fun��o ser� apenas para distribuir as cartas do baralho no in�cio da partida.
*
*  $EP Par�metros
*     pSeqVis	  - ponteiro para a sequ�ncia vis�vel
*     pListaCarta - ponteiro para uma lista contendo a carta a ser inserida
*				    N�o pode ser NULL
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK				   - se a carta foi inserida sem problemas
*     SEQVIS_CondRetImpossInserirCarta - se n�o foi poss�vel inserir a carta
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_InserirCartaSemRestr(SEQVIS_tppSeqVis pSeqVis,  LIS_tppLista pListaCarta);

/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Remover carta da sequ�ncia vis�vel
*
*  $ED Descri��o da fun��o
*     Remove o elemento especificado da sequ�ncia, seguido por todos os elementos ap�s ele. O elemento pode 
*	  estar em qualquer parte da sequ�ncia desde que os elementos da pr�ximas posi��es sigam as condi��es 
*	  impostas pelo jogo freecell. Ou seja, os elementos seguintes devem ter naipe de cor diferente do anterior 
*	  e devem ter s�mbolo antecessor ao do elemento anterior.
*
*  $EP Par�metros
*     pSeqVis		 - ponteiro para a sequ�ncia vis�vel.
*	  pCarta		 - carta a ser retirada
*	  pListaRemovida - lista que vai receber as cartas retiradas
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK				   - se o elemento foi retirado sem problemas
*	  SEQVIS_CondRetNaoAchou		   - se o elemento a ser retirado n�o est� na sequ�ncia vis�vel especificada
*	  SEQVIS_CondRetImpossRetirarCarta - se n�o foi poss�vel retirar a carta
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_RemoverCarta(SEQVIS_tppSeqVis pSeqVis, CAR_tppCarta pCarta, LIS_tppLista *pListaRemovida);


/***********************************************************************
*
*  $FC Fun��o: SEQVIS  &Obter lista de cartas
*
*  $ED Descri��o da fun��o
*     Recebe uma sequ�ncia vis�vel e guarda em um endere�o recebido a lista de cartas
*     da sequ�ncia.
*
*  $EP Par�metros
*     pSeqVis  - ponteiro para a sequ�ncia vis�vel
*	  pLista   - endere�o que vai receber a lista de cartas
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK	- obteve a lista sem problemas
*	  SEQVIS_CondRetSeqVisNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_ObterListaCartas( SEQVIS_tppSeqVis pSeqVis, LIS_tppLista *pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Imprimir sequ�ncia vis�vel
*
*  $ED Descri��o da fun��o
*     Imprime as cartas pertencentes � sequ�ncia vis�vel recebida em ordem.
*
*  $EP Par�metros
*     pSeqVis - ponteiro a sequ�ncia vis�vel.
*
*  $FV Valor retornado
*    SEQVIS_CondRetOK				  - conseguiu imprimir
*	 SEQVIS_CondRetImpossivelImprimir - n�o conseguiu imprimir
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_ImprimeSeqVis(SEQVIS_tppSeqVis pSeqVis);

#undef SequenciasVisiveis_EXT

/********** Fim do m�dulo de defini��o: SEQVIS  Sequ�ncia Vis�vel **********/

#endif