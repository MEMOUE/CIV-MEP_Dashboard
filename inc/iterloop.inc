* ----------------------------------------------------------------------------------------
*
*  Give a good starting guess for next year
*
* ----------------------------------------------------------------------------------------

$setArgs lastYear

loop(t$(ts(t) and not ifComp and ord(t) gt 2 and (ifLoad and years(t) gt %lastYear% or not ifLoad)),

   work = power(1 + ggdppcT(t), gap(t)) ;

   nd.l(a,t)              = work*nd.l(a,t-1) ;
   vav.l(a,v,t)           = work*vav.l(a,v,t-1) ;
   pxv.l(a,v,t)           = pxv.l(a,v,t-1) ;
   px.l(a,t)              = px.l(a,t-1) ;
   pp.l(a,t)              = pp.l(a,t-1) ;
   xf.l(a,lnd,t)            = work*xf.l(a,lnd,t-1) ;
   lab1.l(a,v,t)          = work*lab1.l(a,v,t-1) ;
   kse.l(a,v,t)           = work*kse.l(a,v,t-1) ;
   pva.l(a,v,t)           = pva.l(a,v,t-1) ;
   xf.l(a,l,t)            = work*xf.l(a,l,t-1) ;
   plab1.l(a,v,t)         = plab1.l(a,v,t-1) ;
   kd.l(a,v,t)            = work*kd.l(a,v,t-1) ;
   xnrgp.l(a,v,t)         = work*xnrgp.l(a,v,t-1) ;
   pkse.l(a,v,t)          = pkse.l(a,v,t-1) ;

   swage.l(a,l,t)         = swage.l(a,l,t-1) ;
   pswage.l(a,l,t)        = pswage.l(a,l,t-1) ;
   pk.l(a,v,t)            = pk.l(a,v,t-1) ;
   pk_pt.l(a,v,t)         = pk_pt.l(a,v,t-1) ;
   pnrgp.l(a,v,t)         = pnrgp.l(a,v,t-1) ;
   pnd.l(a,t)             = pnd.l(a,t-1) ;
   xpv.l(a,v,t)           = work*xpv.l(a,v,t-1) ;
   pva.l(a,v,t)           = pva.l(a,v,t-1) ;
   xp.l(a,t)              = work*xp.l(a,t-1) ;

   x.l(a,i,t)             = work*x.l(a,i,t-1) ;
   p.l(a,i,t)             = p.l(a,i,t-1) ;
   xs.l(i,t)              = work*xs.l(i,t-1) ;
   ps.l(i,t)              = ps.l(i,t-1) ;
  delst.fx(i,t)           = delst.l(i,t-1) ;

   yh.l(h,t)              = work*yh.l(h,t-1) ;
   savh.l(h,t)            = work*savh.l(h,t-1) ;
   ev.l(h,t)              = ev.l(h,t-1) ;

   yg.l(g,t)              = work*yg.l(g,t-1) ;

   savg.l(t)              = work*savg.l(t-1) ;
   rsg.fx(t)               = rsg.l(t-1) ;
$ontext

   rsg.l(t)               = 1*rsg.l(t-1) ;
$offtext
*   savf.l(t)              = savf.l(t-1) ;

   yf.l(oa,t)             = work*yf.l(oa,t-1) ;
   xfd.l(oa,t)$(not adpinv(oa))  = work*xfd.l(oa,t-1) ;
   xfd.l(oa,t)$(adpinv(oa))      = xfd.l(oa,t-1) ;
   pf.l(oa,t)             = pf.l(oa,t-1) ;

   xkf.l(h,k,t)           = work*xkf.l(h,k,t-1) ;
   pkf.l(h,k,t)           = pkf.l(h,k,t-1) ;
   xkfnnrg.l(h,k,t)       = work*xkfnnrg.l(h,k,t-1) ;
   xkfnrg.l(h,k,t)        = work*xkfnrg.l(h,k,t-1) ;
   pkfnnrg.l(h,k,t)       = pkfnnrg.l(h,k,t-1) ;
   pkfnrg.l(h,k,t)        = pkfnrg.l(h,k,t-1) ;
*  xkfshr.l(oa,k,t)       = xkfshr.l(oa,k,t-1) ;
*  akf.l(oa,k,t)          = akf.l(oa,k,t-1) ;

*  consScale.l(h,t)       = consScale.l(h,t-1) ;
*  uh.l(h,t)              = uh.l(h,t-1) ;
*  hpop.l(h,t)            = hpop.l(h,t-1) ;

*  eh.l(h,k,t)            = eh.l(h,k,t-1) ;
*  bh.l(h,k,t)            = bh.l(h,k,t-1) ;

*  incelas.l(h,k,t)       = incelas.l(h,k,t-1) ;
*  ued.l(h,k,kp,t)        = ued.l(h,k,kp,t-1) ;
*  ced.l(h,k,kp,t)        = ced.l(h,k,kp,t-1) ;
*  ape.l(h,k,kp,t)        = ape.l(h,k,kp,t-1) ;

   xfnnrg.l(f,t)        = work*xfnnrg.l(f,t-1) ;
   xfnrg.l(f,t)         = work*xfnrg.l(f,t-1) ;
   pfnnrg.l(f,t)        = pfnnrg.l(f,t-1) ;
   pfnrg.l(f,t)         = pfnrg.l(f,t-1) ;

   xa.l(i,aa,t)           = work*xa.l(i,aa,t-1) ;
   xat.l(i,t)             = work*xat.l(i,t-1) ;
   pa.l(i,t)              = pa.l(i,t-1) ;

   xd.l(i,t)              = work*xd.l(i,t-1) ;
   pd.l(i,t)              = pd.l(i,t-1) ;
   pda.l(i,t)             = pda.l(i,t-1) ;
   xe.l(i,t)              = work*xe.l(i,t-1) ;
   pe.l(i,t)              = pe.l(i,t-1) ;
   pwe.l(i,t)             = pwe.l(i,t-1) ;
   pwm.l(i,t)             = pwm.l(i,t-1) ;

   xm.l(i,t)              = work*xm.l(i,t-1) ;
   pma.l(i,t)             = pma.l(i,t-1) ;

*  lsT.l(l,t)             = lsT.l(l,t-1) ;
   wage.l(l,t)            = wage.l(l,t-1) ;
*  ls.l(a,l,t)            = ls.l(a,l,t-1) ;

   tland.l(lnd,t)             = tland.l(lnd,t-1) ;
   ptland.l(lnd,t)            = ptland.l(lnd,t-1) ;
   pland.l(a,lnd,t)           = pland.l(a,lnd,t-1) ;
   pland_pt.l(a,lnd,t)           = pland_pt.l(a,lnd,t-1) ;

   kxrat.l(a,t)           = kxrat.l(a,t-1) ;
   rrat.l(a,t)            = rrat.l(a,t-1) ;
   trent.l(t)             = trent.l(t-1) ;

   kaps.l(t)              = work*kaps.l(t-1) ;
   kstock.l(t)            = work*kstock.l(t-1) ;


   invGFact.l(t)          = invGFact.l(t-1) ;
*  Give it a good guess
   if(0,
   loop(inv,
      kstock.l(t)$(ts(t) and gap(t) gt 1) = (kstock.l(t-1) - invGFact.l(t)*xfd.l(inv,t-1))*power(1-depr.l(t), gap(t))
               +   invGFact.l(t)*(work*xfd.l(inv,t-1)) ;
   ) ;
   ) ;

*  tdelst.l(t)            = tdelst.l(t) ;
*  rtdelst.l(t)           = rtdelst.l(t) ;
   pdelst.l(t)            = pdelst.l(t-1) ;

   totexp.l(t)              = work*totexp.l(t-1) ;
   rtotexp.l(t)             = work*rtotexp.l(t-1) ;
   pexp.l(t)              = pexp.l(t-1) ;
   totimp.l(t)              = work*totimp.l(t-1) ;
   rtotimp.l(t)             = work*rtotimp.l(t-1) ;
   pimp.l(t)              = pimp.l(t-1) ;

   pgdpmp.l(t)            = pgdpmp.l(t-1) ;


*Calvin temporary change to be checked : change restore
   rgdppc.l(t)            = work*rgdppc.l(t-1) ;
   gdpmp.l(t)             = work*gdpmp.l(t-1) ;
   rgdpmp.l(t)            = work*rgdpmp.l(t-1) ;

*   rgdppc.l(t)            = 1*rgdppc.l(t-1) ;
*   gdpmp.l(t)             = 1*gdpmp.l(t-1) ;
*   rgdpmp.l(t)            = 1*rgdpmp.l(t-1) ;


*Calvin modification : change restore
   ggdppc.l(t)            = work*ggdppc.l(t-1) ;
*   ggdppc.fx(t) = ggdppcT(t) ;

   pgdpfc.l(t)            = pgdpfc.l(t-1) ;
   gdpfc.l(t)             = work*gdpfc.l(t-1) ;
   rgdpfc.l(t)            = work*rgdpfc.l(t-1) ;

*   rshrGDP.l(f,t)         = rshrGDP.l(f,t-1) ;
   nshrGDP.l(f,t)         = nshrGDP.l(f,t-1) ;

   emiComm.l(em,emSrc,aa,t)      = work*emiComm.l(em,emSrc,aa,t-1) ;
   emiFact.l(em,fp,a,t)      = work*emiFact.l(em,fp,a,t-1) ;
   emiXP.l(em,a,t)        = work*emiXP.l(em,a,t-1) ;
   emiTot.l(em,t)         = work*emiTot.l(em,t-1) ;
   emiGHG.l(t)            = work*emiGHG.l(t-1) ;

   pnum.l(t)              = pnum.l(t-1)   ;
*   er.l(t)= er.l(t-1);
    er.fx(t) = 1 ;

    v_chiLs.l(l,t) = v_chiLs.l(l,t-1);
    FLFP.l(fl,t) = FLFP.l(fl,t-1);
    FLFPTot.l(t) = FLFPTot.l(t-1);
    MLFPTot.l(t) = MLFPTot.l(t-1);
*    brate.l(t)   = brate.l(t-1);
    brateU.l(t)  = brateU.l(t-1);

   debtPay.l(instfd,t) = debtPay.l(instfd,t)*work ;
   debtNew.l(instfd,t) = debtNew.l(instfd,t)*work ;
   DebtStkF.l(t)    = DebtStkF.l(t-1) + SUM(instf,debtNew.l(instf,t) - debtPay.l(instf,t) )                    ;
   DebtStkD.l(t)    = DebtStkD.l(t-1) + SUM(instd,debtNew.l(instd,t) - debtPay.l(instd,t) )                   ;
   DebtStkT.l(t)    = DebtStkD.l(t) + DebtStkF.l(t)        ;
   debtGDP.l(t)     = DebtStkT.l(t) / gdpmp.l(t)   ;
   debtNewT.l(t)    = sum(instfd,debtNew.l(instfd,t))  ;

    ) ;

loop(t$(ts(t) and ifVint and ord(t) eq 2 and (ifLoad and years(t) gt %lastYear% or not ifLoad)),

*  May have to jump start some variables in the first simulation year

   loop((Old,New),
      lab1.l(a,New,t)  = 0.1*lab1.l(a,Old,t) ;
      vav.l(a,New,t)   = 0.1*vav.l(a,Old,t) ;
      xpv.l(a,New,t)   = 0.1*xpv.l(a,Old,t) ;
      kse.l(a,New,t)   = 0.1*kse.l(a,Old,t) ;
      kd.l(a,New,t)    = 0.1*kd.l(a,Old,t) ;
      xnrgp.l(a,New,t) = 0.1*xnrgp.l(a,Old,t) ;

   ) ;
   kaps.l(t) = 1*sum((a, v), pk.l(a,v,t)*kd.l(a,v,t)) ;
   kapy.l(t)   = sum((a,v), kd.l(a,v,t)*pk.l(a,v,t)) ;
) ;

*- update total capital
*-if there are more than one capital this needs to change
   xf.l(a,cap,t) =  sum(v,kd.l(a,v,t)) ;
* ----------------------------------------------------------------------------------------
*
*     Zero out non-active variables
*
* ----------------------------------------------------------------------------------------

x.fx(a,i,ts)$(ap(a,i,ts) eq 0) = 0 ;
p.fx(a,i,ts)$(ap(a,i,ts) eq 0) = 1 ;
xp.fx(a,ts)$(not aact(a))      = 0 ;
xpv.fx(a,v,t)$(not aact(a))    = 0 ;
pp.fx(a,ts)$(not aact(a))      = 1 ;
xs.fx(i,ts)$(not iact(i))      = 0 ;
ps.fx(i,ts)$(not iact(i))      = 1 ;

loop(t0,
   yf.fx(oa,ts)$(yf.l(oa,t0) = 0) = 0 ;
   xfd.fx(oa,ts)$(yf.l(oa,t0) = 0) = 0 ;
   pf.fx(oa,ts)$(yf.l(oa,t0) = 0) = 1 ;
) ;

loop(v$vOld(v),
   kxrat.fx(a,t)$(ak(a,v,t) eq 0) = 1 ;
   rrat.fx(a,t)$(ak(a,v,t)  eq 0) = 1 ;
) ;
pk.fx(a,v,t)$(ak(a,v,t) eq 0)    = 1 ;
pk_pt.fx(a,v,t)$(ak(a,v,t) eq 0)    = 1 ;

xkf.fx(h,k,ts)$(not akfAct(h,k))    = 0 ;
pkf.fx(h,k,ts)$(not akfAct(h,k))    = 1 ;
xkfshr.fx(h,k,ts)$(not akfAct(h,k)) = 0 ;

xkfnnrg.fx(h,k,ts)$(aknnrg(h,k) eq 0) = 0 ;
pkfnnrg.fx(h,k,ts)$(aknnrg(h,k) eq 0) = 1 ;
xkfnrg.fx(h,k,ts)$(aknrg(h,k) eq 0) = 0 ;
pkfnrg.fx(h,k,ts)$(aknrg(h,k) eq 0) = 1 ;

xfnnrg.fx(f,ts)$(afnnrg(f,ts) eq 0) = 0 ;
pfnnrg.fx(f,ts)$(afnnrg(f,ts) eq 0) = 1 ;
xfnrg.fx(f,ts)$(afnrg(f,ts) eq 0) = 0 ;
pfnrg.fx(f,ts)$(afnrg(f,ts) eq 0) = 1 ;

pma.fx(i,ts)$(not iimp(i))      = 1 ;
pda.fx(i,ts)$(not idom(i))      = 1 ;
xat.fx(i,ts)$(not iarm(i))      = 0 ;
xa.fx(i,aa,ts)$(sam(i,aa) eq 0) = 0 ;
pa.fx(i,ts)$(not iarm(i))       = 1 ;
paf.fx(i,aa,ts)$(not iarm(i))   = 1 ;
pd.fx(i,ts)$(not idom(i))       = 1 ;
xd.fx(i,ts)$(not idom(i))       = 0 ;
pe.fx(i,ts)$(not iexp(i))       = 1 ;
xe.fx(i,ts)$(not iexp(i))       = 0 ;
pwe.fx(i,ts)$(not iexp(i))      = 1 ;
pwm.fx(i,ts)$(not iimp(i))      = 1 ;
xm.fx(i,ts)$(not iimp(i))       = 0 ;

tdelst.fx(ts)$(ifdelSt eq 0)    = 0 ;
rtdelst.fx(ts)$(ifdelSt eq 0)   = 0 ;
pdelst.fx(ts)$(ifdelSt eq 0)    = 1 ;

xf.fx(a,l,ts)$(gammal(a,l,ts) eq 0)    = 0 ;
ls.fx(a,l,ts)$(gammal(a,l,ts) eq 0)    = 0 ;
swage.fx(a,l,ts)$(gammal(a,l,ts) eq 0) = 0 ;
pswage.fx(a,l,ts)$(gammal(a,l,ts) eq 0) = 0 ;



loop(v$vOld(v),
   xf.fx(a,lnd,ts)$(aland(a,lnd,ts) eq 0)  = 0 ;
   pland.fx(a,lnd,ts)$(aland(a,lnd,ts) eq 0) = 1 ;
   pland_pt.fx(a,lnd,ts)$(aland(a,lnd,ts) eq 0) = 1 ;
) ;

tland.fx(lnd,ts)$(not ifLand)  = 0 ;
ptland.fx(lnd,ts)$(not ifLand) = 1 ;

loop(v0,
   kd.fx(a,v,ts)$(gammak(a,ts) eq 0) = 0 ;
   pk.fx(a,v,ts)$(gammak(a,ts) eq 0) = 1 ;
   pk_pt.fx(a,v,ts)$(gammak(a,ts) eq 0) = 1 ;
) ;

transfers.fx(inst,instp,ts)$(chiTr(inst,instp) eq 0) = 0 ;

*emi.fx(em,is,aa,t)$(rhoEmi(em,is,aa) eq 0) = 0 ;
emiComm.fx(em,emSrc,aa,t)$(rhoEmi(em,emSrc,aa) eq 0) = 0 ;
emiFact.fx(em,fp,a,t)$(rhoEmiFac(em,fp,a) eq 0) = 0 ;
emiXP.fx(em,a,t)$(rhoEmiXP(em,a) eq 0)     = 0 ;

*-HD: Fix labor price if not employed
plab1.fx(a,v,t)$(not alab1(a,v,t)) = 0;
*lab1.fx(a,v,t)$(not alab1(a,v,t)) = 0;


* ----------------------------------------------------------------------------
*
*  Debt variables
*
* ----------------------------------------------------------------------------

   debtPay.fx(inst,t)$(NOT debtPay.l(inst,t)) = 0 ;
   debtNew.fx(inst,t)$(NOT debtNew.l(inst,t)) = 0 ;

* ----------------------------------------------------------------------------------------
*
*     Exogenize initial values and lagged variables
*
* ----------------------------------------------------------------------------------------

*  Fix initial values (for price deflators)

ps.fx(i,t0)  = ps.l(i,t0) ;
pwe.fx(i,t0) = pwe.l(i,t0) ;
pwm.fx(i,t0) = pwm.l(i,t0) ;

pland.fx(a,lnd,t0) = pland.l(a,lnd,t0) ;
pland_pt.fx(a,lnd,t0) = pland_pt.l(a,lnd,t0) ;

swage.fx(a,l,t0) = swage.l(a,l,t0) ;
pswage.fx(a,l,t0) = pswage.l(a,l,t0) ;
pk.fx(a,v,t0)    = pk.l(a,v,t0) ;
pk_pt.fx(a,v,t0)    = pk.l(a,v,t0) ;

*  Fix initial values for dynamic equations, i.e. lagged values
* added to solve imbalance 22 03 2021
tImp.fx(i,tt-1) = tImp.l(i,tt-1) ;
*----------------------------------
rgdppc.fx(tt-1)   = rgdppc.l(tt-1) ;
xfd.fx(inv,tt-1)   = xfd.l(inv,tt-1) ;
xfd.fx(adpinv,tt-1)   = xfd.l(adpinv,tt-1) ;
kaps.fx(tt-1)     = kaps.l(tt-1) ;
kstock.fx(tt-1)   = kstock.l(tt-1) ;

kaps.fx(t0)              = kaps.l(t0) ;
kstock.fx(t0)            = kstock.l(t0) ;


kd.fx(a,v,tt-1)   = kd.l(a,v,tt-1) ;
lambdal.fx(a,l,tt-1) = lambdal.l(a,l,tt-1) ;
lambdal.fx(a,l,tt)$(not acal(a)) = 1 ;
transfers.fx(inst,instp,tt-1) = transfers.l(inst,instp,tt-1) ;
xf.fx(a,fp,tt-1) = xf.l(a,fp,tt-1) ;

DebtStkD.fx(tt-1)       = DebtStkD.l(tt-1)       ;
DebtStkF.fx(tt-1)       = DebtStkF.l(tt-1)       ;
DebtStkT.fx(tt-1)       = DebtStkT.l(tt-1)       ;
debtPay.fx(inst,tt-1)   = debtPay.l(inst,tt-1)   ;
debtNew.fx(inst,tt-1)   = debtNew.l(inst,tt-1)   ;
debtGDP.fx(tt-1)        = debtGDP.l(tt-1)       ;
DebtIntF.fx(t0)         = DebtIntF.l(t0)       ;
DebtIntD.fx(t0)         = DebtIntD.l(t0)       ;


v_chiLs.fx(l,tt-1) = v_chiLs.l(l,tt-1) ;

xa.fx(ihea,aasoc,tt-1) = xa.l(ihea,aasoc,tt-1) ;
xa.fx(iedu,aasoc,tt-10)$(ord(tt)>10) = xa.l(iedu,aasoc,tt-10) ;
xa.fx(iedu,aasoc,tt-9)$(ord(tt)>10) = xa.l(iedu,aasoc,tt-9) ;
deprate.fx(cohorts,tt-1) = deprate.l(cohorts,tt-1);
popAge.fx(age,tt-1)  = popAge.l(age,tt-1) ;
pop.fx(cohorts,tt-1) = pop.l(cohorts,tt-1) ;
*lsT.fx(lf,tt-1) = lsT.l(lf,tt-1);
*brateU.fx(tt-1)    = brateU.l(tt-1) ;
*brate.fx(tt-1)    = brate.l(tt-1) ;
*unemp.fx(tt-1) = unemp.l(tt-1) ;
aps.fx(h,tt-1) = aps.l(h,tt-1)  ;

dmgShftLambdaL.fx(tt-9) = dmgShftLambdaL.l(tt-9);

xa.fx(i,aa,t0)  = xa.l(i,aa,t0) ;
*brate.fx(t0)    = brate.l(t0) ;
   dmgShftTFP.fx(t0)        = dmgShftTFP.l(t0)        ;
   dmgShftLambdaL_HH.fx(t0) = dmgShftLambdaL_HH.l(t0) ;
   dmgShftLambdaL.fx(t0)    = dmgShftLambdaL.l(t0)    ;
   dmgShftLand.fx(t0)       = dmgShftLand.l(t0)       ;
   dmgShftChie.fx(t0)       = dmgShftChie.l(t0)       ;
   dmgShftLambdaEh.fx(t0)   = dmgShftLambdaEh.l(t0)   ;
   dmgShftDepr.fx(t0)       = dmgShftDepr.l(t0)   ;

* ----------------------------------------------------------------------------------------
*
*     Define closure rules
*
* ----------------------------------------------------------------------------------------

*  Public balance

$ontext
*- free pit
   tPITD0.lo(t) = -inf ;
   tPITD0.up(t) = +inf ;
*OR ree pit and cit
tdr.lo(t) = -inf ;
tdr.up(t) = +inf ;

$offtext

*-government saving

*   dyntab("SAVG-GDP",tt)=0;
*   savg.fx(tt)  = dyntab("SAVG-GDP",tt)*rgdpmp.l(tt-1);

   rsg.l(ts) = rsg.l(ts);
   rsg.lo(ts) = -inf ;
   rsg.up(ts) = +inf ;

*- government consumption
   rshrGDP.l(gov,t)$ts(t) = rshrGDP.l(gov,t-1);

*   rshrGDP.lo(gov,ts) = -inf ;
*   rshrGDP.up(gov,ts) = +inf ;
*lmb made endo
   rshrGDP.fx(gov,t)$ts(t) = rshrGDP.l(gov,t-1);
   xfd.lo(gov,ts) = -inf ;
   xfd.up(gov,ts) = +inf ;
*lmb made exo for DD analysis
*   xa.fx(in,f,t)$[ts(t) and f1(f) ] = xa.l(in,f,t-1)*(1+GDPpcProj(tt)/100) ;

*- government investment
*   rshrGDP.fx(ginv,t)$ts(t)  = 100*dyntab("GovInv-GDP",t);
   rshrGDP.fx(ginv,t)$ts(t)  = rshrGDP.l(ginv,t);

   xfd.lo(ginv,ts) = -inf ;
   xfd.up(ginv,ts) = +inf ;

*   xfd.fx(ginv,ts) = rshrGDP.l(ginv,ts)*rgdpmp.l(ts)/100 ;

*-private savings (marginal propensity to save)
   chims.fx(ts) = chims.l(ts) ;

*-numeriare
*   pnum.fx(ts) = pnum.l(ts);
   pnum.lo(ts) = -inf ;
   pnum.up(ts) = +inf ;

*-foreign saving = trade balance

  savf.fx(tt) = savf.l(tt-1)*(1+GDPpcProj(tt)/100);
*  savf.lo(tt) = -inf;
*  savf.up(tt) = +inf;

*-exchange rate
*   er.lo(ts) = -inf ;
*   er.up(ts) = +inf ;
   er.fx(ts) = er.l(ts) ;

* ----------------------------------------------------------------------------------------                                    *
*     Specify dynamic assumptions
*
* ----------------------------------------------------------------------------------------

if(ifComp eq 1,

*  Comparative static simulation -- no dynamocs

   lambdan.fx(a,v,ts) = lambdan.l(a,v,ts) ;
   lambdav.fx(a,v,ts) = lambdav.l(a,v,ts) ;
*   lambdal.fx(a,l,ts) = lambdal.l(a,l,ts) ;
   lambdak.fx(a,v,ts) = lambdak.l(a,v,ts) ;
   gl.fx(ts)          = 0 ;

else

*  Dynamic simulations -- update productivity shifters

   lambdan.fx(a,v,t)$ts(t) = lambdan.l(a,v,t-1)*power(1 + exProd(a,v,t), gap(t)) ;
   lambdav.fx(a,v,t)$ts(t) = lambdav.l(a,v,t-1)*power(1 + exProd(a,v,t), gap(t)) ;
   lambdak.fx(a,v,t)$ts(t) = lambdak.l(a,v,t) ;

*Calvin temporary modification  to maintain the efficiency constant
*   lambdaep.fx(a,e,v,t)$ts(t)  = lambdaep.l(a,e,v,t-1)*power(1 + geP(e,a,v,t), gap(t)) ;

   lambdaep.fx(a,e,v,t)$ts(t)  = lambdaep.l(a,e,v,t-1)*1 ;

   lambdaeh.fx(h,e,k,t)$ts(t)  = lambdaeh.l(h,e,k,t-1)*power(1 + geC(h,e,k,t), gap(t)) ;
   lambdaef.fx(f,e,t)$ts(t)    = lambdaef.l(f,e,t-1)*power(1 + geF(f,e,t), gap(t)) ;

   lambdat.fx(a,lnd,t)$ts(t)       = lambdat.l(a,lnd,t-1)*power(1 + yexo(a,t), gap(t)) ;
   lambdak.fx(a,v,t)$ts(t)     = lambdak.l(a,v,t-1)*power(1 + kprod(a,t), gap(t)) ;

   pop.l(cohorts,t)$ts(t) = popT(cohorts,t) ;


*  Labor supply shifter grows at the same rate as the working age population

*Calvin temporary modification
*   chiLs(l,t)$ts(t) = chiLs(l,t-1)*popT("p1564",t)/popT("p1564",t-1) ;
*   chiLs(l,t)$ts(t) = chiLs(l,t-1);

      chiLs(l,t) = 1;

*      chiLs(l,t)$ts(t) = chiLs(l,t-1)*pop.l("p1564",t)/pop.l("p1564",t-1) ;


*  Total capital is fixed if gap equals 1

   kstock.fx(t)$(ts(t) and gap(t) eq 1) = (1-depr.l(t))*kstock.l(t-1) + sum(inv, xfd.l(inv,t-1)) ;

   kstock.lo(t)$(ts(t) and gap(t) gt 1) = -inf ;
   kstock.up(t)$(ts(t) and gap(t) gt 1) =  inf ;

) ;


if(ifComp ne 1 and ifCal eq 1,

*  Baseline scenario --> gdp per capita growth is fixed, labor productivity is endogenous

   ggdppc.fx(ts) = ggdppcT(ts) ;
*   rgdppc.fx(ts) = rgdppc.l(ts)*power(1 + ggdppc.l(ts), gap(ts)) ;
*   rgdpmp.fx(t)$ts(t)  = (1+dyntab("GDP",t)/100)*rgdpmp.l(t-1) ;
*   gl.lo(ts)     = -inf ;
*   gl.up(ts)     = +inf ;
    tfp.lo(t)     = -inf ;
    tfp.up(t)     = +inf ;
*    tfp.fx(t)     =  tfp.l(t);
    gl.fx(ts)     = gl.l(ts) ;
*   ggdppc.lo(ts) = -inf ;
*   ggdppc.up(ts) = +inf ;

*lmb made endogenous
   brateU.fx(t)$ts(t) =  popAge.l("age000",t) / sum(age$mapage(age,"P1564"),popAge.l(age,t-1));

*-adaptation investments in the baseline (level fixed, shares adjusts)
   xfd.fx(adpinv,t) = sum(t0,xfd.l(adpinv,t0)) ;
   adpInvShr.lo(adpinv,t) = -inf ;
   adpInvShr.up(adpinv,t) = +inf ;

elseif (ifComp ne 1 and ifCal ne 1),

*  Dynamic scenarios with pre-calibrated productivity trends

   ggdppc.lo(ts) = -inf ;
   ggdppc.up(ts) = +inf ;

   gl.fx(ts)     = gl.l(ts) ;
   tfp.fx(t)     = tfp.l(t);

*-fix labor productivity to initial levels
*   lambdal.fx(a,l,ts) = lambdal.l(a,l,ts) ;
*lmb
*   brateU.fx(t)$ts(t) = brateU.l(t) ;
   brateU.fx(t)$ts(t) = brateU.l(t-1)*( brateScale(t)/brateScale(t-1) ) ;

);

*- alternatives
$ontext
  savg.fx(tt) =dyntab("SAVG_GDP",tt)*rgdpmp.l(tt);
  savf.fx(tt) =dyntab("SAVF_GDP",tt-1)*rgdpmp.l(tt);
*   savg.fx(ts) =savg.l(ts)*(1 + ggdppcT(ts));
*  savf.fx(ts) = savf.l(ts)*(1 + ggdppcT(ts)) ;

  rsg.l(ts) = rsg.l(ts);
   rsg.lo(ts) = -inf ;
   rsg.up(ts) = +inf ;


*  Government expenditures as a share of GDP are fixed
   rshrGDP.l(gov,t)$ts(t) = rshrGDP.l(gov,t-1);
   rshrGDP.lo(gov,ts) = -inf ;
   rshrGDP.up(gov,ts) = +inf ;
*   rshrGDP.fx(gov,t)$ts(t)  = 100*dyntab("GovCons_GDP",t) ;
   xfd.lo(gov,ts) = -inf ;
   xfd.up(gov,ts) = +inf ;

$offtext

*- update transfers from ROW by population growth

rowtransfers.fx(inst,t)$(ord(t)>1) = rowtransfers.l(inst,t-1) * pop.l("PTOTL",t)/pop.l("PTOTL",t-1) ;

*-increase factor tax by previous period's GDP deflator
*fwtx.fx(a,l,t)$(ord(t)>1)  = sum(t0,fwtx.l(a,l,t0)/pgdpmp.l(t0)) * pgdpmp.l(t-1) ;
tfac.fx(a,fp,t)$(NOT sum(is$mapftax(fp,is),sam(is,a)))  = 0 ;

*-emission trading
*- add ifemiTrade
        loop(t0,
        emPerm.l(em,aa,tt) = emiSecA.l(em,aa,t0);
        );
        emSupply.FX(em,t) =  0 ;
        emRev.FX(em,aa,t) = 0;
        embuy.FX(em,aa,t) = 0;

        emRev.FX(em,aa,t)$(NOT emSwitch)  = 0;
        emBuy.FX(em,aa,t)$(NOT emSwitch)  = 0;


*        emical.lo(tt) = -inf ;
*        emical.up(tt) = +inf ;

*        emiGHG.fx(tt) =  emiGHGTarg(tt) ;

