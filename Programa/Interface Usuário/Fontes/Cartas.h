#if ! defined( Cartas_MOD )
#define Cartas_MOD
/***************************************************************************
*
*  $MCD M�dulo de defini��o: CAR Cartas
*
*  Arquivo gerado:              Cartas.h
*  Letras identificadoras:      CAR
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1		  psm	14/abr/2017	In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa o tipo Cartas e as fun��es que determinam se uma carta � sucessora ou antecessora de outra.
*
***************************************************************************/

#if defined( Cartas_OWN )
	#define Cartas_EXT
#else
	#define Cartas_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo de refer�ncia para uma carta */
	typedef struct CAR_tagCarta * CAR_tppCarta;



/***********************************************************************
*
*  $TC Tipo de dados: CAR Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da carta
*
***********************************************************************/

	typedef enum {

		CAR_CondRetOK,
		/* Concluiu corretamente */

		CAR_CondRetFaltouMemoria,
		/* Faltou mem�ria ao alocar */

		CAR_CondRetCartaNaoExiste,
		/* Concluiu que a carta n�o existe */

		CAR_CondRetFalse
		/* Fun��o n�o retornou o que diz o t�tulo dela */

	} CAR_tpCondRet;


/***********************************************************************
*
*  $TC Tipo de dados: CAR Naipe
*
*
*  $ED Descri��o do tipo
*     Naipes de uma carta
*
***********************************************************************/

	typedef enum {

		Copas,
		Espadas,
		Ouros,
		Paus

	} CAR_Naipe;


/***********************************************************************
*
*  $TC Tipo de dados: CAR Simbolo
*
*
*  $ED Descri��o do tipo
*     Simbolos de uma carta
*
***********************************************************************/
	typedef enum {

		S_A,
		S_2,
		S_3,
		S_4,
		S_5,
		S_6,
		S_7,
		S_8,
		S_9,
		S_10,
		S_J,
		S_Q,
		S_K

	} CAR_Simbolo;


/***********************************************************************
*
*  $TC Tipo de dados: CAR Cor
*
*
*  $ED Descri��o do tipo
*     Cores de uma carta
*
***********************************************************************/
	
	typedef enum {

		Preto,
		Vermelho

	} CAR_Cor;


/***********************************************************************
*
*  $FC Fun��o: CAR  Criar uma carta
*
*  $ED Descri��o da fun��o
*     Cria uma carta
*
*  $EP Par�metros
*     simbolo - s�mbolo da carta a ser criada
*	  naipe   - naipe da carta a ser criada
*     cor	  - cor da carta a ser criada
*	  pCarta  - endere�o que vai receber a carta a ser criada
*
*  $FV Valor retornado
*     CAR_CondRetOK				- se criou a carta sem problemas
*	  CAR_CondRetFaltouMemoria  - se faltou mem�ria ao alocar a carta
*
***********************************************************************/

	CAR_tpCondRet CAR_CriarCarta(CAR_Simbolo simbolo, CAR_Naipe naipe, CAR_tppCarta *pCarta);


/***********************************************************************
*
*  $FC Fun��o: CAR  Destruir Carta
*
*  $ED Descri��o da fun��o
*     Destr�i a carta fornecida.
*     O par�metro ponteiro para a carta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta
*
*  $FV Valor retornado
*     CAR_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	CAR_tpCondRet CAR_DestruirCarta(CAR_tppCarta pCarta);


/***********************************************************************
*
*  $FC Fun��o: CAR  Simbolo sucessor
*
*  $ED Descri��o da fun��o
*     Recebe ponteiros para duas cartas e diz se o s�mbolo da segunda � sucessor do da primeira.
*
*  $EP Par�metros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas n�o existe
*     CAR_CondRetOK				- se o s�mbolo da segunda carta for sucessor do da primeira
*	  CAR_CondRetFalse			- caso contr�rio
*
***********************************************************************/

	CAR_tpCondRet CAR_SimboloSucessor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);


/***********************************************************************
*
*  $FC Fun��o: CAR  S�mbolo antecessor
*
*  $ED Descri��o da fun��o
*     Recebe ponteiros para duas cartas e diz se o s�mbolo da segunda � antecessor do da primeira.
*
*  $EP Par�metros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas n�o existe
*     CAR_CondRetOK				- se o s�mbolo da segunda carta for antecessor do da primeira
*	  CAR_CondRetFalse			- caso contr�rio
*
***********************************************************************/

	CAR_tpCondRet CAR_SimboloAntecessor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);


/***********************************************************************
*
*  $FC Fun��o: CAR  � Primeira Carta
*
*  $ED Descri��o da fun��o
*     Recebe ponteiro para uma carta e diz se seu s�mbolo corresponde ao primeiro, 
*     entre os 13, na ordem crescente. Ou seja, se seu s�mbolo � ou n�o S_A.
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se a carta n�o existe
*     CAR_CondRetOK				- se o s�mbolo da carta for um S_A
*	  CAR_CondRetFalse			- se o s�mbolo da carta n�o for um S_A
*
***********************************************************************/

	CAR_tpCondRet CAR_EhPrimeiraCarta(CAR_tppCarta pCarta);


/***********************************************************************
*
*  $FC Fun��o: CAR  Tem Mesmo Naipe
*
*  $ED Descri��o da fun��o
*     Recebe ponteiros para duas cartas e diz se as duas tem mesmo naipe ou n�o
*
*  $EP Par�metros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas n�o existe
*     CAR_CondRetOK				- se as duas tiverem mesmo naipe
*	  CAR_CondRetFalse			- se n�o tiverem mesmo naipe
*
***********************************************************************/

	CAR_tpCondRet CAR_TemMesmoNaipe(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);


/***********************************************************************
*
*  $FC Fun��o: CAR  Tem Mesma Cor
*
*  $ED Descri��o da fun��o
*     Recebe ponteiros para duas cartas e diz se as duas tem mesma cor ou n�o
*
*  $EP Par�metros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas n�o existe
*     CAR_CondRetOK				- se as duas tiverem mesma cor
*	  CAR_CondRetFalse			- se n�o tiverem mesma cor
*
***********************************************************************/

	CAR_tpCondRet CAR_TemMesmaCor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);
	

/***********************************************************************
*
*  $FC Fun��o: CAR  Converte carta para string
*
*  $ED Descri��o da fun��o
*     Recebe um ponteiro para uma carta e converte para uma string representando a carta correspondente.
*	  A primeira letra da string � a letra inicial do naipe da carta e a segunda letra � o s�mbolo da carta.
*	  Por quest�o de simplicidade, o s�mbolo 10 � representado pela letra 'D' na string.
*
*  $EP Par�metros
*     pCarta		 - ponteiro para a carta
*	  stringCarta[3] - string que vai receber a string que representa a carta dada
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se a carta n�o existe
*     CAR_CondRetOK				- se retornou a string sem problemas
*
***********************************************************************/

	CAR_tpCondRet CAR_CartaParaString(CAR_tppCarta pCarta, char stringCarta[3]);


/***********************************************************************
*
*  $FC Fun��o: CAR  Converte string para carta
*
*  $ED Descri��o da fun��o
*     Recebe uma string e um endere�o que receber� a carta criada a partir da string.
*	  A primeira letra da string � a letra inicial do naipe da carta e a segunda letra � o s�mbolo da carta.
*	  Por quest�o de simplicidade, o s�mbolo 10 � representado pela letra 'D' na string.
*
*  $EP Par�metros
*	  stringCarta[3] - string a partir da qual ser� produzida uma carta
*     pCarta		 - endere�o que vai receber a carta criada
*
*  $FV Valor retornado
*	  CAR_CondRetFaltouMemoria  - se faltou mem�ria para criar carta
*	  CAR_CondRetCartaNaoExiste - se a sring n�o corresponde a uma carta v�lida
*     CAR_CondRetOK				- se retornou a string sem problemas
*
***********************************************************************/

	CAR_tpCondRet CAR_StringParaCarta(char stringCarta[3], CAR_tppCarta *pCarta);


/***********************************************************************
*
*  $FC Fun��o: CAR  Compara cartas
*
*  $ED Descri��o da fun��o
*     Recebe duas cartas e verifica se s�o iguais ou diferentes.
*
*  $EP Par�metros
*	  pCarta1 - ponteiro para a primeira carta
*     pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas n�o existir
*     CAR_CondRetOK				- se as cartas s�o iguais
*	  CAR_CondRetFalse			- se as cartas s�o diferentes
*
***********************************************************************/

	CAR_tpCondRet CAR_ComparaCartas(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2) ;

#undef Cartas_EXT

/********** Fim do m�dulo de defini��o: CAR  Cartas **********/

#endif
