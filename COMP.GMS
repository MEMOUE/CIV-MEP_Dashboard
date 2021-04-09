$offlisting
$onempty

$include 'ngaasam2006.dat'
$include 'ngaaBase.dat'

$offempty
$onlisting

set t time / base, check, homog / ;
set ts(t) Simulation period ; ts(t) = no ;
set tsim(t) ;
set t0(t) / base / ;
alias (t,tt) ;

parameter years(t) /
   base     1
   check    2
   homog    3
/ ;

parameter gap(t) ; gap(t) = 1 ;

file csv / comp.csv / ;
put csv ;
put "Simulation,Variable,Sector,Qualifier,Year,Value" / ;
csv.pc=5 ;
csv.nd=9 ;

file samcsv / compsam.csv / ;
scalar ifSam / 1 / ;
if(ifSam,
   put samcsv ;
   put "Simulation,rLab,cLab,Year,Value" / ;
   samcsv.pc=5 ;
   samcsv.nd=9 ;
) ;

set v       Vintages       / Old / ;
set v0(v)   Initialization / Old / ;
set vc(v)   Calibration    / Old / ;
set vOld(v) Old vintage    / Old / ;
set Old(v)  / Old / ;
set New(v)  / Old / ;

set mapv(v, vint) /
   Old.Old
   Old.New
/ ;

scalar ifVint / 0 / ;
scalar ifLoad / 0 / ;

set diag /
   modStatus
   Walras
/ ;

parameters
   diagnostics(diag, t)
;

file screen / con / ;
put screen ;

*  Set ifComp to 1 for comparative static simulations

scalar ifComp / 1 / ;

*  Set ifCal to 1 for BaU scenarios

scalar ifCal / 0 / ;

*  Set ifCDE to 1 for using the CDE utility function

scalar ifCDE / 1 / ;

*  Closure rules

set cr /

*  Default -- government expenditures are fixed in real terms
*             government savings are fixed in real terms
*             household tax shifter is endogenous
*             investment is savings driven
*             public and foreign savings are fixed
*             household savings shifter is fixed
*             trade balance is fixed, and gdp deflator is endogenous

   default

/ ;

parameter closure(cr) ; closure('default') = yes ;

$include 'model.gms'

$include 'compscn.dat'

$include 'cal.gms'

loop(tt,

   if (ord(tt) gt 1,

      ts(tt) = yes ;

      $$batinclude 'iterloop.gms' 0

      if (ts('homog'),

         er.fx(ts) = 1.5 ;

*        lambdat.fx(a,ts) = 1.1 ;

*        lambdal.fx(a,l,ts) = 1.1 ;
*        lambdaep.fx(a,e,v,ts) = 1.10 ;
*        lambdaef.fx(oa,e,k,ts) = 1.10 ;
*        te.fx(i,ts) = -0.2 ;
*        emiTot.fx("CO2",ts) = 0.9*emiTot.l("CO2",'base') ;
*        emitax.lo("CO2",ts) = -inf ;
*        emitax.up("CO2",ts) = +inf ;
*        emitax.fx("CO2",ts) = 0.001*217.69542*inscale/escale ;
*        display emiTax.l ;
      ) ;

      options limrow=3, limcol=3 ;
      options iterlim = 10 ;

      solve cge using mcp ;

      diagnostics("modStatus",ts) = cge.solvestat ;
      diagnostics("Walras",ts) = walras.l/inscale ;

      if (cge.solvestat eq 1,
         put screen ;
         put // "Solved for year ", years(tt):4:0 // ;
         tsim(ts) = yes ;
         loop(diag,
            if(sameas(diag,"modStatus"), put diag.tl:<10, diagnostics(diag,tt):12:0 / ; ) ;
            if(sameas(diag,"Walras"), put diag.tl:<10, diagnostics(diag,tt):12:5 / ; ) ;
         ) ;
         putclose screen ;
      else
         put screen ;
         put // "Failed to solve for year ", years(tt):4:0 // ;
         tsim(ts) = no ;
         loop(diag,
            if(sameas(diag,"modStatus"), put diag.tl:<10, diagnostics(diag,tt):12:0 / ; ) ;
            if(sameas(diag,"Walras"), put diag.tl:<10, diagnostics(diag,tt):12:5 / ; ) ;
         ) ;
         putclose screen ;
      ) ;

      ts(tt) = no ;

   ) ;

) ;

display diagnostics ;

set sim / comp / ;
loop(sim,

$include "postsim.gms" ;

) ;
