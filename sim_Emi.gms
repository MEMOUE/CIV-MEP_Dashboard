*$offlisting
$offsymlist
$offsymxref

* put simulation name here
$setGlobal SimName  "carbtax"

$setGlobal shkFile %SimName%

*-Change here if two different sims use the same shock file
$ifi %SimName% == "carbtax" $setglobal shkFile "simEmi"

$setGlobal oDir     ".\res"
$setGlobal incF     ".\inc"
$setGlobal simF     ".\sim"
$setGlobal datF     ".\dat"
$setGlobal savF     ".\sav"
$setGlobal datFile  "%SIMNAME%_data_in"


$include "inc\opt.inc"

*  Set ifCal to 1 for BaU scenarios
scalar ifCal / 0 / ;

$setGlobal inBaUGDX  "%odir%\BaU.gdx"

$setglobal BridgeFile BaseBridge_v1.xlsx

$include "%incF%\dynamDef.inc"

$include "%incF%\reportDecl.inc"


*ued.fx(h,k,kp,t) = ued.l(h,k,kp,t) ;
*incelas.fx(h,k,t) = incelas.l(h,k,t) ;

*set tshock(t) years shocks are affective /2022*2050/;
set tshock(t) years shocks are effective /2022*2040/;

set iter /1*4/ ;
Parameter iterNum(iter) ;

iterNum(iter) = ord(iter) ;


$include %simF%\shkcalc.inc

*loop(tt$(years(tt) le 2030),
loop(tt$(years(tt) le 2040),

   if (ord(tt) gt 1,

      ts(tt) = yes ;

*     Ignore BaU
      $$batinclude '%incF%\iterloop.inc' 2018

$include %simF%\shk_%shkFile%.inc

      options limrow=0, limcol=0 ;
*      options solprint=off ;
      options iterlim=100000 ;

*if(years(tt)=2018,
if(0,
      options limrow=3, limcol=0 ;
      options solprint=off ;
      options iterlim=10000 ;
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
          options solprint=off ;
          options limrow=3, limcol=0 ;
          solve cge using mcp ;
          if(cge.solvestat = 1,
*          optfile(tt) = iterNum(iter)
             );
          );
        );
*$offtext

      diagnostics("modStatus",ts) = cge.modelstat ;
      diagnostics("solStatus",ts) = cge.solvestat ;
      diagnostics("Walras",ts) = walras.l/inscale ;

if( (cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1 OR abs(Walras.l) > 1E-3 ),
   put screen ;
   put // "FAILED SOLVED %SIMNAME%  FOR ", tt.tl ;
   putclose;
);

   $$include %incF%\samCalc.inc

abort$(cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1) "Infeasible Solution" ;
abort$(abs(Walras.l) > 1E-3) "Walras > 0";
*$include report.inc
      ts(tt) = no ;

   ) ;

   put screen ;
   put // "SOLVED %SIMNAME% FOR ", tt.tl ;
   putclose;
   $$include %incF%\report.inc
) ;

execute_unload "%odir%\%simName%.gdx" ;


