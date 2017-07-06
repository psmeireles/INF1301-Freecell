#if !defined( SequenciaVisivel_MOD )
#define SequenciaVisivel_MOD

/***************************************************************************
*
*  $MCD Módulo de definição: SEQVIS Sequência Visível
*
*  Arquivo gerado:              SequenciaVisivel.h
*  Letras identificadoras:      SEQVIS
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1		  psm	13/abr/2017	Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa uma sequência visível do jogo Freecell.
*     As sequências visíveis são as sequências onde as cartas do jogo são inicialmente dispostas.
*	  O tabuleiro do jogo tem 8 sequências visíveis.
*	  Uma sequência visível é estruturada como uma lista de cartas.
***************************************************************************/

#include "Cartas.h"
#include "LISTA.H"

/* Controle de escopo do arquivo de definição */

#if defined( SequenciaVisivel_MOD )
	#define SequenciaVisivel_EXT
#else
	#define SequenciaVisivel_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um conjunto de sequências visíveis */

	typedef struct SEQVIS_tagSeqVis * SEQVIS_tppSeqVis;

/***********************************************************************
*
*  $TC Tipo de dados: SEQVIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da sequência visível
*
***********************************************************************/

	typedef enum {

		SEQVIS_CondRetOK,
		/* Concluiu corretamente */

		SEQVIS_CondRetListaVazia,
		/* A lista não contém elementos */

		SEQVIS_CondRetFimLista,
		/* Foi atingido o fim de lista */

		SEQVIS_CondRetNaoAchou,
		/* Não encontrou o valor procurado */

		SEQVIS_CondRetFaltouMemoria,
		/* Faltou memória ao tentar criar um elemento de lista */

		SEQVIS_CondRetImpossRetirarCarta,
		/* A carta especificada não pode ser removida */

		SEQVIS_CondRetImpossInserirCarta,
		/* A carta especificada não pode ser inserida */

		SEQVIS_CondRetListaErrada,
		/* A lista de cartas não obedece as restrições do jogo Free Cell */

		SEQVIS_CondRetImpossivelImprimir,
		/* A carta especificada não pode ser impressa */

		SEQVIS_CondRetListaNaoExiste,
		/* pSeqVis->pLinha == NULL */

		SEQVIS_CondRetSeqVisNaoExiste
		/* pSeqVis == NULL */
	

	} SEQVIS_tpCondRet;


/***********************************************************************
*
*  $FC Função: SEQVIS  Criar uma sequência visível
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada
*
*  $EP Parâmetros
*     pSeqVis - endereço que vai receber a sequência visível criada
*
*  $FV Valor retornado
*	  SEQVIS_CondRetOK			  - se tiver criado sem problemas
*	  SEQVIS_CondRetFaltouMemoria - se tiver faltado memória
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_CriarSeqVis(SEQVIS_tppSeqVis *pSeqVis);


/***********************************************************************
*
*  $FC Função: SEQVIS  Destruir sequência visível
*
*  $ED Descrição da função
*     Destrói a sequência visível fornecida.
*     O parâmetro ponteiro para a sequência não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*
*  $EP Parâmetros
*     pSeqVis - ponteiro para a sequência visível
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_DestruirSeqVis(SEQVIS_tppSeqVis pSeqVis);


/***********************************************************************
*
*  $FC Função: SEQVIS  Inserir carta na sequência visível seguindo a restrição de naipe e número
*
*  $ED Descrição da função
*     Insere uma carta, ou bloco de cartas, na última posição da sequência visível.
*     Caso a sequência esteja vazia, insere a primeira carta da lista.
*	  A inserção da carta deve seguir os padrões do jogo Freecell. Ou seja, a carta inserida na sequência
*	  deve ter naipe de cor diferente e símbolo antecessor aos da carta anterior da sequência.
*	  Essa função será usada para movimentar as cartas durante a partida.
*
*  $EP Parâmetros
*     pSeqVis	   - ponteiro para a sequência visível
*     pListaCartas - ponteiro para a cabeça da lista que contém as cartas a serem inseridas
*				     Não pode ser NULL. Estragada no final.
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK			  - se o elemento inserido retirado sem problemas
*     SEQVIS_CondRetFaltouMemoria - se não houve espaço suficiente na sequência visível para inserir carta
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_InserirCartaRestr(SEQVIS_tppSeqVis pSeqVis,  LIS_tppLista pListaCartas);


/***********************************************************************
*
*  $FC Função: SEQVIS  Inserir carta na sequência visível sem a restrição de naipe e número
*
*  $ED Descrição da função
*     Insere uma carta na última posição da sequência visível.
*     Caso a sequência esteja vazia, insere o primeiro elemento da lista.
*	  A inserção da carta não deve seguir os padrões do jogo Freecell. Ou seja, a carta inserida na sequência
*	  não precisa ter naipe de cor diferente e símbolo antecessor aos da carta anterior da sequência.
*	  Essa função será apenas para distribuir as cartas do baralho no início da partida.
*
*  $EP Parâmetros
*     pSeqVis	  - ponteiro para a sequência visível
*     pListaCarta - ponteiro para uma lista contendo a carta a ser inserida
*				    Não pode ser NULL
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK				   - se a carta foi inserida sem problemas
*     SEQVIS_CondRetImpossInserirCarta - se não foi possível inserir a carta
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_InserirCartaSemRestr(SEQVIS_tppSeqVis pSeqVis,  LIS_tppLista pListaCarta);

/***********************************************************************
*
*  $FC Função: SEQVIS  Remover carta da sequência visível
*
*  $ED Descrição da função
*     Remove o elemento especificado da sequência, seguido por todos os elementos após ele. O elemento pode 
*	  estar em qualquer parte da sequência desde que os elementos da próximas posições sigam as condiçÕes 
*	  impostas pelo jogo freecell. Ou seja, os elementos seguintes devem ter naipe de cor diferente do anterior 
*	  e devem ter símbolo antecessor ao do elemento anterior.
*
*  $EP Parâmetros
*     pSeqVis		 - ponteiro para a sequência visível.
*	  pCarta		 - carta a ser retirada
*	  pListaRemovida - lista que vai receber as cartas retiradas
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK				   - se o elemento foi retirado sem problemas
*	  SEQVIS_CondRetNaoAchou		   - se o elemento a ser retirado não está na sequência visível especificada
*	  SEQVIS_CondRetImpossRetirarCarta - se não foi possível retirar a carta
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_RemoverCarta(SEQVIS_tppSeqVis pSeqVis, CAR_tppCarta pCarta, LIS_tppLista *pListaRemovida);


/***********************************************************************
*
*  $FC Função: SEQVIS  &Obter lista de cartas
*
*  $ED Descrição da função
*     Recebe uma sequência visível e guarda em um endereço recebido a lista de cartas
*     da sequência.
*
*  $EP Parâmetros
*     pSeqVis  - ponteiro para a sequência visível
*	  pLista   - endereço que vai receber a lista de cartas
*
*  $FV Valor retornado
*     SEQVIS_CondRetOK	- obteve a lista sem problemas
*	  SEQVIS_CondRetSeqVisNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_ObterListaCartas( SEQVIS_tppSeqVis pSeqVis, LIS_tppLista *pLista ) ;

/***********************************************************************
*
*  $FC Função: SEQVIS  Imprimir sequência visível
*
*  $ED Descrição da função
*     Imprime as cartas pertencentes à sequência visível recebida em ordem.
*
*  $EP Parâmetros
*     pSeqVis - ponteiro a sequência visível.
*
*  $FV Valor retornado
*    SEQVIS_CondRetOK				  - conseguiu imprimir
*	 SEQVIS_CondRetImpossivelImprimir - não conseguiu imprimir
*	  SEQVIS_CondRetSeqVisNaoExiste
*	  SEQVIS_CondRetListaNaoExiste
*
***********************************************************************/

	SEQVIS_tpCondRet SEQVIS_ImprimeSeqVis(SEQVIS_tppSeqVis pSeqVis);

#undef SequenciasVisiveis_EXT

/********** Fim do módulo de definição: SEQVIS  Sequência Visível **********/

#endif