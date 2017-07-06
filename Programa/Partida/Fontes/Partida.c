/***************************************************************************
*
*  $MCI Módulo de implementação: PAR  Partida
*
*  Arquivo gerado:              Partida.c
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm, mcc
*
*  $HA Histórico de evolução:
*     Versão  Autor       Data     Observações
*     1		  psm, mcc	07/jun/2017	Início do desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>

#define PARTIDA_OWN
#include "PARTIDA.h"
#undef PARTIDA_OWN



/***********************************************************************
*
*  $TC Tipo de dados: PAR Tabuleiro
*
*
***********************************************************************/

   typedef struct PAR_tagTabuleiro {

         LIS_tppLista pLista ;
               /* Ponteiro para o valor contido no elemento */

   } PAR_tpTabuleiro ;


/***** Protótipos das funções encapuladas no módulo *****/

   static PAR_tpCondRet CriarTabuleiro( PAR_tppTabuleiro  *pTabuleiro ) ;

   static PAR_tpCondRet DistribuirBaralho( PAR_tppTabuleiro  pTabuleiro, 
										   EMB_tppBaralho pBaralho ) ;

   static PAR_tpCondRet DestruirTabuleiro( PAR_tppTabuleiro  pTabuleiro ) ;



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  $FC Função: PAR  &Iniciar partida
*  ****/

   PAR_tpCondRet PAR_IniciarPartida( PAR_tppTabuleiro *pTabuleiro )
   {

	   EMB_tppBaralho pBaralho ;

	   if( CriarTabuleiro( pTabuleiro ) == PAR_CondRetFaltouMemoria )
		   return PAR_CondRetFaltouMemoria ;
	   if( EMB_CriarBaralho( &pBaralho ) == EMB_CondRetFaltouMemoria ) 
		   return PAR_CondRetFaltouMemoria ;
	   if( EMB_Embaralhar( pBaralho ) == EMB_CondRetFaltouMemoria ) 
		   return PAR_CondRetFaltouMemoria ;
	   return DistribuirBaralho( *pTabuleiro, pBaralho ) ;

   } /* Fim função: PAR  &Criar lista */


/***************************************************************************
*
*  $FC Função: PAR  &Jogar
*  ****/

   PAR_tpCondRet PAR_Jogar( PAR_tppTabuleiro pTabuleiro )
	{

		int pos ;
		int posSeqVis ;
		int qtdVazios ;
		int tamanho ;
		char c1 ;
		char c2 ;
		char stringCarta[3] ;
		CAR_tppCarta pCarta ;
		CAR_tpCondRet retornoCarta ;
		LIS_tpCondRet retornoLista ;
		LIS_tppLista pLista ;
		LIS_tppLista pListaRemovida ;
		ESPEXT_tppEspExt pEspExt ;
		ESPEXT_tppEspExt pEspExt1 ;
		ESPEXT_tpCondRet retornoEspExt ;
		ESPEXT_tppEspExt pEspExt2 ;
		SEQVIS_tppSeqVis pSeqVis ;
		SEQVIS_tpCondRet retornoSeqVis ;
		SEQVIS_tppSeqVis pSeqVis2 ;
		SEQORD_tppSeqOrd pSeqOrd ;
		SEQORD_tpCondRet retornoSeqOrd ;

		c1 = 'n';

		if( LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta, &pListaRemovida) == LIS_CondRetFaltouMemoria )	/* Lista que vai receber o elemento retirado */
		{
			return PAR_CondRetFaltouMemoria;
		}


		ESCOLHA:
		if ( c1 == 'v' || c1 == 'e' )
		{
			IrInicioLista( &(pTabuleiro->pLista) ) ;

			switch (c1)
			{
			case 'v' :
				{
					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, posSeqVis ) ;

					if ( LIS_ObterValor(pTabuleiro->pLista, (void **) &pSeqVis) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}

					retornoSeqVis = SEQVIS_InserirCartaSemRestr( pSeqVis, pListaRemovida ); /*Devolve a carta para onde estava inicialmente */
					if ( !( retornoSeqVis == SEQVIS_CondRetOK || retornoSeqVis == SEQVIS_CondRetImpossInserirCarta ) )
					{
						return PAR_CondRetEstruturaErrada;
					}
					break ;
				}

			case 'e' :
				{
					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 8 ) ;

					if ( LIS_ObterValor(pTabuleiro->pLista, (void **) &pEspExt1) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}

					retornoEspExt = ESPEXT_ObterListaCartas( pEspExt1, &pLista ) ;  /* Obtem pLista do Espaço Extra */

					if ( retornoEspExt == ESPEXT_CondRetEspExtNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ; 
					}

					IrInicioLista( &(pLista) ) ;

					retornoEspExt = ESPEXT_InserirCarta( pEspExt1, pListaRemovida );

					break;
				}
			}
			PAR_ImprimirTabuleiro( pTabuleiro ) ;
		}

		printf("\nDigite a carta que voce quer mover, no padrao:\n");
		printf("Uma das seguintes letras, 'C', 'P', 'E' ou 'O' (maiuscula), indicando o naipe \n");
		printf("E um numero entre 2 e 9 ou uma das seguintes letras maiuscula 'A', 'J', 'Q', 'K' ou 'D' (correspondente ao numero 10)\n");
		printf("Ou digite 'x' caso queira cancelar essa jogada\n");
		fflush(stdin);
		scanf(" %2[^\n]",&stringCarta);
		if ( stringCarta[0] == 'x' )
		{
			goto SAIDA;
		}

		retornoCarta = CAR_StringParaCarta(stringCarta, &pCarta) ;
		if( retornoCarta == CAR_CondRetFaltouMemoria )
		{
			return PAR_CondRetFaltouMemoria ;
		}

		else if( retornoCarta == CAR_CondRetCartaNaoExiste )
		{
			do
			{
				printf( "\nComando Invalido.\n" ) ;
				printf("Digite a carta que voce quer mover, no padrao:\n");
				printf("Uma das seguintes letras, 'C', 'P', 'E' ou 'O' (maiuscula), indicando o naipe \n");
				printf("E um numero entre 2 e 9 ou uma das seguintes letras maiuscula 'A', 'J', 'Q', 'K' ou 'D' (correspondente ao numero 10)\n");
				printf("Ou digite 'x' caso queira cancelar essa jogada\n");
				fflush(stdin);
				scanf(" %2[^\n]",&stringCarta);
				retornoCarta = CAR_StringParaCarta(stringCarta, &pCarta) ;
				if( retornoCarta == CAR_CondRetFaltouMemoria )
				{
					return PAR_CondRetFaltouMemoria ;
				}

				if ( stringCarta[0] == 'x' )
				{
					goto SAIDA;
				}

			} while( retornoCarta == CAR_CondRetCartaNaoExiste ) ;
			
		}
		IrInicioLista( &(pTabuleiro->pLista) ) ;
		
		do
		{
			printf("\nIndique onde esta a carta que deseja mover, digite a letra:\n");
			printf(" 'v' - Se a carta estiver em uma das sequencias visiveis \n");
			printf(" 'e' - Se a carta estiver em um dos espacos extras \n");
			printf("Ou digite 'x' caso queira cancelar essa jogada\n");
			fflush(stdin);
			scanf(" %c",&c1);

			switch (c1) 
			{
			case 'x' :
				{
					goto SAIDA ;
					break;
				}

			case 'e' :
				{
					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 8 ) ;

					if ( retornoLista == LIS_CondRetListaVazia )
					{
						return PAR_CondRetListaVazia ;
					}


					if ( LIS_ObterValor(pTabuleiro->pLista, (void **) &pEspExt1) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}


					retornoEspExt = ESPEXT_ObterListaCartas( pEspExt1, &pLista ) ;  /* Obtem pLista do Espaço Extra */

					if ( retornoEspExt == ESPEXT_CondRetEspExtNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ; 
					}

					IrInicioLista( &(pLista) ) ;

					if ( LIS_ProcurarValor( (int (*) (void *pDado1, void *pDado2)) CAR_ComparaCartas, pLista, pCarta ) != LIS_CondRetOK )
					{
						printf("\nEssa estrutura nao contem a carta escolhida, tente outra jogada\n\n");
						goto ESCOLHA;
					}

					retornoEspExt = ESPEXT_RemoverCarta( pEspExt1, pCarta, &pListaRemovida) ; /* Exclui carta do tabuleiro e guarda em uma lista auxiliar */
					if ( retornoEspExt == ESPEXT_CondRetFaltouMemoria ) 
					{
						return PAR_CondRetFaltouMemoria ;
					}

					else if ( retornoEspExt == ESPEXT_CondRetListaNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ;
					}

					else if ( retornoEspExt == ESPEXT_CondRetNaoAchou )
					{
						printf("\nEssa estrutura nao contem a carta escolhida, digite uma nova carta\n\n");
						goto ESCOLHA;				
					}

					break;
				}

			case 'v' :
				{
					printf("\n Indique em qual sequencia visivel se encontra a carta que você deseja mover:\n");
					printf("Digite um numero entre 0 e 7 (sendo 0 referente a primeira sequencia visivel, mais acima, e 7 a sequencia mais abaixo)\n");
					fflush(stdin);
					scanf("%d",&posSeqVis);

					while(posSeqVis<0 || posSeqVis>7)
					{
						printf("\n Sequencia visivel invalida, digite novamente\n");
						fflush(stdin);
						scanf("%d",&posSeqVis);
					}

					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, posSeqVis ) ;

					if ( retornoLista == LIS_CondRetListaVazia )
					{
						return PAR_CondRetListaVazia ;
					}

					if ( LIS_ObterValor(pTabuleiro->pLista, (void **) &pSeqVis) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}

					retornoSeqVis = SEQVIS_ObterListaCartas( pSeqVis, &pLista ) ;

					if ( retornoSeqVis == SEQVIS_CondRetSeqVisNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ;
					}

					if (LIS_ProcurarValor( (int (*) (void *pDado1, void *pDado2)) CAR_ComparaCartas, pLista, pCarta ) != LIS_CondRetOK )
					{
						printf("\nEssa estrutura nao contem a carta escolhida, digite uma nova carta\n\n");
						goto ESCOLHA;
					}

					retornoSeqVis = SEQVIS_RemoverCarta( pSeqVis, pCarta, &pListaRemovida);

					if ( retornoSeqVis == SEQVIS_CondRetListaNaoExiste || retornoSeqVis == SEQVIS_CondRetSeqVisNaoExiste ) /* Exclui carta do tabuleiro e guarda em uma lista auxiliar */
					{
						return PAR_CondRetEstruturaErrada ;
					}

					else if ( retornoSeqVis == SEQVIS_CondRetNaoAchou ) /* Exclui carta do tabuleiro e guarda em uma lista auxiliar */
					{
						printf("\nEssa estrutura nao contem a carta escolhida, digite uma nova carta\n\n");
						goto ESCOLHA;
					}

					else if ( retornoSeqVis == SEQVIS_CondRetImpossRetirarCarta ) /* Exclui carta do tabuleiro e guarda em uma lista auxiliar */
					{
						printf("\nNao eh possivel remover essa carta deste lugar\n\n");
						goto ESCOLHA;
					}

					break;
				}

			default :

				printf("\nEntrada invalida, digite novamente:\n");
				break;
			}

		}while( !(c1!='e' || c1!='v') );

		
		IrInicioLista( &(pTabuleiro->pLista) ) ;
		retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 8 ) ;

		if ( retornoLista == LIS_CondRetListaVazia )
		{
			return PAR_CondRetListaVazia ;
		}

		if ( LIS_ObterValor(pTabuleiro->pLista, (void **) &pEspExt) != LIS_CondRetOK )
		{
			return PAR_CondRetListaVazia ;
		}

		ESPEXT_ObterNumEspExtVazios( pEspExt, &qtdVazios ) ; /* obtem o numero de espaços extras vazios */
		LIS_ObterTam( pListaRemovida, &tamanho ); /* obtem o tamanho do bloco de cartas que deseja ser movido */

		if ( tamanho > 1 + qtdVazios ) /* verifica o numero maximos de cartas que podem ser movidas */
		{
			printf("\n Jogada invalida! Com %d espaços vazios, você pode mover no maximo %d cartas\n",qtdVazios,qtdVazios+1);
			printf("\n Digite uma nova carta que deseje mover\n");
			goto ESCOLHA;
		}


		IrInicioLista( &(pTabuleiro->pLista) ) ;

		do
		{
			printf("\nIndique para onde voce deseja mover a carta, digite a letra:\n") ;
			printf(" 'v' - Se for para uma das sequências visiveis \n") ;
			printf(" 'e' - Se for um dos espaços extras \n") ;
			printf(" 'o' - Se for uma dos das sequências ordenadas \n") ;
			printf("Ou digite 'x' caso queira cancelar essa jogada\n");
			fflush(stdin);
			scanf(" %c",&c2) ;

			switch (c2)
			{
			case 'x' :
				{
					goto ESCOLHA;
					break;
				}

			case 'e' :
				{
					if ( qtdVazios == 0 )
					{
						printf("\n Nao ha mais espacos vazios disponiveis, tente outra jogada \n");
						goto ESCOLHA;
					}

					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 8 ) ;
				
					if ( retornoLista == LIS_CondRetListaVazia )
					{
						return PAR_CondRetListaVazia ;
					}

					if ( LIS_ObterValor(pTabuleiro->pLista, (void **) &pEspExt2) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}

					retornoEspExt = ESPEXT_ObterListaCartas( pEspExt2, &pLista ) ;  /* Obtem pLista do Espaço Extra */

					if ( retornoEspExt == ESPEXT_CondRetEspExtNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ; 
					}

					pos = 4 - qtdVazios; /* descobre qual é o primeiro espaço extra vazio */
					IrInicioLista( &pLista ) ;
					retornoLista = LIS_AvancarElementoCorrente( pLista, pos ) ;

					retornoEspExt = ESPEXT_InserirCarta( pEspExt2, pListaRemovida );

					if ( retornoEspExt == ESPEXT_CondRetListaNaoExiste )
					{
						return PAR_CondRetListaNaoExiste ;
					}

					else if( retornoEspExt == ESPEXT_CondRetImpossInserirCarta || retornoEspExt == ESPEXT_CondRetListaVazia )
					{
						printf("\nImpossivel fazer essa jogada, tente novamente\n\n");
						goto ESCOLHA;	
					}	

					break;

				}

			case 'v' :
				{
					printf("\n Indique a posicao da sequencia visivel em que você quer inserir a carta:\n") ;
					printf("Digite um numero entre 0 e 7 (sendo 0 referente a primeira sequencia visivel, mais acima, e 7 a sequencia mais abaixo)\n") ;
					fflush(stdin);
					scanf("%d",&pos) ;

					while(pos<0 || pos>7)
					{
						printf("\n Sequencia visivel invalida, digite novamente\n");
						fflush(stdin);
						scanf("%d",&pos);
					}

					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, pos ) ;
					if ( retornoLista == LIS_CondRetFimLista )
					{
						return PAR_CondRetFimLista ;
					}

					else if ( retornoLista == LIS_CondRetListaVazia )
					{
						return PAR_CondRetListaVazia ;
					}

					if ( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqVis2 ) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}	

					retornoSeqVis = SEQVIS_ObterListaCartas( pSeqVis2, &pLista ) ;

					if ( retornoSeqVis == SEQVIS_CondRetSeqVisNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ;
					}

					retornoSeqVis = SEQVIS_InserirCartaRestr( pSeqVis2, pListaRemovida );

					if ( retornoSeqVis == SEQVIS_CondRetSeqVisNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ;
					}

					if ( retornoSeqVis == SEQVIS_CondRetListaNaoExiste )
					{
						return PAR_CondRetListaNaoExiste ;
					}

					else if( retornoSeqVis == SEQVIS_CondRetListaVazia || retornoSeqVis ==  SEQVIS_CondRetImpossInserirCarta )
					{
						printf("\nImpossivel fazer essa jogada, tente novamente\n\n");
						goto ESCOLHA;                                               
					}	

					break;
				}

			case 'o' :
				{
					if ( stringCarta[0] == 'C' )
					{
						pos = 0;
					}

					else if ( stringCarta[0] == 'P' )
					{
						pos = 1;
					}

					else if ( stringCarta[0] == 'E' )
					{
						pos = 2;
					}

					else if ( stringCarta[0] == 'O' )
					{
						pos = 3;
					}

					retornoLista = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 9+pos ) ;   
					 
					if ( retornoLista == LIS_CondRetListaVazia )
					{
						return PAR_CondRetListaVazia ;
					}

					if ( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) != LIS_CondRetOK )
					{
						return PAR_CondRetListaVazia ;
					}	

					retornoSeqOrd = SEQORD_ObterListaCartas( pSeqOrd, &pLista ) ;
					if ( retornoSeqOrd == SEQORD_CondRetSeqOrdNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ;
					}

					retornoSeqOrd = SEQORD_InserirCarta( pSeqOrd, pListaRemovida ) ;

					if ( retornoSeqOrd == SEQORD_CondRetSeqOrdNaoExiste )
					{
						return PAR_CondRetEstruturaErrada ;
					}

					else if ( retornoSeqOrd == SEQORD_CondRetListaNaoExiste )
					{
						PAR_CondRetListaNaoExiste ;
					}

					else if( retornoSeqOrd == SEQORD_CondRetListaVazia || retornoSeqOrd == SEQORD_CondRetImpossInserirCarta )
					{
						printf("Impossivel fazer essa jogada, tente novamente\n\n"); 
						goto ESCOLHA;														
					}

					break;
				}

			default :

				printf("\nEntrada invalida, digite novamente:\n");
				break;
			
			}

		}while( !(c2=='e' || c2=='v' || c2=='o') );

		SAIDA: return PAR_CondRetOK ;

	} /* Fim função: PAR Jogar */
   


/***************************************************************************
*
*  $FC Função: PAR  &Verificar vitória
*  ****/

   PAR_tpCondRet PAR_VerificarVitoria( PAR_tppTabuleiro pTabuleiro )
   {

	  SEQORD_tpCondRet retorno1, retorno2, retorno3, retorno4 ;
	  SEQORD_tppSeqOrd pSeqOrd ;

	  if( pTabuleiro == NULL )
		  return PAR_CondRetTabuleiroNaoExiste ;
	  if( pTabuleiro->pLista == NULL )
		  return PAR_CondRetListaNaoExiste ;

	  IrInicioLista( &(pTabuleiro->pLista) );
	  if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 9 ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  retorno1 = SEQORD_VerificaSeqOrd( pSeqOrd ) ;

	  if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  retorno2 = SEQORD_VerificaSeqOrd( pSeqOrd ) ;

	  if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  retorno3 = SEQORD_VerificaSeqOrd( pSeqOrd ) ;

	  if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	  retorno4 = SEQORD_VerificaSeqOrd( pSeqOrd ) ;

	  if(  retorno1 == SEQORD_CondRetOK
		&& retorno2 == SEQORD_CondRetOK
		&& retorno3 == SEQORD_CondRetOK
		&& retorno4 == SEQORD_CondRetOK )
		return PAR_CondRetVenceu ;

	  return PAR_CondRetOK ;

   } /* Fim função: PAR  &Terminar partida */


/***************************************************************************
*
*  $FC Função: PAR  &Terminar partida
*  ****/

   PAR_tpCondRet PAR_TerminarPartida( PAR_tppTabuleiro pTabuleiro )
   {

	   if( DestruirTabuleiro( pTabuleiro ) == PAR_CondRetOK )
	   {
		   printf("Partida encerrada.\n") ;
		   return PAR_CondRetOK ;
	   }
	   return PAR_CondRetEstruturaErrada ;

   } /* Fim função: PAR  &Terminar partida */


/***************************************************************************
*
*  $FC Função: PAR  &Imprimir tabuleiro
*  ****/

   PAR_tpCondRet PAR_ImprimirTabuleiro( PAR_tppTabuleiro pTabuleiro )
   {

	   ESPEXT_tppEspExt pEspExt ;
	   SEQORD_tppSeqOrd pSeqOrd ;
	   SEQVIS_tppSeqVis pSeqVis ;
	   int i ;

	   if( pTabuleiro == NULL )
		  return PAR_CondRetTabuleiroNaoExiste ;
	   if( pTabuleiro->pLista == NULL )
		  return PAR_CondRetListaNaoExiste ;

	   /* Imprimir espaços extras */
	   IrInicioLista( &(pTabuleiro->pLista) );
	   if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 8 ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	   if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pEspExt ) != LIS_CondRetOK )
		   return PAR_CondRetEstruturaErrada ;
	   if( ESPEXT_ImprimeEspExt( pEspExt ) != ESPEXT_CondRetOK )
		   return PAR_CondRetImpossivelImprimir ;
	   printf("\t") ;

	   /* Imprimir sequências ordenadas */
	   for( i = 0; i < 4; i++ )
	   {
		   if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) != LIS_CondRetOK )
			   return PAR_CondRetEstruturaErrada ;
		   if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) != LIS_CondRetOK )
			   return PAR_CondRetEstruturaErrada ;
		   if( SEQORD_ImprimeSeqOrd( pSeqOrd ) != SEQORD_CondRetOK )
			   return PAR_CondRetImpossivelImprimir ;
	   }
	   printf("\n\n") ;

	   /* Imprimir sequências visíveis */
	   IrInicioLista( &(pTabuleiro->pLista) ) ;
	   if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqVis ) != LIS_CondRetOK )
			   return PAR_CondRetEstruturaErrada ;
	   if( SEQVIS_ImprimeSeqVis( pSeqVis ) != SEQVIS_CondRetOK )
			   return PAR_CondRetImpossivelImprimir ;
	   for( i = 1; i < 8; i++ )
	   {
		   if( LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) != LIS_CondRetOK )
			   return PAR_CondRetEstruturaErrada ;
		   if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqVis ) != LIS_CondRetOK )
			   return PAR_CondRetEstruturaErrada ;
		   if( SEQVIS_ImprimeSeqVis( pSeqVis ) != SEQVIS_CondRetOK )
			   return PAR_CondRetImpossivelImprimir ;
	   }

	   return PAR_CondRetOK ;

   } /* Fim função: PAR  &Imprimir tabuleiro */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: PAR  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   static PAR_tpCondRet CriarTabuleiro( PAR_tppTabuleiro *pTabuleiro )
   {

	  SEQVIS_tppSeqVis  vSeqVis[8];
	  ESPEXT_tppEspExt  EspExt;
	  SEQORD_tppSeqOrd  vSeqOrd[4];
	  int i;

      *pTabuleiro = (PAR_tpTabuleiro *) malloc( sizeof( PAR_tpTabuleiro ) );

	  if( LIS_CriarLista( (void (*) (void *pDado)) NULL, &((*pTabuleiro)->pLista) )
		  == LIS_CondRetFaltouMemoria )
		  return PAR_CondRetFaltouMemoria ;

	  for( i = 0; i < 8; i++ )
	  {
		  if( SEQVIS_CriarSeqVis( &vSeqVis[i] ) == SEQVIS_CondRetFaltouMemoria		/* Cria as sequências visíveis */
			  || LIS_InserirElementoApos( (*pTabuleiro)->pLista, vSeqVis[i] ) )		/* Insere as sequências visíveis no tabuleiro */
			  return PAR_CondRetFaltouMemoria;
	  }

	 if( ESPEXT_CriarEspExt( &EspExt ) == ESPEXT_CondRetFaltouMemoria	/* Cria os espaços extras */
		|| LIS_InserirElementoApos( (*pTabuleiro)->pLista, EspExt ) )		/* Insere os espaços extras no tabuleiro */
		return PAR_CondRetFaltouMemoria;

	  for( i = 0; i < 4; i++ )
	  {
		   if( SEQORD_CriarSeqOrd( &vSeqOrd[i] ) == SEQORD_CondRetFaltouMemoria	/* Cria as sequências ordenadas */
			   ||  LIS_InserirElementoApos( (*pTabuleiro)->pLista, vSeqOrd[i] ) )	/* Insere as sequências ordenadas no tabuleiro */
			   return PAR_CondRetFaltouMemoria;			
	  }

	  return PAR_CondRetOK;

   } /* Fim função: PAR  -Criar tabuleiro */


/***********************************************************************
*
*  $FC Função: PAR  -Distribuir baralho
*
*  $ED Descrição da função
*     Distribui o baralho recebino nas sequências visíveis do tabuleiro
*
***********************************************************************/

   static PAR_tpCondRet DistribuirBaralho( PAR_tppTabuleiro pTabuleiro, 
										   EMB_tppBaralho pBaralho )
   {
	   
	   LIS_tppLista pListaCartas, aux ;
	   SEQVIS_tppSeqVis pSeqVis ;
	   LIS_tpCondRet retorno ;
	   int i ;

	   if( pTabuleiro == NULL )
		  return PAR_CondRetTabuleiroNaoExiste ;
	   if( pTabuleiro->pLista == NULL )
		  return PAR_CondRetListaNaoExiste ;
	   if( pBaralho == NULL ) 
		   return PAR_CondRetBaralhoNaoExiste ;

	   EMB_ObterListaCartas( pBaralho, &pListaCartas ) ;
	   EMB_DestruirBaralho( pBaralho ) ;

	   if( pListaCartas == NULL )
		   return PAR_CondRetListaNaoExiste ;

	   for( i = 0; i < 52; i++ )
	   {
		   if( LIS_CriarLista( (void (*) (void *pDado)) CAR_DestruirCarta, &aux ) == LIS_CondRetFaltouMemoria )	/* Cria lista auxiliar */
			   return PAR_CondRetFaltouMemoria ;
		   
		   IrInicioLista( &(pTabuleiro->pLista) ) ;						/* Vai para o início da lista de listas do tabuleiro */
		   retorno = LIS_AvancarElementoCorrente( pTabuleiro->pLista, i%8 ) ;		/* Vai para a sequência visível i%8 */

		   if( retorno == LIS_CondRetListaVazia )
			   return PAR_CondRetListaVazia ;
		   else if( retorno == LIS_CondRetFimLista )
			   return PAR_CondRetEstruturaErrada ;

		   if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqVis ) == LIS_CondRetListaVazia )	/* Obtém a sequência visível */
			   return PAR_CondRetListaVazia ;

		   if( LIS_RemoverElemento( pListaCartas, &aux ) == LIS_CondRetListaVazia ) 		/* Tira a carta do baralho */
			   return PAR_CondRetListaVazia ;

		   if( SEQVIS_InserirCartaSemRestr( pSeqVis, aux ) == SEQVIS_CondRetImpossInserirCarta )	/* Insere a carta na sequência visível (destrói lista auxiliar) */
			   return PAR_CondRetEstruturaErrada ;

	   }

	   return PAR_CondRetOK ;

   } /* Fim função: PAR  -Distribuir baralho */


/***********************************************************************
*
*  $FC Função: PAR  -Destruir tabuleiro
*
***********************************************************************/

	static PAR_tpCondRet DestruirTabuleiro( PAR_tppTabuleiro pTabuleiro )
	{

		int i ;
		ESPEXT_tppEspExt pEspExt ;
		LIS_tpCondRet retorno ;

		if( pTabuleiro == NULL )
		{
			free( pTabuleiro ) ;
			return PAR_CondRetOK ;
		}

		IrInicioLista( &(pTabuleiro->pLista) ) ;

		for( i = 0; i < 8; i++ )
		{

			SEQVIS_tppSeqVis pSeqVis ;

			if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqVis ) == LIS_CondRetListaVazia )
			{
				LIS_DestruirLista( pTabuleiro->pLista );
				free(pTabuleiro);
				return PAR_CondRetOK;
			}

			SEQVIS_DestruirSeqVis( pSeqVis ) ;

			retorno = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) ;

			if( retorno == LIS_CondRetListaVazia )
			{
				LIS_DestruirLista( pTabuleiro->pLista );
				free(pTabuleiro);
				return PAR_CondRetOK;
			}
		    else if( retorno == LIS_CondRetFimLista )
			   return PAR_CondRetEstruturaErrada ;

		}

		if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pEspExt ) == LIS_CondRetListaVazia )
		{
			LIS_DestruirLista( pTabuleiro->pLista );
			free(pTabuleiro);
			return PAR_CondRetOK;
		}

		ESPEXT_DestruirEspExt( pEspExt ) ;

		retorno = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) ;

		if( retorno == LIS_CondRetListaVazia )
		{
			LIS_DestruirLista( pTabuleiro->pLista );
			free(pTabuleiro);
			return PAR_CondRetOK;
		}
		else if( retorno == LIS_CondRetFimLista )
			return PAR_CondRetEstruturaErrada ;

		for( i = 9; i < 13; i++ )
		{

			SEQORD_tppSeqOrd pSeqOrd ;

			if( LIS_ObterValor( pTabuleiro->pLista, (void **) &pSeqOrd ) == LIS_CondRetListaVazia )
				break ;

			SEQORD_DestruirSeqOrd( pSeqOrd ) ;
			
			if( i != 12 )
			{
				retorno = LIS_AvancarElementoCorrente( pTabuleiro->pLista, 1 ) ;

				if( retorno == LIS_CondRetListaVazia )
					break ;
				else if( retorno == LIS_CondRetFimLista )
					return PAR_CondRetEstruturaErrada ;
			}

		}

		LIS_DestruirLista( pTabuleiro->pLista );
		free(pTabuleiro);
		return PAR_CondRetOK;
	} /* Fim função: PAR  Destruir tabuleiro */

/********** Fim do módulo de implementação: PAR  Partida **********/

