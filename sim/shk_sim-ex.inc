
     elecMix.lo(aElec,tt) = -inf; elecMix.up(aElec,tt) = +inf;
     tfpAct.fx(a,tt) = tfpAct.l(a,tt) ;
*     v_as.fx(aElec,ielec,tt) =      v_as.l(aElec,ielec,tt) ;

*-emission trading

loop(t0,
emPerm.l(em,aa,tt) = emiSecA.l(em,aa,t0);
);
emSupply.FX(em,tt) =  0 ;
emRev.FX(em,aa,tt) = 0;
embuy.FX(em,aa,tt) = 0;

emRev.FX(em,aa,tt)$(NOT emSwitch)  = 0;
emBuy.FX(em,aa,tt)$(NOT emSwitch)  = 0;

*       xfd.fx(adpinv,tt) = xfdSIM(adpinv,tt,"%SIMNAME%") ;

$if not %SIMNAME% == "CarTx2030" if(years(tt)>2023,
$if %SIMNAME% == "CarTx2030" if(years(tt)>2029,
$ontext
*- hydro expansion is rather impossible
elecmix.fx("a-HydroP",ielec,tt)   = elecmix.l("a-HydroP",ielec,tt) ;
 tfpact.lo("a-HydroP",tt) = -inf ;
 tfpact.up("a-HydroP",tt) = +inf ;


*-nuclear is already in the baseline and new plants are not foresees before 2030
if(years(tt)<2041,

elecmix.fx("a-NuclearP",ielec,tt)   = elecmix.l("a-NuclearP",ielec,tt) ;
 tfpact.lo("a-NuclearP",tt) = -inf ;
 tfpact.up("a-NuclearP",tt) = +inf ;
);
$offtext



*   emighg.fx("GHGs",tt)  = emighgSIM("GHGs",tt,"%SIMNAME%") ;
*   tEmiD0.lo(t) = -inf;
*   tEmiD0.up(t) = +inf;
   phiEmi(em,emSrc,aa) = 0 ;
*$ifthen %SIMNAME% == HighCarTx
*   phiEmi(em,emSrc,aa)$(tEmiD2SIM(aa,tt,"%SIMNAME%") AND tEmiM1SIM(em,tt,"%SIMNAME%")) = 1 ;
*   tEmiD2.fx(a,tt) = tEmiD2SIM(a,tt,"HighCarTx") ;

*$else
   phiEmi(em,emSrc,aa)$(rtEmiSIM(em,aa,tt,"%SIMNAME%")) = 1 ;
   rtEmi.fx(em,aa,tt)$(not ema(em))=   rtEmiSIM(em,aa,tt,"%SIMNAME%") ;
   tEmi0.lo(em,aa,tt)$(not ema(em)) = -inf;
   tEmi0.up(em,aa,tt)$(not ema(em)) = +inf;
*$endif

   tEmiM1.fx(em,tt) = tEmiM1SIM(em,tt,"%SIMNAME%");

   tpitD0Cont(h,tt) = tpitD0ContSIM(h,tt,"%SIMNAME%") ;

*


$iftheni %SIMNAME% == "FacTxRcyl"
   ygov.fx(tt) =    ygovSIM(tt,"%SIMNAME%") ;
   tfacMLab.lo(tt) = -inf ;
   tfacMLab.up(tt) = +inf ;
$else
   uh.fx(h,tt)$tpitD0Cont(h,tt)   = uhSIM(h,tt,"%SIMNAME%");
   tPitD1.lo(h,tt)$tpitD0Cont(h,tt) = -inf ;
   tPitD1.up(h,tt)$tpitD0Cont(h,tt) = +inf ;
$endif

   tPrdM1.fx(a,tt) = tPrdM1SIM(a,tt,"%SIMNAME%") ;
   tPafM1.fx(i,tt) = tPafM1SIM(i,tt,"%SIMNAME%") ;

*- government savings
$iftheni %SIMNAME% == "GovntSave"
ygov.lo(tt) = -inf   ;
ygov.up(tt) = +inf   ;
tPitD0.fx(tt) = tPitD0SIM(tt,"%SIMNAME%") ;
tfacMLab.fx(tt) = 1 ;
$endif

*-debt
$iftheni %SIMNAME% == "DebtPaymt"
savg.fx(tt) = savgSIM(tt,"%SIMNAME%")   ;
rDebtStk.lo(tt) = -inf ;
rDebtStk.up(tt) = +inf ;
tPitD0.fx(tt) = tPitD0SIM(tt,"%SIMNAME%") ;
$endif

*government investment
$iftheni %SIMNAME% == "GovntInvt"
ygov.lo(tt) = -inf   ;
ygov.up(tt) = +inf   ;
rshrGDP.lo(ginv,tt) = -inf   ;
rshrGDP.up(ginv,tt) = +inf   ;
rsg.fx(tt) = rsgSIM(tt,"%SIMNAME%") ;
tPitD0.fx(tt) = tPitD0SIM(tt,"%SIMNAME%") ;
$endif


);



*-test shocks
*   emighg.fx("GHGs",tt)  = emighgSIM("GHGs",tt,"%SIMNAME%") ;
*   tEmiD0.lo(t) = -inf;
*   tEmiD0.up(t) = +inf;

tfp.fx(tt)  = tfpSIM(tt,"%SIMNAME%") ;

*lambdak.fx(a,v,t) = lambdakSIM(a,v,t,"CapitlPro") ;



kstock.fx(tt) = kstocksim(tt,"CapStoDes") ; 