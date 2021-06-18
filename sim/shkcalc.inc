
Parameter
    rgdpmpSIM(t,sim)
    xaSIM(i,aa,t,sim)
    chiPASIM(i,t,sim)
    lambdalSIM(a,l,t,sim)
    chilambdalSIM(l,t,sim)
    chilambdalASIM(a,l,t,sim)
    lambdatSIM(a,lnd,t,sim)
    rshrGDPSIM(f,t,sim)
    gammapSIM(a,i,t,sim)
    rsgSIM(t,sim)
    chilsSIM(l,t,sim)
    popGrSIM(cohorts,t,sim)
    popGr(cohorts,t,sim)
    popSIM(cohorts,t,sim)
    hpopSIM(h,t,sim)
    chimsSIM(t,sim)
    culIndexSIM(l,t,sim)

    savfSIM(t,sim)
    savgSIM(t,sim)
    pwmSIM(i,t,sim)
    pweSIM(i,t,sim)
    lambdakSIM(a,v,t,sim)
    lambdavSIM(a,v,t,sim)
    tfpActSIM(a,t,sim)
    amargsim(i,j,t,sim)
    brateSIM(t,sim)
    drateSIM(age,t,sim)

    epsheaSIM(l,t,sim)
    epseduSIM(l,t,sim)
    epsCulSIM(l,t,sim)
    sigmaksSIM(a,v,t,sim)
    sigmakSIM(a,v,t,sim)
    sigmaVSIM(a,v,t,sim)
    sigmaxSIM(i,t,sim)

    xfdsim(oa,t,sim)

    emiTotSIM(em,t,sim)
    emiSecASIM(em,aa,tt,sim)
    emitaxSIM(em,t,sim)
    chiEmiSIM(em,i,aa,t,sim)
    lambdaepSIM(a,e,v,tt,sim)
    lambdaehSIM(h,e,k,tt,sim)
    lambdaefSIM(f,e,tt,sim)
    tempDSIM(t,sim)
    adpInvShrSIM(adpinv,t,sim)
    yfSIM(adpinv,t,sim)
    xfSIM(adpinv,t,sim)
    ygSIM(g,t,sim)
    ygovSIM(t,sim)

   tFacSIM(a,fp,t,sim)           Factor tax
   rtFacSIM(a,fp,t,sim)          Real Factor tax
   tFac0SIM(a,fp,t,sim)          Factor tax base level
   tFacD0SIM(t,sim)              Factor tax additive adjuster for all dimensions
   tFacD1SIM(a,t,sim)            Factor tax additive adjuster for activity a
   tFacD2SIM(fp,t,sim)           Factor tax additive adjuster for factor fp
   tFacM0SIM(t,sim)              Factor tax multiplicative adjuster for all dimensions
   tFacM1SIM(a,t,sim)            Factor tax multiplicative adjuster for activity a
   tFacM2SIM(fp,t,sim)           Factor tax multiplicative adjuster for factor fp


   tpsbSIM(a,t,sim)              Production Subsidy
   tpsb0SIM(a,t,sim)             Production Subsidy base level
   tpsbD0SIM(t,sim)              Production Subsidy additive adjuster for all dimensions
   tpsbD1SIM(a,t,sim)            Production Subsidy additive adjuster for activity a
   tpsbM0SIM(t,sim)              Production Subsidy multiplicative adjuster for all dimensions
   tpsbM1SIM(a,t,sim)            Production Subsidy multiplicative adjuster for activity a

   tPrdSIM(a,t,sim)              Production Tax
   tPrd0SIM(a,t,sim)             Production Tax base level
   tPrdD0SIM(t,sim)              Production Tax additive adjuster for all dimensions
   tPrdD1SIM(a,t,sim)            Production Tax additive adjuster for activity a
   tPrdM0SIM(t,sim)              Production Tax multiplicative adjuster for all dimensions
   tPrdM1SIM(a,t,sim)            Production Tax multiplicative adjuster for activity a

   tExpSIM(i,t,sim)              Export tax
   tExp0SIM(i,t,sim)             Export tax base level
   tExpD0SIM(t,sim)              Export tax additive adjuster for all dimensions
   tExpD1SIM(i,t,sim)            Export tax additive adjuster for activity a
   TExpM0SIM(t,sim)              Export tax multiplicative adjuster for all dimensions
   tExpM1SIM(i,t,sim)            Export tax multiplicative adjuster for commodity i

   tVatSIM(i,n,t,sim)            Value added tax
   tVat0SIM(i,n,t,sim)           Value added tax base level
   tVatD0SIM(t,sim)              Value added tax additive adjuster for all dimensionsnsion
   tVatD1SIM(i,t,sim)            Value added tax additive adjuster for commodity i
   tVatD2SIM(n,t,sim)            Value added tax additive adjuster for source n
   tVatM0SIM(t,sim)              Value added tax multiplicative adjuster for all dim
   tVatM1SIM(i,t,sim)            Value added tax multiplicative adjuster for commodity i
   tVatM2SIM(n,t,sim)            Value added tax multiplicative adjuster for source n

   tImpSIM(i,t,sim)              Import tax
   tImp0SIM(i,t,sim)             Import tax base level
   tImpD0SIM(t,sim)              Import tax additive adjuster for all dimensions
   tImpD1SIM(i,t,sim)            Import tax additive adjuster for commodity i
   tImpM0SIM(t,sim)              Import tax multiplicative adjuster for all dimensions
   tImpM1SIM(i,t,sim)            Import tax multiplicative adjuster for commodity i

   tEmiSIM(em,aa,t,sim)          Agent specific emission tax
   rtEmiSIM(em,aa,t,sim)         Agent specific emission tax
   tEmi0SIM(em,aa,t,sim)         Agent specific emission tax base level
   tEmiD0SIM(t,sim)              Agent specific emission tax additive adjuster for all dimensionsnsion
   tEmiD1SIM(em,t,sim)           Agent specific emission tax additive adjuster for emission em
   tEmiD2SIM(aa,t,sim)            Agent specific emission tax additive adjuster for agent aa
   tEmiM0SIM(t,sim)              Agent specific emission tax multiplicative adjuster for all dim
   tEmiM1SIM(em,t,sim)           Agent specific emission tax multiplicative adjuster for emission em
   tEmiM2SIM(aa,t,sim)           Agent specific emission tax multiplicative adjuster for agent aa

   tPITSIM(h,t,sim)              Personal income tax
   tPIT0SIM(h,t,sim)             Personal income tax base level
   tPITD0SIM(t,sim)              Personal income tax additive adjuster for all dimensions
   tPITD1SIM(h,t,sim)            Personal income tax additive adjuster for household h
   tPITM0SIM(t,sim)              Personal income tax multiplicative adjuster for all dimensions
   tPITM1SIM(h,t,sim)            Personal income tax multiplicative adjuster for household h

   tCITSIM(entr,t,sim)           Corporate income tax
   tCIT0SIM(entr,t,sim)          Corporate income tax base level
   tCITD0SIM(t,sim)              Corporate income tax additive adjuster for all dimensions
   tCITD1SIM(entr,t,sim)         Corporate income tax additive adjuster for enterprise entr
   tCITM0SIM(t,sim)              Corporate income tax multiplicative adjuster for all dimensions
   tCITM1SIM(entr,t,sim)         Corporate income tax multiplicative adjuster for enterprise entr

   tDrSIM(t,sim)                Personal and Corporate income tax multiplicative adjuster

   tPafSIM(i,aa,t,sim)           Agent specific commodity tax
   PafSIM(i,aa,t,sim)            Agent specific commodity price
   tPaf0SIM(i,aa,t,sim)          Agent specific commodity tax base level
   tPafD0SIM(t,sim)              Agent specific commodity tax additive adjuster for all dimensions
   tPafD1SIM(i,t,sim)            Agent specific commodity tax additive adjuster for commodity i
   tPafD2SIM(aa,t,sim)           Agent specific commodity tax additive adjuster for agent aa
   tPafM0SIM(t,sim)              Agent specific commodity tax multiplicative adjuster for all dimensions
   tPafM1SIM(i,t,sim)            Agent specific commodity tax multiplicative adjuster for commodity i
   tPafM2SIM(aa,t,sim)           Agent specific commodity tax multiplicative adjuster for agent aa

   emiGHGSIM(t,sim)            Greenhouse gas emissions
;
    emiGHGSIM(t,sim)               = emiGHG.l(t)           ;
    rgdpmpSIM(t,sim)               = rgdpmp.l(t)           ;
    savfSIM(t,sim)                 = savf.l(t)             ;
    savgSIM(t,sim)                 = savg.l(t)             ;
    pwmSIM(i,t,sim)                = pwm.l(i,t)            ;
    pweSIM(i,t,sim)                = pwe.l(i,t)            ;
    lambdakSIM(a,v,t,sim)          = lambdak.l(a,v,t)      ;
    lambdavSIM(a,v,t,sim)          = lambdav.l(a,v,t)      ;
    amargsim(i,j,t,sim)            = amarg(i,j)            ;

    epsheaSIM(l,t,sim)             = epshea(l,t)           ;
    epseduSIM(l,t,sim)             = epsedu(l,t)           ;
    epsCulSIM(l,t,sim)             = epsCul(l,t)           ;
    sigmaksSIM(a,v,t,sim)          = sigmaks(a,v)          ;
    sigmakSIM(a,v,t,sim)           = sigmak(a,v)           ;
    sigmaVSIM(a,v,t,sim)           = sigmaV(a,v)           ;
    sigmaxSIM(i,t,sim)             = sigmax(i)             ;
    popSIM(cohorts,t,sim)          = pop.l(cohorts,t)      ;
    hpopSIM(h,t,sim)               = hpop.l(h,t)           ;
    chimsSIM(t,sim)                = chims.l(t)            ;
    chilsSIM(l,t,sim)              = 1                     ;
    lambdalSIM(a,l,t,sim)          = lambdal.l(a,l,t)      ;
    chilambdalSIM(l,t,sim)          = chilambdal(l,t)      ;
    chilambdalASIM(a,l,t,sim)       = chilambdalA(a,l,t)      ;
    lambdatSIM(a,lnd,t,sim)        = lambdat.l(a,lnd,t)        ;
    rshrGDPSIM(f,t,sim)            = rshrGDP.l(f,t)        ;
    rsgSIM(t,sim)                  = rsg.l(t)                 ;
    culIndexSIM(l,t,sim)           = culIndex(l,t)            ;
    brateSIM(t,sim)                = brateU.l(t)              ;
    drateSIM(age,t,sim)            = drate.l(age,t)              ;
    xfdsim(oa,t,sim)               = xfd.l(oa,t)             ;
    tfpActSIM(a,t,sim)             = tfpAct.l(a,t)            ;
    emiTotSIM(em,t,sim)            = emiTot.l(em,t)           ;
    emiSecASIM(em,aa,tt,sim)       = emiSecA.l(em,aa,tt)      ;
    lambdaepSIM(a,e,v,t,sim)       = lambdaep.l(a,e,v,t)      ;
    lambdaehSIM(h,e,k,t,sim)       = lambdaeh.l(h,e,k,t)      ;
    lambdaefSIM(f,e,t,sim)         = lambdaef.l(f,e,t)        ;
    tempDSIM(t,sim)                = tempD(t)              ;
    adpInvShrSIM(adpinv,t,sim)     = adpInvShr.l(adpinv,t)    ;
    xfdSIM(adpinv,t,sim)        = xfd.l(adpinv,t)               ;
    yfSIM(adpinv,t,sim)         = yf.l(adpinv,t)               ;
    ygSIM(g,t,sim)              = yg.l(g,t)          ;
    ygovSIM(t,sim)              = ygov.l(t) ;
*-emission target
    emical.fx(tt) = emical.l(tt) ;

   tFacSIM(a,fp,t,sim)           = tFac.l(a,fp,t)           ;
   rtFacSIM(a,fp,t,sim)          = rtFac.l(a,fp,t)          ;
   tFac0SIM(a,fp,t,sim)          = tFac0.l(a,fp,t)          ;
   tFacD0SIM(t,sim)              = tFacD0.l(t)              ;
   tFacD1SIM(a,t,sim)            = tFacD1.l(a,t)            ;
   tFacD2SIM(fp,t,sim)           = tFacD2.l(fp,t)           ;
   tFacM0SIM(t,sim)              = tFacM0.l(t)              ;
   tFacM1SIM(a,t,sim)            = tFacM1.l(a,t)            ;
   tFacM2SIM(fp,t,sim)           = tFacM2.l(fp,t)           ;


   tpsbSIM(a,t,sim)              = tpsb.l(a,t)              ;
   tpsb0SIM(a,t,sim)             = tpsb0.l(a,t)             ;
   tpsbD0SIM(t,sim)              = tpsbD0.l(t)              ;
   tpsbD1SIM(a,t,sim)            = tpsbD1.l(a,t)            ;
   tpsbM0SIM(t,sim)              = tpsbM0.l(t)              ;
   tpsbM1SIM(a,t,sim)            = tpsbM1.l(a,t)            ;

   tPrdSIM(a,t,sim)              = tPrd.l(a,t)              ;
   tPrd0SIM(a,t,sim)             = tPrd0.l(a,t)             ;
   tPrdD0SIM(t,sim)              = tPrdD0.l(t)              ;
   tPrdD1SIM(a,t,sim)            = tPrdD1.l(a,t)            ;
   tPrdM0SIM(t,sim)              = tPrdM0.l(t)              ;
   tPrdM1SIM(a,t,sim)            = tPrdM1.l(a,t)            ;

   tExpSIM(i,t,sim)              = tExp.l(i,t)              ;
   tExp0SIM(i,t,sim)             = tExp0.l(i,t)             ;
   tExpD0SIM(t,sim)              = tExpD0.l(t)              ;
   tExpD1SIM(i,t,sim)            = tExpD1.l(i,t)            ;
   TExpM0SIM(t,sim)              = TExpM0.l(t)              ;
   tExpM1SIM(i,t,sim)            = tExpM1.l(i,t)            ;

   tVatSIM(i,n,t,sim)            = tVat.l(i,n,t)            ;
   tVat0SIM(i,n,t,sim)           = tVat0.l(i,n,t)           ;
   tVatD0SIM(t,sim)              = tVatD0.l(t)              ;
   tVatD1SIM(i,t,sim)            = tVatD1.l(i,t)            ;
   tVatD2SIM(n,t,sim)            = tVatD2.l(n,t)            ;
   tVatM0SIM(t,sim)              = tVatM0.l(t)              ;
   tVatM1SIM(i,t,sim)            = tVatM1.l(i,t)            ;
   tVatM2SIM(n,t,sim)            = tVatM2.l(n,t)            ;

   tImpSIM(i,t,sim)              = tImp.l(i,t)              ;
   tImp0SIM(i,t,sim)             = tImp0.l(i,t)             ;
   tImpD0SIM(t,sim)              = tImpD0.l(t)              ;
   tImpD1SIM(i,t,sim)            = tImpD1.l(i,t)            ;
   tImpM0SIM(t,sim)              = tImpM0.l(t)              ;
   tImpM1SIM(i,t,sim)            = tImpM1.l(i,t)            ;

   tEmiSIM(em,aa,t,sim)          = tEmi.l(em,aa,t)          ;
   rtEmiSIM(em,aa,t,sim)         = rtEmi.l(em,aa,t)         ;
   tEmi0SIM(em,aa,t,sim)         = tEmi0.l(em,aa,t)         ;
   tEmiD0SIM(t,sim)              = tEmiD0.l(t)              ;
   tEmiD1SIM(em,t,sim)           = tEmiD1.l(em,t)           ;
   tEmiD2SIM(aa,t,sim)           = tEmiD2.l(aa,t)           ;
   tEmiM0SIM(t,sim)              = tEmiM0.l(t)              ;
   tEmiM1SIM(em,t,sim)           = tEmiM1.l(em,t)           ;
   tEmiM2SIM(aa,t,sim)           = tEmiM2.l(aa,t)           ;

   tPITSIM(h,t,sim)              = tPIT.l(h,t)              ;
   tPIT0SIM(h,t,sim)             = tPIT0.l(h,t)             ;
   tPITD0SIM(t,sim)              = tPITD0.l(t)              ;
   tPITD1SIM(h,t,sim)            = tPITD1.l(h,t)            ;
   tPITM0SIM(t,sim)              = tPITM0.l(t)              ;
   tPITM1SIM(h,t,sim)            = tPITM1.l(h,t)            ;

   tCITSIM(entr,t,sim)           = tCIT.l(entr,t)           ;
   tCIT0SIM(entr,t,sim)          = tCIT0.l(entr,t)          ;
   tCITD0SIM(t,sim)              = tCITD0.l(t)              ;
   tCITD1SIM(entr,t,sim)         = tCITD1.l(entr,t)         ;
   tCITM0SIM(t,sim)              = tCITM0.l(t)              ;
   tCITM1SIM(entr,t,sim)         = tCITM1.l(entr,t)         ;

   tDrSIM(t ,sim)                = tDr.l(t )                ;

   tPafSIM(i,aa,t,sim)           = tPaf.l(i,aa,t)           ;
   PafSIM(i,aa,t,sim)            = Paf.l(i,aa,t)           ;
   tPaf0SIM(i,aa,t,sim)          = tPaf0.l(i,aa,t)          ;
   tPafD0SIM(t,sim)              = tPafD0.l(t)              ;
   tPafD1SIM(i,t,sim)            = tPafD1.l(i,t)            ;
   tPafD2SIM(aa,t,sim)           = tPafD2.l(aa,t)           ;
   tPafM0SIM(t,sim)              = tPafM0.l(t)              ;
   tPafM1SIM(i,t,sim)            = tPafM1.l(i,t)            ;
   tPafM2SIM(aa,t,sim)           = tPafM2.l(aa,t)           ;

   chiPASIM(i,t,sim)           = chiPA(i) ;
   xaSIM(i,aa,t,sim)           = xa.l(i,aa,t);

*    emisect(a) = YES ;

*-------------------------------------------------------------------------------
*--Carbon tax -----------------------------------------------------------------------------
set aaemi(aa) sectors covered by emission pricing ???
/
$ontext
set.agr
set.man
set.srv
set.h
$offtext
*$ontext
a-ely
a-otp
a-wtp
a-atp
set.h
*$offtext
/
;
* shock on real emission rate: er in usd * amount of emi tax * scaling (in basebridge and check if total emissions
* correspond to actual data in Mega ton)* period to apply the tax
* scaling * exchange rate*amount in $

* apply a 1 FCFA tax to check if tax works well by looking at YG. if applied on all, then yg=emitot,
* if on selected users, should correspond to share of these sectors in total emission (75%)
*  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2021)  =   1 ;

* apply shock -----------------------------------------------------------------------------------
* shock on real emission rate: er in usd * amount of emi tax * scaling (in basebridge and check if total emissions
* correspond to actual data in Mega ton)* period to apply the tax
$ontext
  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2021)  =  0.555 * 10 * (years(t)-2021)/9 ;
  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2030)  =  0.555 * (10 + 11 * (years(t)-2030)/10) ;
  tEmiM1SIM(ema,t,"carbtax") = 0 ;
  emiGHGSIM(t,"carbtax") = emiGHGSIM(t,"BaU") * 0.90 ;
$offtext

*$ontext
  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2021)  =   555*10 * (years(t)-2021)/9 ;
*  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2030)  =   500*20 * (years(t)-2030)/10 ;
*  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2030)  =  tEmiSIM(em,aaemi,t-1,"carbtax")+500*10 * (years(t)-2030)/10 ;
  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2030)  =  555*10 +555*10 * (years(t)-2030)/10 ;
*  tEmiSIM(em,aaemi,t,"carbtax")$(tshock(t) and years(t)>2030)  =  0.555 * (10 + 11 * (years(t)-2030)/10) ;
  tEmiM1SIM(ema,t,"carbtax") = 0 ;
*$offtext
