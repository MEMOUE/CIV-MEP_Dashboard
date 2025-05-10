*$offlisting
$offsymlist
$offsymxref

$setGlobal SimName  "pi"

$setGlobal oDir     ".\res"
$setGlobal incF     ".\inc"
$setGlobal datF     ".\dat"
$setGlobal savF     ".\sav"
$setGlobal datFile  "%SIMNAME%_data_in"

$include "inc\opt.inc"

scalar    ifCal  Set to 1 for BaU    / 0 /
;

$setGlobal inBaUGDX  "%odir%\BaU.gdx"


$include "%incF%\dynamDef.inc"
$include "%incF%\reportDecl.inc"


set iter /1*4/ ;
Parameter iterNum(iter) ;

iterNum(iter) = ord(iter) ;
*
Parameter
emiGHGTarg(t) ;
loop(tt$(t0(tt)),

$include %incF%\samCalc.inc
);

   $$onmulti
   set sim "All simulations for which settings are available"
   /
        bau
        pi
       pi_plus
   /;
   $$offmulti

    Parameter
 xpSIM(a,t,sim) "production"
xpBAU(a,t)
;

variable
xpBAUv(a,t);

$gdxin %inBaUGDX%
    $$load xpBAUv = xp
$gdxin
*

xpSIM(a,t,sim) = xpBAUv.l(a,t);

*or
xpSIM('a-gold',tt,'pi')$((years(tt) ge 2024))           = xpSIM('a-gold',tt,'bau') + xpSIM('a-gold',tt,'bau')*(GoldSIM('or',tt)/MinBAU('or',tt)-1); 

*petrole
xpSIM('a-oil',tt,'pi')$((years(tt) ge 2024))           = xpSIM('a-oil',tt,'bau') + xpSIM('a-oil',tt,'bau')*(OilSIM('petrole',tt)/MinBAU('petrole',tt)-1);

*gaz


xpSIM('a-gas',tt,'pi')$((years(tt) ge 2024))           = xpSIM('a-gas',tt,'bau') + xpSIM('a-gas',tt,'bau')*(GasSIM('gaz',tt)/MinBAU('gaz',tt)-1);


*autres mineraies

xpSIM('a-oxt',tt,'pi')$((years(tt) ge 2024))           = xpSIM('a-oxt',tt,'bau') + 0.002*(xpSIM('a-oxt',tt,'bau')*(BauxSIM('bauxite',tt)/MinBAU('bauxite',tt)-1)) + xpSIM('a-oxt',tt,'bau')*(IronCopperSIM('fercuivre',tt))
+
0.0085*(xpSIM('a-oxt',tt,'bau')*(DiamSIM('diamant',tt)/MinBAU('diamant',tt)-1))
+
0.0175*(xpSIM('a-oxt',tt,'bau')*(MnSIM('manganese',tt)/MinBAU('manganese',tt)-1))
;



 loop(tt$(years(tt) le 2040),
   if (ord(tt) gt 1,

      ts(tt) = yes ;

*     Ignore BaU



$ontext
$offText
   
      $$batinclude '%incF%\iterloop.inc' 2020
      
     elecMix.lo(aElec,ielec,tt) = -inf; elecMix.up(aElec,ielec,tt) = +inf;
     tfpAct.fx(a,tt) = tfpAct.l(a,tt) ;

* government consumption fixed in level or in percentage points of GDP
*xfd.fx(gov,ts)       = xfdsim(gov,ts,"%SIMNAME%");
rshrGDP.fx(gov,ts)       = rshrGDP.l(gov,ts);
*ObalGDP.lo(ts) = -inf;
*ObalGDP.up(ts) = +inf;
fiscalbalanceGDP.lo(ts) = -inf;
fiscalbalanceGDP.up(ts) = +inf;

* government investment fixed in level or in percentage points of GDP

   rshrGDP.fx(ginv,ts)  = rshrGDP.l(ginv,ts);
   xfd.lo(ginv,ts) = -inf ;
   xfd.up(ginv,ts) = +inf ;

* Marginal propensity to save becomes exogenous and private investment/GDP endogenous
   chims.fx(tt) = chims.l(tt) ;
   rshrGDP.lo(inv,tt) = -inf ;
   rshrGDP.up(inv,tt) = +inf ;

* debt is now endogenous with fixed debt shifter
chiDebtShf.fx(tt) = chiDebtShf.l(tt) ;
debtGDP.lo(tt) = -inf;
debtGDP.up(tt) = +inf;


 xp.fx('a-gold',tt)$(years(tt) ge 2024) = xpSIM('a-gold',tt,'pi');
 chixFacA.up('a-gold',tt)$(years(tt) ge 2024) = +inf ;
  chixFacA.lo('a-gold',tt)$(years(tt) ge 2024)  = -inf ;
*
xp.fx('a-oil',tt)$(years(tt) ge 2024) = xpSIM('a-oil',tt,'pi');
  chixFacA.up('a-oil',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-oil',tt)$(years(tt) ge 2024)  = -inf ;

xp.fx('a-gas',tt)$(years(tt) ge 2024) = xpSIM('a-gas',tt,'pi');
  chixFacA.up('a-gas',tt)$(years(tt) ge 2024) = +inf ;
  chixFacA.lo('a-gas',tt)$(years(tt) ge 2024)  = -inf ;

xp.fx('a-oxt',tt)$(years(tt) ge 2024) = xpSIM('a-oxt',tt,'pi');
  chixFacA.up('a-oxt',tt)$(years(tt) ge 2024) = +inf ;
  chixFacA.lo('a-oxt',tt)$(years(tt) ge 2024)  = -inf ;  



      options limrow=0, limcol=0 ;
*      options solprint=off ;
      options iterlim=10000 ;
*$onText
    if(years(tt)=2021,
      options limrow=300, limcol=0 ;
      options solprint=off ;
      options iterlim=10000 ;
    );
      cge.optFile = 1 ;
      solve cge using mcp ;
      
*$offtext

*$onText   
if(0,
      options limrow=3, limcol=0 ;
      options solprint=off ;
      options iterlim=10000 ;
);
*      cge.optFile = 5 ;
      cge.optFile = 2 ;
      solve cge using mcp ;

*$offtext
$ontext
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
$offtext

      diagnostics("modStatus",ts) = cge.modelstat ;
      diagnostics("solStatus",ts) = cge.solvestat ;
      diagnostics("Walras",ts) = walras.l/inscale ;




if( (cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1 OR abs(Walras.l) > 1E-3 ),
   put screen ;
   put // "FAILED SOLVED  %SIMNAME%  FOR ", tt.tl ;
   putclose;
);

   $$include %incF%\samCalc.inc

   abort$(cge.MODELSTAT > 2 OR cge.SOLVESTAT > 1) "Infeasible Solution" ;
   abort$(abs(Walras.l) > 1E-3) "Walras > 0";

      ts(tt) = no ;

   ) ;
   put screen ;
   put // "SOLVED  %SIMNAME%  FOR ", tt.tl ;
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


