/***************************************************************************
*  $MCI Módulo de implementação: SEQVIS  Sequência visível
*
*  Arquivo gerado:              SequenciaVisivel.c
*  Letras identificadoras:      SEQVIS
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       psm   14/abr/2017 inicio do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define SequenciaVisivel_OWN
#include "SequenciaVisivel.h"
#undef SequenciaVisivel_OWN

/***********************************************************************
*
*  $TC Tipo de dados: SEQVIS Descritor da cabeça da sequência
*
*
***********************************************************************/

	typedef struct SEQVIS_tagSeqVis {

		LIS_tppLista pLinha;
		/* Ponteiro para a cabeça de uma lista que vai armazenar as cartas */

	} SEQVIS_tpSeqVis;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: SEQVIS  Criar sequência visível
*  ****/

	SEQVIS_tpCondRet SEQVIS_CriarSeqVis(SEQVIS_tppSeqVis *pSeqVis)
	{

		*pSeqVis = (SEQVIS_tpSeqVis *) malloc(sizeof(SEQVIS_tpSeqVis));
		if (pSeqVis == NULL)
		{
			return SEQVIS_CondRetFaltouMemoria;
		} /* if */

		if( LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta, &((*pSeqVis)->pLinha) ) == LIS_CondRetFaltouMemoria)
		{
			return SEQVIS_CondRetFaltouMemoria;
		}

		return SEQVIS_CondRetOK;

	} /* Fim função: SEQVIS  Criar sequência visível */


/***************************************************************************
*
*  Função: SEQVIS  Destruir sequência visível
*  ****/

	SEQVIS_tpCondRet SEQVIS_DestruirSeqVis(SEQVIS_tppSeqVis pSeqVis)
	{

		if( pSeqVis == NULL )
		{
			free( pSeqVis ) ;
			return SEQVIS_CondRetOK;
		}

		LIS_DestruirLista(pSeqVis->pLinha);

		free(pSeqVis);
		return SEQVIS_CondRetOK;
	} /* Fim função: SEQVIS  Destruir sequência visível */


/***************************************************************************
*
*  Função: SEQVIS  Inserir carta na sequência visível seguindo a restrição de naipe e número
*  ****/

	SEQVIS_tpCondRet SEQVIS_InserirCartaRestr(SEQVIS_tppSeqVis pSeqVis, LIS_tppLista pListaCartas)
	{
		CAR_tppCarta pCartaSeq = NULL, pCartaLis = NULL;

		if( pSeqVis == NULL )
			return SEQVIS_CondRetSeqVisNaoExiste ;
		if( pSeqVis->pLinha == NULL )
			return SEQVIS_CondRetListaNaoExiste ;

		if (pListaCartas == NULL)
			return SEQVIS_CondRetImpossInserirCarta;

		IrInicioLista(&pListaCartas);
		IrFinalLista(&pSeqVis->pLinha);

		LIS_ObterValor(pSeqVis->pLinha, (void **) &pCartaSeq);
		if( LIS_ObterValor(pListaCartas, (void **) &pCartaLis) == LIS_CondRetListaVazia )
			return SEQVIS_CondRetListaVazia;

		if (pCartaSeq == NULL ||												/* Não tem nenhuma carta na sequência */
			( CAR_SimboloAntecessor( pCartaSeq, pCartaLis) == CAR_CondRetOK &&	/* Símbolo da lista é o antecessor do da sequência */
			  CAR_TemMesmaCor( pCartaSeq, pCartaLis) == CAR_CondRetFalse ) )	/* Cor da lista é diferente da sequência */
		{ /* Verificação da restrição de cor e símbolo */
			LIS_ConcatenarLista(pSeqVis->pLinha, pListaCartas);
			return SEQVIS_CondRetOK;
		}
		else
			return SEQVIS_CondRetImpossInserirCarta;
	} /* Fim função: SEQVIS  Inserir carta na sequência visível seguindo a restrição de naipe e número */


/***************************************************************************
*
*  Função: SEQVIS  Inserir carta na sequência visível sem a restrição de naipe e número
*  ****/

	SEQVIS_tpCondRet SEQVIS_InserirCartaSemRestr(SEQVIS_tppSeqVis pSeqVis, LIS_tppLista pListaCarta)
	{
		if( pSeqVis == NULL )
			return SEQVIS_CondRetSeqVisNaoExiste ;
		if( pSeqVis->pLinha == NULL )
			return SEQVIS_CondRetListaNaoExiste ;

		if( pListaCarta == NULL )
			return SEQVIS_CondRetImpossInserirCarta ;
		if( LIS_ConcatenarLista( pSeqVis->pLinha, pListaCarta ) == LIS_CondRetListaVazia )
			return SEQVIS_CondRetImpossInserirCarta ;

		return SEQVIS_CondRetOK;
	} /* Fim função: SEQVIS  Inserir carta na sequência visível sem a restrição de naipe e número */


/***************************************************************************
*
*  Função: SEQVIS  Remover carta da sequência visível
*  ****/

	SEQVIS_tpCondRet SEQVIS_RemoverCarta(SEQVIS_tppSeqVis pSeqVis, CAR_tppCarta pCarta, LIS_tppLista *pListaRemovida)
	{

		int cont = 0;

		if( pSeqVis == NULL )
			return SEQVIS_CondRetSeqVisNaoExiste ;
		if( pSeqVis->pLinha == NULL )
			return SEQVIS_CondRetListaNaoExiste ;

		if (LIS_ProcurarValor( (int (*) (void *pDado1, void *pDado2)) CAR_ComparaCartas, pSeqVis->pLinha, pCarta ) != LIS_CondRetOK )
			return SEQVIS_CondRetNaoAchou;

		while (LIS_AvancarElementoCorrente(pSeqVis->pLinha, 1) == LIS_CondRetOK)
		{
			CAR_tppCarta pAnt, pAtual;

			LIS_ObterValor(pSeqVis->pLinha, (void **) &pAtual);	/* Guarda carta atual */

			if(LIS_AvancarElementoCorrente(pSeqVis->pLinha, -1) == LIS_CondRetOK)
				LIS_ObterValor(pSeqVis->pLinha, (void **) &pAnt);				/* Guarda carta anterior */
			else
				return SEQVIS_CondRetImpossRetirarCarta;

			if(LIS_AvancarElementoCorrente(pSeqVis->pLinha, 1) == LIS_CondRetOK){	/* Volta pra carta atual */
				if (CAR_SimboloAntecessor(pAnt, pAtual) == CAR_CondRetFalse || CAR_TemMesmaCor(pAnt, pAtual) == CAR_CondRetOK)	/* Compara cor e símbolo */
					return SEQVIS_CondRetImpossRetirarCarta;
			} /* if */
			else
				return SEQVIS_CondRetImpossRetirarCarta;
			cont--;
		} /* while */

		if(cont != 0)
			LIS_AvancarElementoCorrente(pSeqVis->pLinha, cont);
		
		if(LIS_RetirarListaElem(pSeqVis->pLinha, pListaRemovida) == LIS_CondRetOK)
			return SEQVIS_CondRetOK;
		else
			return SEQVIS_CondRetImpossRetirarCarta;

	}/* Fim função: SEQVIS  Remover carta da sequência visível */


/***************************************************************************
*
*  $FC Função: SEQVIS  &Obter lista de cartas
*  ****/

   SEQVIS_tpCondRet SEQVIS_ObterListaCartas( SEQVIS_tppSeqVis pSeqVis, LIS_tppLista *pLista )
   {
	 
      if( pSeqVis == NULL )
			return SEQVIS_CondRetSeqVisNaoExiste ;

      *pLista = pSeqVis->pLinha ;

	  return SEQVIS_CondRetOK;

   } /* Fim função: SEQVIS  &Obter lista de cartas */


/***************************************************************************
*
*  Função: SEQVIS  Imprime sequência visível
*  ****/

	SEQVIS_tpCondRet SEQVIS_ImprimeSeqVis(SEQVIS_tppSeqVis pSeqVis)
	{
		CAR_tppCarta pCarta;

		if( pSeqVis == NULL )
			return SEQVIS_CondRetSeqVisNaoExiste ;
		if( pSeqVis->pLinha == NULL )
			return SEQVIS_CondRetListaNaoExiste ;

		
		IrInicioLista(&pSeqVis->pLinha);
		if( LIS_ObterValor(pSeqVis->pLinha, (void **) &pCarta) == LIS_CondRetListaVazia )
		{
			printf("0\n");
		}
		else
		{
			do
			{
				char stringCarta[3];
				if(CAR_CartaParaString(pCarta, stringCarta) == CAR_CondRetCartaNaoExiste)
					return SEQVIS_CondRetImpossivelImprimir;
				else
					printf("%s ", stringCarta);
			} while( LIS_AvancarElementoCorrente(pSeqVis->pLinha, 1) == LIS_CondRetOK
				    && LIS_ObterValor(pSeqVis->pLinha, (void **) &pCarta) == LIS_CondRetOK );
			printf("\n");
		}
		return SEQVIS_CondRetOK;

	}/* Fim função: Imprime sequência visível */


/********** Fim do módulo de implementação: SEQVIS  Sequência Visível **********/
