REM Executa os testes de todos os Scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TesteSeqOrd	/s..\Scripts\TesteSeqOrd	/l..\Produto\TesteSeqOrd	/a..\Scripts\estatisticas
if errorlevel 4 goto sai

..\Ferramentas\exbestat /e..\Scripts\estatisticas

:sai