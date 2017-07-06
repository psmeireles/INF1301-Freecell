/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
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
#include	"CESPDIN.H"
#include    "LerParm.h"

#include    "Lista.h"

/* Tabela dos nomes dos comandos de teste específicos */

static const char RESET_LISTA_CMD         [ ] = "=resetteste"      ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"      ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"   ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"   ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"    ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"     ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem"  ;
static const char OBTER_TAM_CMD           [ ] = "=obtertam"        ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"     ;
static const char REMOVER_ELEM_CMD		  [ ] = "=removerelem"	   ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"        ;
static const char IR_FIM_CMD              [ ] = "=irfinal"         ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"     ;
static const char PROCURAR_VALOR_CMD	  [ ] = "=procurarvalor"   ;
static const char RETIRAR_LISTA_ELEM_CMD  [ ] = "=retirarlistaelem";
static const char CONCATENAR_LISTA_CMD    [ ] = "=concatenarlista" ;

/* Os comandos a seguir somente operam em modo _DEBUG */

#ifdef _DEBUG
static const char VER_CABECA_CMD		  [ ] = "=verificarcabeca" ;
static const char VER_LISTA_CMD			  [ ] = "=verificarlista"  ;
static const char VER_MEMORIA_CMD		  [ ] = "=verificarmemoria";
static const char DETURPAR_CMD			  [ ] = "=deturparlista"   ;
#endif

int estaInicializado = 0 ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define IRRELEVANTE 2

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

#define TAM_LISTA_TST 10

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista  CondRetEsp
*     =destruirlista                inxLista  
*     =esvaziarlista                inxLista  CondRetEsp
*     =inselemantes                 inxLista  string    CondRetEsp
*     =inselemapos                  inxLista  string    CondRetEsp
*     =obtervalorelem               inxLista  string    CondRetEsp
*     =obtertam                     inxLista  ValEsp    CondRetEsp
*     =excluirelem                  inxLista  CondRetEsp
*	  =removerelem					inxLista1 inxLista2 CondRetEsp
*     =irinicio                     inxLista  CondRetEsp
*     =irfinal                      inxLista  CondRetEsp
*     =avancarelem                  inxLista  numElem   CondRetEsp
*	  =procurarvalor				inxLista  string	CondRetEsp
*	  =retirarlistaelem				inxLista1 inxLista2 CondRetEsp
*	  =concatenarlista				inxLista1 inxLista2 CondRetEsp  
*
*
*	  Estes comandos somente podem ser executados se o modulo tiver sido
*     compilado com _DEBUG ligado
*
*     =verificarcabeca			    inxLista  CondRetEsp
*     =verificarlista			    inxLista  CondRetEsp
*     =verificarmemoria
*     =deturparlista	 		    inxLista  idCodigoDeturpa 
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista   = -1 ,
		  inxLista1  = -1 ,
		  inxLista2  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ;
		  
	#ifdef _DEBUG
	  int idCodigoDeturpa = -1 ;
	#endif
	  
      LIS_tpCondRet CondRetObtida ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i = -1;
      int tamLista = -1;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;
	  pDado = NULL ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = LIS_CriarLista( DestruirValor, &vtListas[ inxLista ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar lista." );

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao esvaziar lista." );

         } /* fim ativa: Testar Esvaziar lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRetObtida = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado ) ;

            if ( CondRetObtida != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao inserir antes." ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRetObtida = LIS_InserirElementoApos( vtListas[ inxLista ] , pDado ) ;

            if ( CondRetObtida != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao inserir apos." ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir elemento */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condicao de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir elemento */

      /* Testar remover elemento */

         else if ( strcmp( ComandoTeste , REMOVER_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                  &inxLista1 , &inxLista2 , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista1 , IRRELEVANTE ))
			  || ( ! ValidarInxLista( inxLista2 , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

			return TST_CompararInt( CondRetEsp ,
                      LIS_RemoverElemento( vtListas[ inxLista1 ], &vtListas[ inxLista2 ] ) ,
                     "Condicao de retorno errada ao remover elemento."   ) ;

         } /* fim ativa: Testar remover elemento */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = LIS_ObterValor( vtListas[ inxLista ], (void **) &pDado ) ;

			if ( CondRetEsp == LIS_CondRetListaNaoExiste )
            {
               return TST_CompararInt( CondRetEsp , CondRetObtida ,
											   "Lista nao deveria existir." ) ;
            } /* if */
			
            if ( CondRetEsp == LIS_CondRetListaVazia )
            {
               return TST_CompararInt( CondRetEsp , CondRetObtida ,
											   "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
											   "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
									   "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

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

         } /* fim ativa: Testar obter valor do elemento corrente */


      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = IrInicioLista( &vtListas[ inxLista ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao ir para o elemento inicial." );

         } /* fim ativa: Testar ir para o elemento inicial */

      /* Testar Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = IrFinalLista( &vtListas[ inxLista ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao ir para o elemento final." );

         } /* fim ativa: Testar Ir para o elemento final */

      /* Testar Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
												  "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: Testar Avançar elemento */

      /* Testar Procurar valor */

         else if ( strcmp( ComandoTeste , PROCURAR_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , &inxLista , StringDado ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */
			
			CondRetObtida = LIS_ProcurarValor( (int (*) (void *pDado1, void *pDado2)) strcmp, vtListas[ inxLista ] , (void *) StringDado ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida,
								   "Condicao de retorno errada ao proccurar valor" ) ;

         } /* fim ativa: Testar Procurar valor */
		 
		 
	  /* Testar Retirar lista de elementos */

		 else if( strcmp( ComandoTeste, RETIRAR_LISTA_ELEM_CMD ) == 0 )
		 {

			numLidos = LER_LerParametros( "iii" , &inxLista1 , &inxLista2 ,
                                &CondRetEsp ) ;

			if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista1 , IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

			
			CondRetObtida = LIS_RetirarListaElem( vtListas[ inxLista1 ], &vtListas[ inxLista2 ] );

			return TST_CompararInt( CondRetEsp, CondRetObtida,
									"Condicao de retorno diferente da esperada ao retirar lista de elementos");

		 } /* fim ativa: Testar Retirar lista de elementos */

	  /* Testar Concatenar lista */

		 else if( strcmp( ComandoTeste, CONCATENAR_LISTA_CMD ) == 0 )
		 {

			numLidos = LER_LerParametros( "iii" , &inxLista1 , &inxLista2 ,
                                &CondRetEsp ) ;

			if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista1 , IRRELEVANTE ))
			  || ( ! ValidarInxLista( inxLista2 , IRRELEVANTE )))
            {
               return TST_CondRetParm ;
            } /* if */

			if( ValidarInxLista( inxLista1 , NAO_VAZIO )
			  && ValidarInxLista( inxLista2 , NAO_VAZIO ))
			  {
				i = 0;
				LIS_ObterTam( vtListas[ inxLista1 ], &tamLista );
				i += tamLista;
				LIS_ObterTam( vtListas[ inxLista2 ], &tamLista );
				i += tamLista;
			  }

			CondRetObtida = LIS_ConcatenarLista( vtListas[ inxLista1 ], vtListas[ inxLista2 ] );
			
			if( CondRetObtida == LIS_CondRetOK )
				vtListas[ inxLista2 ] = NULL ;
			
			LIS_ObterTam( vtListas[ inxLista1 ], &tamLista );
			
			if(i != tamLista
			  && ValidarInxLista( inxLista1 , IRRELEVANTE )
			  && ValidarInxLista( inxLista2 , IRRELEVANTE ))
				return TST_CompararInt(i, tamLista,
										"Tamanho da lista diferente do esperado"); 

			return TST_CompararInt(CondRetEsp, CondRetObtida,
									"Condicao de retorno diferente do esperado");

		 } /* fim ativa: Testar Concatenar lista */


	  /* Testar verificador de cabeça */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_CABECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || !ValidarInxLista( inxLista,  IRRELEVANTE ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                             LIS_VerificarCabeca( vtListas[ inxLista ] ) ,
                             "Retorno incorreto ao verificar cabeca." ) ;

         } /* fim ativa: Testar verificador de cabeça */
      #endif

      /* Testar verificador de lista */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                                          &inxLista , &CondRetEsp ) ;
            if ( ( numLidos != 2 )
              || !ValidarInxLista( inxLista, IRRELEVANTE ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                             LIS_VerificarLista( vtListas[ inxLista ] ) ,
                             "Retorno incorreto ao verificar lista." ) ;

         } /* fim ativa: Testar verificador de lista */
      #endif

      /* Deturpar uma lista */

	  #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , DETURPAR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista , &idCodigoDeturpa ) ;

            if ( ( numLidos != 2 )
              || ! (ValidarInxLista( inxLista, IRRELEVANTE )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_Deturpar( vtListas[ inxLista ] , idCodigoDeturpa ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Deturpar uma lista */
      #endif
     

      /* Verificar vazamento de memória */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_MEMORIA_CMD ) == 0 )
         {

            CED_ExibirTodosEspacos( CED_ExibirTodos ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Verificar vazamento de memória */
      #endif

      return TST_CondRetNaoConhec ;

   } /* Fim Função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim Função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
	  if ( Modo == IRRELEVANTE )
		return TRUE;	 
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

   } /* Fim Função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

