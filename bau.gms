*$offlisting
$offsymlist
$offsymxref

$setGlobal SimName  "BaU"

$setGlobal oDir     ".\res"
$setGlobal incF     ".\inc"
$setGlobal datF     ".\dat"
$setGlobal savF     ".\sav"
$setGlobal datFile  "%SIMNAME%_data_in"

$include "inc\opt.inc"

scalar    ifCal  Set to 1 for BaU    / 1 /
;



$setglobal BridgeFile BaseBridge_v2.xlsx

$include "%incF%\dynamDef.inc"
$include "%incF%\reportDecl.inc"

Parameter
emiGHGTarg(t) ;
loop(tt$(t0(tt)),

$include %incF%\samCalc.inc
);

* loop(tt$(years(tt) le 2030),
 loop(tt$(years(tt) le 2040),
   if (ord(tt) gt 1,

      ts(tt) = yes ;

*     Ignore BaU

      $$batinclude '%incF%\iterloop.inc' 2018

      options limrow=0, limcol=0 ;
*      options solprint=off ;
      options iterlim=10000 ;

    if(years(tt)=2018,
      options limrow=300, limcol=0 ;
      options solprint=off ;
      options iterlim=10000 ;
    );
      cge.optFile = 1 ;
      solve cge using mcp ;

      diagnostics("modStatus",ts) = cge.modelstat ;
      diagnostics("solStatus",ts) = cge.solvestat ;
      diagnostics("Walras",ts) = walras.l/inscale ;




if( (cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1 OR abs(Walras.l) > 1E-3 ),
   put screen ;
   put // "FAILED SOLVED BaU FOR ", tt.tl ;
   putclose;
);

   $$include %incF%\samCalc.inc

   abort$(cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1) "Infeasible Solution" ;
   abort$(abs(Walras.l) > 1E-3) "Walras > 0";

      ts(tt) = no ;

   ) ;
   put screen ;
   put // "SOLVED BaU FOR ", tt.tl ;
   putclose;

   $$include %incF%\report.inc
) ;

Parameter PrExIm(*,i,t) ;

*-Diagnostics

Loop(t0,
PrExIm("Prod",i,t)$xs.l(i,t0) = xs.l(i,t)/xs.l(i,t0) ;
PrExIm("Expo",i,t)$xe.l(i,t0) = xe.l(i,t)/xe.l(i,t0) ;
PrExIm("Impo",i,t)$xm.l(i,t0) = xm.l(i,t)/xm.l(i,t0) ;
PrExIm("ExPr",i,t)$xs.l(i,t)  = xe.l(i,t)/xs.l(i,t) ;
);



execute_unload "%odir%\%simName%.gdx" ;
*display fl;

