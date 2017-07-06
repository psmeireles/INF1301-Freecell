/***************************************************************************
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
*
***************************************************************************/

#include "LISTA.H"						
#include <stdlib.h>
#include <stdio.h>

#define SequenciaOrdenada_OWN
#include "SequenciaOrdenada.h"
#undef SequenciaOrdenada_OWN

/***********************************************************************
*
*  $TC Tipo de dados: SEQORD Descritor da cabeça da sequência
*
*
***********************************************************************/

	typedef struct SEQORD_tagSeqOrd
	{

		LIS_tppLista pColuna;
		/* Ponteiro para a cabeça de uma lista que vai armazenar as cartas */

	} SEQORD_tpSeqOrd;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: SEQORD  Criar sequência ordenada
*  ****/

	SEQORD_tpCondRet SEQORD_CriarSeqOrd(SEQORD_tppSeqOrd *pSeqOrd)
	{

		*pSeqOrd = (SEQORD_tpSeqOrd *) malloc(sizeof(SEQORD_tpSeqOrd));
		if (pSeqOrd == NULL)
		{
			return SEQORD_CondRetFaltouMemoria;
		} /* if */
		
		if( LIS_CriarLista( (void (*)(void *pDado)) CAR_DestruirCarta, &((*pSeqOrd)->pColuna) ) == LIS_CondRetFaltouMemoria)
		{
			return SEQORD_CondRetFaltouMemoria;
		}

		return SEQORD_CondRetOK;

	} /* Fim função: SEQORD  Criar sequência ordenada */


/***************************************************************************
*
*  Função: SEQVIS  Destruir sequência ordenada
*  ****/

	SEQORD_tpCondRet SEQORD_DestruirSeqOrd(SEQORD_tppSeqOrd pSeqOrd)
	{

		if( pSeqOrd == NULL )
		{
			free( pSeqOrd ) ;
			return SEQORD_CondRetOK;
		}

		LIS_DestruirLista(pSeqOrd->pColuna);

		free(pSeqOrd);
		return SEQORD_CondRetOK;
	} /* Fim função: SEQORD  Destruir sequência ordenada */

	
/***************************************************************************
*
*  Função: SEQORD  Inserir carta na sequência ordenada
*  ****/

	SEQORD_tpCondRet SEQORD_InserirCarta(SEQORD_tppSeqOrd pSeqOrd, LIS_tppLista pListaCarta)
	{
		int quantidade;
		CAR_tppCarta pCartaSeq, pCarta;

		if( pSeqOrd == NULL )
			return SEQORD_CondRetSeqOrdNaoExiste ;
		if( pSeqOrd->pColuna == NULL )
			return SEQORD_CondRetListaNaoExiste ;

		if (LIS_ObterTam(pListaCarta, &quantidade) == LIS_CondRetListaNaoExiste )
			return SEQORD_CondRetListaNaoExiste ;

		if ( quantidade == 0 )
			return SEQORD_CondRetListaVazia;

		if (pListaCarta == NULL || quantidade != 1)    /*Se a lista de cartas recebida estiver vazia ou com mais de uma carta*/
			return SEQORD_CondRetImpossInserirCarta;

		IrFinalLista( &(LIS_tppLista) pSeqOrd->pColuna);

		if ( LIS_ObterValor(pSeqOrd->pColuna, (void **) &pCartaSeq) != LIS_CondRetOK )
		{
			pCartaSeq = NULL ;
		}
		
		LIS_ObterValor(pListaCarta, (void **) &pCarta) ;

		/*Caso não tenha nenhuma carta na sequência e a carta a ser inserida tem símbolo S_A*/
		if (pCartaSeq == NULL && CAR_EhPrimeiraCarta(pCarta) == CAR_CondRetOK)
		{
			LIS_ConcatenarLista(pSeqOrd->pColuna, pListaCarta);
			return SEQORD_CondRetOK;
		}

		else if (CAR_TemMesmoNaipe(pCartaSeq, pCarta) == CAR_CondRetOK &&  /*Carta a ser inserida tem mesmo naipe da sequência */
			CAR_SimboloSucessor(pCartaSeq, pCarta) == CAR_CondRetOK)       /*Carta a ser inserida é sucessora da carta do topo da sequência */
		{
			LIS_ConcatenarLista(pSeqOrd->pColuna, pListaCarta);
			return SEQORD_CondRetOK;
		}
		else
			return SEQORD_CondRetImpossInserirCarta;

	} /* Fim função: SEQORD  Inserir carta na sequência ordenada */


/***************************************************************************
*
*  Função: SEQORD  Verifica Objetivo
*  ****/

	SEQORD_tpCondRet SEQORD_VerificaSeqOrd(SEQORD_tppSeqOrd pSeqOrd)
	{
		int tam;

		if( pSeqOrd == NULL )
			return SEQORD_CondRetSeqOrdNaoExiste ;
		if( pSeqOrd->pColuna == NULL )
			return SEQORD_CondRetListaNaoExiste ;

		LIS_ObterTam( pSeqOrd->pColuna, &tam);

		if(tam == 13)
			return SEQORD_CondRetOK;
		else
			return SEQORD_CondRetListaNaoCheia;

	} /* Fim função: SEQORD  Verifica sequência ordenada */


/***************************************************************************
*
*  $FC Função: SEQORD  &Obter lista de cartas
*  ****/

   SEQORD_tpCondRet SEQORD_ObterListaCartas( SEQORD_tppSeqOrd pSeqOrd, LIS_tppLista *pLista )
   {
	 
      if( pSeqOrd == NULL )
			return SEQORD_CondRetSeqOrdNaoExiste ;

      *pLista = pSeqOrd->pColuna ;

	  return SEQORD_CondRetOK ;

   } /* Fim função: SEQORD  &Obter lista de cartas */



/***************************************************************************
*
*  Função: SEQORD  Imprime sequência ordenada
*  ****/

	SEQORD_tpCondRet SEQORD_ImprimeSeqOrd(SEQORD_tppSeqOrd pSeqOrd)
	{
		
		CAR_tppCarta pCarta ;
		char stringCarta[3] ;

		if( pSeqOrd == NULL )
			return SEQORD_CondRetSeqOrdNaoExiste ;
		if( pSeqOrd->pColuna == NULL )
			return SEQORD_CondRetListaNaoExiste ;

		IrFinalLista( &(LIS_tppLista) pSeqOrd->pColuna) ;
		if( LIS_ObterValor(pSeqOrd->pColuna, (void **) &pCarta) == LIS_CondRetListaVazia )
		{
			printf("0 ");
		}
		else
		{
			if(CAR_CartaParaString(pCarta, stringCarta) == CAR_CondRetCartaNaoExiste)
			{
				return SEQORD_CondRetImpossivelImprimir;
			}
			else
			{
				printf("%s ", stringCarta);
			}
		}
		return SEQORD_CondRetOK;

	}/* Fim função: Imprime sequência ordenada */


/********** Fim do módulo de implementação: SEQORD  Sequência Ordenada **********/
