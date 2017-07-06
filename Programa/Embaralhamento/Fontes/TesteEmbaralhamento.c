/***************************************************************************
*  $MCI Módulo de implementação: TEMB Teste embaralhamento
*
*  Arquivo gerado:              TesteEmbaralhamento.c
*  Letras identificadoras:      TEMB
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       psm   01/mai/2017 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Embaralhamento.h"
#include	"Lista.h"


static const char RESET_EMB_CMD        [ ] = "=resetteste"       ;
static const char CRIAR_BARALHO_CMD    [ ] = "=criarbaralho"     ;
static const char DESTRUIR_BARALHO_CMD [ ] = "=destruirbaralho"  ;
static const char EMBARALHAR_CMD       [ ] = "=embaralhar"		 ;
static const char OBTER_LISTA_CMD      [ ] = "=obterlistacartas" ;
static const char OBTER_TAM_CMD        [ ] = "=obtertam"         ;
static const char DESTRUIR_LISTA_CMD   [ ] = "=destruirlista"    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define IRRELEVANTE 2

#define DIM_VT_BARALHO   10
#define DIM_VT_LISTA	 10
#define DIM_VALOR     100

EMB_tppBaralho   vtBaralhos[ DIM_VT_BARALHO ] ;
LIS_tppLista	 vtListas[ DIM_VT_LISTA ]   ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxBaralho( int inxBaralho , int Modo ) ;
   static int ValidarInxLista( int inxLista , int Modo )     ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TEMB &Testar embaralhamento
*
*  $ED Descrição da função
*     Podem ser criadas até 10 baralhos, identificados pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarbaralho                 inxBaralho  CondRetEsp
*     =destruirbaralho              inxBaralho  
*     =embaralhar					inxBaralho  CondRetEsp
*	  =obterlistacartas				inxBaralho  inxLista CondRetEsp
*	  =obtertam						inxBaralho  ValEsp   CondRetEsp
*	  =destruirlista				inxLista	
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxBaralho  = -1 ,
		  inxLista    = -1 ,
          numLidos    = -1 ,
          CondRetEsp  = -1 ,
		  tamLista    = -1 ;

      int CondRetObtida ;

	  char   StringDado[  DIM_VALOR ] ;

      int ValEsp = -1 ;

      int i ;


      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de embaralhamento */

         if ( strcmp( ComandoTeste , RESET_EMB_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_BARALHO ; i++ )
            {
               vtBaralhos[ i ] = NULL ;
			   vtListas[ i ]   = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de embaralhamento */

      /* Testar Criar baralho*/

         else if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxBaralho, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxBaralho( inxBaralho , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = EMB_CriarBaralho( &vtBaralhos[ inxBaralho ] ) ;

            return TST_CompararInt( CondRetEsp, CondRetObtida,
               "Condicao de retorno errada ao criar baralho."  ) ;

         } /* fim ativa: Testar Criar baralho */

      /* Testar Destruir baralho */

         else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxBaralho ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxBaralho( inxBaralho , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            EMB_DestruirBaralho( vtBaralhos[ inxBaralho ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir baralho*/

      /* Testar Embaralhar */

         else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxBaralho, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxBaralho( inxBaralho , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = EMB_Embaralhar( vtBaralhos[ inxBaralho ] ) ;
            
            return TST_CompararInt( CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao embaralhar" ) ;

         } /* fim ativa: Testar Embaralhar */

	   /* Testar Obter lista de cartas */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                               &inxBaralho, &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxBaralho( inxBaralho , IRRELEVANTE ))
			  || ( ! ValidarInxLista( inxLista , VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = EMB_ObterListaCartas( vtBaralhos[ inxBaralho ], &vtListas[ inxLista ] ) ;
            
            return TST_CompararInt( CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao obter lista de cartas" ) ;

         } /* fim ativa: Testar Obter lista de cartas */

	   /* Testar obter tamanho da lista */

         else if ( strcmp( ComandoTeste , OBTER_TAM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &ValEsp, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = LIS_ObterTam( vtListas[ inxLista ],  &tamLista ) ;
            
			if ( CondRetEsp == LIS_CondRetListaNaoExiste )
            {
               return TST_CompararInt( CondRetEsp , CondRetObtida ,
											   "Lista não deveria existir." ) ;
            } /* if */
			
            if(tamLista != ValEsp)
               return TST_CompararInt( ValEsp , tamLista ,
									  "Tamanho da lista errado" ) ;

            return TST_CompararInt(CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao obter tamanho") ;

         } /* fim ativa: Testar obter tamanho da lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TEMB &Testar baralho */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TEMB -Validar indice do baralho
*
***********************************************************************/

   int ValidarInxBaralho( int inxBaralho , int Modo )
   {

      if ( ( inxBaralho <  0 )
        || ( inxBaralho >= DIM_VT_BARALHO ))
      {
         return FALSE ;
      } /* if */
      
	  if( Modo == IRRELEVANTE )
		return TRUE ;
      if ( Modo == VAZIO )
      {
         if ( vtBaralhos[ inxBaralho ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtBaralhos[ inxBaralho ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TEMB -Validar indice do baralho */

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice da lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
	  if( Modo == IRRELEVANTE )
		return TRUE ;
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TEMB -Validar indice da lista */

/********** Fim do módulo de implementação: TEMB Teste baralho **********/