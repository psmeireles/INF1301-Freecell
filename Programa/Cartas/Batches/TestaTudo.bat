REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TesteCartas	/s..\Scripts\TesteCartas /l..\Produto\TesteCartas /a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Ferramentas\exbestat /e..\Scripts\estatisticas

:sai