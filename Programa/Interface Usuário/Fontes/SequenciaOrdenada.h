#if !defined( SequenciaOrdenada_MOD )
#define SequenciaOrdenada_MOD

/***************************************************************************
*
*  $MCI M�dulo de implementa��o: SEQORD  Sequ�ncia Ordenada
*
*  Arquivo gerado:              SequenciaOrdenada.c
*  Letras identificadoras:      SEQORD
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: mcc
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       mcc   15/abr/2017 inicio do desenvolvimento
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa uma sequ�ncia ordenada do jogo Freecell.
*     Cada sequ�ncia ordenada come�a inicialmente vazia e corresponde � um 
*     naipe. Deve ser preenchida em ordem crescente com todas as cartas de
*     seu naipe. 
*	  O tabuleiro do jogo tem 4 sequ�ncias ordenadas.
*     Se todas as sequ�ncias ordenadas forem totalmente preenchidas, o 
*     objetivo do jogo � alcan�ado.
***************************************************************************/

#include "Cartas.h"
#include "LISTA.H"

/* Controle de escopo do arquivo de defini��o */

#if defined( SequenciaOrdenada_MOD )
	#define SequenciaOrdenada_EXT
#else
	#define SequenciaOrdenada_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um conjunto de sequ�ncias ordenadas */

	typedef struct SEQORD_tagSeqOrd * SEQORD_tppSeqOrd;

/***********************************************************************
*
*  $TC Tipo de dados: SEQORD Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da sequ�ncia ordenada
*
***********************************************************************/

	
	typedef enum {

		SEQORD_CondRetOK,
		/* Concluiu corretamente */

		SEQORD_CondRetListaVazia,
		/* A lista n�o cont�m elementos */

		SEQORD_CondRetListaNaoCheia,
		/* A lista foi n�o totalmente preenchida */

		SEQORD_CondRetFaltouMemoria,
		/* Faltou mem�ria ao tentar criar um elemento de lista */

		SEQORD_CondRetImpossInserirCarta,
		/* A carta especificada n�o pode ser inserida */

		SEQORD_CondRetImpossivelImprimir,
		/* A carta especificada n�o pode ser impressa */

		SEQORD_CondRetSeqOrdNaoExiste,
		/* pSeqOrd == NULL */

		SEQORD_CondRetListaNaoExiste
		/* pSeqOrd->pColuna == NULL */

	} SEQORD_tpCondRet;
	
/***********************************************************************
*
*  $FC Fun��o: SEQORD  Criar uma sequ�ncia ordenada
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada
*
*  $EP Par�metros
*     pSeqOrd - endere�o que vai receber a sequ�ncia ordenada criada
*
*  $FV Valor retornado
*	  SEQORD_CondRetOK			  - se tiver criado sem problemas
*	  SEQORD_CondRetFaltouMemoria - se tiver faltado mem�ria
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_CriarSeqOrd(SEQORD_tppSeqOrd *pSeqOrd);

/***********************************************************************
*
*  $FC Fun��o: SEQVIS  Destruir sequ�ncia ordenada
*
*  $ED Descri��o da fun��o
*     Destr�i a sequ�ncia ordenada fornecida.
*     O par�metro ponteiro para a sequ�ncia n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*
*  $EP Par�metros
*     pSeqOrd - ponteiro para a sequ�ncia ordenada
*
*  $FV Valor retornado
*     SEQORD_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_DestruirSeqOrd(SEQORD_tppSeqOrd pSeqOrd);


/***********************************************************************
*
*  $FC Fun��o: SEQORD  Inserir carta na sequ�ncia ordenada
*
*  $ED Descri��o da fun��o
*     Insere uma �nica carta na �ltima posi��o da sequ�ncia ordenada.
*     Caso a sequ�ncia esteja vazia, a �nica carta que poder� ser inserida � uma que tenha o s�mbolo 'A'.
*	  Nos demais casos, a carta s� poder� ser inserida numa sequ�ncia que tenha em seu topo, uma outra 
*     carta de mesmo naipe e s�mbolo antecessor ao da carta que pretende ser inserida. 
*	  Essa fun��o ser� usada para movimentar as cartas das sequ�ncias visiveis ou espa�os extras para a sequ�ncia ordenada
*     durante a partida.
*
*  $EP Par�metros
*     pSeqOrd	    - ponteiro para a sequ�ncia ordenada
*     pListaCarta	- ponteiro para a lista de carta a ser inserida
*				      N�o pode ser NULL
*
*  $FV Valor retornado
*     SEQORD_CondRetOK					- se inseriu a carta com sucesso
*	  SEQORD_CondRetListaVazia			- se a lista com a carta est� vazia
*     SEQORD_CondRetImpossInserirCarta  - caso contr�rio
*	  SEQORD_CondRetListaNaoExiste
*	  SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_InserirCarta(SEQORD_tppSeqOrd pSeqOrd, LIS_tppLista pListaCarta);


/***********************************************************************
*
*  $FC Fun��o: SEQORD  Verifica sequ�ncia ordenada
*
*  $ED Descri��o da fun��o
*     Verifica se sequ�ncia ordenada est� totalmente preenchida com as cartas de seus naipe
*
*  $EP Par�metros
*     pSeqOrd	  - ponteiro para a sequ�ncia ordenada
*     
*  $FV Valor retornado
*     SEQORD_CondRetOK				- se a sequ�ncia ordenada est� completa
*     SEQORD_CondRetListaNaoCheia	- e a sequ�ncia ordenada n�o est� completa
*	  SEQORD_CondRetListaNaoExiste
*	  SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_VerificaSeqOrd(SEQORD_tppSeqOrd pSeqOrd);


/***********************************************************************
*
*  $FC Fun��o: SEQORD  &Obter lista de cartas
*
*  $ED Descri��o da fun��o
*     Recebe uma sequ�ncia ordenada e guarda em um endere�o recebido a lista de cartas
*     da sequ�ncia.
*
*  $EP Par�metros
*     pSeqOrd  - ponteiro para a sequ�ncia ordenada
*	  pLista   - endere�o que vai receber a lista de cartas
*
*  $FV Valor retornado
*     SEQORD_CondRetOK	- obteve a lista sem problemas
*	  SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

   SEQORD_tpCondRet SEQORD_ObterListaCartas( SEQORD_tppSeqOrd pSeqOrd, LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: SEQORD  Imprimir sequ�ncia ordenada
*
*  $ED Descri��o da fun��o
*     Imprime a �ltima carta inserida na sequ�ncia ordenada, ou 0 se
*     a sequ�ncia ordenada estiver vazia.
*
*  $EP Par�metros
*     pSeqOrd - ponteiro a sequ�ncia ordenada.
*
*  $FV Valor retornado
*    SEQORD_CondRetOK				  - conseguiu imprimir
*	 SEQORD_CondRetImpossivelImprimir - n�o conseguiu imprimir
*	 SEQORD_CondRetListaNaoExiste
*	 SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_ImprimeSeqOrd(SEQORD_tppSeqOrd pSeqOrd);


#undef SequenciasOrdenadas_EXT

/********** Fim do m�dulo de defini��o: SEQORD  Sequ�ncia ordenada **********/

#endif
