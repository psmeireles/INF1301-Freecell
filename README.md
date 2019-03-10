# Freecell
Assignment for INF1301 - Modular Programming in Pontifical Catholic University of Rio de Janeiro (PUC-Rio)

## Group members 
Renata Troccoli

Marcelo Costalonga (https://github.com/costalonga)

Pedro Meireles (https://github.com/psmeireles)


## Program description
This program implements a Freecell game. All modules have been tested with a provided automatic test framework.

## Source files

EMBARALHAMENTO.C

CARTAS.C	

LISTA.C

SEQUENCIASORDENADAS.C

SEQUENCIASVISIVEIS.C

ESPACOSEXTRAS.C

INTERFACEUSUARIO.C

PARTIDA.C

TST_ESPC.C	

TESTELISTA.C

TESTESEQORD.C

TESTESEQVIS.C

TESTEESPEXT.C

TESTECARTAS.C

TESTEEMBARALHAMENTO.C



EMBARALHAMENTO.H                                                        

CARTAS.H							

LISTA.H					

SEQUENCIASORDENADAS.H					

SEQUENCIASVISIVEIS.H						

ESPACOSEXTRAS.H

PARTIDA.H							

LERPARM.H							

GENERICO.H							

TST_ESPC.H							

CONTA.C								

CESPDIN.H


	
### Test framework		
			
ArcaboucoTeste.lib


### Counter declaration file

Lista.count



### Script files

TesteEmbaralhamento.script

TesteCartas.script

TesteLista.script

TesteListaCont.script                                                                

TesteDeturpaLista.script

TesteSeqOrd.script								

TesteSeqVis.script								

TesteEspExt.script
	
							

### Log files						

TesteLista.log								

TesteListaDebug.log

TesteDeturpaLista.log

TesteEmbaralhamento.log								

TesteCartas.log								

TesteSeqOrd.log                                                                

TesteSeqVis.log								

TesteEspExt.log



### Definition files

IdTiposEspaco.def

TiposEspacosLista.def

		
						
### Executable files

TesteLista.exe								

TesteListaDebug.exe

TesteEmbaralhamento.exe								

TesteCartas.exe								

TesteSeqOrd.exe                                                                

TesteSeqVis.exe								

TesteEspExt.exe

TesteIU.exe

TestePartida.exe



### Bat files		
					
Compila.bat                                                                
CompilaTudo.bat                                                                
CriaLib.bat                                                               
GeraMake.bat                                                               
GeraTudo.bat                                                               
LimpaObj.bat                                                                
LimpaTudo.bat                                                                
Teste.bat                                                               
TestaTudo.bat                                                               
Tudo.bat                                                                
vsvars32.bat



### Report files
					
RELATORIO-Renata.txt								

RELATORIO-Marcelo.txt								

RELATORIO-Pedro.txt


### Readme files

LEIAME.TXT
README.MD



## Usage

How to compile and execute tests:

1. Go to folder "Batches" in each module
2. Open the command line
3. Execute vsvars32.bat and tudo.bat
4. Executable will be generated in "Produto"

How to execute using .exe file:

1. Go to folder "Produto" in each module
2. Open the command line
3. Execute "Teste{MODULE_NAME}.exe"
4. Commands to execute:
		TRAB4-*.exe /s../Scripts/TesteModulo.script
	  where * is the number corresponding to the module
5. For modules that don't have test scripts, just run TRAB4-*.exe.

To play the game, follow the previous instructions with module InterfaceUsuario


## Comments
TRAB4-5 -> List with debugs

TRAB4-6 -> List without debugs
