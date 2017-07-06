/***************************************************************************
*  $MCI módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>

#ifdef _DEBUG
	#include   "CESPDIN.H"
	#include   "GENERICO.h"
	#include   "CONTA.h"
	#include   "..\\Tabelas\\IdTiposEspaco.def"
#endif

#define LISTA_OWN
	#include "LISTA.h"
#undef LISTA_OWN


/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

		 LIS_tppLista pCabeca ;
			   /* Ponteiro para a cabeça da lista que possui o elemento */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

   static void TratadorNaoApontaParaCabeca( LIS_tppLista pLista ) ;

#ifdef _DEBUG

   static LIS_tpCondRet VerificarElem( tpElemLista *pElem ) ;

#endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  $FC Função: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( void   ( * ExcluirValor ) ( void * pDado ), LIS_tppLista *pLista )
   {
	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista" ) ;
      #endif

      *pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( *pLista == NULL )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_CriarLista: Faltou memoria" ) ;
		 #endif
         return LIS_CondRetFaltouMemoria ;
      } /* if */

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista: Nao faltou memoria" ) ;
      #endif

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_CriarLista: Definiu tipo do espaco" ) ;
			CED_DefinirTipoEspaco( *pLista, LIS_TipoEspacoCabeca ) ;
	  #endif

      LimparCabeca( *pLista ) ;

      (*pLista)->ExcluirValor = ExcluirValor ;

      return LIS_CondRetOK;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  $FC Função: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_DestruirLista" ) ;
      #endif

	  if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_DestruirLista: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetOK ;
	  }

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_DestruirLista: Lista nao e NULL" ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

	  return LIS_CondRetOK;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_EsvaziarLista" ) ;
      #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_EsvaziarLista: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_EsvaziarLista: Lista nao e NULL" ) ;
      #endif

      pElem = pLista->pOrigemLista ;

      while ( pElem != NULL )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_EsvaziarLista: Liberar elemento") ;
		 #endif
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_EsvaziarLista: Limpar cabeca" ) ;
      #endif
      LimparCabeca( pLista ) ;

	  return LIS_CondRetOK;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_InserirElementoAntes" ) ;
      #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_InserirElementoAntes: Lista nao e NULL" ) ;
      #endif

	  if( pLista->numElem != 0								/* Se a lista não está vazia */
		  && (pLista->pOrigemLista->pCabeca != pLista		/* e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista) )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

      /* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Faltou memoria ao criar elemento" ) ;
			#endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

		 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Nao faltou memoria ao criar elemento" ) ;
		 #endif

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Inserir elemento em lista vazia" ) ;
			#endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Inserir elemento em lista nao vazia" ) ;
			#endif

            if ( pLista->pElemCorr->pAnt != NULL )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes: Elemento corrente nao e o inicial" ) ;
			   #endif

               pElem->pAnt = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes: Elemento corrente e o inicial" ) ;
			   #endif

               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos" ) ;
	  #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Lista nao e NULL" ) ;
	  #endif

	  if( pLista->numElem != 0								/* Se a lista não está vazia */
		  && (pLista->pOrigemLista->pCabeca != pLista		/* e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista) )
	  {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

      /* Criar elemento a inserir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos: Faltou memoria ao criar elemento" ) ;
			#endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Nao faltou memoria ao criar elemento" ) ;
	 	 #endif

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos: Inserir elemento em lista vazia" ) ;
			#endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos: Inserir elemento em lista nao vazia" ) ;
			#endif
            if ( pLista->pElemCorr->pProx != NULL)
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoApos: Elemento corrente nao e final" ) ;
				#endif
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoApos: Elemento corrente e final" ) ;
				#endif
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ExcluirElemento" ) ;
	  #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ExcluirElemento: Lista nao e NULL" ) ;
	  #endif

      if ( pLista->numElem == 0 )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_ExcluirElemento: Lista vazia" ) ;
		 #endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  else if(pLista->pOrigemLista->pCabeca != pLista		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista)
	  {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ExcluirElemento: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ExcluirElemento: Lista nao esta vazia" ) ;
	  #endif

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente nao e o inicial" ) ;
			#endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente e o inicial" ) ;
			#endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente nao e o final" ) ;
			#endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente e o final" ) ;
			#endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  $FC Função: LIS  &Remover apenas um elemento
*  ****/

   LIS_tpCondRet LIS_RemoverElemento( LIS_tppLista pLista, LIS_tppLista *pCabeca )
   {

      tpElemLista * pElem ;
	  void * pValor ;

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_RemoverElemento" ) ;
	  #endif

      if( pLista == NULL || *pCabeca == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_RemoverElemento: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_RemoverElemento: Lista nao e NULL" ) ;
	  #endif

      if ( pLista->numElem == 0 )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_RemoverElemento: Lista vazia" ) ;
		 #endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  else if(pLista->pOrigemLista->pCabeca != pLista		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista)
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_RemoverElemento: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

	  #ifdef _DEBUG
			CNT_CONTAR( "LIS_RemoverElemento: Lista nao esta vazia" ) ;
	  #endif

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_RemoverElemento: Elemento corrente nao e o inicial" ) ;
			#endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } 
		 else 
		 {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_RemoverElemento: Elemento corrente e o inicial" ) ;
			#endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_RemoverElemento: Elemento corrente nao e o final" ) ;
			#endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } 
		 else
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_RemoverElemento: Elemento corrente e o final" ) ;
			#endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */
		 
		 pValor = pElem->pValor ;
		 
		 pElem->pValor = NULL ;
		 
		 LiberarElemento ( pLista, pElem ) ;
		 
		return LIS_InserirElementoAntes( *pCabeca, pValor ) ;

   } /* Fim função: LIS  &Remover elemento */


/***************************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void **pValor )
   {

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ObterValor" ) ;
	  #endif
	  
      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterValor: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ObterValor: Lista nao e NULL" ) ;
	  #endif

      if ( pLista->numElem == 0 )
      {
		 #ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterValor: Lista esta vazia" ) ;
		 #endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  else if(pLista->pOrigemLista->pCabeca != pLista		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista)
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterValor: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ObterValor: Lista nao esta vazia" ) ;
	  #endif

      *pValor = pLista->pElemCorr->pValor ;
	  
	  return LIS_CondRetOK;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */


/***************************************************************************
*
*  $FC Função: LIS  &Obter tamanho da lista
*  ****/

   LIS_tpCondRet LIS_ObterTam( LIS_tppLista pLista, int *pTamanho )
   {

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ObterTam" ) ;
	  #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterTam: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ObterTam: Lista nao e NULL" ) ;
	  #endif

	  if( pLista->numElem != 0								/* Se a lista não está vazia */
		  && (pLista->pOrigemLista->pCabeca != pLista		/* e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista) )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterTam: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

      *pTamanho = pLista->numElem;
	  
	  return LIS_CondRetOK;

   } /* Fim função: LIS  &Obter tamanho da lista*/

/***************************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*  ****/

   LIS_tpCondRet IrInicioLista( LIS_tppLista *pLista )
   {

      #ifdef _DEBUG
		CNT_CONTAR( "LIS_IrInicioLista" ) ;
	  #endif

      if( *pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_IrInicioLista: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_IrInicioLista: Lista nao e NULL" ) ;
	  #endif

	  if( (*pLista)->numElem != 0								/* Se a lista não está vazia */
		  && ((*pLista)->pOrigemLista->pCabeca != *pLista		/* e um dos ponteiros não aponta pra cabeça */
		   || (*pLista)->pElemCorr->pCabeca != *pLista
		   || (*pLista)->pFimLista->pCabeca != *pLista) )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_IrInicioLista: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( *pLista ) ;
	  }

      (*pLista)->pElemCorr = (*pLista)->pOrigemLista ;

	  return LIS_CondRetOK;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*  ****/

   LIS_tpCondRet IrFinalLista( LIS_tppLista *pLista )
   {

      #ifdef _DEBUG
		CNT_CONTAR( "LIS_IrFinalLista" ) ;
	  #endif

      if( *pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_IrFinalLista: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_IrFinalLista: Lista nao e NULL" ) ;
	  #endif

	  if( (*pLista)->numElem != 0								/* Se a lista não está vazia */
		  && ((*pLista)->pOrigemLista->pCabeca != *pLista		/* e um dos ponteiros não aponta pra cabeça */
		   || (*pLista)->pElemCorr->pCabeca != *pLista
		   || (*pLista)->pFimLista->pCabeca != *pLista) )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_IrFinalLista: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( *pLista ) ;
	  }

      (*pLista)->pElemCorr = (*pLista)->pFimLista ;

	  return LIS_CondRetOK;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;
	  tpElemLista * pElem ;
	  
	  
	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente" ) ;
	  #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista nao e NULL" ) ;
	  #endif

      /* Tratar lista vazia */

         if ( pLista->numElem == 0 )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista esta vazia" ) ;
			#endif
            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */
		 else if(pLista->pOrigemLista->pCabeca != pLista		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista)
		 {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Entrou no tratador" ) ;
			#endif
			TratadorNaoApontaParaCabeca( pLista ) ;
		 }

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista nao esta vazia" ) ;
		 #endif

      /* Tratar Avançar para frente */

         if ( numElem > 0 )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancar para frente" ) ;
			#endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancou elemento" ) ;
			   #endif

               if ( pElem == NULL )
               {
				  #ifdef _DEBUG
						CNT_CONTAR( "LIS_AvancarElementoCorrente: Chegou no final da lista" ) ;
				  #endif

                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Terminou de avancar elemento" ) ;
			#endif

            if ( pElem != NULL )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao chegou no final da lista" ) ;
			   #endif

               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Elemento final vira o corrente" ) ;
			#endif

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar Avançar para frente */

      /* Tratar Avançar para trás */

         else if ( numElem < 0 )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancar para tras" ) ;
			#endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Voltou elemento" ) ;
			   #endif

               if ( pElem == NULL )
               {
				  #ifdef _DEBUG
						CNT_CONTAR( "LIS_AvancarElementoCorrente: Chegou no inicio da lista" ) ;
				  #endif

                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Terminou de voltar elemento" ) ;
			#endif

            if ( pElem != NULL )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao chegou no inicio da lista" ) ;
			   #endif

               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Elemento inicial vira o corrente" ) ;
			#endif

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar Avançar para trás */

		 #ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao avanca elemento" ) ;
		 #endif

      /* Tratar não Avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( int (* CompararValor) (void * pDado1, void * pDado2),
									LIS_tppLista pLista , void * pValor )
   {

      tpElemLista * pElem ;

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor" ) ;
	  #endif

      if( pLista == NULL )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "LIS_ProcurarValor: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Lista nao e NULL" ) ;
	  #endif

      if ( pLista->numElem == 0 )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_ProcurarValor: Lista esta vazia" ) ;
		 #endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  else if(pLista->pOrigemLista->pCabeca != pLista		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista)
	  {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ProcurarValor: Entrou no tratador" ) ;
		  #endif

		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Lista nao esta vazia" ) ;
	  #endif

      for ( pElem  = pLista->pOrigemLista ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ProcurarValor: Procurar no elemento" ) ;
		  #endif

         if ( CompararValor( pElem->pValor, pValor ) == 0 )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_ProcurarValor: Achou" ) ;
			#endif

            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_ProcurarValor: Procurar no proximo" ) ;
		 #endif

      } /* for */

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Nao achou" ) ;
	  #endif

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


/***********************************************************************
*
*  $FC Função: LIS  &Retirar lista de elementos 
*  ****/

   LIS_tpCondRet LIS_RetirarListaElem(LIS_tppLista pLista, LIS_tppLista *pCabecaCorr) 
   {

	   tpElemLista *pCorr, *p;
	   int nElemCorr = 0;

	   #ifdef _DEBUG
			CNT_CONTAR( "LIS_RetirarListaElem" ) ;
	   #endif

	   if( pLista == NULL )
	   {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_RetirarListaElem: Lista e NULL" ) ;
		  #endif
		  return LIS_CondRetListaNaoExiste ;
	   }

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_RetirarListaElem: Lista nao e NULL" ) ;
	   #endif

       if ( pLista->numElem == 0 )
       {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_RetirarListaElem: Lista esta vazia" ) ;
		  #endif
          return LIS_CondRetListaVazia ;
       } /* if */
 	   else if(pLista->pOrigemLista->pCabeca != pLista		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista)
	   {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_RetirarListaElem: Entrou no tratador" ) ;
		  #endif
		  TratadorNaoApontaParaCabeca( pLista ) ;
	   }

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_RetirarListaElem: Lista nao esta vazia" ) ;
	   #endif

	   if( LIS_CriarLista(pLista->ExcluirValor, pCabecaCorr) == LIS_CondRetFaltouMemoria )	/* Lista que vai receber os elementos retirados */
	   {
		   #ifdef _DEBUG
			 CNT_CONTAR( "LIS_RetirarListaElem: Faltou memoria ao criar lista" ) ;
		   #endif
		   return LIS_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
			CNT_CONTAR( "LIS_RetirarListaElem: Nao faltou memoria ao criar lista" ) ;
	   #endif

	   for (p = pLista->pElemCorr; p != NULL; p = p->pProx) /* Contagem de elementos depois do elemento a ser retirado */
	   {
		   #ifdef _DEBUG
			 CNT_CONTAR( "LIS_RetirarListaElem: Contou elemento depois do que sera retirado" ) ;
		   #endif
		   nElemCorr++;
		   p->pCabeca = *pCabecaCorr ;
	   }

	   #ifdef _DEBUG
			CNT_CONTAR( "LIS_RetirarListaElem: Terminou de contar" ) ;
	   #endif

	   pCorr = pLista->pElemCorr;
	   
	   if(pCorr->pAnt != NULL)
	   {
		    #ifdef _DEBUG
				CNT_CONTAR( "LIS_RetirarListaElem: Elemento retirado nao e o inicial" ) ;
		    #endif

			pCorr->pAnt->pProx = NULL;	/* Desencadeia à direita */
	   
			pLista->pElemCorr = pCorr->pAnt;	
	   
			pLista->pFimLista = pLista->pElemCorr;
	   }
	   else
	   {
		    #ifdef _DEBUG
				CNT_CONTAR( "LIS_RetirarListaElem: Elemento retirado e o inicial" ) ;
		    #endif

			pLista->pOrigemLista = NULL;
			pLista->pFimLista = NULL;
			pLista->pElemCorr = NULL;
	   }

	   pLista->numElem -= nElemCorr;

	   #ifdef _DEBUG
				CNT_CONTAR( "LIS_RetirarListaElem: Desencadeia a esquerda" ) ;
	   #endif
		   
	   pCorr->pAnt = NULL;	/* Desencadeia à esquerda */
	    
	   
	   (*pCabecaCorr)->numElem = nElemCorr;
	   (*pCabecaCorr)->pOrigemLista = pCorr;
	   (*pCabecaCorr)->pElemCorr = pCorr;

	   for (p = (*pCabecaCorr)->pElemCorr; p->pProx != NULL; p = p->pProx) ;

	   (*pCabecaCorr)->pFimLista = p;

	   return LIS_CondRetOK;
   }/* Fim função: LIS  &Retirar lista de elementos */


/***********************************************************************
*
*  $FC Função: LIS  &Concatenar lista
*  ****/

   LIS_tpCondRet LIS_ConcatenarLista(LIS_tppLista pPrincipal, LIS_tppLista pConcatenada)
   {
	   
	   tpElemLista *p;

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_ConcatenarLista" ) ;
	   #endif

	   if( pPrincipal == NULL || pConcatenada == NULL )
	   {
		   #ifdef _DEBUG
			 CNT_CONTAR( "LIS_ConcatenarLista: Uma das listas e NULL" ) ;
		   #endif
		   return LIS_CondRetListaNaoExiste ;
	   }

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_ConcatenarLista: Nenhuma das listas e NULL" ) ;
	   #endif
		   
	   if (pConcatenada->numElem == 0)
	   {
		   #ifdef _DEBUG
			CNT_CONTAR( "LIS_ConcatenarLista: Lista concatenada esta vazia" ) ;
		   #endif

		   return LIS_CondRetListaVazia;
	   }
	   else if(pConcatenada->pOrigemLista->pCabeca != pConcatenada		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
		   || pConcatenada->pElemCorr->pCabeca != pConcatenada
		   || pConcatenada->pFimLista->pCabeca != pConcatenada)
	   {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ConcatenarLista: Lista concatenada entrou no tratador" ) ;
		  #endif

		  TratadorNaoApontaParaCabeca( pConcatenada ) ;
	   }

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_ConcatenarLista: Lista concatenada nao esta vazia" ) ;
	   #endif

	   if (pPrincipal->numElem == 0)
	   {
		   #ifdef _DEBUG
			 CNT_CONTAR( "LIS_ConcatenarLista: Lista principal esta vazia" ) ;
		   #endif

		   pPrincipal->pOrigemLista = pConcatenada->pOrigemLista;
		   pPrincipal->pElemCorr = pConcatenada->pElemCorr;
	   }
	   else {

		   #ifdef _DEBUG
			 CNT_CONTAR( "LIS_ConcatenarLista: Lista principal nao esta vazia" ) ;
		   #endif

		   if(pPrincipal->pOrigemLista->pCabeca != pPrincipal		/* Se a lista não está vazia e um dos ponteiros não aponta pra cabeça */
			   || pPrincipal->pElemCorr->pCabeca != pPrincipal
			   || pPrincipal->pFimLista->pCabeca != pPrincipal)
		   {
			   #ifdef _DEBUG
				  CNT_CONTAR( "LIS_ConcatenarLista: Lista principal entrou no tratador" ) ;
			   #endif

			   TratadorNaoApontaParaCabeca( pPrincipal ) ;
		   }

		   pPrincipal->pFimLista->pProx = pConcatenada->pOrigemLista;		/* O próximo elemento do final da principal é o primeiro da concatenada */
		   pConcatenada->pOrigemLista->pAnt = pPrincipal->pFimLista;		/* O anterior ao primeiro da concatenada é o final da principal */
	   }

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_ConcatenarLista: Atualiza lista principal e libera a concatenada" ) ;
	   #endif

	   pPrincipal->numElem += pConcatenada->numElem;					/* Número de elementos da principal é somado ao da concatenada */
	   pPrincipal->pFimLista = pConcatenada->pFimLista;					/* Fim da lista principal é o fim da lista conctatenada */
	   

	   /* Mudando as cabeças dos elementos */
	   for( p = pPrincipal->pOrigemLista; p != NULL; p = p->pProx )
	   {
		   #ifdef _DEBUG
			CNT_CONTAR( "LIS_ConcatenarLista: Mudou cabeca do elemento" ) ;
		   #endif

		   p->pCabeca = pPrincipal ;
	   }

	   #ifdef _DEBUG
		 CNT_CONTAR( "LIS_ConcatenarLista: Terminou de mudar as cabecas dos elementos concatenados" ) ;
	   #endif
		
	   LimparCabeca( pConcatenada ) ;
	   LIS_DestruirLista( pConcatenada ) ;
	   
	   return LIS_CondRetOK;
   }


#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar uma lista
*  ****/

   LIS_tpCondRet LIS_VerificarLista( void * pListaParm )
   {

      LIS_tppLista pLista = NULL ;

	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_VerificarLista" ) ;
	  #endif

      if ( LIS_VerificarCabeca( pListaParm ) != LIS_CondRetOK )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarLista: Cabeca esta errada" ) ;
		 #endif

         return LIS_CondRetEstruturaErrada ;
      } /* if */

	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_VerificarLista: Cabeca esta correta" ) ;
	  #endif

      CED_MarcarEspacoAtivo( pListaParm ) ;

      pLista = ( LIS_tppLista ) ( pListaParm ) ;

      if(  VerificarElem( pLista->pOrigemLista ) != LIS_CondRetOK
		|| VerificarElem( pLista->pElemCorr ) != LIS_CondRetOK
		|| VerificarElem( pLista->pFimLista ) != LIS_CondRetOK )
	  {
		#ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarLista: Ponteiros da cabeca estao errados" ) ;
		#endif

		return LIS_CondRetEstruturaErrada ;
	  }

	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_VerificarLista: Lista esta correta" ) ;
	  #endif
	  
	  return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar uma lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar cabeça da lista
*  ****/

   LIS_tpCondRet LIS_VerificarCabeca( void * pCabecaParm )
   {

      LIS_tppLista pLista = NULL ;

	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_VerificarCabeca" ) ;
	  #endif

      /* Verifica o tipo do espaço */

         if ( pCabecaParm == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Tentou verificar cabeca inexistente" ) ;
			#endif

            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            return LIS_CondRetEstruturaErrada ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Cabeca nao e NULL" ) ;
		 #endif

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Controle de espaco acusou erro" ) ;
			#endif

            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetEstruturaErrada ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Controle de espaco nao acusou erro" ) ;
		 #endif

         if ( TST_CompararInt( LIS_TipoEspacoCabeca , CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espaço de dados não é cabeça de árvore." ) != TST_CondRetOK )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Tipo do espaco esta errado" ) ;
			#endif

            return LIS_CondRetEstruturaErrada ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Tipo do espaco esta certo" ) ;
		 #endif

         pLista = ( LIS_tppLista )( pCabecaParm ) ;

      /* Verifica elemento origem */

         if ( pLista->pOrigemLista != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista tem origem nao NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( pCabecaParm , pLista->pOrigemLista->pCabeca ,
                 "Origem não aponta para cabeça." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Origem nao aponta para a cabeca" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Origem aponta para a cabeca" ) ;
			#endif
         } 
		 else
		 {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista tem origem NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( NULL , pLista->pElemCorr ,
                 "Origem vazia tem nó corrente não NULL." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Origem vazia tem elemento corrente nao NULL" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Origem vazia tem elemento corrente vazio" ) ;
			#endif
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Elemento origem esta correto" ) ;
		 #endif

      /* Verifica elemento corrente */

         if ( pLista->pElemCorr != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista tem elemento corrente nao NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( pCabecaParm , pLista->pElemCorr->pCabeca ,
                 "Elemento corrente não aponta para cabeça." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Elemento corrente nao aponta para a cabeca" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Elemento corrente aponta para a cabeca" ) ;
			#endif
         }
		 else 
		 {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista tem elemento corrente NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( NULL , pLista->pOrigemLista ,
                 "Lista não vazia tem origem NULL." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Lista nao vazia tem origem NULL" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista nao vazia tem origem nao NULL" ) ;
			#endif
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Elemento corrente esta correto" ) ;
		 #endif

	  /* Verifica elemento final */

		 if ( pLista->pFimLista != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista tem elemento final nao NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( pCabecaParm , pLista->pFimLista->pCabeca ,
                 "Elemento final não aponta para cabeça." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Elemento final nao aponta para a cabeca" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Elemento final aponta para a cabeca" ) ;
			#endif
         }
		 else 
		 {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Lista tem elemento final NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( NULL , pLista->pElemCorr ,
                 "Final vazio tem elemento corrente não NULL." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Final vazio tem elemento corrente nao NULL" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Final vazio tem elemento corrente NULL" ) ;
			#endif
         } /* if */

	  #ifdef _DEBUG
		CNT_CONTAR( "LIS_VerificarCabeca: Cabeca esta correta" ) ;
	  #endif

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar cabeça de lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar um elemento da lista
*  ****/

   LIS_tpCondRet LIS_VerificarElem( void * pElemParm )
   {

      tpElemLista *pElem   = NULL ;
      LIS_tppLista pLista = NULL ;

	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_VerificarElem" ) ;
	  #endif

      /* Verificar se é elemento de lista */

         if ( pElemParm == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Tentou verificar elemento inexistente" ) ;
			#endif

            TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
            return LIS_CondRetEstruturaErrada ;

         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Elemento verificado nao e NULL" ) ;
		 #endif

         if ( ! CED_VerificarEspaco( pElemParm , NULL ))
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Controle de espaco acusou erro" ) ;
			#endif

            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetEstruturaErrada ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Controle de espaco nao acusou erro" ) ;
		 #endif

         if ( TST_CompararInt( LIS_TipoEspacoElem , CED_ObterTipoEspaco( pElemParm ) ,
              "Tipo do espaço de dados não é elemento de lista." ) != TST_CondRetOK )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Tipo do espaco nao e elemento de lista" ) ;
			#endif

            return LIS_CondRetEstruturaErrada ;
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Tipo do espaco esta correto" ) ;
		 #endif

         pElem  = ( tpElemLista * )( pElemParm ) ;
         pLista = pElem->pCabeca ;

      /* Verificar elemento anterior */

         if ( pElem->pAnt != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Elemento anterior nao e NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( pElem , pElem->pAnt->pProx,
                 "O próximo do elemento anterior não é este elemento." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Proximo elemento do anterior nao e este elemento" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Este elemento e o proximo elemento do anterior " ) ;
			#endif

            if ( TST_CompararPonteiro( pLista , pElem->pAnt->pCabeca ,
                 "Elemento anterior não pertence à mesma lista." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Elemento anterior nao pertence a mesma lista" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Elemento anterior pertence a mesma lista" ) ;
			#endif
         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Elemento anterior esta correto" ) ;
		 #endif

      /* Verificar elemento seguinte */

         if ( pElem->pProx != NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Elemento seguinte nao e NULL" ) ;
			#endif

            if ( TST_CompararPonteiro( pElem , pElem->pProx->pAnt ,
                 "O anterior do próximo elemento não é este elemento." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: O anterior do proximo elemento nao e este elemento" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Este elemento e o anterior do proximo" ) ;
			#endif

            if ( TST_CompararPonteiro( pLista, pElem->pProx->pCabeca ,
                 "Próximo elemento não pertence à mesma lista." ) != TST_CondRetOK )
            {
			   #ifdef _DEBUG
					CNT_CONTAR( "LIS_VerificarCabeca: Proximo elemento nao pertence a mesma lista" ) ;
			   #endif

               return LIS_CondRetEstruturaErrada ;
            } /* if */

			#ifdef _DEBUG
				CNT_CONTAR( "LIS_VerificarCabeca: Proximo elemento pertence a mesma lista" ) ;
			#endif

         } /* if */

		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_VerificarCabeca: Elemento verificado esta correto" ) ;
		 #endif

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar um elemento da lista */

#endif


   #ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Deturpar lista
*  ****/

   void LIS_Deturpar( void * pListaParm ,
                      LIS_tpModosDeturpacao ModoDeturpar )
   {

      LIS_tppLista pLista = NULL ;

	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_DeturparLista" ) ;
	  #endif

      if ( pListaParm == NULL )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_DeturparLista: Lista e NULL" ) ;
		 #endif
         return ;
      } /* if */
	  
	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_DeturparLista: Lista nao e NULL" ) ;
	  #endif

      pLista = ( LIS_tppLista ) ( pListaParm ) ;

      switch ( ModoDeturpar ) {

      /* Modifica o tipo da cabeça */

         case DeturpaTipoCabeca :
         {
			#ifdef _DEBUG
		       CNT_CONTAR( "LIS_DeturparLista: Deturpou tipo cabeca" ) ;
	        #endif

            CED_DefinirTipoEspaco( pLista , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } /* fim ativa: Modifica o tipo da cabeça */

      /*Anula ponteiro origem*/

         case DeturpaOrigemNulo :
         {

			#ifdef _DEBUG
		       CNT_CONTAR( "LIS_DeturparLista: Deturpou elemento origem" ) ;
	        #endif

			pLista->pOrigemLista = NULL;

            break ;

         } /* fim ativa: Anula ponteiro origem */

      /* Anula ponteiro corrente */

         case DeturpaCorrenteNulo :
         {
			#ifdef _DEBUG
		       CNT_CONTAR( "LIS_DeturparLista: Deturpou elemento corrente" ) ;
	        #endif

            pLista->pElemCorr = NULL;

            break ;

         } /* fim ativa: Anula ponteiro corrente */

      }
   } /* Fim função: ARV  &Deturpar árvore */

#endif

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

	  #ifdef _DEBUG
		 CNT_CONTAR( "LiberarElemento" ) ;
	  #endif
		 
	  if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento: Excluiu valor" ) ;
		 #endif

         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

	  #ifdef _DEBUG
		 CNT_CONTAR( "LiberarElemento: Liberou elemento" ) ;
	  #endif

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

	  #ifdef _DEBUG
		 CNT_CONTAR( "CriarElemento" ) ;
	  #endif

	  if( pLista->numElem != 0								/* Se a lista não está vazia */
		  && (pLista->pOrigemLista->pCabeca != pLista		/* e um dos ponteiros não aponta pra cabeça */
		   || pLista->pElemCorr->pCabeca != pLista
		   || pLista->pFimLista->pCabeca != pLista) )
	  {
		  #ifdef _DEBUG
				CNT_CONTAR( "CriarElemento: Entrou no tratador" ) ;
		  #endif

		  TratadorNaoApontaParaCabeca( pLista ) ;
	  }

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
		 #ifdef _DEBUG
				CNT_CONTAR( "CriarElemento: Faltou memoria ao criar elemento" ) ;
		 #endif

         return NULL ;
      } /* if */

	  #ifdef _DEBUG
			CNT_CONTAR( "CriarElemento: Criou elemento com sucesso" ) ;
	  #endif

	  #ifdef _DEBUG
			CED_DefinirTipoEspaco( pElem, LIS_TipoEspacoElem ) ;
	  #endif
	
      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;
	  pElem->pCabeca = pLista ;
	  
      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
	  #ifdef _DEBUG
		CNT_CONTAR( "LimparCabeca" ) ;
	  #endif

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */


/***********************************************************************
*
*  $FC Função: Tratador para elemento não apontando para cabeça da lista
*
*  $ED Descrição da função:
*	  Trata o caso de ou a origem de uma lista, ou o elemento corrente, ou
* o elemento final não apontar para a cabeça certa.
*	  Recebe um ponteiro para uma lista e faz os três elementos apontarem
* para a cabeça da lista.
*
*  $EP Parâmetros:
*	  $P pLista	- ponteiro para a lista 
*		
************************************************************************/

   void TratadorNaoApontaParaCabeca( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
			CNT_CONTAR( "TratadorNaoApontaParaCabeca" ) ;
	   #endif

	   pLista->pOrigemLista->pCabeca = pLista ;
	   pLista->pElemCorr->pCabeca = pLista ;
	   pLista->pFimLista->pCabeca = pLista ;
   }


/***********************************************************************
*
*  $FC Função: LIS  -Explorar verificando os elementos de uma lista
*
*  $ED Descrição da função
*     Percorre recursivamente a lista verificando os elementos à medida que forem
*     visitados. Caso seja encontrada alguma falha, a verificação será
*     suspensa. Portanto, no caso de falha, é possível que nem todos
*     os elementos da lista sejam visitados.
*
***********************************************************************/
#ifdef _DEBUG

   LIS_tpCondRet VerificarElem( tpElemLista *pElem )
   {

	  LIS_tpCondRet CondErro = LIS_CondRetOK ;

	  #ifdef _DEBUG
		CNT_CONTAR( "VerificarElem" ) ;
	  #endif

      if ( pElem == NULL )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "VerificarElem: Elemento verificado e NULL" ) ;
		 #endif

         return LIS_CondRetOK ;
      } /* if */

	  #ifdef _DEBUG
		CNT_CONTAR( "VerificarElem: Elemento verificado nao e NULL" ) ;
	  #endif

      CED_MarcarEspacoAtivo( pElem ) ;

      CondErro = LIS_VerificarElem( pElem ) ;

      if ( CondErro == LIS_CondRetOK )
      {
		 #ifdef _DEBUG
			CNT_CONTAR( "VerificarElem: Elemento correto. Verifica proximo." ) ;
		 #endif

         CondErro = VerificarElem( pElem->pAnt ) ;
      } /* if */

	  #ifdef _DEBUG
		CNT_CONTAR( "VerificarElem: Elemento incorreto" ) ;
	  #endif

      return CondErro ;

   } /* Fim função: LIS  -Explorar verificando os elementos de uma lista */

#endif

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

