*$offlisting
$offsymlist
$offsymxref



$setGlobal SimName  "CapStoDes"
$ontext
MainCarTx
MainColSb
MainFosSb
MainTxRed
CarTx2030
FacTxRcyl
HighCarTx
NrgExclud
GovntSave
DebtPaymt
GovntInvt
$offtext

$ontext
#      Scenarios
      BAU
1 Main Main scenario
  Carbon price coverage        Industry, Wastewater, Transport, Stationary energy
  Carbon price rate            10 euro in 2024 increasing to 20 from 2030
  Revenue recycling            Cash transfer to bottom 2 household quintiles to make CP impact neutral (amount determined from HH impact assessment)
  Exemptions/ subsidies        Remove fossil fuel subsidies Stop electricity consumption tax and SCT on natural gas

2 Cmnc Implementation commences 2030
  Carbon price coverage        As per main scenario
  Carbon price rate            starts 2030 at 10 euro then 20 euro from 2035
  Revenue recycling            As per main scenario, in line with commencement
  Exemptions/ subsidies        As per main scenario

3 NRcy No revenue recycling
  Carbon price coverage        As per main scenario
  Carbon price rate            As per main scenario
  Revenue recycling            Govt savings or debt repayment or investment
  Exemptions/ subsidies        As per main scenario

4 IRcy Revenue recycled as income tax reduction
  Carbon price coverage        As per main scenario
  Carbon price rate            As per main scenario
  Revenue recycling            HH transfers from main scenario plus remaining revenue generated to income tax reduction.
  Exemptions/ subsidies        As per main scenario

6 High Higher carbon price
  Carbon price coverage        As per main scenario
  Carbon price rate            Forecast EU ETS price from 2024
  Revenue recycling            As per main scenario
  Exemptions/ subsidies        As per main scenario

7 NNrg Stationary energy excluded from coverage
  Carbon price coverage        Industry, Wastewater, Transport
  Carbon price rate            As per main scenario
  Revenue recycling            As per main scenario
  Exemptions/ subsidies        As per main scenario

8 NSub No subsidy reform
  Carbon price coverage        As per main scenario
  Carbon price rate            As per main scenario
  Revenue recycling            As per main scenario
  Exemptions/ subsidies        No subsidy reform
$offtext
$setGlobal shkFile sim

*-Change here if two different sims use the same shock file
$ifi %SimName% == "INDC" $setglobal shkFile "sim8"
*$ifi %SimName% == "CarTx2030" $setglobal shkFile "sim2030"

$setGlobal oDir     ".\res"
$setGlobal incF     ".\inc"
$setGlobal simF     ".\sim"
$setGlobal datF     ".\dat"
$setGlobal savF     ".\sav"
$setGlobal datFile  "%SIMNAME%_data_in"


$include "inc\opt.inc"

*  Set ifCal to 1 for BaU scenarios
scalar ifCal / 0 / ;

$include "%incF%\dynamDef.inc"

$include "%incF%\reportDecl.inc"

oscale = 1/inscale;
oscale = 1;

*ued.fx(h,k,kp,t) = ued.l(h,k,kp,t) ;
*incelas.fx(h,k,t) = incelas.l(h,k,t) ;

set tshock(t) years shocks are affective /2020*2040/;

$include %simF%\shkcalc.inc



loop(tt$(years(tt) le 2040),
*loop(tt$(years(tt) le 2020),

   if (ord(tt) gt 1,

      ts(tt) = yes ;

*     Ignore BaU
      $$batinclude '%incF%\iterloop.inc' 2017

$include %simF%\shk_%shkFile%.inc

      options limrow=0, limcol=0 ;
      options solprint=off ;
      options iterlim=50 ;

*if(years(tt)=2030,
if(0,
      options limrow=3, limcol=0 ;
      options solprint=off ;
      options iterlim=10 ;
);
*      cge.optFile = 5 ;
      cge.optFile = 2 ;
      solve cge using mcp ;
*$ontext
*- this is to find the correct opt file
    Loop(iter,
       if(cge.solvestat = 2 OR cge.solvestat = 3 ,

          put_utility 'log' // "Trying different opt files for the year ", tt.tl, "opt file=", iterNum(iter) ;
          put screen ;
          put // "Trying different opt files for the year ", tt.tl, "opt file=", iter.tl ;
          putclose;
          $$include %incF%\resLastYear.inc
          cge.optFile = iterNum(iter) ;
          solve cge using mcp ;
          if(cge.solvestat = 1,
          optfile(tt) = iterNum(iter)
             );
          );
        );
*$offtext

      diagnostics("modStatus",ts) = cge.modelstat ;
      diagnostics("solStatus",ts) = cge.solvestat ;
      diagnostics("Walras",ts) = walras.l ;

if( (cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1 OR abs(Walras.l) > 1E-3 ),
   put screen ;
   put // "FAILED SOLVED %SIMNAME%  FOR ", years(tt):4:0 ;
   putclose;
);

   $$include %incF%\samCalc.inc

abort$(cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1) "Infeasible Solution" ;
abort$(abs(Walras.l) > 1E-3) "Walras > 0";
*$include report.inc
      ts(tt) = no ;

   ) ;
   put screen ;
   put // "SOLVED %SIMNAME% FOR ", years(tt):4:0 / ;
   loop(diag,
        if(sameas(diag,"modStatus"), put diag.tl:<10, diagnostics(diag,tt):12:0 / ; ) ;
        if(sameas(diag,"Walras"), put diag.tl:<10, diagnostics(diag,tt):12:12 / ; ) ;
         ) ;
   putclose;

) ;



   $$include %incF%\report.inc

execute_unload "%odir%\%simName%.gdx" ;


