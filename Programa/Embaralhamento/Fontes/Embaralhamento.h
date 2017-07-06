#if ! defined( EMBARALHAMENTO_ )
#define EMBARALHAMENTO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: EMB  Embaralhamento
*
*  Arquivo gerado:              Embaralhamento.h
*  Letras identificadoras:      EMB
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       psm   30/abr/2017 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa baralhos de 52 cartas e embaralhamento.
*     Baralhos s�o compostos por uma lista de cartas.
*
***************************************************************************/
 
#include   "LISTA.H"
#include   "Cartas.h"

#if defined( EMBARALHAMENTO_OWN )
   #define EMBARALHAMENTO_EXT
#else
   #define EMBARALHAMENTO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um baralho */

typedef struct EMB_tagBaralho * EMB_tppBaralho ;


/***********************************************************************
*
*  $TC Tipo de dados: EMB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do m�dulo Embaralhamento
*
***********************************************************************/

   typedef enum {

         EMB_CondRetOK ,
               /* Concluiu corretamente */

		 EMB_CondRetBaralhoVazio ,
			   /* O baralho est� vazio */

         EMB_CondRetTamanhoErrado ,
               /* N�o encontrou o valor procurado */

         EMB_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao tentar criar um baralho */

		 EMB_CondRetBaralhoNaoExiste 
			   /* Se algo no baralho � NULL e n�o poderia ser */

   } EMB_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: EMB  &Criar baralho
*
*  $ED Descri��o da fun��o
*     Cria um baralho.
*	  Um baralho � composto por um ponteiro para uma cabe�a de uma lista com as cartas.
*	  O baralho � criado com todas as 52 cartas em ordem alfab�tica por naipe e, em
*     cada naipe, em ordem crescente por s�mbolo.
*
*  $EP Par�metros
*	  pBaralho		- endere�o que vai receber o baralho a ser criado
*
*  $FV Valor retornado
*     EMB_CondRetOK				- se tiver criado o baralho com sucesso
*	  EMB_CondRetFaltouMemoria  - se n�o tiver conseguido alocar mem�ria para o baralho
*	  EMB_CondRetListaNaoExiste - se (*pBaralho)->pCartas � NULL
*
***********************************************************************/

   EMB_tpCondRet EMB_CriarBaralho( EMB_tppBaralho *pBaralho ) ;


/***********************************************************************
*
*  $FC Fun��o: EMB  &Destruir baralho
*
*  $ED Descri��o da fun��o
*     Destr�i o baralho fornecido.
*     O par�metro ponteiro para o baralho n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, o baralho resultar�
*     estruturalmente incorreto.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     EMB_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   EMB_tpCondRet EMB_DestruirBaralho( EMB_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Fun��o: EMB  &Embaralhar
*
*  $ED Descri��o da fun��o
*     Embaralha as cartas contidas no baralho em uma ordem aleat�ria.
*	  Pega as cartas da lista do baralho e distribui em ordem aleat�ria
*	  em uma nova lista. Depois, troca o ponteiro da lista do baralho.
*
*  $EP Par�metros
*     pBaralho - ponteiro para o baralho a ser embaralhado
*
*  $FV Valor retornado
*     EMB_CondRetOK				  - embaralhou sem problemas
*	  EMB_CondRetTamanhoErrado	  - tamanho do baralho errado
*	  EMB_CondRetFaltouMemoria	  - faltou memoria para criar a lista nova
*	  EMB_CondRetBaralhoNaoExiste - pBaralho � NULL
*
***********************************************************************/

   EMB_tpCondRet EMB_Embaralhar( EMB_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Fun��o: EMB  &Obter lista de cartas
*
*  $ED Descri��o da fun��o
*     Recebe um baralho e guarda em um endere�o recebido a lista de cartas
*     do baralho. Baralho passa a ficar vazio.
*
*  $EP Par�metros
*     pBaralho - ponteiro para o baralho
*	  pLista   - endere�o que vai receber a lista de cartas
*
*  $FV Valor retornado
*     EMB_CondRetOK				- obteve a lista sem problemas
*	  EMB_CondRetTamanhoErrado	- tamanho do baralho errado
*
***********************************************************************/

   EMB_tpCondRet EMB_ObterListaCartas( EMB_tppBaralho pBaralho, LIS_tppLista *pLista ) ;


#undef EMBARALHAMENTO_EXT

/********** Fim do m�dulo de defini��o: EMB  Embaralhamento **********/
#else
#endif