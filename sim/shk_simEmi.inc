
*$ontext
* Introduce a 25$ carbon tax
   phiEmi(em,emSrc,aa) = 0 ;
   phiEmi(em,emSrc,aa)$(rtEmiSIM(em,aa,tt,"%SIMNAME%")) = 1 ;
*   phiEmi(em,emSrc,aa)$(rtEmiSIM(em,aa,tt,"%SIMNAME%") and emilow(aa)) = 0.1 ;
   rtEmi.fx(em,aa,tt)$(not ema(em))=   rtEmiSIM(em,aa,tt,"%SIMNAME%") ;
   tEmi0.lo(em,aa,tt)$(not ema(em)) = -inf;
   tEmi0.up(em,aa,tt)$(not ema(em)) = +inf;

*$offtext
$ontext
emighg.fx(tt) = emiGHGSIM(tt,"%SIMNAME%") ;
tEmiD0.lo(tt) = -inf ;
tEmiD0.up(tt) = +inf ;

$offtext


