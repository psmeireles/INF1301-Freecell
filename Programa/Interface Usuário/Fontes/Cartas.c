/***************************************************************************
*  $MCI M�dulo de implementa��o: CAR  Cartas
*
*  Arquivo gerado:              Cartas.c
*  Letras identificadoras:      CAR
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       psm   14/abr/2017 inicio do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>

#define Cartas_OWN
#include "Cartas.h"
#undef Cartas_OWN

/***********************************************************************
*
*  $TC Tipo de dados: CAR Descritor da carta
*
*
***********************************************************************/

	typedef struct CAR_tagCarta {

		CAR_Naipe naipe;

		CAR_Simbolo simbolo;

		CAR_Cor cor;

	} CAR_tpCarta;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CAR Criar carta
*  ****/

	CAR_tpCondRet CAR_CriarCarta(CAR_Simbolo simbolo, CAR_Naipe naipe, CAR_tppCarta *pCarta)
	{
		*pCarta = (CAR_tpCarta *)malloc(sizeof(CAR_tpCarta));
		if (*pCarta == NULL)
			return CAR_CondRetFaltouMemoria;

		(*pCarta)->simbolo = simbolo;
		(*pCarta)->naipe = naipe;

		if (naipe == Paus || naipe == Espadas)
			(*pCarta)->cor = Preto;
		else
			(*pCarta)->cor = Vermelho;

		return CAR_CondRetOK;
	} /* Fim fun��o: CAR  Criar carta */

/***************************************************************************
*
*  Fun��o: CAR Destruir carta
*  ****/

	CAR_tpCondRet CAR_DestruirCarta(CAR_tppCarta pCarta)
	{
		free(pCarta);
		return CAR_CondRetOK;
	} /* Fim fun��o: CAR  Destruir carta */


/***************************************************************************
*
*  Fun��o: CAR � sucessor
*  ****/

	CAR_tpCondRet CAR_SimboloSucessor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2)
	{
		if (pCarta1 == NULL || pCarta2 == NULL)
			return CAR_CondRetCartaNaoExiste;
		else if ( (int) pCarta1->simbolo == (int) pCarta2->simbolo - 1 )
			return CAR_CondRetOK;
		else
			return CAR_CondRetFalse;
	} /* Fim fun��o: CAR  � sucessor */


/***************************************************************************
*
*  Fun��o: CAR � antecessor
*  ****/

	CAR_tpCondRet CAR_SimboloAntecessor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2)
	{
		if (pCarta1 == NULL || pCarta2 == NULL)
			return CAR_CondRetCartaNaoExiste;
		else if ( (int) pCarta1->simbolo == (int)pCarta2->simbolo + 1)
			return CAR_CondRetOK;
		else
			return CAR_CondRetFalse;
	} /* Fim fun��o: CAR  � antecessor */


/***************************************************************************
*
*  Fun��o: CAR � Primeira Carta
*  ****/

	CAR_tpCondRet CAR_EhPrimeiraCarta(CAR_tppCarta pCarta)
	{
		if (pCarta == NULL)
			return CAR_CondRetCartaNaoExiste;
		else if (pCarta->simbolo == S_A)
			return CAR_CondRetOK;
		else
			return CAR_CondRetFalse;
	} /* Fim fun��o: CAR  � Primeira Carta */


/***************************************************************************
*
*  Fun��o: CAR Tem Mesmo Naipe
*  ****/

	CAR_tpCondRet CAR_TemMesmoNaipe(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2)
	{
		if (pCarta1 == NULL || pCarta2 == NULL)
			return CAR_CondRetCartaNaoExiste;
		else if (pCarta1->naipe == pCarta2->naipe)
			return CAR_CondRetOK;
		else
			return CAR_CondRetFalse;
	} /* Fim fun��o: CAR  Tem Mesmo Naipe */


/***************************************************************************
*
*  Fun��o: CAR Tem Mesma Cor
*  ****/

	CAR_tpCondRet CAR_TemMesmaCor(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2)
	{
		if (pCarta1 == NULL || pCarta2 == NULL)
			return CAR_CondRetCartaNaoExiste;
		else if(pCarta1->cor == pCarta2->cor)
			return CAR_CondRetOK;
		else
			return CAR_CondRetFalse;
	} /* Fim fun��o: CAR  Tem Mesma Cor */


/***************************************************************************
*
*  Fun��o: CAR Converte carta para string
*  ****/

	CAR_tpCondRet CAR_CartaParaString(CAR_tppCarta pCarta, char stringCarta[3])
	{
		if (pCarta == NULL)
			return CAR_CondRetCartaNaoExiste;

		if(pCarta->naipe == Copas)
			stringCarta[0] = 'C';
		else if(pCarta->naipe == Paus)
			stringCarta[0] = 'P';
		else if(pCarta->naipe == Espadas)
			stringCarta[0] = 'E';
		else
			stringCarta[0] = 'O';

		if(pCarta->simbolo == S_A)
			stringCarta[1] = 'A';
		else if(pCarta->simbolo == S_J)
			stringCarta[1] = 'J';
		else if(pCarta->simbolo == S_Q)
			stringCarta[1] = 'Q';
		else if(pCarta->simbolo == S_K)
			stringCarta[1] = 'K';
		else if(pCarta->simbolo == S_10)
			stringCarta[1] = 'D';
		else
			stringCarta[1] = '1' + (char) pCarta->simbolo;
		
		stringCarta[2] = '\0';
		return CAR_CondRetOK;
	} /* Fim fun��o: CAR  Converte carta para string */


/***************************************************************************
*
*  Fun��o: CAR Converte string para carta
*  ****/

	CAR_tpCondRet CAR_StringParaCarta(char stringCarta[3], CAR_tppCarta *pCarta)
	{
		CAR_Simbolo simbolo;
		CAR_Naipe naipe;

		if(stringCarta[0] == 'C')
			naipe = Copas;
		else if(stringCarta[0] == 'P')
			naipe = Paus;
		else if(stringCarta[0] == 'E')
			naipe = Espadas;
		else if(stringCarta[0] == 'O')
			naipe = Ouros;
		else
			return CAR_CondRetCartaNaoExiste;

		if(stringCarta[1] == 'A')
			simbolo = S_A;
		else if(stringCarta[1] == 'J')
			simbolo = S_J;
		else if(stringCarta[1] == 'Q')
			simbolo = S_Q;
		else if(stringCarta[1] == 'K')
			simbolo = S_K;
		else if(stringCarta[1] == 'D')
			simbolo = S_10;
		else if(stringCarta[1] >= '2' && stringCarta[1] <= '9')
			simbolo = (CAR_Simbolo) ((int) (stringCarta[1] - '2') + S_2);
		else
			return CAR_CondRetCartaNaoExiste;
		
		if( CAR_CriarCarta(simbolo, naipe, pCarta) == CAR_CondRetFaltouMemoria )
			return CAR_CondRetFaltouMemoria;

		return CAR_CondRetOK;
	} /* Fim fun��o: CAR  Converte string para carta */

	
/***************************************************************************
*
*  Fun��o: CAR Compara cartas
*  ****/

	CAR_tpCondRet CAR_ComparaCartas(CAR_tppCarta pCarta1, CAR_tppCarta pCarta2)
	{
		
		if (pCarta1 == NULL || pCarta2 == NULL)
			return CAR_CondRetCartaNaoExiste;

		if( pCarta1->simbolo == pCarta2->simbolo && pCarta1->naipe == pCarta2->naipe )
			return CAR_CondRetOK;

		return CAR_CondRetFalse;

	} /* Fim fun��o: CAR  Compara cartas */

/********** Fim do m�dulo de implementa��o: CAR  Cartas **********/
