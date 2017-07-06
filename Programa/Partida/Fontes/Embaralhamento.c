/***************************************************************************
*  $MCI M�dulo de implementa��o: EMB  Embaralhamento
*
*  Arquivo gerado:              Embaralhamento.c
*  Letras identificadoras:      EMB
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       psm   30/abr/2017 in�cio desenvolvimento
*
***************************************************************************/

#include   <memory.h>
#include   <malloc.h>
#include   <stdlib.h>
#include   <time.h>
#include   <stdio.h>


#define EMBARALHAMENTO_OWN
	#include "Embaralhamento.h"
#undef EMBARALHAMENTO_OWN

#define TAM_BARALHO 52

/***********************************************************************
*
*  $TC Tipo de dados: EMB Baralho
*
*
***********************************************************************/

   typedef struct EMB_tagBaralho {

         LIS_tppLista pCartas;
               /* Ponteiro para a lista com as cartas do baralho */

   } EMB_tpBaralho ;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: EMB  &Criar baralho
*  ****/

   EMB_tpCondRet EMB_CriarBaralho( EMB_tppBaralho *pBaralho )
   {
	  int i;
	  CAR_tppCarta pCarta = NULL;
	  LIS_tpCondRet retorno;

      *pBaralho = ( EMB_tpBaralho * ) malloc( sizeof( EMB_tpBaralho )) ;
      if ( *pBaralho == NULL )
      {
         return EMB_CondRetFaltouMemoria ;
      } /* if */

      if( LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta, &((*pBaralho)->pCartas) )
		  == LIS_CondRetFaltouMemoria )
		  return EMB_CondRetFaltouMemoria ;

	  for(i = 0; i < TAM_BARALHO; i++){
		  
		  /* Criar cada carta:

		  Simbolo = i%13

		  Naipes est�o em ordem alfab�tica, logo:
		  Naipe = i/13 */

		  /* Cria cartas em ordem alfab�tica por naipe e em ordem crescente dentro dos naipes. Cores dos naipes est�o alternadas */
		  if( CAR_CriarCarta( (CAR_Simbolo) (i%13), (CAR_Naipe) (i/13), &pCarta)		
			  == CAR_CondRetFaltouMemoria )																				
			  return EMB_CondRetFaltouMemoria;

		  retorno = LIS_InserirElementoApos( (*pBaralho)->pCartas, pCarta ) ;
		  if( retorno == LIS_CondRetFaltouMemoria )
			  return EMB_CondRetFaltouMemoria ;
		  else if( retorno == LIS_CondRetListaNaoExiste )
			  return EMB_CondRetBaralhoNaoExiste ;

	  }

      return EMB_CondRetOK;

   } /* Fim fun��o: EMB  &Criar baralho */

/***************************************************************************
*
*  $FC Fun��o: EMB  &Destruir baralho
*  ****/

   EMB_tpCondRet EMB_DestruirBaralho( EMB_tppBaralho pBaralho )
   {

      if( pBaralho == NULL )
	  {
		  free(pBaralho) ;
		  return EMB_CondRetOK ;
	  }

      if(pBaralho->pCartas != NULL)
		  LIS_DestruirLista( pBaralho->pCartas ) ;

      free( pBaralho ) ;

	  return EMB_CondRetOK;

   } /* Fim fun��o: EMB  &Destruir baralho */

/***************************************************************************
*
*  $FC Fun��o: EMB  &Embaralhar
*  ****/

   EMB_tpCondRet EMB_Embaralhar( EMB_tppBaralho pBaralho )
   {

	   int i = -1, tamBaralho = -1;
	   LIS_tppLista pListaDestino = NULL;
      
       if( pBaralho == NULL )
		   return EMB_CondRetBaralhoNaoExiste ;

	   if( LIS_ObterTam( pBaralho->pCartas, &tamBaralho ) == LIS_CondRetListaNaoExiste )
		   return EMB_CondRetBaralhoNaoExiste ;

	   if( tamBaralho != TAM_BARALHO )
		   return EMB_CondRetTamanhoErrado;

	   if( LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta, &pListaDestino ) == LIS_CondRetFaltouMemoria )
		   return EMB_CondRetFaltouMemoria;

	   IrInicioLista( &pListaDestino );
	   
	   srand((unsigned) time(NULL));
	   
	   for(i = TAM_BARALHO; i > 0; i--)
	   {

		   LIS_tpCondRet condRetLis;
		   int inxCarta = rand() % i;							/* Sorteia uma carta */

		   IrInicioLista( &pBaralho->pCartas );					/* Inicio do baralho */
		   
		   if( LIS_AvancarElementoCorrente( pBaralho->pCartas, inxCarta ) != LIS_CondRetOK )		/* Vai para a carta sorteada */
				return EMB_CondRetTamanhoErrado;
		   
		   condRetLis = LIS_RemoverElemento( pBaralho->pCartas, &pListaDestino ) ;					/* Retira a carta sorteada e bota na pListaDestino */
		   if( condRetLis == LIS_CondRetListaVazia )							
				return EMB_CondRetBaralhoVazio;
		   else if( condRetLis == LIS_CondRetFaltouMemoria )
			    return EMB_CondRetFaltouMemoria;
	   }

	   /* Agora pListaDestino cont�m uma lista de cartas em uma ordem aleat�ria, e pBaralho->pCartas est� vazia */
	   LIS_DestruirLista( pBaralho->pCartas );	/* Destr�i a lista antiga */
	   pBaralho->pCartas = pListaDestino;		/* Baralho agora � composto pela lista embaralhada */

	   LIS_ObterTam( pBaralho->pCartas, &tamBaralho );
	   if( tamBaralho != TAM_BARALHO )			/* Verifica��o do tamanho do baralho */
		   return EMB_CondRetTamanhoErrado;

	   return EMB_CondRetOK;

   } /* Fim fun��o: EMB  &Embaralhar */


/***************************************************************************
*
*  $FC Fun��o: EMB  &Obter lista de cartas
*  ****/

   EMB_tpCondRet EMB_ObterListaCartas( EMB_tppBaralho pBaralho, LIS_tppLista *pLista )
   {
	  int tamBaralho = -1;

      if( pBaralho == NULL )
		  return EMB_CondRetBaralhoNaoExiste ;

	  LIS_ObterTam( pBaralho->pCartas, &tamBaralho ) ;

	  if( tamBaralho != TAM_BARALHO )
		  return EMB_CondRetTamanhoErrado ;

      *pLista = pBaralho->pCartas ;
	  
	  pBaralho->pCartas = NULL ;

	  return EMB_CondRetOK;

   } /* Fim fun��o: EMB  &Obter lista de cartas */

/********** Fim do m�dulo de implementa��o: EMB  Embaralhamento **********/