#if !defined( SequenciaOrdenada_MOD )
#define SequenciaOrdenada_MOD

/***************************************************************************
*
*  $MCI Módulo de implementação: SEQORD  Sequência Ordenada
*
*  Arquivo gerado:              SequenciaOrdenada.c
*  Letras identificadoras:      SEQORD
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: mcc
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       mcc   15/abr/2017 inicio do desenvolvimento
*  $ED Descrição do módulo
*     Este módulo implementa uma sequência ordenada do jogo Freecell.
*     Cada sequência ordenada começa inicialmente vazia e corresponde à um 
*     naipe. Deve ser preenchida em ordem crescente com todas as cartas de
*     seu naipe. 
*	  O tabuleiro do jogo tem 4 sequências ordenadas.
*     Se todas as sequências ordenadas forem totalmente preenchidas, o 
*     objetivo do jogo é alcançado.
***************************************************************************/

#include "Cartas.h"
#include "LISTA.H"

/* Controle de escopo do arquivo de definição */

#if defined( SequenciaOrdenada_MOD )
	#define SequenciaOrdenada_EXT
#else
	#define SequenciaOrdenada_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um conjunto de sequências ordenadas */

	typedef struct SEQORD_tagSeqOrd * SEQORD_tppSeqOrd;

/***********************************************************************
*
*  $TC Tipo de dados: SEQORD Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da sequência ordenada
*
***********************************************************************/

	
	typedef enum {

		SEQORD_CondRetOK,
		/* Concluiu corretamente */

		SEQORD_CondRetListaVazia,
		/* A lista não contém elementos */

		SEQORD_CondRetListaNaoCheia,
		/* A lista foi não totalmente preenchida */

		SEQORD_CondRetFaltouMemoria,
		/* Faltou memória ao tentar criar um elemento de lista */

		SEQORD_CondRetImpossInserirCarta,
		/* A carta especificada não pode ser inserida */

		SEQORD_CondRetImpossivelImprimir,
		/* A carta especificada não pode ser impressa */

		SEQORD_CondRetSeqOrdNaoExiste,
		/* pSeqOrd == NULL */

		SEQORD_CondRetListaNaoExiste
		/* pSeqOrd->pColuna == NULL */

	} SEQORD_tpCondRet;
	
/***********************************************************************
*
*  $FC Função: SEQORD  Criar uma sequência ordenada
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada
*
*  $EP Parâmetros
*     pSeqOrd - endereço que vai receber a sequência ordenada criada
*
*  $FV Valor retornado
*	  SEQORD_CondRetOK			  - se tiver criado sem problemas
*	  SEQORD_CondRetFaltouMemoria - se tiver faltado memória
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_CriarSeqOrd(SEQORD_tppSeqOrd *pSeqOrd);

/***********************************************************************
*
*  $FC Função: SEQVIS  Destruir sequência ordenada
*
*  $ED Descrição da função
*     Destrói a sequência ordenada fornecida.
*     O parâmetro ponteiro para a sequência não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*
*  $EP Parâmetros
*     pSeqOrd - ponteiro para a sequência ordenada
*
*  $FV Valor retornado
*     SEQORD_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_DestruirSeqOrd(SEQORD_tppSeqOrd pSeqOrd);


/***********************************************************************
*
*  $FC Função: SEQORD  Inserir carta na sequência ordenada
*
*  $ED Descrição da função
*     Insere uma única carta na última posição da sequência ordenada.
*     Caso a sequência esteja vazia, a única carta que poderá ser inserida é uma que tenha o símbolo 'A'.
*	  Nos demais casos, a carta só poderá ser inserida numa sequência que tenha em seu topo, uma outra 
*     carta de mesmo naipe e símbolo antecessor ao da carta que pretende ser inserida. 
*	  Essa função será usada para movimentar as cartas das sequências visiveis ou espaços extras para a sequência ordenada
*     durante a partida.
*
*  $EP Parâmetros
*     pSeqOrd	    - ponteiro para a sequência ordenada
*     pListaCarta	- ponteiro para a lista de carta a ser inserida
*				      Não pode ser NULL
*
*  $FV Valor retornado
*     SEQORD_CondRetOK					- se inseriu a carta com sucesso
*	  SEQORD_CondRetListaVazia			- se a lista com a carta está vazia
*     SEQORD_CondRetImpossInserirCarta  - caso contrário
*	  SEQORD_CondRetListaNaoExiste
*	  SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_InserirCarta(SEQORD_tppSeqOrd pSeqOrd, LIS_tppLista pListaCarta);


/***********************************************************************
*
*  $FC Função: SEQORD  Verifica sequência ordenada
*
*  $ED Descrição da função
*     Verifica se sequência ordenada está totalmente preenchida com as cartas de seus naipe
*
*  $EP Parâmetros
*     pSeqOrd	  - ponteiro para a sequência ordenada
*     
*  $FV Valor retornado
*     SEQORD_CondRetOK				- se a sequência ordenada está completa
*     SEQORD_CondRetListaNaoCheia	- e a sequência ordenada não está completa
*	  SEQORD_CondRetListaNaoExiste
*	  SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_VerificaSeqOrd(SEQORD_tppSeqOrd pSeqOrd);


/***********************************************************************
*
*  $FC Função: SEQORD  &Obter lista de cartas
*
*  $ED Descrição da função
*     Recebe uma sequência ordenada e guarda em um endereço recebido a lista de cartas
*     da sequência.
*
*  $EP Parâmetros
*     pSeqOrd  - ponteiro para a sequência ordenada
*	  pLista   - endereço que vai receber a lista de cartas
*
*  $FV Valor retornado
*     SEQORD_CondRetOK	- obteve a lista sem problemas
*	  SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

   SEQORD_tpCondRet SEQORD_ObterListaCartas( SEQORD_tppSeqOrd pSeqOrd, LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Função: SEQORD  Imprimir sequência ordenada
*
*  $ED Descrição da função
*     Imprime a última carta inserida na sequência ordenada, ou 0 se
*     a sequência ordenada estiver vazia.
*
*  $EP Parâmetros
*     pSeqOrd - ponteiro a sequência ordenada.
*
*  $FV Valor retornado
*    SEQORD_CondRetOK				  - conseguiu imprimir
*	 SEQORD_CondRetImpossivelImprimir - não conseguiu imprimir
*	 SEQORD_CondRetListaNaoExiste
*	 SEQORD_CondRetSeqOrdNaoExiste
*
***********************************************************************/

	SEQORD_tpCondRet SEQORD_ImprimeSeqOrd(SEQORD_tppSeqOrd pSeqOrd);


#undef SequenciasOrdenadas_EXT

/********** Fim do módulo de definição: SEQORD  Sequência ordenada **********/

#endif
