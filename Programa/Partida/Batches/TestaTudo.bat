REM Executa os testes de todos os Scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

ECHO Nao ha testes a serem feitos

if errorlevel 4 goto sai


:sai