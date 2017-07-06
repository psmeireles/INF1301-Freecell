/***************************************************************************
*  $MCI M�dulo de implementa��o: TESPEXT Teste Espa�os Extras
*
*  Arquivo gerado:              TestEspExt.c
*  Letras identificadoras:      TESPEXT
*
*  Projeto: INF 1301 / Free Cel
*  Gestor:  LES/DI/PUC-Rio
*  Autores: psm
*			rta
*			mcc
*
*  $HA Hist�rico de evolu��o:
*     Vers�o	  Autor			 Data     Observa��es
*     1       rta, mcc, psm   07/mai/2017 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "EspacosExtras.h"


static const char RESET_ESPEXT_CMD			   [ ] = "=resetteste"           ;
static const char CRIAR_ESPEXT_CMD			   [ ] = "=criarespext"          ;
static const char OBTER_NUM_ESP_EXT_VAZIOS_CMD [ ] = "=obternumespextvazios" ;
static const char DESTRUIR_ESPEXT_CMD		   [ ] = "=destruirespext"       ;
static const char INS_CARTA_CMD				   [ ] = "=inscarta"             ;
static const char REMOVER_CARTA_CMD			   [ ] = "=removercarta"         ;
static const char CRIAR_LISTA_CARTAS_CMD	   [ ] = "=criarlistacartas"     ;
static const char INS_CARTA_LISTA_CMD		   [ ] = "=inscartalista"        ;
static const char DESTRUIR_LISTA_CARTAS_CMD	   [ ] = "=destruirlistacartas"  ;
static const char OBTER_LISTA_CARTAS_CMD   	   [ ] = "=obterlistacartas"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define IRRELEVANTE 2

#define DIM_VALOR     100

#define DIM_VT_LISTA_CARTAS 10

ESPEXT_tppEspExt   pEspExt ;
LIS_tppLista	   vtListaCartas[ DIM_VT_LISTA_CARTAS ] ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int ValidarInxListaCartas( int inxListaCartas, int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TESPEXT &Testar espa�os extras
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 4 espa�os extras, identificadas pelos �ndices 0 a 4
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula os espa�os extras. Provoca vazamento de mem�ria
*     =criarespext                  CondRetEsp
*	  =obternumespextvazios			ValEsp
*     =destruirespext           
*     =inscarta                     inxListaCartas CondRetEsp
*     =removercarta	                StringCarta	   inxListaCartas CondRetEsp 
*	  =criarlistacartas				inxListaCartas CondRetEsp
*	  =inscartalista				inxListaCartas StringCarta    CondRetEsp
*	  =destruirlistacartas			inxListaCartas
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos   = -1 ,
          CondRetEsp = -1 ,
		  inxListaCartas = -1 ,
		  qtdVazios = -1 ;

      int CondRetObtida = -1 ;
	  int i = 0;

	  CAR_tppCarta pCarta = NULL ;
      int ValEsp = -1 ;

      char StringCarta[ 3 ] ;
	  StringCarta[0] = 0 ;
	 

      /* Efetuar reset de teste de espa�os extras */

         if ( strcmp( ComandoTeste , RESET_ESPEXT_CMD ) == 0 )
         {

			pEspExt = NULL ;
			for( i = 0 ; i < DIM_VT_LISTA_CARTAS ; i++ )
            {
			   vtListaCartas[ i ] = NULL ;
            } /* for */
            
            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de espa�os extras */

      /* Testar Criar espa�os extras */

         else if ( strcmp( ComandoTeste , CRIAR_ESPEXT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if ( ( numLidos != 1 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = ESPEXT_CriarEspExt( &pEspExt ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar sequencia visivel." );

         } /* fim ativa: Testar Criar espa�os extras */

      /* Testar Obter n�mero de espa�os extras vazios */

         else if ( strcmp( ComandoTeste , OBTER_NUM_ESP_EXT_VAZIOS_CMD ) == 0 )
         {
			
			numLidos = LER_LerParametros( "i", &ValEsp ) ;

            if ( ( numLidos != 1 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            ESPEXT_ObterNumEspExtVazios( pEspExt, &qtdVazios ) ;
            			
            return TST_CompararInt( ValEsp , qtdVazios ,
                     "Quantidade de espacos extras vazios diferente do esperado." ); ;

         } /* fim ativa: Testar Destruir Espaco Extra */

      /* Testar Destruir espaco extra */

         else if ( strcmp( ComandoTeste , DESTRUIR_ESPEXT_CMD ) == 0 )
         {

            ESPEXT_DestruirEspExt( pEspExt ) ;
            pEspExt = NULL ;
			
            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir Espaco Extra */

      /* Testar inserir carta no espa�o extra */

         else if ( strcmp( ComandoTeste , INS_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &inxListaCartas , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
			  || ( ! ValidarInxListaCartas( inxListaCartas, IRRELEVANTE)) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = ESPEXT_InserirCarta( pEspExt,
												vtListaCartas[ inxListaCartas ] );

			return TST_CompararInt( CondRetEsp, CondRetObtida,
				"Condicao de retorno diferente da esperada na insercao de carta" );

         } /* fim ativa: Testar inserir carta */

      /* Testar remover carta do espaco extra */

         else if ( strcmp( ComandoTeste , REMOVER_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "sii", StringCarta,
										&inxListaCartas, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
			  || CAR_StringParaCarta( StringCarta, &pCarta ) == CAR_CondRetCartaNaoExiste ) 
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = ESPEXT_RemoverCarta( pEspExt, pCarta,
												&vtListaCartas[ inxListaCartas ] );

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
									"Condi��o de retorno errada ao remover carta."   ) ;

         } /* fim ativa: Testar remover carta do espaco extra */

      /* Testar criar lista de cartas */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxListaCartas, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxListaCartas( inxListaCartas , IRRELEVANTE )))
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

            numLidos = LER_LerParametros( "i" , &inxListaCartas ) ;

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

            numLidos = LER_LerParametros( "ii" ,
                       &inxListaCartas , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxListaCartas( inxListaCartas , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = ESPEXT_ObterListaCartas( pEspExt, &vtListaCartas[ inxListaCartas ] ) ;

            return TST_CompararInt(CondRetEsp, CondRetObtida,
								   "Condicao de retorno errada ao obter lista de cartas");

         } /* fim ativa: Testar obter lista de cartas */
		 
      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TSEQVIS &Testar sequ�ncia vis�vel */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

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

   } /* Fim fun��o: TESPEXT -Validar indice de lista de cartas */


/********** Fim do m�dulo de implementa��o: TESPEXT Teste espa�os extras **********/