
*-efficiency gains
   tfpAct.fx(a,tt)= tfpActSIM(a,tt,"%SIMNAME%")  ;

* Source of efficiency gain
    xfd.fx(ginv,tt) =  xfdSIM(ginv,tt,"%SIMNAME%") ;
    rshrGDP.lo(ginv,tt) = -inf;
    rshrGDP.up(ginv,tt) = +inf;

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
