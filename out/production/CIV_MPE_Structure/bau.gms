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


$include "%incF%\dynamDef.inc"
$include "%incF%\reportDecl.inc"

Parameter
emiGHGTarg(t) ;
loop(tt$(t0(tt)),

$include %incF%\samCalc.inc
);





 loop(tt$(years(tt) le 2040),
   if (ord(tt) gt 1,

      ts(tt) = yes ;

*     Ignore BaU

 
   
$ontext
   xp.fx('a-gold',tt)$(years(tt) ge 2024)       = xp.l('a-gold',tt-1)*(MinBAU("or",tt)/MinBAU("or",tt-1));
  chixFacA.up('a-gold',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-gold',tt)$(years(tt) ge 2024)  = -inf ;
   
*petrole
  xp.fx('a-oil',tt)$(years(tt) ge 2024)        = xp.l('a-oil',tt-1) * (MinBAU("petrole",tt)/MinBAU("petrole",tt-1)) ;
  chixFacA.up('a-oil',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-oil',tt)$(years(tt) ge 2024) = -inf ;  

*gaz
  xp.fx('a-gas',tt)$(years(tt) ge 2024)        = xp.l('a-gas',tt-1) * (MinBAU("gaz",tt)/MinBAU("gaz",tt-1)) ;
  chixFacA.up('a-gas',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-gas',tt)$(years(tt) ge 2024) = -inf ;
   
  
 xp.fx('a-mn',tt)$(years(tt) ge 2024)       = xp.l('a-mn',tt-1)*(MinBAU("manganese",tt)/MinBAU("manganese",tt-1));
  chixFacA.up('a-mn',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-mn',tt)$(years(tt) ge 2024)  = -inf ;
   

    
   
   xp.fx('a-ni',tt)$(years(tt) ge 2024)       = xp.l('a-ni',tt-1)*(MinBAU("nickel",tt)/MinBAU("nickel",tt-1));
  chixFacA.up('a-ni',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-ni',tt)$(years(tt) ge 2024)  = -inf ;
 
  
   xp.fx('a-bauxite',tt)$(years(tt) ge 2024)       = xp.l('a-bauxite',tt-1)*(MinBAU("bauxite",tt)/MinBAU("bauxite",tt-1));
  chixFacA.up('a-bauxite',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-bauxite',tt)$(years(tt) ge 2024)  = -inf ;
   
*diamant
  xp.fx('a-diamon',tt)$(years(tt) ge 2024)        = xp.l('a-diamon',tt-1) * (MinBAU("diamant",tt)/MinBAU("diamant",tt-1)) ;
  chixFacA.up('a-diamon',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-diamon',tt)$(years(tt) ge 2024) = -inf ;

*petrole
  xp.fx('a-oil',tt)$(years(tt) ge 2024)        = xp.l('a-oil',tt-1) * (MinBAU("petrole",tt)/MinBAU("petrole",tt-1)) ;
  chixFacA.up('a-oil',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-oil',tt)$(years(tt) ge 2024) = -inf ;  

*gaz
  xp.fx('a-gas',tt)$(years(tt) ge 2024)        = xp.l('a-gas',tt-1) * (MinBAU("gaz",tt)/MinBAU("gaz",tt-1)) ;
  chixFacA.up('a-gas',tt)$(years(tt) ge 2024) = +inf ;
   chixFacA.lo('a-gas',tt)$(years(tt) ge 2024) = -inf ;
   

$offtext


      $$batinclude '%incF%\iterloop.inc' 2020







      options limrow=0, limcol=0 ;
*      options solprint=off ;
      options iterlim=10000 ;

    if(years(tt)=2021,
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

*   $$include %incF%\report.inc
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


