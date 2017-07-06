/***************************************************************************
*  $MCI M�dulo de implementa��o: ESPEXT  Espa�os Extras
*
*  Arquivo gerado:              Espa�osExtras.c
*  Letras identificadoras:      ESPEXT
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: rnt
*			psm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o     Autor    Data     Observa��es
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
*  $TC Tipo de dados: ESPEXT Elemento do Espa�o Extras
*
*
***********************************************************************/

	typedef struct ESPEXT_tagEspExt {
	
		LIS_tppLista pLista;
		/* Ponteiro para a cabe�a de uma lista que vai armazenar as cartas */

		int numEspExtVazios;
		/* Numero de espa�os extras vazios */

	} ESPEXT_tpEspExt;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ESPEXT  Criar espa�os extras
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

	} /* Fim fun��o: ESPEXT  Criar espa�os extras */


/***************************************************************************
*
*  Fun��o: ESPEXT  Destruir espa�os extras
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
	} /* Fim fun��o: EXPEXT  Destruir espa�os extras */


/***************************************************************************
*
*  Fun��o: ESPEXT  Inserir carta em espa�os extras
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

	} /* Fim fun��o: ESPEXT  Inserir carta em espa�os extras */


/***************************************************************************
*
*  Fun��o: ESPEXT  Remover carta dos espa�os extras
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

	}/* Fim fun��o: ESPEXT  Remover carta dos espa�os extras */


/***************************************************************************
*
*  $FC Fun��o: ESPEXT  &Obter lista de cartas
*  ****/

   ESPEXT_tpCondRet ESPEXT_ObterListaCartas( ESPEXT_tppEspExt pEspExt, LIS_tppLista *pLista )
   {
	 
      if( pEspExt == NULL )
		  return ESPEXT_CondRetEspExtNaoExiste ;

      *pLista = pEspExt->pLista ;

	  return ESPEXT_CondRetOK;

   } /* Fim fun��o: ESPEXT  &Obter lista de cartas */


/***************************************************************************
*
*  Fun��o: ESPEXT  Imprimir espa�os extras
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

	}/* Fim fun��o: Imprime espa�os extras */


/***************************************************************************
*
*  Fun��o: ESPEXT  Obter numero de espa�os extras vazios
*  ****/

	ESPEXT_tpCondRet ESPEXT_ObterNumEspExtVazios( ESPEXT_tppEspExt pEspExt, int *qtdVazios )
	{

		if( pEspExt == NULL )
			return ESPEXT_CondRetEspExtNaoExiste ;

		*qtdVazios = pEspExt->numEspExtVazios ;

		return ESPEXT_CondRetOK;
	} /* Fim fun��o: EXPEXT  Obter numero de espa�os espa�os extras vazios */

/********** Fim do m�dulo de implementa��o: ESPEXT  Espa�os extras **********/