
*    lambdal.fx(a,l,tt)= lambdalSIM(a,l,tt,"%SIMNAME%")  ;
*    lambdat.fx(a,tt)= lambdatSIM(a,tt,"%SIMNAME%")  ;
    tfpAct.fx(a,tt)= tfpActSIM(a,tt,"%SIMNAME%")  ;
    gammapSIM(a,i,t,"%SIMNAME%") = gammap(a,i,t) ;

    rsg.fx(tt) = rsgSIM(tt,"%SIMNAME%");
*    rsg.lo(tt) =  -inf ;
*    rsg.up(tt) =  +inf ;

*    rshrGDP.fx(gov,tt) = rshrGDP.l(gov,tt);
    rshrGDP.lo(gov,tt) = -inf ;
    rshrGDP.up(gov,tt) = +inf;

    rshrGDP.lo(ginv,tt) = -inf;
    rshrGDP.up(ginv,tt) = +inf;

    xf.fx(ginv,ts) =  xfSIM(ginv,ts,"%SIMNAME%") ;

*- impose revenue neutrality
*       chdTax.lo(tt) = -inf;
*       chdTax.up(tt) = +inf;
   brateU.fx(tt) = brateSIM(tt,"%SIMNAME%") ;
*deprate.lo(cohorts,t) = -inf;
*deprate.up(cohorts,t) = +inf ;

deprate.l(cohorts,t) = pop.l(cohorts,t)/pop.l("P1564",t) ;

*deprate.fx("P1564",tt) = deprate.l("P1564",tt) ;
*deprate.fx("PTOTL",tt) = pop.l("PTOTL",tt)/pop.l("P1564",tt) ;

*chims.fx(tt) = chimsSIM(tt,"%SIMNAME%");
* xa.fx(isoc,gov,tt) = xa.l(isoc,gov,tt)*1.2 ;
 chiPA(i) = chipaSIM(i,tt,"%SIMNAME%")  ;
 patax.fx(i,fd,tt)  =  pataxSIM(i,fd,tt,"%SIMNAME%") ;

* epsSoc(l,tt) = epsSocSIM(l,tt,"%SIMNAME%") ;

culIndex(l,t) = culIndexSIM(l,t,"%SIMNAME%")        ;

    rsg.fx(tt) = rsgSIM(tt,"%SIMNAME%");
    rshrGDP.lo(gov,tt) = -inf ;
    rshrGDP.up(gov,tt) = +inf;
