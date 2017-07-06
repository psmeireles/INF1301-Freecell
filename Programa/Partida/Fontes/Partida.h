
/***************************************************************************
*
*  $MCD Módulo de definição: PAR  Partida
*
*  Arquivo gerado:              Partida.h
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
*  $ED Descrição do módulo
*     Implementa uma partida de Freecell.
*	  Usa uma lista de listas para armazenar as sequências visíveis, os espaços
* extras e as sequências ordenadas. Cada elemento da lista aponta para a struct
* correspondente a cada uma das estruturas supracitadas. Os oito primeiros nós
* são referentes às sequências visíveis, os quatro seguintes aos espaços extras
* e os quatro últimos às sequências ordenadas.
*	  Ao criar uma partida, distribui-se as cartas do baralho nas sequências
* visíveis. Uma partida pode ser encerrada a qualquer momento, mesmo que o 
* objetivo não tenha sido alcançado.
*
***************************************************************************/
 
#include "Embaralhamento.h"
#include "SequenciaOrdenada.h"
#include "SequenciaVisivel.h"
#include "EspacosExtras.h"


/* Controle de escopo do arquivo de definição */

#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

/* Tipo referência para um tabuleiro */

typedef struct PAR_tagTabuleiro * PAR_tppTabuleiro ;

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da partida
*
***********************************************************************/

   typedef enum {

         PAR_CondRetOK ,
               /* Concluiu corretamente */

         PAR_CondRetListaVazia ,
               /* A lista não contém elementos */

         PAR_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         PAR_CondRetNaoAchou ,
               /* não encontrou o valor procurado */

		 PAR_CondRetEstruturaErrada,
		       /* Estrutura do tabuleiro está errada */

         PAR_CondRetFaltouMemoria,
		       /* Faltou memória ao tentar criar um elemento de lista */

		 PAR_CondRetImpossivelImprimir,
               /* Não foi possível imprimir o tabuleiro */

		 PAR_CondRetVenceu,
               /* Venceu o jogo */

		 PAR_CondRetTabuleiroNaoExiste,
			   /* pTabuleiro == NULL */

		 PAR_CondRetListaNaoExiste,
			   /* Alguma lista é NULL */

		 PAR_CondRetBaralhoNaoExiste
			   /* Alguma baralho é NULL */

   } PAR_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PAR  &Iniciar partida
*
*  $ED Descrição da função
*     Inicia uma partida de Freecell.
*     Cria um tabuleiro e um baralho. Embaralha as cartas e distribui nas
* sequências visíveis do tabuleiro criado. As quatro primeiras sequências
* recebem 7 cartas cada, e as quatro últimas recebem 6.
*
*  $EP Parâmetros
*     pTabuleiro - endereço onde será criado o tabuleiro
*
*  $FV Valor retornado
*     PAR_CondRetOK				- se tiver iniciado a partida com sucesso
*	  PAR_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para o tabuleiro
*
***********************************************************************/

   PAR_tpCondRet PAR_IniciarPartida( PAR_tppTabuleiro *pTabuleiro ) ;

/***********************************************************************
*
*  $FC Função: PAR  &Jogar
*
*  $ED Descrição da função
*     Função que imprime as mensagens para o usuário, indicando os possiveis
* movimentos a serem feitos e executa as jogadas de movimentação entre cartas 
* de acordo com o que o usuário digitou. Exibe também mensagens de erro quando
* o usuário tenta efetuar um movimento inválido.
*	  Permite o usuário cancelar uma jogada a qualquer momento.
*
*  $EP Parâmetros
*     pTabuleiro - endereço do tabuleiro que contém todas as cartas, sequências e 
*				   espaços extras.
*
*  $FV Valor retornado
*     PAR_CondRetOK				 - se tiver efetuado uma jogada com sucesso
*	  PAR_CondRetFaltouMemoria   - se não tiver conseguido alocar memória alguma de suas variáveis
*	  PAR_CondRetEstruturaErrada - se alguma das estruturas utilizadas estiver errada
***********************************************************************/

   PAR_tpCondRet PAR_Jogar( PAR_tppTabuleiro pTabuleiro ) ;


/***********************************************************************
*
*  $FC Função: PAR  &Verificar vitória
*
*  $ED Descrição da função
*     Verifica se o jogador venceu a partida.
*     Verifica se as quatro sequências ordenadas estão cheias.
*
*  $EP Parâmetros
*     pTabuleiro - tabuleiro que contém as sequências
*
*  $FV Valor retornado
*     PAR_CondRetOK				  - se ainda não tiver vencido
*	  PAR_CondRetEstruturaErrada  - se a estrutura do tabuleiro estiver errada
*	  PAR_CondRetVenceu			  - se o jogador tiver vencido
*	  PAR_CondRetTabuleiroNaoExiste
*	  PAR_CondRetListaNaoExiste
*
***********************************************************************/

   PAR_tpCondRet PAR_VerificarVitoria( PAR_tppTabuleiro pTabuleiro ) ;



/***********************************************************************
*
*  $FC Função: PAR  &Terminar partida
*
*  $ED Descrição da função
*     Termina uma partida de Freecell.
*     Destrói o tabuleiro e imprime na tela que a partida foi encerrada.
*
*  $EP Parâmetros
*     pTabuleiro - tabuleiro que será destruído
*
*  $FV Valor retornado
*     PAR_CondRetOK				 - se tiver terminado a partida com sucesso
*	  PAR_CondRetEstruturaErrada - se a estrutura do tabuleiro estiver errada
*								   e não tiver sido possível destruí-lo
*
***********************************************************************/

   PAR_tpCondRet PAR_TerminarPartida( PAR_tppTabuleiro pTabuleiro ) ;


/***********************************************************************
*
*  $FC Função: PAR  &Imprimir tabuleiro
*
*  $ED Descrição da função
*     Imprime a situação atual do tabuleiro.
*     Os espaços extras serão impressos na primeira linha à esquerda.
*	  Na mesma linha, mais	à direita, serão impressas as sequências ordenadas.
*	  Por fim, nas 8 linhas seguintes serão impressas as sequências visíveis.
*
*  $EP Parâmetros
*     pTabuleiro - tabuleiro que será impresso
*
*  $FV Valor retornado
*     PAR_CondRetOK					- se tiver terminado a partida com sucesso
*	  PAR_CondRetEstruturaErrada	- se a estrutura do tabuleiro estiver errada
*	  PAR_CondRetImpossivelImprimir - se não tiver sido possível imprimir
*	  PAR_CondRetTabuleiroNaoExiste
*	  PAR_CondRetListaNaoExiste
*
***********************************************************************/

   PAR_tpCondRet PAR_ImprimirTabuleiro( PAR_tppTabuleiro pTabuleiro ) ;

#undef PARTIDA_EXT

/********** Fim do módulo de definição: PAR  Lista duplamente encadeada **********/

