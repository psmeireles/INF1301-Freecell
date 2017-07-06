/***************************************************************************
*  $MCI Módulo de implementação: ESPEXT  Espaços Extras
*
*  Arquivo gerado:              EspaçosExtras.c
*  Letras identificadoras:      ESPEXT
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: rnt
*			psm
*
*  $HA Histórico de evolução:
*     Versão     Autor    Data     Observações
*     1       rnt, psm  16/abr/2017 inicio do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>


#define EspacosExtras_OWN
#include "EspacosExtras.h"
#undef EspacosExtras_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ESPEXT Elemento do Espaço Extras
*
*
***********************************************************************/

	typedef struct ESPEXT_tagEspExt {
	
		LIS_tppLista pLista;
		/* Ponteiro para a cabeça de uma lista que vai armazenar as cartas */

		int numEspExtVazios;
		/* Numero de espaços extras vazios */

	} ESPEXT_tpEspExt;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ESPEXT  Criar espaços extras
*  ****/

	ESPEXT_tpCondRet ESPEXT_CriarEspExt( ESPEXT_tppEspExt *pEspExt )
	{

		*pEspExt = (ESPEXT_tpEspExt *) malloc( sizeof( ESPEXT_tpEspExt ) );
		if (*pEspExt == NULL)
		{
			return ESPEXT_CondRetFaltouMemoria;
		} /* if */

		if( LIS_CriarLista( (void (*)(void *pDado)) CAR_DestruirCarta, &((*pEspExt)->pLista) ) == LIS_CondRetFaltouMemoria )
		{
			return ESPEXT_CondRetFaltouMemoria;
		}

		(*pEspExt)->numEspExtVazios = 4;

		return ESPEXT_CondRetOK;

	} /* Fim função: ESPEXT  Criar espaços extras */


/***************************************************************************
*
*  Função: ESPEXT  Destruir espaços extras
*  ****/

	ESPEXT_tpCondRet ESPEXT_DestruirEspExt( ESPEXT_tppEspExt pEspExt )
	{

		if( pEspExt == NULL )	
		{
			free( pEspExt ) ;
			return ESPEXT_CondRetOK ;
		}

		LIS_DestruirLista( pEspExt->pLista ) ;

		free(pEspExt) ;

		return ESPEXT_CondRetOK ;
	} /* Fim função: EXPEXT  Destruir espaços extras */


/***************************************************************************
*
*  Função: ESPEXT  Inserir carta em espaços extras
*  ****/

	ESPEXT_tpCondRet ESPEXT_InserirCarta(ESPEXT_tppEspExt pEspExt, LIS_tppLista pListaCarta)
	{
		int quantidade;
		LIS_tpCondRet retorno ;

		if (pEspExt == NULL || pListaCarta == NULL)
			return ESPEXT_CondRetImpossInserirCarta;

		if (LIS_ObterTam(pListaCarta, &quantidade) == LIS_CondRetListaNaoExiste )
			return ESPEXT_CondRetListaNaoExiste ;

		if (quantidade != 1)  
			return ESPEXT_CondRetImpossInserirCarta;

		if ( pEspExt->numEspExtVazios > 0 )
		{
			retorno = LIS_ConcatenarLista( pEspExt->pLista , pListaCarta ) ;
			if( retorno == LIS_CondRetListaVazia )
				return ESPEXT_CondRetListaVazia ;
			else if( retorno == LIS_CondRetListaNaoExiste )
				return ESPEXT_CondRetListaNaoExiste ;
			pEspExt->numEspExtVazios--;
			return ESPEXT_CondRetOK;
		}
		else 
			return ESPEXT_CondRetImpossInserirCarta;

	} /* Fim função: ESPEXT  Inserir carta em espaços extras */


/***************************************************************************
*
*  Função: ESPEXT  Remover carta dos espaços extras
*
*  ****/

	ESPEXT_tpCondRet  ESPEXT_RemoverCarta(ESPEXT_tppEspExt pEspExt, CAR_tppCarta pCarta, LIS_tppLista *pListaRemovida)
	{
		LIS_tpCondRet condRetLis;
		if ( pEspExt == NULL || pCarta == NULL )
			return ESPEXT_CondRetImpossRetirarCarta;
		
		if ( pEspExt->pLista == NULL )
			return ESPEXT_CondRetListaNaoExiste;

		if ( pEspExt->numEspExtVazios == 4 )
			return ESPEXT_CondRetListaVazia;

		condRetLis = LIS_ProcurarValor( (int (*) (void *pDado1, void *pDado2)) CAR_ComparaCartas, pEspExt->pLista, pCarta );
		if ( condRetLis != LIS_CondRetOK )
			return ESPEXT_CondRetNaoAchou;

		condRetLis = LIS_RemoverElemento(pEspExt->pLista, pListaRemovida );
		if ( condRetLis == LIS_CondRetListaVazia )
			return ESPEXT_CondRetListaVazia;
		else if ( condRetLis == LIS_CondRetFaltouMemoria )
			return ESPEXT_CondRetFaltouMemoria;
		
		pEspExt->numEspExtVazios++;
		return ESPEXT_CondRetOK;

	}/* Fim função: ESPEXT  Remover carta dos espaços extras */


/***************************************************************************
*
*  $FC Função: ESPEXT  &Obter lista de cartas
*  ****/

   ESPEXT_tpCondRet ESPEXT_ObterListaCartas( ESPEXT_tppEspExt pEspExt, LIS_tppLista *pLista )
   {
	 
      if( pEspExt == NULL )
		  return ESPEXT_CondRetEspExtNaoExiste ;

      *pLista = pEspExt->pLista ;

	  return ESPEXT_CondRetOK;

   } /* Fim função: ESPEXT  &Obter lista de cartas */


/***************************************************************************
*
*  Função: ESPEXT  Imprimir espaços extras
*
*  ****/

	ESPEXT_tpCondRet ESPEXT_ImprimeEspExt(ESPEXT_tppEspExt pEspExt)
	{
		CAR_tppCarta pCarta = NULL ;
		int i;

		if( pEspExt == NULL )
		  return ESPEXT_CondRetEspExtNaoExiste ;
		
		if( IrInicioLista( &pEspExt->pLista ) == LIS_CondRetListaNaoExiste )
			return ESPEXT_CondRetListaNaoExiste ;
		
		for(i = 0; i < 4 - pEspExt->numEspExtVazios; i++)
		{
			char stringCarta[3];
			LIS_ObterValor( pEspExt->pLista, (void **) &pCarta ) ;
			if( CAR_CartaParaString( pCarta, stringCarta ) == CAR_CondRetOK )
				printf("%s ", stringCarta) ;
			else
				return ESPEXT_CondRetImpossivelImprimir ;
			LIS_AvancarElementoCorrente( pEspExt->pLista, 1 );
		}

		for(i = pEspExt->numEspExtVazios; i > 0; i--)
			printf("0 ") ;

		return ESPEXT_CondRetOK;

	}/* Fim função: Imprime espaços extras */


/***************************************************************************
*
*  Função: ESPEXT  Obter numero de espaços extras vazios
*  ****/

	ESPEXT_tpCondRet ESPEXT_ObterNumEspExtVazios( ESPEXT_tppEspExt pEspExt, int *qtdVazios )
	{

		if( pEspExt == NULL )
			return ESPEXT_CondRetEspExtNaoExiste ;

		*qtdVazios = pEspExt->numEspExtVazios ;

		return ESPEXT_CondRetOK;
	} /* Fim função: EXPEXT  Obter numero de espaços espaços extras vazios */

/********** Fim do módulo de implementação: ESPEXT  Espaços extras **********/