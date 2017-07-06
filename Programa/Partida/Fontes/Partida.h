
/***************************************************************************
*
*  $MCD M�dulo de defini��o: PAR  Partida
*
*  Arquivo gerado:              Partida.h
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm, mcc
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor       Data     Observa��es
*     1		  psm, mcc	07/jun/2017	In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa uma partida de Freecell.
*	  Usa uma lista de listas para armazenar as sequ�ncias vis�veis, os espa�os
* extras e as sequ�ncias ordenadas. Cada elemento da lista aponta para a struct
* correspondente a cada uma das estruturas supracitadas. Os oito primeiros n�s
* s�o referentes �s sequ�ncias vis�veis, os quatro seguintes aos espa�os extras
* e os quatro �ltimos �s sequ�ncias ordenadas.
*	  Ao criar uma partida, distribui-se as cartas do baralho nas sequ�ncias
* vis�veis. Uma partida pode ser encerrada a qualquer momento, mesmo que o 
* objetivo n�o tenha sido alcan�ado.
*
***************************************************************************/
 
#include "Embaralhamento.h"
#include "SequenciaOrdenada.h"
#include "SequenciaVisivel.h"
#include "EspacosExtras.h"


/* Controle de escopo do arquivo de defini��o */

#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

/* Tipo refer�ncia para um tabuleiro */

typedef struct PAR_tagTabuleiro * PAR_tppTabuleiro ;

/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da partida
*
***********************************************************************/

   typedef enum {

         PAR_CondRetOK ,
               /* Concluiu corretamente */

         PAR_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         PAR_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         PAR_CondRetNaoAchou ,
               /* n�o encontrou o valor procurado */

		 PAR_CondRetEstruturaErrada,
		       /* Estrutura do tabuleiro est� errada */

         PAR_CondRetFaltouMemoria,
		       /* Faltou mem�ria ao tentar criar um elemento de lista */

		 PAR_CondRetImpossivelImprimir,
               /* N�o foi poss�vel imprimir o tabuleiro */

		 PAR_CondRetVenceu,
               /* Venceu o jogo */

		 PAR_CondRetTabuleiroNaoExiste,
			   /* pTabuleiro == NULL */

		 PAR_CondRetListaNaoExiste,
			   /* Alguma lista � NULL */

		 PAR_CondRetBaralhoNaoExiste
			   /* Alguma baralho � NULL */

   } PAR_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: PAR  &Iniciar partida
*
*  $ED Descri��o da fun��o
*     Inicia uma partida de Freecell.
*     Cria um tabuleiro e um baralho. Embaralha as cartas e distribui nas
* sequ�ncias vis�veis do tabuleiro criado. As quatro primeiras sequ�ncias
* recebem 7 cartas cada, e as quatro �ltimas recebem 6.
*
*  $EP Par�metros
*     pTabuleiro - endere�o onde ser� criado o tabuleiro
*
*  $FV Valor retornado
*     PAR_CondRetOK				- se tiver iniciado a partida com sucesso
*	  PAR_CondRetFaltouMemoria  - se n�o tiver conseguido alocar mem�ria para o tabuleiro
*
***********************************************************************/

   PAR_tpCondRet PAR_IniciarPartida( PAR_tppTabuleiro *pTabuleiro ) ;

/***********************************************************************
*
*  $FC Fun��o: PAR  &Jogar
*
*  $ED Descri��o da fun��o
*     Fun��o que imprime as mensagens para o usu�rio, indicando os possiveis
* movimentos a serem feitos e executa as jogadas de movimenta��o entre cartas 
* de acordo com o que o usu�rio digitou. Exibe tamb�m mensagens de erro quando
* o usu�rio tenta efetuar um movimento inv�lido.
*	  Permite o usu�rio cancelar uma jogada a qualquer momento.
*
*  $EP Par�metros
*     pTabuleiro - endere�o do tabuleiro que cont�m todas as cartas, sequ�ncias e 
*				   espa�os extras.
*
*  $FV Valor retornado
*     PAR_CondRetOK				 - se tiver efetuado uma jogada com sucesso
*	  PAR_CondRetFaltouMemoria   - se n�o tiver conseguido alocar mem�ria alguma de suas vari�veis
*	  PAR_CondRetEstruturaErrada - se alguma das estruturas utilizadas estiver errada
***********************************************************************/

   PAR_tpCondRet PAR_Jogar( PAR_tppTabuleiro pTabuleiro ) ;


/***********************************************************************
*
*  $FC Fun��o: PAR  &Verificar vit�ria
*
*  $ED Descri��o da fun��o
*     Verifica se o jogador venceu a partida.
*     Verifica se as quatro sequ�ncias ordenadas est�o cheias.
*
*  $EP Par�metros
*     pTabuleiro - tabuleiro que cont�m as sequ�ncias
*
*  $FV Valor retornado
*     PAR_CondRetOK				  - se ainda n�o tiver vencido
*	  PAR_CondRetEstruturaErrada  - se a estrutura do tabuleiro estiver errada
*	  PAR_CondRetVenceu			  - se o jogador tiver vencido
*	  PAR_CondRetTabuleiroNaoExiste
*	  PAR_CondRetListaNaoExiste
*
***********************************************************************/

   PAR_tpCondRet PAR_VerificarVitoria( PAR_tppTabuleiro pTabuleiro ) ;



/***********************************************************************
*
*  $FC Fun��o: PAR  &Terminar partida
*
*  $ED Descri��o da fun��o
*     Termina uma partida de Freecell.
*     Destr�i o tabuleiro e imprime na tela que a partida foi encerrada.
*
*  $EP Par�metros
*     pTabuleiro - tabuleiro que ser� destru�do
*
*  $FV Valor retornado
*     PAR_CondRetOK				 - se tiver terminado a partida com sucesso
*	  PAR_CondRetEstruturaErrada - se a estrutura do tabuleiro estiver errada
*								   e n�o tiver sido poss�vel destru�-lo
*
***********************************************************************/

   PAR_tpCondRet PAR_TerminarPartida( PAR_tppTabuleiro pTabuleiro ) ;


/***********************************************************************
*
*  $FC Fun��o: PAR  &Imprimir tabuleiro
*
*  $ED Descri��o da fun��o
*     Imprime a situa��o atual do tabuleiro.
*     Os espa�os extras ser�o impressos na primeira linha � esquerda.
*	  Na mesma linha, mais	� direita, ser�o impressas as sequ�ncias ordenadas.
*	  Por fim, nas 8 linhas seguintes ser�o impressas as sequ�ncias vis�veis.
*
*  $EP Par�metros
*     pTabuleiro - tabuleiro que ser� impresso
*
*  $FV Valor retornado
*     PAR_CondRetOK					- se tiver terminado a partida com sucesso
*	  PAR_CondRetEstruturaErrada	- se a estrutura do tabuleiro estiver errada
*	  PAR_CondRetImpossivelImprimir - se n�o tiver sido poss�vel imprimir
*	  PAR_CondRetTabuleiroNaoExiste
*	  PAR_CondRetListaNaoExiste
*
***********************************************************************/

   PAR_tpCondRet PAR_ImprimirTabuleiro( PAR_tppTabuleiro pTabuleiro ) ;

#undef PARTIDA_EXT

/********** Fim do m�dulo de defini��o: PAR  Lista duplamente encadeada **********/

