* lowe birth rate
  brateU.fx(tt) = brateSIM(tt,"%SIMNAME%") ;

*support consumption by making health and education more affordable
*  tPaf0.fx(i,fd,tt)  =  tPaf0SIM(i,fd,tt,"%SIMNAME%") ;
$ontext
   paf.fx(ihea,aasoc,tt)$(years(tt)<2021) =  paf.l(ihea,aasoc,tt);
 tPaf0.lo(ihea,aasoc,tt)$(years(tt)<2021) = -inf;
 tPaf0.up(ihea,aasoc,tt)$(years(tt)<2021) = +inf;
   paf.fx(iedu,aasoc,tt)$(years(tt)<2021) =  paf.l(iedu,aasoc,tt);
 tPaf0.lo(iedu,aasoc,tt)$(years(tt)<2021) = -inf;
 tPaf0.up(iedu,aasoc,tt)$(years(tt)<2021) = +inf;
$offtext

* education and health expenditure
  xa.fx(ihea,f,tt)$[f1(f)] = xaSIM(ihea,f,tt,"%SIMNAME%") ;
  xa.fx(iedu,f,tt)$[f1(f)] = xaSIM(iedu,f,tt,"%SIMNAME%") ;

* Financing of expenditure
    rsg.fx(tt)$(years(tt) < 2036) = rsgSIM(tt,"%SIMNAME%");
*    rsg.fx(tt) = rsgSIM(tt,"%SIMNAME%");
*    rshrGDP.lo(gov,tt) = -inf ;
*    rshrGDP.up(gov,tt) = +inf;

*- impose revenue neutrality
*taxing houeholds and entreprises
         tdr.lo(tt)$(years(tt) < 2036)  = -inf ;
         tdr.up(tt)$(years(tt) < 2036)  = +inf ;

*taxing only households
*         tPITM0.lo(tt) = -inf ;
*         tPITM0.up(tt) = +inf ;
*taxing everything
*         tmAll.lo(tt)$(years(tt) < 2036) = -inf ;
*         tmAll.up(tt)$(years(tt) < 2036) = +inf ;
