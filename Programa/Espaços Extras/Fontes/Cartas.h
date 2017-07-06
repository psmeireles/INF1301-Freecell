#if ! defined( Cartas_MOD )
#define Cartas_MOD
/***************************************************************************
*
*  $MCD Módulo de definição: CAR Cartas
*
*  Arquivo gerado:              Cartas.h
*  Letras identificadoras:      CAR
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1		  psm	14/abr/2017	Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o tipo Cartas e as funções que determinam se uma carta é sucessora ou antecessora de outra.
*
***************************************************************************/

#if defined( Cartas_OWN )
	#define Cartas_EXT
#else
	#define Cartas_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo de referência para uma carta */
	typedef struct CAR_tagCarta * CAR_tppCarta;



/***********************************************************************
*
*  $TC Tipo de dados: CAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da carta
*
***********************************************************************/

	typedef enum {

		CAR_CondRetOK,
		/* Concluiu corretamente */

		CAR_CondRetFaltouMemoria,
		/* Faltou memória ao alocar */

		CAR_CondRetCartaNaoExiste,
		/* Concluiu que a carta não existe */

		CAR_CondRetFalse
		/* Função não retornou o que diz o título dela */

	} CAR_tpCondRet;


/***********************************************************************
*
*  $TC Tipo de dados: CAR Naipe
*
*
*  $ED Descrição do tipo
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
*  $ED Descrição do tipo
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
*  $ED Descrição do tipo
*     Cores de uma carta
*
***********************************************************************/
	
	typedef enum {

		Preto,
		Vermelho

	} CAR_Cor;


/***********************************************************************
*
*  $FC Função: CAR  Criar uma carta
*
*  $ED Descrição da função
*     Cria uma carta
*
*  $EP Parâmetros
*     simbolo - símbolo da carta a ser criada
*	  naipe   - naipe da carta a ser criada
*     cor	  - cor da carta a ser criada
*	  pCarta  - endereço que vai receber a carta a ser criada
*
*  $FV Valor retornado
*     CAR_CondRetOK				- se criou a carta sem problemas
*	  CAR_CondRetFaltouMemoria  - se faltou memória ao alocar a carta
*
***********************************************************************/

	CAR_tpCondRet CAR_CriarCarta(CAR_Simbolo simbolo, CAR_Naipe naipe, CAR_tppCarta *pCarta);


/***********************************************************************
*
*  $FC Função: CAR  Destruir Carta
*
*  $ED Descrição da função
*     Destrói a carta fornecida.
*     O parâmetro ponteiro para a carta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta
*
*  $FV Valor retornado
*     CAR_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	CAR_tpCondRet CAR_DestruirCarta(CAR_tppCarta pCarta);


/***********************************************************************
*
*  $FC Função: CAR  Simbolo sucessor
*
*  $ED Descrição da função
*     Recebe ponteiros para duas cartas e diz se o símbolo da segunda é sucessor do da primeira.
*
*  $EP Parâmetros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas não existe
*     CAR_CondRetOK				- se o símbolo da segunda carta for sucessor do da primeira
*	  CAR_CondRetFalse			- caso contrário
*
***********************************************************************/

	CAR_tpCondRet CAR_SimboloSucessor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);


/***********************************************************************
*
*  $FC Função: CAR  Símbolo antecessor
*
*  $ED Descrição da função
*     Recebe ponteiros para duas cartas e diz se o símbolo da segunda é antecessor do da primeira.
*
*  $EP Parâmetros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas não existe
*     CAR_CondRetOK				- se o símbolo da segunda carta for antecessor do da primeira
*	  CAR_CondRetFalse			- caso contrário
*
***********************************************************************/

	CAR_tpCondRet CAR_SimboloAntecessor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);


/***********************************************************************
*
*  $FC Função: CAR  É Primeira Carta
*
*  $ED Descrição da função
*     Recebe ponteiro para uma carta e diz se seu símbolo corresponde ao primeiro, 
*     entre os 13, na ordem crescente. Ou seja, se seu símbolo é ou não S_A.
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se a carta não existe
*     CAR_CondRetOK				- se o símbolo da carta for um S_A
*	  CAR_CondRetFalse			- se o símbolo da carta não for um S_A
*
***********************************************************************/

	CAR_tpCondRet CAR_EhPrimeiraCarta(CAR_tppCarta pCarta);


/***********************************************************************
*
*  $FC Função: CAR  Tem Mesmo Naipe
*
*  $ED Descrição da função
*     Recebe ponteiros para duas cartas e diz se as duas tem mesmo naipe ou não
*
*  $EP Parâmetros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas não existe
*     CAR_CondRetOK				- se as duas tiverem mesmo naipe
*	  CAR_CondRetFalse			- se não tiverem mesmo naipe
*
***********************************************************************/

	CAR_tpCondRet CAR_TemMesmoNaipe(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);


/***********************************************************************
*
*  $FC Função: CAR  Tem Mesma Cor
*
*  $ED Descrição da função
*     Recebe ponteiros para duas cartas e diz se as duas tem mesma cor ou não
*
*  $EP Parâmetros
*     pCarta1 - ponteiro para a primeira carta
*	  pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas não existe
*     CAR_CondRetOK				- se as duas tiverem mesma cor
*	  CAR_CondRetFalse			- se não tiverem mesma cor
*
***********************************************************************/

	CAR_tpCondRet CAR_TemMesmaCor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2);
	

/***********************************************************************
*
*  $FC Função: CAR  Converte carta para string
*
*  $ED Descrição da função
*     Recebe um ponteiro para uma carta e converte para uma string representando a carta correspondente.
*	  A primeira letra da string é a letra inicial do naipe da carta e a segunda letra é o símbolo da carta.
*	  Por questão de simplicidade, o símbolo 10 é representado pela letra 'D' na string.
*
*  $EP Parâmetros
*     pCarta		 - ponteiro para a carta
*	  stringCarta[3] - string que vai receber a string que representa a carta dada
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se a carta não existe
*     CAR_CondRetOK				- se retornou a string sem problemas
*
***********************************************************************/

	CAR_tpCondRet CAR_CartaParaString(CAR_tppCarta pCarta, char stringCarta[3]);


/***********************************************************************
*
*  $FC Função: CAR  Converte string para carta
*
*  $ED Descrição da função
*     Recebe uma string e um endereço que receberá a carta criada a partir da string.
*	  A primeira letra da string é a letra inicial do naipe da carta e a segunda letra é o símbolo da carta.
*	  Por questão de simplicidade, o símbolo 10 é representado pela letra 'D' na string.
*
*  $EP Parâmetros
*	  stringCarta[3] - string a partir da qual será produzida uma carta
*     pCarta		 - endereço que vai receber a carta criada
*
*  $FV Valor retornado
*	  CAR_CondRetFaltouMemoria  - se faltou memória para criar carta
*	  CAR_CondRetCartaNaoExiste - se a sring não corresponde a uma carta válida
*     CAR_CondRetOK				- se retornou a string sem problemas
*
***********************************************************************/

	CAR_tpCondRet CAR_StringParaCarta(char stringCarta[3], CAR_tppCarta *pCarta);


/***********************************************************************
*
*  $FC Função: CAR  Compara cartas
*
*  $ED Descrição da função
*     Recebe duas cartas e verifica se são iguais ou diferentes.
*
*  $EP Parâmetros
*	  pCarta1 - ponteiro para a primeira carta
*     pCarta2 - ponteiro para a segunda carta
*
*  $FV Valor retornado
*	  CAR_CondRetCartaNaoExiste - se uma das cartas não existir
*     CAR_CondRetOK				- se as cartas são iguais
*	  CAR_CondRetFalse			- se as cartas são diferentes
*
***********************************************************************/

	CAR_tpCondRet CAR_ComparaCartas(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2) ;

#undef Cartas_EXT

/********** Fim do módulo de definição: CAR  Cartas **********/

#endif
