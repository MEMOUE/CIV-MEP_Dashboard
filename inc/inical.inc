* ----------------------------------------------------------------------------
*
*  Initialize energy prices
*
* ----------------------------------------------------------------------------
parameters
hwork(h)
 lwork(l) ;
parameter
   psb0(i)   Basic supply price
;

psb0(i)   = 1 ;
ps.l(i,t) = 1 ;

loop(e,

   psb0(e) =
*  Calculate total supply in value
             (sum(a0, sum(i0$mapis(i0,e), sam0(a0, i0)))
           +  sum((is0,row)$mapis(is0,row), sum(i0$mapis(i0,e), sam0(is0, i0))))
*  Calculate total supply in volume
           / (sum(a0, sum(i0$mapis(i0,e), sam0(a0, i0)/nrgPriceBase(i0)))
           + sum((is0,row)$mapis(is0,row), sum(i0$mapis(i0,e), sam0(is0, i0)/nrgPriceBase(i0)))) ;

) ;

if(0,
*  Ignore energy price initialization
   psb0(e) = 1 ;
) ;

*  Reset ps for sectors with no domestic output

loop(e,

   ps.l(e,t)$(sum(a0, sum(i0$mapis(i0,e), sam0(a0, i0))) eq 0) = 1 ;
   ps.l(e,t)$(sum(a0, sum(i0$mapis(i0,e), sam0(a0, i0))) ne 0) = psb0(e) ;

) ;

p.l(a,i,t) = ps.l(i,t) ;

* ----------------------------------------------------------------------------
*
*  Initialize production variables
*
* ----------------------------------------------------------------------------
*-hd: factor tax

*pk.l(a,v,t)     = sum(cap, sam(Cap,a)-sum(ftx,sam(ftx,cap)))/sum(cap, sam(Cap,a)) ;
pk.l(a,v,t)     = 1;
*pland.l(a,lnd,t)    = sum(lnd, sam(lnd,a)-sum(ftx,sam(ftx,lnd)))/sum(lnd, sam(lnd,a)) ;
pland.l(a,lnd,t)    = 1;


pp.l(a,t)       = 1 ;
pnd.l(a,t)      = 1 ;
pnrgp.l(a,v,t)  = 1 ;
pva.l(a,v,t)    = 1 ;
pkse.l(a,v,t)   = 1 ;
pksk.l(a,v,t)   = 1 ;
plab1.l(a,v,t)  = 1 ;
plab2.l(a,v,t)  = 1 ;
pa.l(i,t)       = 1 ;

xa.l(i,aa,t)    = sam(i,aa)/pa.l(i,t) ;
nd.l(a,t)       = sum(in, pa.l(in,t)*xa.l(in,a,t))/pnd.l(a,t) ;

*  Initialize labor demand volume to values in SAM
*  !!!! We may wish to override this with actual volumes if data becomes available

xf.l(a,l,t)     = labor(l,a) ;
*xf.l(a,l,t)     = labor(l,a) ;
xf.l(a,lnd,t)     = sam(lnd,a) / pland.l(a,lnd,t) ;

kd.l(a,v0,t)    = sum(cap, sam(Cap,a))/pk.l(a,v0,t) ;

*-if there are more than one capital this needs to be modified
xf.l(a,cap,t) =  sum(v,kd.l(a,v,t)) ;

*-be careful with this
*xf.l(a,l,t)$(NOT xf.l(a,l,t))  = sam(l,a) ;



swage.l(a,l,t)$(xf.l(a,l,t) ne 0)  = sam(l,a)/xf.l(a,l,t) ;
*swage.l(a,l,t)$(xf.l(a,l,t) ne 0)  = 1 ;


loop(t0, ldFlag(a,l)$xf.l(a,l,t0) = 1 ; ) ;

*DP modif for factor taxes; here factor taxes are defined as specific/unit
   tFac0.fx(a,l,t)$xf.l(a,l,t)          = sum(is$mapftax(l,is),sam(is,a))/(swage.l(a,l,t) * xf.l(a,l,t));
   tFac0.fx(a,lnd,t)$xf.l(a,lnd,t)          = sum(is$mapftax(lnd,is),sam(is,a))/(pland.l(a,lnd,t) * xf.l(a,lnd,t));
   tFac0.fx(a,cap,t)$xf.l(a,cap,t)          = sum(is$mapftax(cap,is),sam(is,a))/sum(v0,(pk.l(a,v0,t) * xf.l(a,cap,t)));
   tFac0.fx(a,fp,t)$(NOT xf.l(a,fp,t))          = 0;
   tFacD0.fx(t)              = 0;
   tFacD1.fx(a,t)            = 0;
   tFacD2.fx(fp,t)           = 0;
   tFacM0.fx(t)              = 1;
   tFacM1.fx(a,t)            = 1;
   tFacM2.fx(fp,t)           = 1;
   tfacMLab.fx(t)            = 1;
   tfacMCap.fx(t)            = 1;
   tfacMlnd.fx(t)            = 1;

   tFac.l(a,fp,t)           = (tFac0.l(a,fp,t) + (tFacD0.l(t) + tFacD1.l(a,t) + tFacD2.l(fp,t)))
                     *tFacM0.l(t) * tFacM1.l(a,t) * tFacM2.l(fp,t) ;


rtfac.l(a,l,t)$(xf.l(a,l,t) ne 0) = tfac.l(a,l,t) ;
*fwtx.fx(a,"F-unskill",t)$(xf.l(a,"F-unskill",t) ne 0) = sam("FWL_UNSKL",a)/xf.l(a,"F-unskill",t) ;
pswage.l(a,l,t)= swage.l(a,l,t) *( 1+ tFac.l(a,l,t));

pland_pt.l(a,lnd,t) = pland.l(a,lnd,t) *(1 +tfac.l(a,lnd,t)) ;

pk_pt.l(a,v,t)     = pk.l(a,v,t) * (1 + sum(cap,tfac.l(a,cap,t)));

lab1.l(a,v0,t)  = sum(l$ul(l), pswage.l(a,l,t)*xf.l(a,l,t))/plab1.l(a,v0,t) ;
lab2.l(a,v0,t)  = sum(l$sl(l), pswage.l(a,l,t)*xf.l(a,l,t))/plab2.l(a,v0,t) ;




xnrgp.l(a,v0,t) = sum(e, sam(e,a))/pnrgp.l(a,v0,t) ;

ksk.l(a,v0,t)   = (kd.l(a,v0,t)*pk_pt.l(a,v0,t) + lab2.l(a,v0,t)*plab2.l(a,v0,t))/pksk.l(a,v0,t) ;
kse.l(a,v0,t)   = (ksk.l(a,v0,t)*pksk.l(a,v0,t) + xnrgp.l(a,v0,t)*pnrgp.l(a,v0,t))/pkse.l(a,v0,t) ;

vav.l(a,v0,t)   = (sum(lnd,xf.l(a,lnd,t)*pland_pt.l(a,lnd,t))
                +  lab1.l(a,v0,t)*plab1.l(a,v0,t)
                +  kse.l(a,v0,t)*pkse.l(a,v0,t)) / pva.l(a,v0,t) ;

xpv.l(a,v0,t)   = pnd.l(a,t)*nd.l(a,t) + pva.l(a,v0,t)*vav.l(a,v0,t) ;
xp.l(a,t)       = (sum(v0, xpv.l(a,v0,t)) + sum(ptx,sam(ptx,a)) + sum(psb,sam(psb,a)))/pp.l(a,t) ;
x.l(a,i,t)      = sam(a,i) / p.l(a,i,t) ;
xs.l(i,t)       = sum(a, p.l(a,i,t)*x.l(a,i,t)) / ps.l(i,t) ;
delst.fx(i,t)   = sum(stb,sam(i,stb)) / ps.l(i,t) ;

*  !!!! This needs to be checked -- for the moment, if delst > xs, assign all to imports
*  !!!! This was needed for coal imports

*  Must re-value mdelst once we have tariffs

mdelst.l(i,t)$(delst.l(i,t) gt xs.l(i,t)) = delst.l(i,t) ;
delst.fx(i,t)$(delst.l(i,t) gt xs.l(i,t)) = 0 ;

loop(t$(ord(t) eq 1),
   aact(a) = yes$(xp.l(a,t) ne 0) ;
) ;

loop(t$(ord(t) eq 1),
   iact(i) = yes$(xs.l(i,t) ne 0) ;
) ;

loop(v0,
   tpsb0.fx(a,t)$(xpv.l(a,v0,t) ne 0)             = sum(psb,sam(psb,a))/xpv.l(a,v0,t) ;
    );
   tpsbD0.fx(t)              = 0;
   tpsbD1.fx(a,t)            = 0;
   tpsbM0.fx(t)              = 1;
   tpsbM1.fx(a,t)            = 1;
   tpsb.l(a,t)              = (tpsb0.l(a,t) + (tpsbD0.l(t) + tpsbD1.l(a,t)))
                     *tpsbM0.l(t) * tpsbM1.l(a,t) ;

loop(v0,
   tPrd0.fx(a,t)$(xpv.l(a,v0,t) ne 0)             = sum(ptx,sam(ptx,a))/xpv.l(a,v0,t)
    );
   tPrdD0.fx(t)              = 0;
   tPrdD1.fx(a,t)            = 0;
   tPrdM0.fx(t)              = 1;
   tPrdM1.fx(a,t)            = 1;
   tPrd.l(a,t)              = (tPrd0.l(a,t) + (tPrdD0.l(t) + tPrdD1.l(a,t)))
                     *tPrdM0.l(t) * tPrdM1.l(a,t) ;


px.l(a,t)     = pp.l(a,t)/(1 + tprd.l(a,t) + tpsb.l(a,t)) ;
pxv.l(a,v,t)  = px.l(a,t) ;
xpv.l(a,v0,t) = xpv.l(a,v0,t)/pxv.l(a,v0,t) ;


* ----------------------------------------------------------------------------
*
*  Initialize debt variables
*
* ----------------------------------------------------------------------------

*-assign debt parameters

*- shares of institutions in debt payments
    chiDebtPayD(instd)$sum(instdp,SAM(instdp,"i-debt"))   =  SAM(instd,"i-debt")/sum(instdp,SAM(instdp,"i-debt")) ;
    chiDebtPayF(instf)$sum(instfp,SAM(instfp,"i-debt"))   =  SAM(instf,"i-debt")/sum(instfp,SAM(instfp,"i-debt")) ;

*-debt repayment ratio
    rDebtStkD.fx(t)$DebtStkD0        = sum(instdp,SAM(instdp,"i-debt")) / DebtStkD0 - DebtIntD0/100;
    rDebtStkF.fx(t)$DebtStkF0        = sum(instfp,SAM(instfp,"i-debt")) / DebtStkF0 - DebtIntF0/100;
    rDebtStk.fx(t) = 1;


   DebtStkF.l(t) = DebtStkF0                    ;
   DebtStkD.l(t) = DebtStkD0                    ;
   DebtStkT.l(t) = DebtStkD.l(t) + DebtStkF.l(t)        ;
   debtPay.l(instfd,t) = SAM(instfd,"i-debt")   ;
   debtNew.l(instfd,t) = SAM("i-debt",instfd)   ;
   debtNew.fx(instfd,t)$(not  debtNew.l(instfd,t)) =  0  ;
   debtNewT.l(t) = sum(instfd,SAM("i-debt",instfd))   ;

   DebtIntF.l(t) =  DebtIntF0 ;
   DebtIntD.l(t) =  DebtIntD0 ;



* ----------------------------------------------------------------------------
*
*  Initialize income variables
*
* ----------------------------------------------------------------------------


yf.l(oa,t)  = sum(i, pa.l(i,t)*xa.l(i,oa,t)) ;

yf0(f,t) = yf.l(f,t) ;

kapy.l(t)   = sum((a,v0), kd.l(a,v0,t)*pk.l(a,v0,t)) ;
transfers.l(inst,instp,t) = sam(inst,instp) ;

yh.l(h,t)   = sum(lnd, sam(h, lnd)) + sum(l, sam(h,l)) + sum(cap, sam(h,cap))
            + sum((instp,inst)$mapinst(h,instp), transfers.l(instp, inst,t))
            +  SUM(instd$mapinst(h,instd),debtPay.l(instd,t)) ;

gini.l(t)  = 2 * sum(h,ord(h) * yh.l(h,t))/(card(h)*sum(h,yh.l(h,t))) - (card(h)+1)/card(h) ;

savh.l(h,t) = sum(inv, sam(inv,h)) ;

   tDr.fx(t )                = 1;

   tPIT0.fx(h,t)             = sum(dtx, sam(dtx,h))/yh.l(h,t) ;
   tPITD0.fx(t)              = 0;
   tPITD1.fx(h,t)            = 0;
   tPITM0.fx(t)              = 1;
   tPITM1.fx(h,t)            = 1;
   tPIT.l(h,t)              = (tPit0.l(h,t) + (tPitD0.l(t) + tPitD1.l(h,t)))
                              * tDr.l(t) * tPitM0.l(t) * tPitM1.l(h,t);


loop((h,instp,t)$mapinst(h,instp),
   totTr.l(instp,t) = sum(inst, transfers.l(inst,instp,t)) ;
   if(t0(t),
      work = yh.l(h,t) ;
      if (work ne 0,
         chiTotTr(instp)  = totTr.l(instp,t) / work ;
      ) ;
   ) ;
) ;

aps.l(h,t) = savh.l(h,t)/(yh.l(h,t) *(1-tPIT.l(h,t) ) - sum((inst)$mapinst(h,inst), totTr.l(inst,t))) ;

chims.fx(t) = 1 ;

loop(t0,
   aps0(h)    = aps.l(h,t0) ;
) ;

entrY.l(entr,t) = sum(is, sam(entr,is)) ;
entrTax.l(entr,t) = sum(dtx, sam(dtx,entr)) ;

   tCIT0.fx(entr,t)          = sum(dtx, sam(dtx,entr))/entrY.l(entr,t) ;
   tCITD0.fx(t)              = 0;
   tCITD1.fx(entr,t)         = 0;
   tCITM0.fx(t)              = 1;
   tCITM1.fx(entr,t)         = 1;
   tCIT.l(entr,t)           = (tCit0.l(entr,t) + (tCitD0.l(t) + tCitD1.l(entr,t)))
                               * tDr.l(t) * tCitM0.l(t) * tCitM1.l(entr,t);

savEntr.l(entr,t) = sum(inv, sam(inv,entr)) + sum(ginv, sam(ginv,entr));

apsEntr.fx(entr,t) = entrY.l(entr,t) - entrTax.l(entr,t) ;
apsEntr.fx(entr,t)$(apsEntr.l(entr,t) ne 0) = savEntr.l(entr,t) / apsEntr.l(entr,t) ;

loop((entr,instp,t)$mapinst(entr,instp),
   totTr.l(instp,t) = sum(inst, transfers.l(inst,instp,t)) ;
   if(t0(t),
      work = entrY.l(entr,t) - entrTax.l(entr,t) - savEntr.l(entr,t) - debtNew.l(instp,t) ;
      if (work ne 0,
         chiTotTr(instp)  = totTr.l(instp,t) / work ;
      ) ;
   ) ;
) ;

loop((row,instp,t)$mapinst(row, instp),
   totTr.l(instp,t) = sum(inst, transfers.l(inst,instp,t)) ;
   rowtransfers.fx(inst,t) = transfers.l(inst,instp,t) ;

*transfers.l(inst,instp,t) =e= er.l(t)*rowtransfers.l(inst,t) ;
) ;
*Calvin addition--temporary to address issue on household remittances calibration
*   rowtransfers.fx("hhold",t) = transfers.l("hhold","rowld",t) ;


loop((instp,t0),
   work = sum(inst, transfers.l(inst,instp,t0)) ;
   chiTr(inst,instp)$(work ne 0) = transfers.l(inst,instp,t0)/work ;
) ;
*display  mapinst,chiTr, rowtransfers.l, transfers.l;



* ----------------------------------------------------------------------------
*
*  Initialize final demand variables
*
* ----------------------------------------------------------------------------




pf.l(oa,t) = 1 ;
xfd.l(oa,t) = yf.l(oa,t)/pf.l(oa,t) ;
adpInvShr.fx(adpinv,t)$sum(f$map_adpInv(f,adpinv),xfd.l(f,t)) = xfd.l(adpinv,t) / sum(f$map_adpInv(f,adpinv),xfd.l(f,t))  ;
adpInvShr.fx(adpinv,t)$(NOT sum(f$map_adpInv(f,adpinv),xfd.l(f,t))) = 0 ;
xfT(oa,t)  = xfd.l(oa,t) ;

pkfnnrg.l(h,k,t) = 1 ;
xkfnnrg.l(h,k,t) = sum(in, transMat(in, k, h))/pkfnnrg.l(h,k,t) ;

pkfnrg.l(h,k,t) = 1 ;
xkfnrg.l(h,k,t) = sum(e, transMat(e, k, h))/pkfnrg.l(h,k,t) ;

pkf.l(h,k,t) = 1 ;
xkf.l(h,k,t) = (pkfnnrg.l(h,k,t)*xkfnnrg.l(h,k,t) + pkfnrg.l(h,k,t)*xkfnrg.l(h,k,t))/pkf.l(h,k,t) ;

xkfshr.l(h,k,t) = pkf.l(h,k,t)*xkf.l(h,k,t)/yf.l(h,t) ;

lambdaeh.fx(h,e,k,t) = 1 ;

pfnnrg.l(f,t) = 1 ;
xfnnrg.l(f,t) = sum(in, pa.l(in,t)*xa.l(in,f,t))/pfnnrg.l(f,t) ;

pfnrg.l(f,t)  = 1 ;
xfnrg.l(f,t)  = sum(e, pa.l(e,t)*xa.l(e,f,t))/pfnrg.l(f,t) ;

lambdaef.fx(f,e,t) = 1 ;

* ----------------------------------------------------------------------------
*
*  Initialize imports
*
* ----------------------------------------------------------------------------

er.fx(t) = 1 ;

loop(row,
   iimp(i)$(sam(row,i) ne 0) = yes ;
) ;

pwm.l(i,t)$iimp(i)       = psb0(i) /er.l(t) ;
pwm.l(i,t)$(not iimp(i)) = 1 ;
pwmROW.fx(i,t)           = pwm.l(i,t) ;

loop((mtx,row),
   tImp0.fx(i,t)$iimp(i) = sam(mtx,i)/sam(row,i) ;
   tImp0.fx(i,t)$(not iimp(i)) = 0;
    ) ;
   tImpD0.fx(t)              = 0;
   tImpD1.fx(i,t)            = 0;
   tImpM0.fx(t)              = 1;
   tImpM1.fx(i,t)            = 1;
   tImp.l(i,t)              = (tImp0.l(i,t) + (tImpD0.l(t) + tImpD1.l(i,t)))
                               *tImpM0.l(t) * tImpM1.l(i,t)  ;

*  Re-base imported inventory

mdelst.fx(i,t) = mdelst.l(i,t)/(pwm.l(i,t)*er.l(t)*(1+tImp.l(i,t))) ;

*  Calculate import volumes

loop(row,
   xm.l(i,t) = sam(row,i)/(er.l(t)*pwm.l(i,t)) - mdelst.l(i,t) ;
) ;

* display pwm.l, tImp.l, mdelst.l, xm.l ;

* ----------------------------------------------------------------------------
*
*  Initialize exports
*
* ----------------------------------------------------------------------------

*  Assume trade and transport margins are uniform across all nodes, then

pmarg.l(i,t) = 1 ;

$ontext
tmg.fx(j,"d",t) = xs.l(j,t) - delst.l(j,t) + xm.l(j,t) ;
tmg.fx(j,"d",t)$(tmg.l(j,"d",t) eq 0) = NA ;
display tmg.l ; abort "temp" ;
$offtext

*mODIFICATION TEMPORAIRE DE CAlvin

tmg.fx(j,"d",t) =  sum(i, sam(i,j))
                / (pmarg.l(j,t)*(xs.l(j,t) - delst.l(j,t) + xm.l(j,t))) ;

*tmg.fx(j,"d",t) = 0;

tmg.fx(j,n,t) = tmg.l(j, "d", t) ;
display tmg.l ;

loop(row,
   iexp(i)$(sam(i,row) ne 0) = yes ;
) ;

pe.l(i,t)$iexp(i) = ps.l(i,t) ;
pe.l(i,t)$(not iexp(i)) = 1 ;
pwe.l(i,t) = 1 ;

loop((row,etx),
   xe.l(i,t)$iexp(i)  = (sam(i,row) - sam(etx,i)) / (pe.l(i,t) + pmarg.l(i,t)*tmg.l(i,"x",t)) ;
   tExp0.fx(i,t)$iexp(i) = sam(etx,i) / (pe.l(i,t) * xe.l(i,t)) ;
   tExp0.fx(i,t)$(not iexp(i)) = 0 ;
   tExpD0.fx(t)              = 0;
   tExpD1.fx(i,t)            = 0;
   TExpM0.fx(t)              = 1;
   tExpM1.fx(i,t)            = 1;
   tExp.l(i,t)              = (tExp0.l(i,t) + (tExpD0.l(t) + tExpD1.l(i,t)))
                              * tExpM0.l(t) * tExpM1.l(i,t)  ;
   pwe.l(i,t)$iexp(i) = (pe.l(i,t)*(1+texp.l(i,t)) + pmarg.l(i,t)*tmg.l(i,"x",t)) / er.l(t) ;
) ;




pweROW.fx(i,t) = pwe.l(i,t) ;

xd.l(i,t) = xs.l(i,t) - xe.l(i,t) - delst.l(i,t) ;

loop((i,t0),
ABORT$(xd.l(i,t0) <  0) 'Exports > Production; check xd';
);


* display xs.l, delst.l, tmg.l, pe.l, xe.l, te.l, pwe.l, xd.l ;

* ----------------------------------------------------------------------------
*
*  Initialize Armington prices
*
* ----------------------------------------------------------------------------

set ax(aa) ; ax(aa) = yes ; ax(i) = no ;

loop(t0,
   idom(i)$(xd.l(i,t0) ne 0) = yes ;
) ;

pd.l(i,t)$idom(i) = ps.l(i,t) ;
pd.l(i,t)$(not idom(i)) = 1 ;

*  Calculate value added tax rate--asssume uniformity between domestic and import

loop(otx,
   tVat0.fx(i,n,t)           = (sam(otx,i))
                 / ((pd.l(i,t) + pmarg.l(i,t)*tmg.l(i,"d",t))*xd.l(i,t)
                 +  (pwm.l(i,t)*er.l(t)*(1+timp.l(i,t)) + pmarg.l(i,t)*tmg.l(i,"m",t))*xm.l(i,t)) ;
    );

   tVat0.fx(i,n,t)$(not sum(otx,sam(otx,i))) = 0;

   tVatD0.fx(t)              = 0;
   tVatD1.fx(i,t)            = 0;
   tVatD2.fx(n,t)            = 0;
   tVatM0.fx(t)              = 1;
   tVatM1.fx(i,t)            = 1;
   tVatM2.fx(n,t)            = 1;
   tVat.l(i,n,t)            = (tVat0.l(i,n,t) + (tVatD0.l(t) + tVatD1.l(i,t) + tVatD2.l(n,t)))
                              * tVatM0.l(t) * tVatM1.l(i,t) * tVatM2.l(n,t);

*  Calculate user prices of domestic and imported goods

pda.l(i,t) = (pd.l(i,t) + pmarg.l(i,t)*tmg.l(i,"d",t))*(1 + tvat.l(i,"d",t)) ;
pma.l(i,t) = (pwm.l(i,t)*er.l(t)*(1+tImp.l(i,t)) + pmarg.l(i,t)*tmg.l(i,"m",t))*(1 + tVat.l(i,"m",t)) ;

* display pd.l, tva.l, pda.l, pma.l ;


loop(i,
   if(1 and e(i),

*     Add up Armington volumes and calculate the Armington price consistent with the volume initialization

      xat.l(i,t) = xd.l(i,t) + xm.l(i,t) ;


*      xat.l(i,t) = xd.l(i,t) + xm.l(i,t) + delst.l(i,t) ;


      pa.l(i,t) = 1 ;
      pa.l(i,t)$(xat.l(i,t) ne 0) = (pda.l(i,t)*xd.l(i,t) + pma.l(i,t)*xm.l(i,t)) / xat.l(i,t) ;

   else

*     Normalize Armington demand
*-HD: delst should be part of this
      pa.l(i,t) = 1 ;
      xat.l(i,t) = (pda.l(i,t)*xd.l(i,t) + pma.l(i,t)*xm.l(i,t)) / pa.l(i,t)  ;

   ) ;
) ;

loop(t0, iarm(i)$(xat.l(i,t0) ne 0) = yes ; ) ;

* display pa.l, xat.l ;

*  Trade and transport margins are not taxed, thus

xa.l(i,j,t) = sam(i,j) / pa.l(i,t) ;

mgencl(j)$(sum(i, sam(i,j)) ne 0) = yes ;

*  Calculate end user demand taxes -- assume uniformity

tmAll.fx(t) = 1 ;

*- HD: find a better way to do this
ABORT$(sum(ssb,1) = 0) "SSB is empty. Please add at least a dummy element" ;

loop((ssb,stx),
   loop((i,t0),
      work = xat.l(i,t0) - sum(j, xa.l(i,j,t0)) ;
      if (work ne 0,
         tPaf0.fx(i,ax,t) = (sam(ssb,i) + sam(stx,i)) / (pa.l(i,t)*work) ;
      else
         tPaf0.fx(i,ax,t) = 0 ;
         )
      ) ;
   );
   tPafD0.fx(t)              = 0; ;
   tPafD1.fx(i,t)            = 0; ;
   tPafD2.fx(aa,t)           = 0; ;
   tPafM0.fx(t)              = 1; ;
   tPafM1.fx(i,t)            = 1; ;
   tPafM2.fx(aa,t)           = 1; ;
   tPaf.l(i,aa,t)           = (tPaf0.l(i,aa,t) + (tPafD0.l(t) + tPafD1.l(i,t) + tPafD2.l(aa,t)))
                               * tPafM0.l(t) * tPafM1.l(i,t) * tPafM2.l(aa,t) * tmAll.l(t) ;



*  Margins don't have user taxes

tpaf0.fx(i,j,t) = 0 ;

xa.l(i,aa,t)$ax(aa) = sam(i,aa) / ((1+ tpaf.l(i,aa,t))*pa.l(i,t)) ;

* ----------------------------------------------------------------------------
*
*  Initialize margin equations
*
* ----------------------------------------------------------------------------

xmarg.l(j,t) = sum(i, sam(i,j)) / pmarg.l(j,t) ;

* ----------------------------------------------------------------------------
*
*  Initialize macro equations
*
* ----------------------------------------------------------------------------

tdelst.l(t)  = sum(i, ps.l(i,t)*delst.l(i,t) + er.l(t)*pwm.l(i,t)*(1+tImp.l(i,t))*mdelst.l(i,t)) ;
rtdelst.l(t) = tdelst.l(t) ;
pdelst.l(t)  = 1 ;
pdelst.l(t)$(rtdelst.l(t) ne 0)  = tdelst.l(t)/rtdelst.l(t) ;
loop(t0,
   ifDelSt$(tdelst.l(t0) eq 0) = 0 ;
) ;

totexp.l(t)  = er.l(t) * sum(i, pwe.l(i,t) * xe.l(i,t)) ;
rtotexp.l(t) = totexp.l(t) ;
pexp.l(t)  = totexp.l(t)/rtotexp.l(t) ;

totimp.l(t)  = er.l(t) * sum(i, pwm.l(i,t) * (xm.l(i,t) + mdelst.l(i,t))) ;
rtotimp.l(t) = totimp.l(t) ;
pimp.l(t)  = totimp.l(t)/rtotimp.l(t) ;

gdpmp.l(t)  = sum(fd, yf.l(fd,t)) + tdelst.l(t) + totexp.l(t) - totimp.l(t) ;
rgdpmp.l(t) = gdpmp.l(t) ;
pgdpmp.l(t) = gdpmp.l(t)/rgdpmp.l(t) ;


   debtGDP.l(t)  = DebtStkT.l(t) / gdpmp.l(t)   ;


*  Rescale PopT   ggdppcT

*popT(cohorts,t) = popT(cohorts,t) ;
pop.l(cohorts,t) = popT(cohorts,t) ;

rgdppc.l(t) = rgdpmp.l(t)/pop.l("ptotl",t) ;

*Calvin modification to be checked
*ggdppc.l(t) = 0 ;
ggdppc.fx(t) = ggdppcT(t) ;
display ggdppc.l, rgdppc.l ;

gdpfc.l(t)  = sum((a,lnd), pland_pt.l(a,lnd,t)*xf.l(a,lnd,t))
            + sum((a,l), pswage.l(a,l,t)*xf.l(a,l,t))
            + sum((a,v), pk_pt.l(a,v,t)*kd.l(a,v,t)) ;
rgdpfc.l(t) = gdpfc.l(t) ;
pgdpfc.l(t) = gdpfc.l(t)/rgdpfc.l(t) ;

rshrGDP.l(f,t) = 100*xfd.l(f,t)/rgdpmp.l(t) ;
rshrGDP.l(f,t) = xfd.l(f,t)/rgdpmp.l(t) ;
nshrGDP.l(f,t) = 100*yf.l(f,t)/gdpmp.l(t) ;
nshrGDP.l(f,t) = yf.l(f,t)/gdpmp.l(t) ;

pnum.l(t)   = pgdpmp.l(t) ;
walras.l    = 0 ;

* ----------------------------------------------------------------------------
*
*  Initialize closure equations
*
* ----------------------------------------------------------------------------

gtax.l(t)     = sum((dtx, gov), sam(dtx,gov)) ;

yg.l("psb",t) = sum(a$aact(a),tpsb.l(a,t)*px.l(a,t)*xp.l(a,t)) ;

yg.l("ptx",t) = sum(a$aact(a),tprd.l(a,t)*px.l(a,t)*xp.l(a,t)) ;

yg.l("otx",t) = sum(i, (pd.l(i,t) + pmarg.l(i,t)*tmg.l(i,"d",t))*tvat.l(i,"d",t)*xd.l(i,t)
              +  (er.l(t)*pwm.l(i,t)*(1+tImp.l(i,t)) + pmarg.l(i,t)*tmg.l(i,"m",t))*tvat.l(i,"m",t)*xm.l(i,t)) ;

yg.l("mtx",t) = sum(i, (xm.l(i,t) + mdelst.l(i,t))*pwm.l(i,t)*er.l(t)*tImp.l(i,t));

yg.l("dtx",t) = sum(h, tpit.l(h,t)*yh.l(h,t)) + sum(entr, tcit.l(entr,t)*entrY.l(entr,t)) + gtax.l(t) ;

yg.l("atx",t) = sum((i,aa), tpaf.l(i,aa,t)*pa.l(i,t)*xa.l(i,aa,t)) ;

yg.l("ftx",t) = sum(a, sum(lnd,tFac.l(a,lnd,t) * pland.l(a,lnd,t)*xf.l(a,lnd,t))
                       + sum(l,tFac.l(a,l,t) * swage.l(a,l,t)*xf.l(a,l,t))
                       + sum((v,cap),tFac.l(a,cap,t) * pk.l(a,v,t)*kd.l(a,v,t)))   ;


*Calvin modification toaccount for natural resosurce remunerations payments to government
ygov.l(t)     = sum((is,gov), sam(gov,is)) ;
*ygov.l(t)     = sum((is,gov), sam(gov,is)) + sum((gov,lnd), sam(gov,lnd)) ;
dgovtax.fx(t) = gtax.l(t) / ygov.l(t) ;

savg.l(t)= ygov.l(t) - gtax.l(t) - sum((inst,gov,instp)$mapinst(gov,instp), transfers.l(inst, instp, t)) - sum(gov, yf.l(gov,t))
              - sum(ginv, yf.l(ginv,t))
              - sum(inst,debtPay.l(inst,t));
              ;

rsg.l(t)      = savg.l(t)/pgdpmp.l(t) ;

loop((gov,instp,t)$mapinst(gov,instp),
   totTr.l(instp,t) = sum(inst, transfers.l(inst,instp,t)) ;
   if(t0(t),
      work = ygov.l(t) ;
      if (work ne 0,
         chiTotTr(instp)  = totTr.l(instp,t) / work ;
      ) ;
   ) ;
) ;

  savf.fx(t)     = sum((inv,row),sam(inv,row))/er.l(t) ;

loop(t0,
    chiDebtNew(instd)$sum(instdp,SAM("i-debt",instdp))    = SAM("i-debt",instd)/ygov.l(t0) ;
    chiDebtNew(instf)$sum(instfp,SAM("i-debt",instfp))    = SAM("i-debt",instf)/ygov.l(t0);
);


* ----------------------------------------------------------------------------
*
*  Initialize factor market variables
*
* ----------------------------------------------------------------------------

ls.l(a,l,t) = xf.l(a,l,t) ;
lsT.l(l,t)  = sum(a, ls.l(a,l,t)) ;
wage.l(l,t) = sum(a, swage.l(a,l,t)*ls.l(a,l,t)) / lsT.l(l,t) ;

tland.l(lnd,t) = sum(a, xf.l(a,lnd,t)) ;

unemp.l(t)=  pop.l("P1564",t) - sum(l,lsT.l(l,t)) ;
awage.l(t) = sum(l,wage.l(l,t)*lsT.l(l,t)) /sum(l,lsT.l(l,t)) ;
loop(t0,
   ifLand$(sum(lnd,tland.l(lnd,t0)) eq 0) = 0 ;
) ;

popAge.l(age,t) =popAge0(t,age) ;

 FLFP.l(fl,t) = lsT.l(fl,t)/pop.l("p1564",t)*3 ;
*lmb modif
* FLFPTot.l(t) = SUM(fl,FLFP.l(fl,t));
 FLFPTot.l(t) = SUM(l$(not ml(l)),lsT.l(l,t))/pop.l("p1564",t)*3.1;
 MLFPTot.l(t) = SUM(l$(ml(l)),lsT.l(l,t))/pop.l("p1564",t)*1.15;

brateU.fx(t) = popAge.l("age000",t)/pop.l("P1564",t) ;
brateScale(t)= brateU.l(t);
*Brate.l(t)  =   brateU.l(t);
*brate.l(t)$(ord(t)>1)  =  brateU.l(t)* ((FLFPTot.l(t-1)/FLFPTot.l(t))**0.001);

drate.fx(age,t)$(ord(t)>1 AND ord(age)>1) =  popAge.l(age,t) / popAge.l(age-1,t-1) ;

popAge.fx(age,t0) = popAge.l(age,t0) ;

ptland.l(lnd,t) = 1 ;
ptland.l(lnd,t)$ifLand = sum(a, pland_pt.l(a,lnd,t)*xf.l(a,lnd,t)) / tland.l(lnd,t) ;

loop(v0,
   kaps.l(t)  = sum(a, kd.l(a,v0,t)) ;
   trent.l(t) = sum(a, pk.l(a,v0,t)*kd.l(a,v0,t)) / kaps.l(t) ;
) ;

kaps.l(t) = 1*sum((a, vOld), pk.l(a,vOld,t)*kd.l(a,vOld,t)) ;
kstock.l(t) = (kaps.l(t)/ror0) ;

* ----------------------------------------------------------------------------
*
*  Initialize dynamic variables
*
* ----------------------------------------------------------------------------

gl.l(t) = 0 ;
lambdan.l(a,v,t) = 1 ;
lambdav.l(a,v,t) = 1 ;
lambdal.l(a,l,t) = 1 ;
lambdak.l(a,v,t) = 1 ;
prodeffct(a)=0;

*  Initialize invGFact to the ratio of an estimate of the LR growth rate of
*  investment + the LR depreciation rate

invGFact.l(t) = 1/(0.07) ;
*invGFact.l(t) = 1 ;

loop(v$vOld(v),
   kxrat.l(a,t)$aact(a) = kd.l(a,v,t)/xpv.l(a,v,t) ;
) ;
rrat.l(a,t)  = 1 ;
rrat.up(a,t) = 1 ;
trent.l(t)   = 1 ;

tempD(t) = 2 * (years(t)-2019)/81 ;

depr.fx(t) = 0.02 ;


tfp.l(t) = 1 ;

Tfploss(man) = 0;
Tfploss(agr) = 0.07 ;
Tfploss(srv) = 0.1 ;

loop((tlast,t0),
tfpAct.fx(a,t) = 1-(years(t)-years(t0))/(years(tlast)-years(t0))*Tfploss(a);
tfpAct.fx(a,t)$(NOT tfpAct.l(a,t))   = 1   ;
);

tfpAct.fx(a,t) = 1   ;

* ----------------------------------------------------------------------------
*
*  Gender parameters
*
* ----------------------------------------------------------------------------

epsEdu(l,t) = 0;
epsEdu(l,t)$(not ml(l)) = 0.01464;
epsEdu(l,t)$(ml(l))     = 0.01464/2;
epsHea(l,t) = 0 ;
epsHea(l,t)$(not ml(l)) = 0.02571 ;
epsHea(l,t)$(ml(l))     = 0.02571/2 ;
**epsHea(fl,t) = 0.5 ;
epsCul(fl,t) = 0.0 ;

culIndex(l,t) = 1 ;

chiLambdaL(l,t)  = 1;
chiLambdaLA(a,l,t)  = 1;

* ----------------------------------------------------------------------------
*
*  Initialize emission variables
*
* ----------------------------------------------------------------------------
*-HD: GHG due to consumption are not included

*emi.l(em,i,is,t) = escale*sum((i0,is0)$(mapis(i0,i) and mapis(is0,is)), emi0(em,i0,is0)) ;
*emi.l(em,fp,is,t) = escale*sum((fp0,is0)$(mapis(fp0,fp) and mapis(is0,is)), emi0(em,fp0,is0)) ;
emiComm.l(em,emSrc,aa,t)$(emiCommFlag(em,emSrc,aa,t)) = escale*sum((js0,is0)$(mapis(js0,emSrc) and mapis(is0,aa)), emi0(em,js0,is0)) ;
emiComm.fx(em,emSrc,aa,t)$(not emiCommFlag(em,emSrc,aa,t)) = 0 ;
emiFact.l(em,fp,a,t) = escale*sum((js0,is0)$(mapis(js0,fp) and mapis(is0,a)), emi0(em,js0,is0)) ;
*emiXP.l(em,a,t)  = escale*sum(a0$mapis(a0,a), emiProd0(em, a0)) ;
emiXP.l(em,a,t)  = escale*sum(a0$mapis(a0,a), emiXP0(em,a0)) ;
emiOth.fx(em,t)  = 0 ;

emiLUCF.fx(em,a,t)   = 0;
*emiLUCF.l("CO2",a,t)   = 13/1000;
*emiLUCF.up("CO2",a,t)   = +inf;
*emiLUCF.lo("CO2",a,t)   = -inf;

emiSecA.l(em,aa,t) =  sum(emSrc,emiComm.l(em,emSrc,aa,t))
                     +  sum((fp,a)$sameas(aa,a), emiFact.l(em,fp,a,t))
                     +  sum(a$sameas(aa,a),emiXP.l(em,a,t))
                     +  sum(a$sameas(aa,a),emiLUCF.l(em,a,t))
                 ;


emiTot.l(em,t)   = sum(aa,emiSecA.l(em,aa,t));
emiGHG.l(t)      = sum(ghg, gwp(ghg)*emiTot.l(ghg,t)) + SUM(em,emiOth.l(em,t)) ;
;



   tEmi0.fx(em,aa,t)         = 0;
   tEmiD0.fx(t)              = 0;
   tEmiD1.fx(em,t)           = 0;
   tEmiD2.fx(aa,t)            = 0;
   tEmiM0.fx(t)              = 1;
   tEmiM1.fx(em,t)           = 1;
   tEmiM2.fx(aa,t)           = 1;
   tEmi.l(em,aa,t)          = (tEmi0.l(em,aa,t) + (tEmiD0.l(t) + tEmiD1.l(em,t) + tEmiD2.l(aa,t)))
                     *tEmiM0.l(t) * tEmiM1.l(em,t) * tEmiM2.l(aa,t) ;
   rtEmi.l(em,aa,t)  = tEmi.l(em,aa,t) ;


emical.fx(t)  = 1 ;

* ----------------------------------------------------------------------------
*
*  Calibrate production equations
*
* ----------------------------------------------------------------------------

if(not ifVint,
   sigmap(a,v)  = oldShr(a)*sigmap0(a,"Old") + (1-oldShr(a))*sigmap0(a,"New") ;
   sigmav(a,v)  = oldShr(a)*sigmav0(a,"Old") + (1-oldShr(a))*sigmav0(a,"New") ;
   sigmaul(a,v) = oldShr(a)*sigmaul0(a,"Old") + (1-oldShr(a))*sigmaul0(a,"New") ;
   sigmasl(a,v) = oldShr(a)*sigmasl0(a,"Old") + (1-oldShr(a))*sigmasl0(a,"New") ;
   sigmak(a,v)  = oldShr(a)*sigmak0(a,"Old") + (1-oldShr(a))*sigmak0(a,"New") ;
   sigmaks(a,v) = oldShr(a)*sigmaks0(a,"Old") + (1-oldShr(a))*sigmaks0(a,"New") ;
   sigmae(a,v)  = oldShr(a)*sigmae0(a,"Old") + (1-oldShr(a))*sigmae0(a,"New") ;
else
   sigmap(a,v)  = sum(vint$mapv(v,vint), sigmap0(a,vint)) ;
   sigmav(a,v)  = sum(vint$mapv(v,vint), sigmav0(a,vint)) ;
   sigmaul(a,v) = sum(vint$mapv(v,vint), sigmaul0(a,vint)) ;
   sigmasl(a,v) = sum(vint$mapv(v,vint), sigmasl0(a,vint)) ;
   sigmak(a,v)  = sum(vint$mapv(v,vint), sigmak0(a,vint)) ;
   sigmaks(a,v) = sum(vint$mapv(v,vint), sigmaks0(a,vint)) ;
   sigmae(a,v)  = sum(vint$mapv(v,vint), sigmae0(a,vint)) ;
) ;

sigman(a)  = sigman0(a) ;
omegap(a)  = omegap0(a) ;
sigmas(i)  = sigmas0(i) ;
sigmamg(i) = sigmamg0(i) ;

*  Let's recast the energy bundle

if(0,
   xnrgp.l(a,v0,t) = sum(e, xa.l(e,a,t)) ;
   pnrgp.l(a,v0,t)$(xnrgp.l(a,v0,t) ne 0) = sum(e, (1+tpaf.l(e,a,t))*pa.l(e,t)*xa.l(e,a,t)) / xnrgp.l(a,v0,t) ;
) ;

loop((a,vc,v0)$aact(a),

   and(a,v,t) = (nd.l(a,t)/xpv.l(a,v0,t))*(pnd.l(a,t)/pxv.l(a,v0,t))**sigmap(a,vc) ;
   ava(a,v,t) = (vav.l(a,v0,t)/xpv.l(a,v0,t))*(pva.l(a,v0,t)/pxv.l(a,v0,t))**sigmap(a,vc) ;

   aland(a,lnd,t) = (xf.l(a,lnd,t)/vav.l(a,v0,t))*(pland_pt.l(a,lnd,t)/pva.l(a,v0,t))**sigmav(a,vc) ;
   alab1(a,v,t) = (lab1.l(a,v0,t)/vav.l(a,v0,t))*(plab1.l(a,v0,t)/pva.l(a,v0,t))**sigmav(a,vc) ;
   akse(a,v,t)  = (kse.l(a,v0,t)/vav.l(a,v0,t))*(pkse.l(a,v0,t)/pva.l(a,v0,t))**sigmav(a,vc) ;

   aksk(a,v,t)  = (ksk.l(a,v0,t)/kse.l(a,v0,t))*(pksk.l(a,v0,t)/pkse.l(a,v0,t))**sigmak(a,vc) ;
   ae(a,v,t)    = (xnrgp.l(a,v0,t)/kse.l(a,v0,t))*(pnrgp.l(a,v0,t)/pkse.l(a,v0,t))**sigmak(a,vc) ;

   ak(a,v,t)    = (kd.l(a,v0,t)/ksk.l(a,v0,t))*(pk_pt.l(a,v0,t)/pksk.l(a,v0,t))**sigmaks(a,vc) ;
   alab2(a,v,t) = (lab2.l(a,v0,t)/ksk.l(a,v0,t))*(plab2.l(a,v0,t)/pksk.l(a,v0,t))**sigmaks(a,vc) ;

   ald(a,l,v,t)$ldFlag(a,l)
                = ((xf.l(a,l,t)/lab1.l(a,v0,t))*(pswage.l(a,l,t)/plab1.l(a,v0,t))**sigmaul(a,vc))$ul(l)
                + ((xf.l(a,l,t)/lab2.l(a,v0,t))*(pswage.l(a,l,t)/plab2.l(a,v0,t))**sigmasl(a,vc))$sl(l)
                ;

   aio(in,a,t)$nd.l(a,t)  = (xa.l(in,a,t)/nd.l(a,t))*(((1+tpaf.l(in,a,t))*pa.l(in,t))/pnd.l(a,t))**sigman(a) ;

   aep(e,a,v,t)$(xnrgp.l(a,v0,t) ne 0) = (xa.l(e,a,t)/xnrgp.l(a,v0,t))*(((1+tpaf.l(e,a,t))*pa.l(e,t))/pnrgp.l(a,v0,t))**sigmae(a,vc) ;

) ;

lambdaep.fx(a,e,v,t) = 1 ;
lambdat.fx(a,lnd,t)      = 1 ;

ap(a,i,t)$(x.l(a,i,t) ne 0) = ((x.l(a,i,t)/xp.l(a,t))*(pp.l(a,t)/p.l(a,i,t))**omegap(a))$(omegap(a) ne inf)
                            + (p.l(a,i,t)*x.l(a,i,t)/(pp.l(a,t)*xp.l(a,t)))$(omegap(a) eq inf) ;
as(a,i,t)$(x.l(a,i,t) ne 0) = ((x.l(a,i,t)/xs.l(i,t))*(p.l(a,i,t)/ps.l(i,t))**sigmas(i))$(sigmas(i) ne inf)
                            + (p.l(a,i,t)*x.l(a,i,t)/(ps.l(i,t)*xs.l(i,t)))$(sigmas(i) eq inf) ;


  ElecMix.l(Aelec,iElec,t) = x.l(aelec,iElec,t)/xs.l(iElec,t);

* ----------------------------------------------------------------------------
*
*  Calibrate income distribution equations
*
* ----------------------------------------------------------------------------

chit(h,lnd,t)$ifLand = sam(h, lnd) / sum(a, pland.l(a,lnd,t)*xf.l(a,lnd,t)) ;
chitentr(entr,lnd,t)$ifLand = sam(entr, lnd) / sum(a, pland.l(a,lnd,t)*xf.l(a,lnd,t)) ;
*chiT(entr,t)$ifLand = sum(lnd, sam(entr, lnd)) / sum(a, pland.l(a,lnd,t)*xf.l(a,lnd,t)) ;
chiTGov(gov,lnd,t)$ifLand = sam(gov, lnd) / sum(a, pland.l(a,lnd,t)*xf.l(a,lnd,t)) ;
chil(h,l,t)      = sam(h,l)/sum(a,swage.l(a,l,t)*xf.l(a,l,t)) ;
chikh(h,t)       = sum(cap, sam(h,cap))/kapy.l(t) ;
chikGov(gov,t)       = sum(cap, sam(gov,cap))/kapy.l(t) ;
chikEntr(entr,t) = sum(cap, sam(entr,cap))/kapy.l(t) ;

* ----------------------------------------------------------------------------
*
*  Calibrate final demand equations
*
* ----------------------------------------------------------------------------

*  Household demand

*  Calibrate aggregate non energy and energy bundles

sigmac(h,k) = sigmac0(h,k) ;
sigmac(h,k)$(sigmac(h,k) eq 1) = 1.01 ;

loop(t$t0(t),
   aknnrg(h,k)$(xkf.l(h,k,t) ne 0) =
      (xkfnnrg.l(h,k,t)/xkf.l(h,k,t))*(pkfnnrg.l(h,k,t)/pkf.l(h,k,t))**sigmac(h,k) ;
   aknrg(h,k)$(xkf.l(h,k,t) ne 0) =
      (xkfnrg.l(h,k,t)/xkf.l(h,k,t))*(pkfnrg.l(h,k,t)/pkf.l(h,k,t))**sigmac(h,k) ;
) ;

*  Calibrate non energy and energy bundles

sigmacaa(h,k) = sigmacaa0(h,k) ;
sigmacaa(h,k)$(sigmacaa(h,k) eq 1) = 1.01 ;

af(h,in,k,t)$(xkfnnrg.l(h,k,t) ne 0) =
   ((transMat(in,k,h)/((1+tpaf.l(in,h,t))*pa.l(in,t)))/xkfnnrg.l(h,k,t))*(((1+tpaf.l(in,h,t))*pa.l(in,t))/pkfnnrg.l(h,k,t))**sigmacaa(h,k) ;

sigmacae(h,k) = sigmacae0(h,k) ;
sigmacae(h,k)$(sigmacae(h,k) eq 1) = 1.01 ;

af(h,e,k,t)$(xkfnrg.l(h,k,t) ne 0) =
   ((transMat(e,k,h)/((1+tpaf.l(e,h,t))*pa.l(e,t)))/xkfnrg.l(h,k,t))*(((1+tpaf.l(e,h,t))*pa.l(e,t))/pkfnrg.l(h,k,t))**sigmacae(h,k) ;

*  Other final demand

*  Calibrate aggregate non energy/energy bundles

sigmaf(f) = sigmaf0(f) ;
sigmaf(f)$(sigmaf(f) eq 1) = 1.01 ;

afnnrg(f,t)$(xfnnrg.l(f,t) ne 0) =
   (xfnnrg.l(f,t)/xfd.l(f,t))*(pfnnrg.l(f,t)/pf.l(f,t))**sigmaf(f) ;
afnrg(f,t)$(xfnrg.l(f,t) ne 0) =
   (xfnrg.l(f,t)/xfd.l(f,t))*(pfnrg.l(f,t)/pf.l(f,t))**sigmaf(f) ;

* Calibrate non energy and energy bundles

sigmafaa(f) = sigmafaa0(f) ;
sigmafaa(f)$(sigmafaa(f) eq 1) = 1.01 ;


aff(f,in,t)$(xfnnrg.l(f,t) ne 0) =
   (xa.l(in,f,t)/xfnnrg.l(f,t))*(((1+tpaf.l(in,f,t))*pa.l(in,t))/pfnnrg.l(f,t))**sigmafaa(f) ;

sigmafae(f) = sigmafae0(f) ;
sigmafae(f)$(sigmafae(f) eq 1) = 1.01 ;

aff(f,e,t)$(xfnrg.l(f,t) ne 0) =
   (xa.l(e,f,t)/xfnrg.l(f,t))*(((1+tpaf.l(e,f,t))*pa.l(e,t))/pfnrg.l(f,t))**sigmafae(f) ;

loop(t$t0(t),
   akfAct(h,k)$(xkfshr.l(h,k,t) ne 0) = yes ;
   xaact(i,aa)$(xa.l(i,aa,t) ne 0)   = yes ;
) ;

* ----------------------------------------------------------------------------
*
*  Calibrate CDE demand equations
*
* ----------------------------------------------------------------------------

incElas.l(h,k,t) = incElas0(h,k) ;
ued.l(h,k,k,t)   = prcElas0(h,k) ;
uh.l(h,t)        = 1 ;

*  Make sure income elasticities are consistent

incElas.l(h,k,t) = incElas0(h,k) + xkfshr.l(h,k,t)*(1 - sum(kk, xkfshr.l(h,kk,t)*incElas0(h,kk)))
                 / sum(kk, xkfshr.l(h,kk,t)*xkfshr.l(h,kk,t)) ;

*hpop.fx(h,t)       = pop.l("ptotl",t) ;
Loop(t$(ord(t)=1),
hpop0(h)     = pop.l("ptotl",t)*SUM(l,(sam(h,l)/wage.l(l,t))/sum((lp,hp),sam(hp,lp)/wage.l(lp,t))) ;
);
hpop.l(h,t)       = hpop0(h)/pop0("ptotl")*pop.l("ptotl",t) ;

deprate.l(cohorts,t) = pop.l(cohorts,t)/pop.l("P1564",t) ;

deprate.fx(cohorts,t0) = deprate.l(cohorts,t0) ;

*deprate.fx("P1564",t) = deprate.l("P1564",t) ;
*deprate.fx("PTOTL",t) = deprate.l("PTOTL",t) ;

xkf.fx(h,k,t0)     = xkf.l(h,k,t0) ;
pkf.fx(h,k,t0)     = pkf.l(h,k,t0) ;
yf.fx(h,t0)        = yf.l(h,t0) ;
xkfshr.fx(h,k,t0)  = xkfshr.l(h,k,t0) ;
kron(k,k) = 1 ;

bh.l(h,k,t0) = incElas.l(h,k,t0) ;
eh.l(h,k,t0) = incElas.l(h,k,t0) ;
uh.fx(h,t0)  = uh.l(h,t0) ;

bh.fx(h,k,t)$(not akfact(h,k)) = 0 ;
eh.fx(h,k,t)$(not akfact(h,k)) = 0 ;
akf(h,k,t)$(not akfact(h,k))   = 0 ;

ts(t)$(ord(t) eq 1) = yes ;

alias(h,hp) ;

if(ifMakeTab=0,
options limrow=0, limcol=0 ;
loop(hp,

   hs(hp) = yes ;

   if(1,
      bh.lo(hp,k,t0) = 0.01 ;
      bh.up(hp,k,t0) = 0.99 ;
      bh.fx(hp,k,t0)$(not akfact(hp,k)) = 0 ;

      incElas.fx(hp,k,t0) = incElas.l(hp,k,t0) ;

      uedLoss.l = 0 ;

      solve bhcal minimizing uedloss using nlp ;

   else

      incElas.fx(hp,k,t0) = incElas.l(hp,k,t0) ;
      ued.fx(hp,k,k,t0)   = ued.l(hp,k,k,t0) ;

      solve bhcal2 using mcp ;

   ) ;

   hs(hp) = no ;
) ;
);


loop(t0,
   bh.fx(h,k,t) = bh.l(h,k,t0) ;
) ;

if(ifMakeTab=0,
options limrow=0, limcol=0 ;
loop(hp,

   hs(hp) = yes ;
   options limrow=0, limcol=0 ;
   if(1,

      eh.lo(hp,k,t0) = 0.01 ;
      eh.fx(hp,k,t0)$(not akfact(hp,k)) = 0 ;
      incElas.lo(hp,k,t0) = -inf ;
      incElas.up(hp,k,t0) =  inf ;

      solve ehcal minimizing incElasLoss using nlp ;

   else

      incElas.fx(hp,k,t0) = incElas.l(hp,k,t0) ;

      solve ehcal2 using mcp ;

   ) ;

   hs(hp) = no ;
) ;
);

*options limrow=0, limcol=0 ;

loop(t0,
   eh.fx(h,k,t) = eh.l(h,k,t0) ;
   incElas.l(h,k,t) = incElas.l(h,k,t0) ;
) ;

ued.l(h,k,kp,t) = xkfshr.l(h,kp,t)*(-bh.l(h,kp,t)
                - (eh.l(h,k,t)*bh.l(h,k,t) - sum(kk, xkfshr.l(h,kk,t)*eh.l(h,kk,t)*bh.l(h,kk,t)))
                /  sum(kk, xkfshr.l(h,kk,t)*eh.l(h,kk,t))) + kron(k,kp)*(bh.l(h,k,t) - 1) ;
ced.l(h,k,kp,t) = ued.l(h,k,kp,t) + xkfshr.l(h,kp,t)*incElas.l(h,k,t) ;
ape.l(h,k,kp,t)$akfact(h,kp) = ced.l(h,k,kp,t)/xkfshr.l(h,kp,t) ;

akf(h,k,t)$akFact(h,k) = (xkfshr.l(h,k,t)/bh.l(h,k,t))*(((yf.l(h,t)/hpop.l(h,t))/pkf.l(h,k,t))**(bh.l(h,k,t)))
                       * (uh.l(h,t)**(-eh.l(h,k,t)*bh.l(h,k,t)))/sum(kk$akfact(h,kk), xkfshr.l(h,kk,t)/bh.l(h,kk,t)) ;

ts(t) = no ;

consScale.l(h,t) = sum(k$akfact(h,k), akf(h,k,t)*bh.l(h,k,t)
                 * (uh.l(h,t)**(eh.l(h,k,t)*bh.l(h,k,t)))
                 * (pkf.l(h,k,t)**(bh.l(h,k,t)))
                 * ((yf.l(h,t)/hpop.l(h,t))**(-bh.l(h,k,t)))) ;


$ontext
file elas / elas.csv / ;
if(1,
   put elas ;
   put "Var,Sector,Qual,Value" / ;
   elas.pc=5 ;
   elas.nd=9 ;

   loop((h,k,t)$t0(t),
      put "incElas0", k.tl, "", incElas0(h,k) / ;
      put "incElas",  k.tl, "", incElas.l(h,k,t) / ;
      put "prElas0",  k.tl,  "", prcElas0(h,k) / ;
      put "bh",       k.tl, "", bh.l(h,k,t) / ;
      put "eh",       k.tl, "", eh.l(h,k,t) / ;
      put "akf",      k.tl, "", akf.l(h,k,t) / ;
      loop(kp,
         put "prElas", k.tl,  kp.tl, ued.l(h,k,kp,t) / ;
         put "cpElas", k.tl,  kp.tl, ced.l(h,k,kp,t) / ;
         put "apElas", k.tl,  kp.tl, ape.l(h,k,kp,t) / ;
      ) ;
   ) ;
) ;
$offtext

* ----------------------------------------------------------------------------
*
*  Calibrate trade equations
*
* ----------------------------------------------------------------------------

sigmam(i) = sigmam0(i) ;
sigmam(i)$(sigmam(i) eq 1) = 1.01 ;

ad(i,t)$(idom(i)) = (xd.l(i,t)/xat.l(i,t))*(pda.l(i,t)/pa.l(i,t))**sigmam(i) ;
am(i,t)$(iimp(i)) = (xm.l(i,t)/xat.l(i,t))*(pma.l(i,t)/pa.l(i,t))**sigmam(i) ;

loop(t0,
   chiPDa(i) = pda.l(i,t0) ;
   chiPMa(i) = pma.l(i,t0) ;
   chiPA(i)  = pa.l(i,t0) ;
) ;

gammamd(i,t) = pa.l(i,t) / pda.l(i,t) ;
gammamm(i,t) = pa.l(i,t) / pma.l(i,t) ;

*  Re-normalize prices

pda.l(i,t) = 1 ;
pma.l(i,t) = 1 ;
pa.l(i,t)  = 1 ;
paf.l(i,aa,t) = (1 + tpaf.l(i,aa,t))*pa.l(i,t) ;

sigmax(i) = sigmax0(i) ;

gd(i,t)$(iact(i)) = ((xd.l(i,t)/(xs.l(i,t) - delst.l(i,t)))*(ps.l(i,t)/pd.l(i,t))**sigmax(i))$(sigmax(i) ne inf)
                  + (pd.l(i,t)*xd.l(i,t)/(ps.l(i,t)*(xs.l(i,t) - delst.l(i,t)))) $(sigmax(i) eq inf) ;
ge(i,t)$(iact(i)) = ((xe.l(i,t)/(xs.l(i,t) - delst.l(i,t)))*(ps.l(i,t)/pe.l(i,t))**sigmax(i))$(sigmax(i) ne inf)
                  + (pe.l(i,t)*xe.l(i,t)/(ps.l(i,t)*(xs.l(i,t) - delst.l(i,t)))) $(sigmax(i) eq inf) ;

loop(t0,
   chiPD(i) = pd.l(i,t0) ;
   chiPE(i) = pe.l(i,t0) ;
   chiPS(i) = ps.l(i,t0) ;
) ;

gammaxd(i,t) = pd.l(i,t) / ps.l(i,t) ;
gammaxe(i,t) = pe.l(i,t) / ps.l(i,t) ;

*  Re-normalize prices

pd.l(i,t) = 1 ;
pe.l(i,t) = 1 ;

*  Re-normalize demand side of make matrix

loop(t0,
   chiP(a,i) = p.l(a,i,t0) ;
) ;

gammap(a,i,t) = ps.l(i,t) / p.l(a,i,t) ;

ps.l(i,t)  = 1 ;
p.l(a,i,t) = 1 ;

etae(i) = etae0(i) ;
chie(i,t)$(iexp(i) and etae(i) ne inf) = xe.l(i,t)*(pwe.l(i,t)/pweROW.l(i,t))**etae(i) ;

loop(t0,
   chiPWE(i)  = pwe.l(i,t0) ;
   chiPWEx(i) = pweROW.l(i,t0) ;
   gammaPWE(i,t) = chiPWEx(i)/chiPWE(i) ;
) ;

pwe.l(i,t)     = 1 ;
pweROW.fx(i,t) = 1 ;

omegam(i) = omegam0(i) ;
chim(i,t)$(iimp(i) and omegam(i) ne inf) = xm.l(i,t)*(pwmROW.l(i,t)/pwm.l(i,t))**omegam(i) ;

*  Re-normalize energy share coefficients in production

loop((a,vc,v0)$aact(a),
   aep(e,a,v,t)$(xnrgp.l(a,v0,t) ne 0) = aep(e,a,v,t) * chiPA(e)**(-sigmae(a,vc)) ;
) ;

* ----------------------------------------------------------------------------
*
*  Calibrate margin equations
*
* ----------------------------------------------------------------------------

loop(t0,
   amarg(i,j)$(sam(i,j) ne 0) = (xa.l(i,j,t0)/xmarg.l(j,t0))
                              * (chiPA(i)*pa.l(i,t0)/pmarg.l(j,t0))**sigmamg(j) ;

   xmarg.fx(j,t)$(xmarg.l(j,t0) = 0) = 0 ;
   pmarg.fx(j,t)$(xmarg.l(j,t0) = 0) = 1 ;

   xa.l(i,j,t)$(amarg(i,j) eq 0) = 0 ;
) ;

* ----------------------------------------------------------------------------
*
*  Calibrate factor market equations
*
* ----------------------------------------------------------------------------

*  Labor markets

epsL(l) = epsL0(l) ;

v_chiLs.l(l,t)$(epsL(l) ne inf) = lsT.l(l,t)*(pnum.l(t)/wage.l(l,t))**epsL(l) ;

chiLs(l,t) = 1 ;

omegal(l) = omegal0(l) ;

phiw(a,l,t) = swage.l(a,l,t)/wage.l(l,t) ;
gammal(a,l,t)$(phiw(a,l,t) ne 0 and omegal(l) ne inf) = (phiw(a,l,t)*ls.l(a,l,t)/lsT.l(l,t))
   * (phiw(a,l,t)*wage.l(l,t)/swage.l(a,l,t))**omegal(l) ;
gammal(a,l,t)$(omegal(l) eq inf) = (swage.l(a,l,t)*ls.l(a,l,t)/(wage.l(l,t)*lsT.l(l,t))) ;

*  Land markets

*-need to differentiate between land types
omegatl(lnd) = omegatl0 ;
omegat(lnd)  = omegat0 ;

atland(lnd,t) = 0 ;
atland(lnd,t)$(omegatl(lnd) ne inf and ifLand) = tland.l(lnd,t)*(pnum.l(t)/ptland.l(lnd,t))**omegatl(lnd) ;

alands(a,lnd,t)$(omegat(lnd) ne inf and ifLand) = (xf.l(a,lnd,t)/tland.l(lnd,t))*(ptland.l(lnd,t)/pland_pt.l(a,lnd,t))**omegat(lnd) ;
alands(a,lnd,t)$(omegat(lnd) eq inf and ifLand) = (pland_pt.l(a,lnd,t)*xf.l(a,lnd,t))/(ptland.l(lnd,t)*tland.l(lnd,t)) ;

*  Capital markets in comparative static mode

loop(v0,

   epsK = sum(vint$mapv(v0,vint), epsK0(vint)) ;
   chiKs(t)$(epsK ne inf) = kaps.l(t)*(pnum.l(t)/trent.l(t))**epsK ;

   omegaK = sum(vint$mapv(v0,vint), omegaK0(vint)) ;

   gammak(a,t)$(omegak ne inf) = (kd.l(a,v0,t)/kaps.l(t)) * (trent.l(t)/pk.l(a,v0,t))**omegak ;
   gammak(a,t)$(omegak eq inf) = (pk.l(a,v0,t)*kd.l(a,v0,t)/(trent.l(t)*kaps.l(t))) ;
) ;



invElas(a) = invElas0(a) ;

* ----------------------------------------------------------------------------
*
*  Calibrate emission equations
*
* ----------------------------------------------------------------------------

chiEmi(em,emSrc,aa,t) = 1 ;
chiEmiFac(em,fp,aa,t) = 1 ;
chiEmiXP(em,a,t)  = 1 ;

*  Assume full participation by all agents
phiEmi(em,emSrc,aa) = 1 ;


loop(t$t0(t),
   rhoEmi(em,emSrc,aa)$( emiComm.l(em,emSrc,aa,t) ne 0)  = emiComm.l(em,emSrc,aa,t) / (chiEmi(em,emSrc,aa,t)*xa.l(emSrc,aa,t)) ;
   rhoEmiFac(em,cap,a)$(emiFact.l(em,cap,a,t) ne 0) = emiFact.l(em,cap,a,t) / (chiEmiFac(em,cap,a,t)*xf.l(a,cap,t)) ;
   rhoEmiFac(em,lnd,a)$(emiFact.l(em,lnd,a,t) ne 0) = emiFact.l(em,lnd,a,t) / (chiEmiFac(em,lnd,a,t)*xf.l(a,lnd,t)) ;

   rhoEmiXP(em,a)$(xp.l(a,t) ne 0) = emiXP.l(em,a,t) / (chiEmiXP(em,a,t)*xp.l(a,t)) ;
) ;

   rhoEmiLnd("CO2",lnd,a)$sum(lndp,sam(lndp,a)) = 15.75/1000*sam(lnd,a)/sum(lndp,sam(lndp,a)) ;




$ontext
*override and use GTAP rates, convert to model base year prices
rhoEmi(em,i,aa)= emitab(em,i,aa)*1/exrates0("USD")*10**3;
rhoEmi(em,"cap",a)= emitab(em,"cap",a)*1/exrates0("USD")*10**3;
rhoEmi(em,lnd,a)= emitab(em,"Land",a)*1/exrates0("USD")*10**3;
rhoEmi(em,"mfst",a)=0;
rhoEmiXP(em,a)= emitab(em,"tot",a)*1/exrates0("USD")*10**3;

rhoEmi(em,"c-Oil",aa)= rhoEmi(em,"c-Oil",aa)*93.72/79.04;
rhoEmi(em,"c-Ref",aa)= rhoEmi(em,"c-Ref",aa)*93.72/79.04;
rhoEmi(em,"c-Coa",aa)= rhoEmi(em,"c-Coa",aa)*109.43/98.97;
rhoEmi(em,"c-GAS",aa)= rhoEmi(em,"c-GAS",aa)*13.21/10.85;

*associate emissions also with products of gas, for electricity only since this commodity also includes steam
rhoEmi(em,"c-NGA","a-GasP")= rhoEmi(em,"c-GAS","a-GasP");
rhoEmi(em,"c-NGA","a-chem")= rhoEmi(em,"c-GAS","a-chem");
$offtext


*-temp change is zero in the baseline
*tempD(t)  = 0 ;



*- DAMAGE FUNCTION PARAMETERS
Parameter dmgScale /2/ ;
    dmgTfpAct0(agr,t) = 0 ;
    dmgTfpAct1(agr,t) = - 1.5389/100*dmgScale ;
    dmgTfpAct2(agr,t) = - 0.1242/100*dmgScale;
    dmgTfpAct3(agr,t) = 0;
    dmgTfpAct4(agr,t) = 0;
    dmgTfpAct5(agr,t) = 0;
    dmgTfpAct6(agr,t) = 0;


*-tourism : %of GDP lost in exports -----------------------------------------------------
Loop(t0,
*    dmgTfpAct0(atour,t) = -75.053*1E-6*rgdpmp.l(t0)/xp.l(atour,t0);
    dmgChie0(ctour,t) = 0;
    dmgChie1(ctour,t) = -1798.4*1E-6*rgdpmp.l(t0)/xs.l(ctour,t0)* dmgScale;
    dmgChie2(ctour,t) = +330.17*1E-6*rgdpmp.l(t0)/xs.l(ctour,t0)* dmgScale;
);

*    dmgLambdaL0(agr) =  0.0093 ;
*    dmgLambdaL0(man) =  0.0110 ;
*    dmgLambdaL0(srv) =  0.0086 ;

*-labor productivity --------------------------------------------------------------------
    dmgLambdaL0(agr) =  0 ;
    dmgLambdaL0(man) =  0 ;
    dmgLambdaL0(srv) =  0 ;

    dmgLambdaL1(agr) =  -0.0331 * dmgScale ;
    dmgLambdaL1(man) =  -0.0203 * dmgScale;
    dmgLambdaL1(srv) =  -0.0114 * dmgScale;

    dmgLambdaL2(agr) =  -0.0015 * 2;
    dmgLambdaL2(man) =   0 ;
    dmgLambdaL2(srv) =   0 ;

    dmgLambdaL_HH1(a,l,t) = -0.1386 * dmgScale;


*    dmgLambdaEh0(h,"c-oil",k,t) = - 0.0031 * dmgScale;
*    dmgLambdaEh0(h,"c-coa",k,t) = - 0.0005 * dmgScale;
*    dmgLambdaEh0(h,"c-coa",k,t) = - 0.0005 * dmgScale;
    dmgLambdaEh0(h,ielec,k,t) = + 0.0018 * dmgScale;

*    dmgLambdaEh0(h,"c-oil",k,t) =  0 ;
*    dmgLambdaEh0(h,"c-gas",k,t) =  0 ;
*    dmgLambdaEh0(h,"c-coa",k,t) =  0 ;
    dmgLambdaEh0(h,ielec,k,t) =  0 ;

*    dmgLambdaEh1(h,"c-coa",k,t) = -0.0118 * dmgScale;
*    dmgLambdaEh1(h,"c-oil",k,t) = -0.0040 * dmgScale;
*    dmgLambdaEh1(h,"c-gas",k,t) = +0.0010 * dmgScale;
    dmgLambdaEh1(h,ielec,k,t) = +0.0010 * dmgScale;

    dmgAtLand0(lnd,t) = 0 ;
    dmgAtLand1(lnd,t) = -2.9777 * 1E-6 * 1000000 * dmgScale;

    dmgdepr1(t) = 0.0104 * dmgScale;
    dmgdepr2(t) = 0.0169 * dmgScale;
    dmgdepr3(t) = 0.0217 * dmgScale;
    dmgdepr4(t) = 0.0278 * dmgScale;
    dmgdepr5(t) = 0.0302 * dmgScale;
    dmgdepr6(t) = 0.0349 * dmgScale;
    dmgdepr7(t) = 0.0365 * dmgScale;


dmgTfpAct.l(a,t)        = 1;
dmgLambdaL_HH.l(a,l,t)  = 1;
dmgLambdaL.l(a,l,t)     = 1;
dmgAtLand.l(lnd,t)      = 1;
dmgChie.l(i,t)          = 1;
dmgLambdaEh.l(h,i,k,t)  = 1;
dmgDepr.l(t)            = 1;

dmgTfpAct.fx(a,t)$(NOT ifDmg)        = 1;
dmgLambdaL_HH.fx(a,l,t)$(NOT ifDmg)  = 1;
dmgLambdaL.fx(a,l,t)$(NOT ifDmg)     = 1;
dmgAtLand.fx(lnd,t)$(NOT ifDmg)      = 1;
dmgChie.fx(i,t)$(NOT ifDmg)          = 1;
dmgLambdaEh.fx(h,i,k,t)$(NOT ifDmg)  = 1;
dmgDepr.fx(t)$(NOT ifDmg)            = 1;


*rhodmg(t) = 0.75;
rhodmg(t) = 0.1;
   dmgShftTFP.l(t)        = 1;
   dmgShftLambdaL_HH.l(t) = 1;
   dmgShftLambdaL.l(t)    = 1;
   dmgShftLand.l(t)       = 1;
   dmgShftChie.l(t)       = 1;
   dmgShftLambdaEh.l(t)   = 1;
   dmgShftDepr.l(t)       = 1;

   dmgShftTFP.fx(t)$(NOT ifDmg)        = 1;
   dmgShftLambdaL_HH.fx(t)$(NOT ifDmg) = 1;
   dmgShftLambdaL.fx(t)$(NOT ifDmg)    = 1;
   dmgShftLand.fx(t)$(NOT ifDmg)       = 1;
   dmgShftChie.fx(t)$(NOT ifDmg)       = 1;
   dmgShftLambdaEh.fx(t)$(NOT ifDmg)   = 1;
   dmgShftDepr.fx(t)$(NOT ifDmg)       = 1;

parameter
shra(a)  share of ag sub sector in aggregate sector output in sam
;
shra(a) = 0;
shra('a-agr') = 0.917187897;
shra('a-frs') = 1- shra('a-agr');

loop(t0,
EV.l(H,T) = PROD[k,(pkf.l(h,k,t0)/pkf.l(h,k,t))**xkfshr.l(h,k,t)] * [yf.l(h,t)-yf.l(h,t0)] ;
*EV.l(H,T) = 1;
*EV.l(H,T) = PROD[k,(pkf.l(h,k,t)/pkf.l(h,k,t))**xkfshr.l(h,k,t)] * [yf.l(h,t)-yf.l(h,t)] ;
);

