#if ! defined( EMBARALHAMENTO_ )
#define EMBARALHAMENTO_
/***************************************************************************
*
*  $MCD Módulo de definição: EMB  Embaralhamento
*
*  Arquivo gerado:              Embaralhamento.h
*  Letras identificadoras:      EMB
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       psm   30/abr/2017 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa baralhos de 52 cartas e embaralhamento.
*     Baralhos são compostos por uma lista de cartas.
*
***************************************************************************/
 
#include   "LISTA.H"
#include   "Cartas.h"

#if defined( EMBARALHAMENTO_OWN )
   #define EMBARALHAMENTO_EXT
#else
   #define EMBARALHAMENTO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um baralho */

typedef struct EMB_tagBaralho * EMB_tppBaralho ;


/***********************************************************************
*
*  $TC Tipo de dados: EMB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo Embaralhamento
*
***********************************************************************/

   typedef enum {

         EMB_CondRetOK ,
               /* Concluiu corretamente */

		 EMB_CondRetBaralhoVazio ,
			   /* O baralho está vazio */

         EMB_CondRetTamanhoErrado ,
               /* Não encontrou o valor procurado */

         EMB_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um baralho */

		 EMB_CondRetBaralhoNaoExiste 
			   /* Se algo no baralho é NULL e não poderia ser */

   } EMB_tpCondRet ;


/***********************************************************************
*
*  $FC Função: EMB  &Criar baralho
*
*  $ED Descrição da função
*     Cria um baralho.
*	  Um baralho é composto por um ponteiro para uma cabeça de uma lista com as cartas.
*	  O baralho é criado com todas as 52 cartas em ordem alfabética por naipe e, em
*     cada naipe, em ordem crescente por símbolo.
*
*  $EP Parâmetros
*	  pBaralho		- endereço que vai receber o baralho a ser criado
*
*  $FV Valor retornado
*     EMB_CondRetOK				- se tiver criado o baralho com sucesso
*	  EMB_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para o baralho
*	  EMB_CondRetListaNaoExiste - se (*pBaralho)->pCartas é NULL
*
***********************************************************************/

   EMB_tpCondRet EMB_CriarBaralho( EMB_tppBaralho *pBaralho ) ;


/***********************************************************************
*
*  $FC Função: EMB  &Destruir baralho
*
*  $ED Descrição da função
*     Destrói o baralho fornecido.
*     O parâmetro ponteiro para o baralho não é modificado.
*     Se ocorrer algum erro durante a destruição, o baralho resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     EMB_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   EMB_tpCondRet EMB_DestruirBaralho( EMB_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Função: EMB  &Embaralhar
*
*  $ED Descrição da função
*     Embaralha as cartas contidas no baralho em uma ordem aleatória.
*	  Pega as cartas da lista do baralho e distribui em ordem aleatória
*	  em uma nova lista. Depois, troca o ponteiro da lista do baralho.
*
*  $EP Parâmetros
*     pBaralho - ponteiro para o baralho a ser embaralhado
*
*  $FV Valor retornado
*     EMB_CondRetOK				  - embaralhou sem problemas
*	  EMB_CondRetTamanhoErrado	  - tamanho do baralho errado
*	  EMB_CondRetFaltouMemoria	  - faltou memoria para criar a lista nova
*	  EMB_CondRetBaralhoNaoExiste - pBaralho é NULL
*
***********************************************************************/

   EMB_tpCondRet EMB_Embaralhar( EMB_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Função: EMB  &Obter lista de cartas
*
*  $ED Descrição da função
*     Recebe um baralho e guarda em um endereço recebido a lista de cartas
*     do baralho. Baralho passa a ficar vazio.
*
*  $EP Parâmetros
*     pBaralho - ponteiro para o baralho
*	  pLista   - endereço que vai receber a lista de cartas
*
*  $FV Valor retornado
*     EMB_CondRetOK				- obteve a lista sem problemas
*	  EMB_CondRetTamanhoErrado	- tamanho do baralho errado
*
***********************************************************************/

   EMB_tpCondRet EMB_ObterListaCartas( EMB_tppBaralho pBaralho, LIS_tppLista *pLista ) ;


#undef EMBARALHAMENTO_EXT

/********** Fim do módulo de definição: EMB  Embaralhamento **********/
#else
#endif