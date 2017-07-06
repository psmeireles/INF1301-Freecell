/***************************************************************************
*
*  $MCI Módulo de implementação: IU	Interface Usuário
*
*  Arquivo gerado:              InterfaceUsuario.c
*  Letras identificadoras:      IU
*
*  Projeto: INF 1301 / Freecell
*  Gestor:  DI/PUC-Rio
*  Autores: psm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1		  psm	15/jun/2017	Início do desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   "Partida.h"


int main()
{

	char c ;
	PAR_tppTabuleiro pTabuleiro ;
	PAR_tpCondRet retorno ;

	printf( "FREECELL\n" ) ;
	printf( "Desenvolvido por:\n" ) ;
	printf( "Marcelo Costalonga\nPedro Meireles\nRenata Acha\n\n" ) ;

	INICIO:
	printf( "Para comecar o jogo, digite 'c':\n" ) ;
	fflush(stdin) ;
	scanf( " %c", &c) ;

	if( c == 'c' )
	{
		retorno = PAR_IniciarPartida( &pTabuleiro ) ;
		if( retorno == PAR_CondRetFaltouMemoria )
		{
			printf( "\nSinto muito, nao foi possivel iniciar o jogo por falta de memoria. Tente novamente mais tarde.\n" ) ;
			return 0;
		}
	}
	else
	{
		system("cls") ;
		printf( "\nComando Invalido. " ) ;
		goto INICIO ;
	}
	

	while( PAR_VerificarVitoria( pTabuleiro ) != PAR_CondRetVenceu )
	{
		system("cls") ;
		PAR_ImprimirTabuleiro( pTabuleiro ) ;
		ESCOLHA:
		printf( "\nDigite 'j' para mover uma carta ou 't' para terminar a partida:\n" ) ;
		fflush(stdin) ;
		scanf( " %c", &c) ;
		printf( "\n" ) ;

		do
		{
			switch( c )
			{
			case 'j':
				{
					PAR_Jogar( pTabuleiro ) ;
					break ;
				}
			case 't':
				{
					system("cls") ;
					PAR_TerminarPartida( pTabuleiro ) ;
					return 0 ;
				}
			default:
				{
					printf( "\nComando Invalido. " ) ;
					goto ESCOLHA ;
				}
			}
		} while( !( c == 'j' || c == 't' ) ) ;

		printf("\n") ;
	}

	printf( "\nParabens, voce venceu!\n" ) ;
	PAR_TerminarPartida( pTabuleiro ) ;
	return 0 ;

}