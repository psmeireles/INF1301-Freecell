/***************************************************************************
*  $MCI Módulo de implementação: TSEQORD Teste sequência ordenada
*
*  Arquivo gerado:              TestSeqOrd.c
*  Letras identificadoras:      TSEQORD
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: mcc
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxSeqOrd( int inxSeqOrd , int Modo )          ;
   static int ValidarInxListaCartas( int inxListaCartas, int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TSEQORD &Testar sequência ordenada
*
*  $ED Descrição da função
*     Podem ser criadas até 10 sequências ordenadas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de sequências ordenadas. Provoca vazamento de memória
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

      /* Efetuar reset de teste de sequência ordenada */

         if ( strcmp( ComandoTeste , RESET_SEQORD_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_SEQORD ; i++ )
            {
               vtSeqOrd[ i ] = NULL ;
			   vtListaCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de sequência ordeanda */

      /* Testar Criar sequência ordenada */

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

         } /* fim ativa: Testar Criar sequência ordenada */

      /* Testar Destruir sequência ordenada */

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

         } /* fim ativa: Testar Destruir sequência ordenada */

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
				"Condicao de retorno diferente da esperada na verificação sequencia ordenada" );

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

   } /* Fim função: TSEQVIS &Testar sequência visível */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TSELIS -Validar indice de sequencia ordenada
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

   } /* Fim função: TSEQORD -Validar indice de sequência ordenada */

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

   } /* Fim função: TSEQORD -Validar indice de lista de cartas */


/********** Fim do módulo de implementação: TSEQORD Teste sequência ordenada **********/
