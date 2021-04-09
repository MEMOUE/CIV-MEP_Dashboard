@echo off
setlocal enableDelayedExpansion

:choiceBau
set /P c=Run BaU [Y/N]?
if /I "%c%" EQU "Y" goto :bau
if /I "%c%" EQU "N" goto :choice1

goto :choiceBau

:bau
::activate below line to run BaU
start "BaU" CALL gams BaU.gms --simName=BaU s=sav\BaU rf=sav\BaU solvelink=5 license="C:\GAMS\win64\30.1\gamslice.txt"


:choice1 
set /P c=Run simulations[Y/N]?
if /I "%c%" EQU "Y" goto :sims
if /I "%c%" EQU "N" goto :choice2
goto :choice1

:exit
exit /B

:sims
FOR %%A IN (LabPR Heaef) DO (
rem use below line to keep windows open 
start "Sim %%A" CALL gams sim.gms --simName=%%A s=sav\%%A o=sav\%%A.lst LF=sav\%%A.log rf=sav\%%A solvelink=5 license="C:\GAMS\win64\30.1\gamslice.txt"
)


:choice2 
set /P c=Prepare Tables [Y/N]?
if /I "%c%" EQU "Y" goto :maktab
if /I "%c%" EQU "N" goto :exit

:maktab
start "Preparing results" CALL gams result.gms solvelink=5 license="C:\GAMS\win64\30.1\gamslice.txt"
rem start "Writing CSV File" CALL gams maketab.gms solvelink=5 license="C:\GAMS\win64\30.1\gamslice.txt"

