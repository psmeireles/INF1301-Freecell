/***************************************************************************
*  $MCI M�dulo de implementa��o: TSEQORD Teste sequ�ncia ordenada
*
*  Arquivo gerado:              TestSeqOrd.c
*  Letras identificadoras:      TSEQORD
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: mcc
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "SequenciaOrdenada.h"


static const char RESET_SEQORD_CMD         [ ] = "=resetteste"         ;
static const char CRIAR_SEQORD_CMD         [ ] = "=criarseqord"        ;
static const char DESTRUIR_SEQORD_CMD      [ ] = "=destruirseqord"     ;
static const char INSERIR_CARTA_CMD        [ ] = "=inserircarta"       ;
static const char VERIFICA_SEQORD_CMD      [ ] = "=verifseqord"        ;
static const char CRIAR_LISTA_CARTAS_CMD   [ ] = "=criarlistacartas"   ;
static const char INS_CARTA_LISTA_CMD      [ ] = "=inserircartalista"  ;
static const char DESTRUIR_LISTA_CARTAS_CMD[ ] = "=destruirlistacartas";
static const char OBTER_LISTA_CARTAS_CMD   [ ] = "=obterlistacartas"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define IRRELEVANTE 2

#define DIM_VT_SEQORD  10
#define DIM_VALOR     100

#define DIM_VT_LISTA_CARTAS 10

SEQORD_tppSeqOrd   vtSeqOrd[ DIM_VT_SEQORD ]            ;
LIS_tppLista	   vtListaCartas[ DIM_VT_LISTA_CARTAS ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxSeqOrd( int inxSeqOrd , int Modo )          ;
   static int ValidarInxListaCartas( int inxListaCartas, int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TSEQORD &Testar sequ�ncia ordenada
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 sequ�ncias ordenadas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de sequ�ncias ordenadas. Provoca vazamento de mem�ria
*     =criarseqord                  inxSeqOrd      CondRetEsp
*     =destruirseqord               inxSeqOrd
*     =inserircarta                 inxSeqOrd      inxListaCartas CondRetEsp
*	  =criarlistacartas				inxListaCartas CondRetEsp
*	  =inserircartalista		    inxListaCartas StringCarta	  CondRetEsp
*	  =destruirlistacartas			inxListaCartas
*	  =obterlistacartas				inxSeqOrd	   inxListaCartas CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxSeqOrd   = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  inxListaCartas = -1 ;

      int CondRetObtida = -1 ;

	  CAR_tppCarta pCarta = NULL;

      int i = -1;

	  char StringCarta[3] ;
	  StringCarta[0] = 0;

      /* Efetuar reset de teste de sequ�ncia ordenada */

         if ( strcmp( ComandoTeste , RESET_SEQORD_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_SEQORD ; i++ )
            {
               vtSeqOrd[ i ] = NULL ;
			   vtListaCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de sequ�ncia ordeanda */

      /* Testar Criar sequ�ncia ordenada */

         else if ( strcmp( ComandoTeste , CRIAR_SEQORD_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxSeqOrd, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxSeqOrd( inxSeqOrd , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = SEQORD_CriarSeqOrd( &vtSeqOrd[ inxSeqOrd ] ) ;  

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar sequencia ordenada." );

         } /* fim ativa: Testar Criar sequ�ncia ordenada */

      /* Testar Destruir sequ�ncia ordenada */

         else if ( strcmp( ComandoTeste , DESTRUIR_SEQORD_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxSeqOrd ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxSeqOrd( inxSeqOrd , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            SEQORD_DestruirSeqOrd( vtSeqOrd[ inxSeqOrd ] ) ;
            vtSeqOrd[ inxSeqOrd ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir sequ�ncia ordenada */

      /* Testar inserir carta */

         else if ( strcmp( ComandoTeste , INSERIR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxSeqOrd , &inxListaCartas , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxSeqOrd( inxSeqOrd , IRRELEVANTE ))
			  || ( ! ValidarInxListaCartas( inxListaCartas, IRRELEVANTE)) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = SEQORD_InserirCarta( vtSeqOrd[ inxSeqOrd ],
												 vtListaCartas[ inxListaCartas ] );

			return TST_CompararInt( CondRetEsp, CondRetObtida,
				"Condicao de retorno diferente da esperada ao inserir carta na sequencia ordenada" );

         } /* fim ativa: Testar inserir carta */

      /* Testar verifica sequencia ordenada */
		 
		 else if ( strcmp( ComandoTeste , VERIFICA_SEQORD_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxSeqOrd , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxSeqOrd( inxSeqOrd , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = SEQORD_VerificaSeqOrd( vtSeqOrd[ inxSeqOrd ] );
										

			return TST_CompararInt( CondRetEsp, CondRetObtida,
				"Condicao de retorno diferente da esperada na verifica��o sequencia ordenada" );

         } /* fim ativa: Testar verificar sequencia ordenada */

      /* Testar criar lista de cartas */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxListaCartas, &CondRetEsp ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta ,
											&vtListaCartas[ inxListaCartas ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar lista de cartas." );

         } /* fim ativa: Testar criar lista de cartas */
		 
	  /* Testar Destruir lista de cartas */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxListaCartas ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxListaCartas( inxListaCartas , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListaCartas[ inxListaCartas ] ) ;
            vtListaCartas[ inxListaCartas ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista de cartas */

	  /* Testar obter lista de cartas */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxSeqOrd,
                       &inxListaCartas , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxListaCartas( inxListaCartas , IRRELEVANTE ))
			  || ( ! ValidarInxSeqOrd( inxSeqOrd, IRRELEVANTE ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = SEQORD_ObterListaCartas( vtSeqOrd[ inxSeqOrd ], &vtListaCartas[ inxListaCartas ] ) ;

            return TST_CompararInt(CondRetEsp, CondRetObtida,
								   "Condicao de retorno errada ao obter lista de cartas");

         } /* fim ativa: Testar obter lista de cartas */
	  
	  /* Testar inserir carta em uma lista de cartas */

         else if ( strcmp( ComandoTeste , INS_CARTA_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxListaCartas , StringCarta, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxListaCartas( inxListaCartas , IRRELEVANTE ))
			  || CAR_StringParaCarta( StringCarta, &pCarta ) != CAR_CondRetOK )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = LIS_InserirElementoApos( vtListaCartas[ inxListaCartas ] ,
													(void *) pCarta ) ;

            return TST_CompararInt(CondRetEsp, CondRetObtida,
								   "Condicao de retorno errada ao inserir carta na lista de cartas");

         } /* fim ativa: Testar inserir carta em uma lista de cartas */
		 
      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TSEQVIS &Testar sequ�ncia vis�vel */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TSELIS -Validar indice de sequencia ordenada
*
***********************************************************************/

   int ValidarInxSeqOrd( int inxSeqOrd , int Modo )
   {

      if ( ( inxSeqOrd <  0 )
        || ( inxSeqOrd >= DIM_VT_SEQORD ))
      {
         return FALSE ;
      } /* if */

	  if ( Modo == IRRELEVANTE )
		return TRUE;	   
      if ( Modo == VAZIO )
      {
         if ( vtSeqOrd[ inxSeqOrd ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtSeqOrd[ inxSeqOrd ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TSEQORD -Validar indice de sequ�ncia ordenada */

   int ValidarInxListaCartas( int inxListaCartas , int Modo )
   {

      if ( ( inxListaCartas <  0 )
        || ( inxListaCartas >= DIM_VT_LISTA_CARTAS ))
      {
         return FALSE ;
      } /* if */
	  
	  if ( Modo == IRRELEVANTE )
		return TRUE;         
      if ( Modo == VAZIO )
      {
         if ( vtListaCartas[ inxListaCartas ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListaCartas[ inxListaCartas ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TSEQORD -Validar indice de lista de cartas */


/********** Fim do m�dulo de implementa��o: TSEQORD Teste sequ�ncia ordenada **********/
