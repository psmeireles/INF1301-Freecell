#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessório desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */

		 LIS_CondRetEstruturaErrada,
			   /* Lista criada de forma errada */

		 LIS_CondRetListaNaoExiste
			   /* Lista referenciada é NULL */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaTipoCabeca        =  1 ,
               /* Modifica o tipo da cabeça */

         DeturpaOrigemNulo        =  2 ,
               /* Anula ponteiro origem */

         DeturpaCorrenteNulo      =  3 ,
               /* Anula ponteiro corrente */

       } LIS_tpModosDeturpacao ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver Descrição do módulo.
*	  pLista		- endereço que vai receber a lista a ser criada
*
*  $FV Valor retornado
*     LIS_CondRetOK				- se tiver criado a lista com sucesso
*	  LIS_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para a lista
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( void ( * ExcluirValor ) ( void * pDado ), LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $FV Valor retornado
*     LIS_CondRetOK    - esvaziou sem problemas
*     LIS_CondRetListaNaoExiste - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*     LIS_CondRetListaNaoExiste - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento após o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*        LIS_CondRetListaNaoExiste - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*     LIS_CondRetListaNaoExiste - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Remover elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento a esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento a direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve remover o elemento.
*     pCabeca  - endereço que vai receber a lista na qual está o elemento removido .
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*	  LIS_CondRetFaltouMemoria
*     LIS_CondRetListaNaoExiste - uma das listas recebidas é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_RemoverElemento( LIS_tppLista pLista, LIS_tppLista *pCabeca ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*	  pValor - endereço da variável que vai receber o valor
*
*  $FV Valor retornado
*     LIS_CondRetOK			- se obteve o valor sem problemas
*	  LIS_CondRetListaVazia - se a lista estiver vazia
*     LIS_CondRetListaNaoExiste  - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void **pValor );


/***********************************************************************
*
*  $FC Função: LIS  &Obter tamanho da lista
*
*  $ED Descrição da função
*     Obtem o tamanho da lista
*
*  $EP Parâmetros
*     pLista   - ponteiro para a lista de onde se quer o valor
*	  pTamanho - endereço da variável que vai receber o tamanho
*
*  $FV Valor retornado
*     LIS_CondRetOK			- se obteve o valor sem problemas
*     LIS_CondRetListaNaoExiste  - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterTam( LIS_tppLista pLista, int *pTamanho );


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     LIS_CondRetOK - foi para o início sem problemas
*     LIS_CondRetListaNaoExiste - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet IrInicioLista( LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     LIS_CondRetOK - foi para o final sem problemas
*     LIS_CondRetListaNaoExiste - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet IrFinalLista( LIS_tppLista *pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo Avança em direção ao final
*     Se numElem for negativo Avança em direção ao início
*     numElem pode ser maior do que o número de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o Número de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                           elementos
*     LIS_CondRetListaVazia - se a lista está vazia
*     LIS_CondRetListaNaoExiste  - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*	  CompararValor	 - ponteiro para função de comparação de valor.
*					   Retorna 0 se for igual e diferente de 0 caso contrário.
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoAchou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia - se a lista estiver vazia
*     LIS_CondRetListaNaoExiste  - lista recebida é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( int   (* CompararValor) ( void * pDado1, void * pDado2 ), 
									LIS_tppLista pLista , void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Retirar lista de elementos
*
*  $ED Descrição da função
*     Retira o elemento corrente e todos os seus sucessores da lista e guarda-os
*	  em uma nova lista. O elemento corrente de cada uma das listas passa a ser o
*	  elemento final.
*    
*  $EP Parâmetros
*     pLista	  - ponteiro para a lista de onde o elemento será retirado
*	  pCabecaCorr - endereço que vai receber a lista com os elementos a serem retirados
*     
*  $FV Valor retornado
*    LIS_CondRetOK	      - se tiver retirado sem problemas
*	 LIS_FaltouMemoria    - se tiver faltado memória ao alocar a nova lista
*	 LIS_ListaVazia	      - se a lista de onde o elemento será retirado estiver vazia
*    LIS_CondRetListaNaoExiste - pLista é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_RetirarListaElem(LIS_tppLista pLista, LIS_tppLista *pCabecaCorr);


/***********************************************************************
*
*  $FC Função: LIS  &Concatenar lista
*
*  $ED Descrição da função
*     Concatena uma lista no fim da lista principal. Estraga pConcatenada.
*    
*  $EP Parâmetros
*     pPrincipal  - ponteiro para a lista principal
*	  pConcatenada- ponteiro para a lista que será concatenada na principal
*     
*  $FV Valor retornado
*     LIS_CondRetListaVazia - se a lista concatenada estiver vazia
*	  LIS_CondRetOK			- se a concatenação foi bem sucedida
*     LIS_CondRetListaNaoExiste  - uma das listas recebidas é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ConcatenarLista(LIS_tppLista pPrincipal, LIS_tppLista pConcatenada);


/***********************************************************************
*
*  $FC Função: LIS  &Verificar uma lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente uma determinada lista.
*     Também marca todos os espaços por ela ocupados.
*
*  $EP Parâmetros
*     $P pListaParm - ponteiro para um espaço que deveria ser uma lista.
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista( void * pListaParm ) ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Verificar uma cabeça de lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade de uma cabeça de lista.
*
*  $EP Parâmetros
*     $P pCabecaParm - ponteiro para um espaço que deveria ser uma cabeça
*                      de lista.
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarCabeca( void * pCabecaParm ) ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Verificar um elemento da lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade de um elemento da lista.
*
*  $EP Parâmetros
*     $P pElemParm - ponteiro para espaço que deveria ser um elemento da lista.
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarElem( void * pElemParm ) ;

#endif


/***********************************************************************
*
*  $FC Função: ARV  &Deturpar lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Corrompe elementos específicos da estrutura da lista.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Parâmetros
*     $P pListaParm   - lista a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpação
*                       ARV_tpModosDeturpacao identifica os modos de
*                       deturpação conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( void * pListaParm ,
                      LIS_tpModosDeturpacao ModoDeturpar ) ;

#endif

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/
#else
#endif
