@ECHO  OFF
REM  Gera todos Scripts de make pelos arquivos .comp

cls

pushd  .

cd ..\Ferramentas
gmake /b..\Composicao /c..\Composicao\TesteLista
gmake /b..\Composicao /c..\Composicao\TesteListaDebug

popd
