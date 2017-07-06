REM Executa os testes de todos os Scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TesteLista	/s..\Scripts\TesteLista	/l..\Produto\TesteLista	/a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Produto\TesteListaDebug	/s..\Scripts\TesteListaCont	/l..\Produto\TesteListaDebug	/a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Produto\TesteListaDebug	/s..\Scripts\TesteDeturpaLista	/l..\Produto\TesteDeturpaLista	/a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Ferramentas\exbestat /e..\Scripts\estatisticas

:sai