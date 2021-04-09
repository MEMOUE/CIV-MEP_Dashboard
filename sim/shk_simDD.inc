
  brateU.fx(tt) = brateSIM(tt,"%SIMNAME%") ;
  culIndex(l,t) = culIndexSIM(l,t,"%SIMNAME%")        ;

*  chiPA(i) = chipaSIM(i,tt,"%SIMNAME%")  ;
  tPaf0.fx(i,fd,tt)  =  tPaf0SIM(i,fd,tt,"%SIMNAME%") ;

$ontext

* epsSoc(l,tt) = epsSocSIM(l,tt,"%SIMNAME%") ;

*pop.fx(cohorts,tt)  =   popSIM(cohorts,tt,"%SIMNAME%");
*hpop.fx(h,tt) =   hpopSIM(h,tt) ;
*chils(L,tt) = chilsSIM(L,tt) ;

    rsg.fx(tt) = rsgSIM(tt,"%SIMNAME%");
    rshrGDP.lo(gov,tt) = -inf ;
    rshrGDP.up(gov,tt) = +inf;

*    rsg.lo(tt) = -inf ;
*    rsg.up(tt) = +inf;

*- impose revenue neutrality
*         tdr.lo(t) = -inf ;
*         tdr.up(t) = +inf ;
$offtext
