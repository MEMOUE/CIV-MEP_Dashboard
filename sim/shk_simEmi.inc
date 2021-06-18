* Introduce a 25$ carbon tax

   phiEmi(em,emSrc,aa) = 0 ;
   phiEmi(em,emSrc,aa)$(tEmiSIM(em,aa,tt,"%SIMNAME%")) = 1 ;
***   phiEmi(em,emSrc,aa)$(rtEmiSIM(em,aa,tt,"%SIMNAME%") and emilow(aa)) = 0.1 ;
*$ontext
   tEmi.fx(em,aa,tt)$(not ema(em))  = tEmiSIM(em,aa,tt,"%SIMNAME%") ;
   tEmi0.lo(em,aa,tt)$(not ema(em)) = -inf;
   tEmi0.up(em,aa,tt)$(not ema(em)) = +inf;
*$offtext
$ontext
   rtEmi.fx(em,aa,tt)$(not ema(em))=   rtEmiSIM(em,aa,tt,"%SIMNAME%") ;
   tEmi0.lo(em,aa,tt)$(not ema(em)) = -inf;
   tEmi0.up(em,aa,tt)$(not ema(em)) = +inf;
$offtext