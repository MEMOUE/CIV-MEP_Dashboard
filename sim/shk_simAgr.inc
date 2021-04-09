
*-efficiency gains
   tfpAct.fx(a,tt)= tfpActSIM(a,tt,"%SIMNAME%")  ;
*    lambdal.fx(a,l,tt)= lambdalSIM(a,l,tt,"%SIMNAME%")  ;
*    lambdat.fx(a,lnd,tt)= lambdatSIM(a,lnd,tt,"%SIMNAME%")  ;
* Source of efficiency gain
    xfd.fx(ginv,ts) =  xfdSIM(ginv,ts,"%SIMNAME%") ;
    rshrGDP.lo(ginv,tt) = -inf;
    rshrGDP.up(ginv,tt) = +inf;
* Financing of expenditure
*    rsg.fx(tt) = rsgSIM(tt,"%SIMNAME%");
*    rshrGDP.lo(gov,tt) = -inf ;
*    rshrGDP.up(gov,tt) = +inf;
*- impose revenue neutrality
*         tdr.lo(t) = -inf ;
*         tdr.up(t) = +inf ;

