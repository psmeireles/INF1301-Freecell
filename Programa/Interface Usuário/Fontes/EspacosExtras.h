#if !defined( EspacosExtras_MOD )
#define EspacosExtras_MOD

/***************************************************************************
*
*  $MCD Módulo de definição: ESPEXT Espaços Extras
*
*  Arquivo gerado:              EspaçosExtras.h
*  Letras identificadoras:      ESPEXT
*
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: rtn
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1		  rtn	14/04/2017	Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa os Espaços Extras do jogo Freecell.
*     Os Espaços Extras são os espaços onde podem ser armazenadas no máximo 4 cartas quaisquer, sendo uma em cada espaço. 
*     Normalmente, essas cartas estão impedindo o alcance de outras cartas e por isso precisam ser movidas.
*	  O tabuleiro do jogo tem 4 espaços extras.
***************************************************************************/

#include "Cartas.h"
#include "LISTA.H"

/* Controle de escopo do arquivo de definição */
#if defined( EspacosExtras_MOD )
	#define EspacosExtras_EXT
#else
	#define EspacosExtras_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um conjunto de espaços extras */

typedef struct ESPEXT_tagEspExt * ESPEXT_tppEspExt;

/***********************************************************************
*
*  $TC Tipo de dados: ESPEXT Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de espaços extras
*
***********************************************************************/

typedef enum {

	ESPEXT_CondRetOK,
	/* Concluiu corretamente */

	ESPEXT_CondRetListaVazia,
	/* A lista não contém elementos */

	ESPEXT_CondRetListaNaoExiste,
	/* A lista não existe */

	ESPEXT_CondRetNaoAchou,
	/* Não encontrou o valor procurado */

	ESPEXT_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de lista */
	
	ESPEXT_CondRetImpossRetirarCarta,
	/* A carta especificada não pode ser removida */

	ESPEXT_CondRetImpossInserirCarta,
	/* A carta especificada não pode ser inserida */

	ESPEXT_CondRetImpossivelImprimir,
	/* Impossivel imprimir espaços extras */

	ESPEXT_CondRetEspExtNaoExiste
	/* pEspExt é NULL */

} ESPEXT_tpCondRet;


/***********************************************************************
*
*  $FC Função: ESPEXT  Criar os espaços extras
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o primeiro espaço extra.
*     Este ponteiro será utilizado pelas funções que manipulem os espaços extras.
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK				- se tiver criado o espaço extra com sucesso.
*	  ESPEXT_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para 
*									 o espaço extra.
*
***********************************************************************/
	
	ESPEXT_tpCondRet ESPEXT_CriarEspExt( ESPEXT_tppEspExt *pEspExt ) ;


/***********************************************************************
*
*  $FC Função: ESPEXT  Destruir espaços extras
*
*  $ED Descrição da função
*     Destrói os espaços extras fornecidos.
*     O parâmetro ponteiro para o espaço não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*
*  $EP Parâmetros
*     pEspExt - ponteiro para os espaços extras
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK - destruiu sem problemas
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_DestruirEspExt( ESPEXT_tppEspExt pEspExt ) ;



/***********************************************************************
*
*  $FC Função: ESPEXT  Inserir carta em espaço extra
*
*  $ED Descrição da função
*     Insere novo elemento no primeiro espaço extra vazio.
*     Caso os espaços estejam vazios, insere o primeiro elemento da lista.
*	  Só podem ser inseridos até 4 elementos.
*
*  $EP Parâmetros
*     pEspExt	  - ponteiro para os espaços extras
*     pListaCarta - ponteiro para a lista de carta a ser inserida
*				    Não pode ser NULL
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK				   - se inseriu corretamente
*     ESPEXT_CondRetListaVazia		   - se a lista com a carta a ser inserida está vazia
*	  ESPEXT_CondRetImpossInserirCarta - se não pôde inserir
*	  ESPEXT_CondRetListaNaoExiste	   - se alguma lista for NULL
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_InserirCarta(ESPEXT_tppEspExt pEspExt,  LIS_tppLista pListaCarta);

/***********************************************************************
*
*  $FC Função: ESPEXT  Remover elemento dos espaços extras
*
*  $ED Descrição da função
*     Remove o elemento especificado dos espaços extras. 
*	  A carta removida vai ser retornada em uma lista.
*
*  $EP Parâmetros
*	  pEspExt - espaços extras
*     pCarta - carta a ser retirada dos espaços extras
*	  pListaRemovida - lista que receberá a carta removida
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK						 - se removeu a carta com sucesso
*	  ESPEXT_CondRetFaltouMemoria			 - se faltou memória ao criar a lista para a carta
*	  ESPEXT_CondRetListaVazia				 - se os espaços extras estão vazios
*	  ESPEXT_CondRetNaoAchou				 - se a carta a ser retirada não está nos espaços extras
*	  ESPEXT_CondRetListaNaoExiste			 - se a lista do baralho não existe
*	  ESPEXT_CondRetImpossRetirarCarta		 - se o baralho ou a carta não existem
*
***********************************************************************/

	ESPEXT_tpCondRet  ESPEXT_RemoverCarta(ESPEXT_tppEspExt pEspExt,
										  CAR_tppCarta pCarta,
										  LIS_tppLista *pListaRemovida);


/***********************************************************************
*
*  $FC Função: ESPEXT  Imprimir espaços extras
*
*  $ED Descrição da função
*     Imprime na tela as cartas nos espaços extras. Caso um espaço esteja vazio,
*	  será impresso '0'.
*
*  $EP Parâmetros
*     pEspExt - ponteiro para espaços extras a serem impressos
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK					     - se imprimiu com sucesso
*	  ESPEXT_CondRetImpossivelImprimir		 - se falhou ao imprimir alguma carta
*	  ESPEXT_CondRetEspExtNaoExiste
*	  ESPEXT_CondRetListaNaoExiste
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_ImprimeEspExt(ESPEXT_tppEspExt pEspExt) ;


/***********************************************************************
*
*  $FC Função: ESPEXT  &Obter lista de cartas
*
*  $ED Descrição da função
*     Recebe uma espaço extra e guarda em um endereço recebido a lista de cartas
*     dos espaços.
*
*  $EP Parâmetros
*     pEspExt  - ponteiro para a sequência visível
*	  pLista   - endereço que vai receber a lista de cartas
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK	
*	  ESPEXT_CondRetEspExtNaoExiste
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_ObterListaCartas( ESPEXT_tppEspExt pEspExt, LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Função: ESPEXT  Obter numero de espaços espaços extras vazios
*
*  $ED Descrição da função
*     Obtém número de espaços extras vazios.
*
*  $EP Parâmetros
*     pEspExt   - espaços extras
*     qtdVazios - endereço da variável que vai receber a quantidade de espaços
*				  extras vazios.
*
*  $FV Valor retornado
*     ESPEXT_CondRetOK
*	  ESPEXT_CondRetEspExtNaoExiste
*
***********************************************************************/

	ESPEXT_tpCondRet ESPEXT_ObterNumEspExtVazios( ESPEXT_tppEspExt pEspExt, int *qtdVazios ) ;

#undef EspacosExtras_EXT

/********** Fim do módulo de definição: ESPEXT  Espaços extras **********/
#endif