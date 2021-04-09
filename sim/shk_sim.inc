     elecMix.lo(aElec,ielec,tt) = -inf; elecMix.up(aElec,ielec,tt) = +inf;
     tfpAct.fx(a,tt) = tfpAct.l(a,tt) ;

*-emission trading

loop(t0,
emPerm.l(em,aa,tt) = emiSecA.l(em,aa,t0);
);
emSupply.FX(em,t) =  0 ;
emRev.FX(em,aa,t) = 0;
embuy.FX(em,aa,t) = 0;

emRev.FX(em,aa,t)$(NOT emSwitch)  = 0;
emBuy.FX(em,aa,t)$(NOT emSwitch)  = 0;

*       xfd.fx(adpinv,tt) = xfdSIM(adpinv,tt,"%SIMNAME%") ;

if(years(tt)>2019,

*-labor productivity
   chilambdal(l,tt) = chilambdalSIM(l,tt,"%SIMNAME%")  ;

*-efficiency gains
*   tfpAct.fx("a-hht",tt) =   tfpActSIM("a-hht",tt,"%SIMNAME%") ;
);
