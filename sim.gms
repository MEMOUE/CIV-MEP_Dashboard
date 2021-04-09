*$offlisting
$offsymlist
$offsymxref

* put simulation name here
*$setGlobal SimName  "Agri25"
$setGlobal SimName  "DemD20"
*$setGlobal SimName  "Combine"
***$setGlobal SimName  "LabPR"
***$setGlobal SimName  "HeaEf"

$setGlobal shkFile %SimName%

*-Change here if two different sims use the same shock file
*$ifi %SimName% == "Agrisim" $setglobal shkFile "sim1"
$ifi %SimName% == "Agri00" $setglobal shkFile "simAgr"
$ifi %SimName% == "Agri10" $setglobal shkFile "simAgr"
$ifi %SimName% == "Agri15" $setglobal shkFile "simAgr"
$ifi %SimName% == "Agri20" $setglobal shkFile "simAgr"
$ifi %SimName% == "Agri25" $setglobal shkFile "simAgr"
$ifi %SimName% == "Agri30" $setglobal shkFile "simAgr"
$ifi %SimName% == "Agri35" $setglobal shkFile "simAgr"

$ifi %SimName% == "DemD05" $setglobal shkFile "simDD"
$ifi %SimName% == "DemD10" $setglobal shkFile "simDD"
$ifi %SimName% == "DemD20" $setglobal shkFile "simDD"
$ifi %SimName% == "DemD30" $setglobal shkFile "simDD"
$ifi %SimName% == "De05NC" $setglobal shkFile "simDD"
$ifi %SimName% == "De10NC" $setglobal shkFile "simDD"
$ifi %SimName% == "De20NC" $setglobal shkFile "simDD"
$ifi %SimName% == "De30NC" $setglobal shkFile "simDD"

$ifi %SimName% == "Combine" $setglobal shkFile "simComb"

$ifi %SimName% == "LabPR" $setglobal shkFile "sim"
$ifi %SimName% == "HeaEf" $setglobal shkFile "sim"

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


set tshock(t) years shocks are affective /2020*2050/;

$include %simF%\shkcalc.inc



loop(tt$(years(tt) le 2050),
*loop(tt$(years(tt) le 2020),

   if (ord(tt) gt 1,

      ts(tt) = yes ;

*     Ignore BaU
      $$batinclude '%incF%\iterloop.inc' 2016

$include %simF%\shk_%shkFile%.inc

      options limrow=0, limcol=0 ;
      options solprint=off ;
      options iterlim=100000 ;

*if(years(tt)=2018,
if(0,
      options limrow=3, limcol=0 ;
      options solprint=off ;
      options iterlim=10000 ;
);
*      cge.optFile = 5 ;
      cge.optFile = 6 ;
      solve cge using mcp ;

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


