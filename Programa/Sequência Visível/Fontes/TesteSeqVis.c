/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste sequência visível
*
*  Arquivo gerado:              TestSeqVis.c
*  Letras identificadoras:      TSEQVIS
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

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "SequenciaVisivel.h"


static const char RESET_SEQVIS_CMD         [ ] = "=resetteste"          ;
static const char CRIAR_SEQVIS_CMD         [ ] = "=criarseqvis"         ;
static const char DESTRUIR_SEQVIS_CMD      [ ] = "=destruirseqvis"      ;
static const char INS_CARTA_RESTR_CMD      [ ] = "=inscartarestr"       ;
static const char INS_CARTA_SEM_RESTR_CMD  [ ] = "=inscartasemrestr"    ;
static const char REMOVER_CARTA_CMD        [ ] = "=removercarta"        ;
static const char CRIAR_LISTA_CARTAS_CMD   [ ] = "=criarlistacartas"    ;
static const char INS_CARTA_LISTA_CMD      [ ] = "=inscartalista"       ;
static const char DESTRUIR_LISTA_CARTAS_CMD[ ] = "=destruirlistacartas" ;
static const char OBTER_LISTA_CARTAS_CMD   [ ] = "=obterlistacartas"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define IRRELEVANTE 2

#define DIM_VT_SEQVIS  10
#define DIM_VALOR     100

#define DIM_VT_LISTA_CARTAS 11

SEQVIS_tppSeqVis   vtSeqVis[ DIM_VT_SEQVIS ]            ;
LIS_tppLista	   vtListaCartas[ DIM_VT_LISTA_CARTAS ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxSeqVis( int inxSeqVis , int Modo )          ;
   static int ValidarInxListaCartas( int inxListaCartas, int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TSEQVIS &Testar sequência visível
*
*  $ED Descrição da função
*     Podem ser criadas até 10 sequências visíveis, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de sequências visíveis. Provoca vazamento de memória
*     =criarseqvis                  inxSeqVis      CondRetEsp
*     =destruirseqvis               inxSeqVis
*     =inscartarestr                inxSeqVis      inxListaCartas  CondRetEsp
*     =inscartasemrestr             inxSeqVis      StringCarta	   CondRetEsp
*     =removercarta	                inxSeqVis      StringCarta	   inxListaCartas	CondRetEsp 
*	  =criarlistacartas				inxListaCartas CondRetEsp
*	  =inscartalista				inxListaCartas StringCarta	   CondRetEsp
*	  =destruirlistacartas			inxListaCartas
*	  =obterlistacartas				inxSeqVis	   inxListaCartas  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxSeqVis   = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  inxListaCartas = -1 ;


      int CondRetObtida ;

	  CAR_tppCarta pCarta ;

      int i = -1;

      char StringCarta[ 2 ] ;
	  StringCarta[ 0 ] = 0 ;
	  
	  LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta, &vtListaCartas[10] ) ;

      /* Efetuar reset de teste de sequência visível */

         if ( strcmp( ComandoTeste , RESET_SEQVIS_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_SEQVIS ; i++ )
            {
               vtSeqVis[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de sequência visível */

      /* Testar Criar srquência visível */

         else if ( strcmp( ComandoTeste , CRIAR_SEQVIS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxSeqVis, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxSeqVis( inxSeqVis , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = SEQVIS_CriarSeqVis( &vtSeqVis[ inxSeqVis ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar sequencia visivel." );

         } /* fim ativa: Testar Criar sequência visível */

      /* Testar Destruir sequência visível */

         else if ( strcmp( ComandoTeste , DESTRUIR_SEQVIS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxSeqVis ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxSeqVis( inxSeqVis , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            SEQVIS_DestruirSeqVis( vtSeqVis[ inxSeqVis ] ) ;
            vtSeqVis[ inxSeqVis ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir sequência visível */

      /* Testar inserir carta com restrição de naipe e número */

         else if ( strcmp( ComandoTeste , INS_CARTA_RESTR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxSeqVis , &inxListaCartas , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxSeqVis( inxSeqVis , IRRELEVANTE ))
			  || ( ! ValidarInxListaCartas( inxListaCartas, IRRELEVANTE)) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = SEQVIS_InserirCartaRestr( vtSeqVis[ inxSeqVis ],
													  vtListaCartas[ inxListaCartas ] );

			return TST_CompararInt( CondRetEsp, CondRetObtida,
				"Condicao de retorno diferente da esperada na insercao com restricao" );

         } /* fim ativa: Testar inserir carta com restrição de naipe e número */

      /* Testar inserir carta sem restrição de naipe e número */

         else if ( strcmp( ComandoTeste , INS_CARTA_SEM_RESTR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxSeqVis , StringCarta , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxSeqVis( inxSeqVis , IRRELEVANTE ))
			  || CAR_StringParaCarta( StringCarta, &pCarta ) == CAR_CondRetCartaNaoExiste )
            {
               return TST_CondRetParm ;
            } /* if */
			
			LIS_EsvaziarLista( vtListaCartas[ 10 ] ) ;
			LIS_InserirElementoApos( vtListaCartas[ 10 ], pCarta ) ;

            CondRetObtida = SEQVIS_InserirCartaSemRestr( vtSeqVis[ inxSeqVis ], vtListaCartas[ 10 ]);														 

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
									"Condicao de retorno errada ao inserir carta sem restricao." ) ;

         } /* fim ativa: Testar inserir carta sem restrição de naipe e número */

      /* Testar remover carta da sequência visível */

         else if ( strcmp( ComandoTeste , REMOVER_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isii" ,
                  &inxSeqVis , StringCarta, &inxListaCartas, &CondRetEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxSeqVis( inxSeqVis , IRRELEVANTE ))
			  || CAR_StringParaCarta( StringCarta, &pCarta ) == CAR_CondRetCartaNaoExiste )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = SEQVIS_RemoverCarta( vtSeqVis[ inxSeqVis ], pCarta,
												&vtListaCartas[ inxListaCartas ] );

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
									"Condição de retorno errada ao remover carta."   ) ;

         } /* fim ativa: Testar remover carta da sequência visível */

      /* Testar criar lista de cartas */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxListaCartas, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxListaCartas( inxListaCartas , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta ,
											&vtListaCartas[ inxListaCartas ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar lista de cartas." );

         } /* fim ativa: Testar criar lista de cartas */

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

            numLidos = LER_LerParametros( "iii" , &inxSeqVis,
                       &inxListaCartas , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxListaCartas( inxListaCartas , IRRELEVANTE ))
			  || ( ! ValidarInxSeqVis( inxSeqVis, IRRELEVANTE ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = SEQVIS_ObterListaCartas( vtSeqVis[ inxSeqVis ], &vtListaCartas[ inxListaCartas ] ) ;

            return TST_CompararInt(CondRetEsp, CondRetObtida,
								   "Condicao de retorno errada ao obter lista de cartas");

         } /* fim ativa: Testar obter lista de cartas */
		 
      return TST_CondRetNaoConhec ;

   } /* Fim função: TSEQVIS &Testar sequência visível */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxSeqVis( int inxSeqVis , int Modo )
   {

      if ( ( inxSeqVis <  0 )
        || ( inxSeqVis >= DIM_VT_SEQVIS ))
      {
         return FALSE ;
      } /* if */
         
	  if ( Modo == IRRELEVANTE )
		return TRUE;     		 
      if ( Modo == VAZIO )
      {
         if ( vtSeqVis[ inxSeqVis ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtSeqVis[ inxSeqVis ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TSEQVIS -Validar indice de sequência visível */

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

   } /* Fim função: TSEQVIS -Validar indice de lista de cartas */


/********** Fim do módulo de implementação: TSEQVIS Teste sequência visível **********/

