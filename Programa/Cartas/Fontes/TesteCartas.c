/***************************************************************************
*  $MCI Módulo de implementação: TCAR Teste Cartas
*
*  Arquivo gerado:              TesteCartas.c
*  Letras identificadoras:      TCAR
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / Free Cell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       psm   05/mai/2017 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Cartas.h"


static const char RESET_CARTA_CMD         [ ] = "=resetteste"        ;
static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta"        ;
static const char DESTRUIR_CARTA_CMD      [ ] = "=destruircarta"     ;
static const char SIMBOLO_SUCESSOR_CMD    [ ] = "=simbolosucessor"   ;
static const char SIMBOLO_ANTECESSOR_CMD  [ ] = "=simboloantecessor" ;
static const char EH_PRIMEIRA_CARTA_CMD   [ ] = "=ehprimeiracarta"   ;
static const char TEM_MESMO_NAIPE_CMD     [ ] = "=temmesmonaipe"     ;
static const char TEM_MESMA_COR_CMD       [ ] = "=temmesmacor"       ;
static const char CARTA_PARA_STRING_CMD   [ ] = "=cartaparastring"   ;
static const char STRING_PARA_CARTA_CMD	  [ ] = "=stringparacarta"	 ;
static const char COMPARA_CARTAS_CMD	  [ ] = "=comparacartas"     ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CARTA   10
#define DIM_VALOR      3

#define TAM_CARTA_TST 10

CAR_tppCarta   vtCartas[ DIM_VT_CARTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxCarta( int inxCarta , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCAR &Testar cartas
*
*  $ED Descrição da função
*     Podem ser criadas até 10 cartas, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de cartas. Provoca vazamento de memória
*     =criarcarta                  inxCarta   simbolo    naipe   cor   CondRetEsp
*     =destruircarta               inxCarta  
*     =simbolosucessor             inxCarta1  inxCarta2  CondRetEsp
*     =simboloantecessor           inxCarta1  inxCarta2  CondRetEsp
*     =ehprimeiracarta             inxCarta   CondRetEsp
*     =temmesmonaipe               inxCarta1  inxCarta2  CondRetEsp
*     =temmesmacor                 inxCarta1  inxCarta2  CondRetEsp
*     =cartaparastring             inxCarta   ValEsp     CondRetEsp
*	  =stringparacarta			   string     inxCarta   CondRetEsp
*	  =comparacartas			   inxCarta1  inxCarta2  CondRetEsp
*     
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxCarta   = -1 ,
		  inxCarta1  = -1 ,
		  inxCarta2  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  simbolo	 = -1 ,
		  naipe		 = -1 ;

      CAR_tpCondRet CondRetObtida ;

	  char	 StringDado[ DIM_VALOR ] ;
      char   ValEsp[ DIM_VALOR ] ;

      int i = -1;

	  StringDado[0] = 0 ;
	  ValEsp[0] = 0 ;

      /* Efetuar reset de teste de cartas */

         if ( strcmp( ComandoTeste , RESET_CARTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_CARTA ; i++ )
            {
               vtCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de cartas */

      /* Testar Criar carta */

         else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiii" , &inxCarta, &simbolo, &naipe, &CondRetEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxCarta( inxCarta , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CAR_CriarCarta( (CAR_Simbolo) simbolo, (CAR_Naipe) naipe,
											&vtCartas[ inxCarta ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao criar carta." );

         } /* fim ativa: Testar Criar carta */

      /* Testar Destruir carta */

         else if ( strcmp( ComandoTeste , DESTRUIR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxCarta ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CAR_DestruirCarta( vtCartas[ inxCarta ] ) ;
            vtCartas[ inxCarta ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir carta */

      /* Testar simbolo sucessor */

         else if ( strcmp( ComandoTeste , SIMBOLO_SUCESSOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxCarta1 , &inxCarta2 , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CAR_SimboloSucessor( vtCartas[ inxCarta1 ] , vtCartas[inxCarta2] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao verificar se simbolo e sucessor." ) ;

         } /* fim ativa: Testar simbolo sucessor */

      /* Testar simbolo antecessor */

         else if ( strcmp( ComandoTeste , SIMBOLO_ANTECESSOR_CMD ) == 0 )
         {

			 numLidos = LER_LerParametros( "iii",
				 &inxCarta1, &inxCarta2, &CondRetEsp ) ;

			 if ( ( numLidos != 3 ) )
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRetObtida = CAR_SimboloAntecessor(vtCartas[inxCarta1], vtCartas[inxCarta2]);

			 return TST_CompararInt(CondRetEsp, CondRetObtida,
				 "Condicao de retorno errada ao verificar se simbolo e antecessor.");

         } /* fim ativa: Testar simbolo antecessor */

      /* Testar É primeira carta */

         else if ( strcmp( ComandoTeste , EH_PRIMEIRA_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxCarta , &CondRetEsp ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = CAR_EhPrimeiraCarta( vtCartas[ inxCarta ] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao verificar se e primeira carta."   ) ;

         } /* fim ativa: Testar É primeira carta */

      /* Testar Tem mesmo naipe */

         else if ( strcmp( ComandoTeste , TEM_MESMO_NAIPE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                  &inxCarta1 , &inxCarta2 , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtida = CAR_TemMesmoNaipe( vtCartas[ inxCarta1 ], vtCartas[ inxCarta2 ] ) ;


		    return TST_CompararInt( CondRetEsp , CondRetObtida ,
                     "Condicao de retorno errada ao verificar se tem mesmo naipe."   ) ;

         } /* fim ativa: Testar Tem mesmo naipe */

	   /* Testar Tem mesma cor */

		 else if (strcmp(ComandoTeste, TEM_MESMA_COR_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("iii",
				 &inxCarta1, &inxCarta2, &CondRetEsp) ;

			 if ( ( numLidos != 3 ) )
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRetObtida = CAR_TemMesmaCor( vtCartas[ inxCarta1 ], vtCartas[ inxCarta2 ] ); 


			 return TST_CompararInt(CondRetEsp, CondRetObtida,
				 "Condicao de retorno errada ao verificar se tem mesma cor.") ;

		 } /* fim ativa: Testar Tem mesma cor */

	  /* Testar Carta para string */

         else if ( strcmp( ComandoTeste , CARTA_PARA_STRING_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxCarta , ValEsp, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CAR_CartaParaString( vtCartas[ inxCarta ],  StringDado ) ;
            
			if (CondRetEsp == CondRetObtida)
			{
				if( CondRetEsp == CAR_CondRetCartaNaoExiste )
					return TST_CompararInt(CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao converter carta para string") ;
				else
					return TST_CompararString( ValEsp, StringDado,
									       "String diferente do esperado ao converter carta para string" ) ;
			}
			else
				return TST_CompararInt(CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao converter carta para string") ;
            

         } /* fim ativa: Testar Carta para string */


 	  /* Testar String para carta */

         else if ( strcmp( ComandoTeste , STRING_PARA_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "sii" ,
                       StringDado , &inxCarta , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CAR_StringParaCarta( StringDado, &vtCartas[ inxCarta ] ) ;
            
            return TST_CompararInt(CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao converter string para carta") ;

         } /* fim ativa: Testar String para carta */

 	  /* Testar Comparar cartas */

         else if ( strcmp( ComandoTeste , COMPARA_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                        &inxCarta1 , &inxCarta2 , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CAR_ComparaCartas( vtCartas[ inxCarta1 ] , vtCartas[ inxCarta2 ] ) ;
            
            return TST_CompararInt(CondRetEsp, CondRetObtida,
									"Condicao de retorno errada ao comparar cartas") ;

         } /* fim ativa: Testar String para carta */


      return TST_CondRetNaoConhec ;

   } /* Fim Função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TCAR -Validar indice da carta
*
***********************************************************************/

   int ValidarInxCarta( int inxCarta , int Modo )
   {

      if ( ( inxCarta <  0 )
        || ( inxCarta >= DIM_VT_CARTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtCartas[ inxCarta ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtCartas[ inxCarta ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim Função: TCAR -Validar indice de carta */

/********** Fim do módulo de implementação: TCAR Teste cartas **********/

