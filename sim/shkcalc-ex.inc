
Parameter
    lambdalSIM(a,l,t,sim)
    chilambdalSIM(l,t,sim)
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
    emiGhgSIM(pollType,t,sim)
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
   tpitD0ContSIM(h,t,sim)        control for relasing income tax
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
   tPaf0SIM(i,aa,t,sim)          Agent specific commodity tax base level
   tPafD0SIM(t,sim)              Agent specific commodity tax additive adjuster for all dimensions
   tPafD1SIM(i,t,sim)            Agent specific commodity tax additive adjuster for commodity i
   tPafD2SIM(aa,t,sim)           Agent specific commodity tax additive adjuster for agent aa
   tPafM0SIM(t,sim)              Agent specific commodity tax multiplicative adjuster for all dimensions
   tPafM1SIM(i,t,sim)            Agent specific commodity tax multiplicative adjuster for commodity i
   tPafM2SIM(aa,t,sim)           Agent specific commodity tax multiplicative adjuster for agent aa

   uhSIM(h,t,sim)                Household welfare
   xpSIM(a,t,sim)                Output
   elecmixSIM(a,t,sim)
   kdsim(a,v,t,sim)
   tfpSIM(t,sim)                 TFP
   kstocksim(t,sim)
;



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
    emical.fx(t) = emical.l(t) ;
    emiGhgSIM(pollType,t,sim) = emiGhg.l(pollType,t) ;
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
   tpitD0ContSIM(h,t,sim)        = tpitD0Cont(h,t)          ;
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
   tPaf0SIM(i,aa,t,sim)          = tPaf0.l(i,aa,t)          ;
   tPafD0SIM(t,sim)              = tPafD0.l(t)              ;
   tPafD1SIM(i,t,sim)            = tPafD1.l(i,t)            ;
   tPafD2SIM(aa,t,sim)           = tPafD2.l(aa,t)           ;
   tPafM0SIM(t,sim)              = tPafM0.l(t)              ;
   tPafM1SIM(i,t,sim)            = tPafM1.l(i,t)            ;
   tPafM2SIM(aa,t,sim)           = tPafM2.l(aa,t)           ;

   uhSIM(h,t,sim)                = uh.l(h,t)                ;
   xpSIM(a,t,sim)                = xp.l(a,t)                ;
   elecmixSIM(a,t,sim)                = elecmix.l(a,t)      ;
   kdsim(a,v,t,sim) =    kd.l(a,v,t) ;
   kstocksim(t,sim) =    kstock.l(t) ;
   tfpSIM(t,sim) =  tfp.l(t) ;


*    emisect(a) = YES ;
$ontext
Current spending on health by gov and HH is 331.9 billion > (47.8 gov't, 284.1 by HHs)             |
                                                                                                   |
2019 Gov't budget is 45.8 billion > from the report                                                |
for full coverage 74.7b is needed w/o optimization, 63.2 b is needed w/ optimization               |
With 63.6b there would be 46000 DALY averted                                                       |
Working age population is 2010508 ; employment is 1509236 > then 46000/1509236  = 3.05% increase   |
in labor productivity.                                                                             |
Government estimate of UHC cost is 6% of GDP which is 363.5b > also close to SAM total health      |
spending. If 75b brings 3% productivity gain, 300b should bring 12% productivity gain. however this is an upper bound
that can be reached in the long term. So we assume 12% will be attained by 2050                    |
                                                                                                   |
                                                                                                   |
                                                                                                   |
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6238021/ : Deaths amenable by UHC is 2995 per year    |
for Armenia 53% of which is due to low quality services . Population data shows that deaths in     |
2018 would be 33,195 which is a 9.02% decline in the death rate.

*- Report suggests a 7-8% efficiency improvement is possible in terms of health outcomes



Average

$offtext

*-checks on popAge0
*  tfpActSIM("a-hht",t,"HeaEf")$(years(t)>2019)  = tfpActSIM("a-hht",t,"BaU") *(1+ 0.08 /11* (years(t)-2019) ) ;

set aaemi(aa) sectors covered by emission pricing
/
set.man
*a-wtr
*a-otp
*a-wtp
a-atp
*set.aelec
set.h
/
;

*  emighgSIM("GHGs",t,"MainTxRed")  = emighg.l("GHGs",t)* (1-0.06*(years(t)-2020)/10);

*-main scenarios
*  Carbon price coverage   Industry, Wastewater, Transport, Stationary energy
*  Carbon price rate       10 euro in 2024 increasing to 20 from 2030
*  Revenue recycling       Cash transfer to bottom 2 household quintiles to make CP impact neutral (amount determined from HH impact assessment)
*  Exemptions/ subsidies   Remove fossil fuel subsidies Stop electricity consumption tax and SCT on natural gas

  rtEmiSIM(em,aaemi,t,"MainCarTx")$(years(t)>2023)  = 5.5 * 10 * 1e-3 * ( 1 + (years(t)-2023)/7);
  rtEmiSIM(em,aaemi,t,"MainCarTx")$(years(t)>2030)  = 5.5 * 20 * 1e-3   ;

  tEmiM1SIM(ema,t,"MainCarTx") = 0 ;

  tpitD0ContSIM(h,t,"MainCarTx")$(ord(h)<3 and years(t)>2023) = 1 ;

  rtEmiSIM(em,aaemi,t,"MainColSb")  = rtEmiSIM(em,aaemi,t,"MainCarTx");
  tEmiM1SIM(ema,t,"MainColSb")    = tEmiM1SIM(ema,t,"MainCarTx")   ;
  tpitD0ContSIM(h,t,"MainColSb")  = tpitD0ContSIM(h,t,"MainCarTx") ;
  tPrdM1SIM("a-coa",t,"MainColSb")$(years(t)>2023)  = tPrdM1.l("a-coa",t) *0.175 ;

  rtEmiSIM(em,aaemi,t,"MainFosSb")  = rtEmiSIM(em,aaemi,t,"MainColSb");  ;
  tEmiM1SIM(ema,t,"MainFosSb")     = tEmiM1SIM(ema,t,"MainColSb")    ;
  tpitD0ContSIM(h,t,"MainFosSb")   = tpitD0ContSIM(h,t,"MainColSb")  ;
  tPrdM1SIM("a-coa",t,"MainFosSb") = tPrdM1SIM("a-coa",t,"MainColSb");

*- ngas subsidies is 109 million according to OECD. Tax in SAM is 596K in SAM. Removing subsidy means 180 times increase
  tPrdM1SIM("a-gas",t,"MainFosSb")$(years(t)>2023)  = tPrdM1.l("a-gas",t)*10 ;

*-oil subsidies are 0.95 billion TL acc to OECD. Tax in SAM is 0.013 billion. Removing subsidy means a 72 times increase
  tPrdM1SIM("a-oil",t,"MainFosSb")$(years(t)>2023)  = tPrdM1.l("a-oil",t)*5 ;

  rtEmiSIM(em,aaemi,t,"MainTxRed")  = rtEmiSIM(em,aaemi,t,"MainFosSb");
  tEmiM1SIM(ema,t,"MainTxRed")     = tEmiM1SIM(ema,t,"MainFosSb")    ;
  tpitD0ContSIM(h,t,"MainTxRed")   = tpitD0ContSIM(h,t,"MainFosSb")  ;
  tPrdM1SIM(a,t,"MainTxRed") = tPrdM1SIM(a,t,"MainFosSb");
*-data from Clare
  tpafM1SIM(ielec,t,"MainTxRed")$(years(t)>2023)  = tpafM1.l(ielec,t)*0.61 ;
  tpafM1SIM("c-gdt",t,"MainTxRed")$(years(t)>2023)  = tpafM1.l("c-gdt",t)*0.8993 ;

*2 Cmnc Implementation commences 2030
*  Carbon price coverage        As per main scenario
*  Carbon price rate            starts 2030 at 10 euro then 20 euro from 2035
*  Revenue recycling            As per main scenario, in line with commencement
*  Exemptions/ subsidies        As per main scenario

  rtEmiSIM(em,aaemi,t,"CarTx2030")$(years(t)>2029)  = 5.5 * 10 * 1e-3 * (1 + (years(t)-2030)/5);
*  rtEmiSIM(em,aaemi,t,"CarTx2030")$(years(t)>2029)  = 5.5 * 20 * 1e-3 ;
  rtEmiSIM(em,aaemi,t,"CarTx2030")$(years(t)>2035)  = 5.5 * 20 * 1e-3 ;

  tEmiM1SIM(ema,t,"CarTx2030")$(years(t)>2029)     = tEmiM1SIM(ema,t,"MainTxRed")     ;
  tpitD0ContSIM(h,t,"CarTx2030")$(years(t)>2029)   = tpitD0ContSIM(h,t,"MainTxRed")   ;
  tPrdM1SIM(a,t,"CarTx2030")$(years(t)>2029) = tPrdM1SIM(a,t,"MainTxRed") ;
  tpafM1SIM(i,t,"CarTx2030")$(years(t)>2029) = tpafM1SIM(i,t,"MainTxRed") ;



set scn3(sim)
/
GovntSave
DebtPaymt
GovntInvt
/
;
*3 NRcy No revenue recycling
*  Carbon price coverage        As per main scenario
*  Carbon price rate            As per main scenario
*  Revenue recycling            (a) Govt savings or (b) debt repayment or (c) investment
*  Exemptions/ subsidies        As per main scenario

  rtEmiSIM(em,aaemi,t,scn3)  = rtEmiSIM(em,aaemi,t,"MainTxRed");
  tEmiM1SIM(ema,t,scn3) = tEmiM1SIM(ema,t,"MainTxRed") ;
  tpitD0ContSIM(h,t,scn3) =  tpitD0ContSIM(h,t,"MainTxRed") ;
  tPrdM1SIM(a,tt,scn3) = tPrdM1SIM(a,tt,"MainTxRed") ;
  tpafM1SIM(i,tt,scn3) = tpafM1SIM(i,tt,"MainTxRed") ;


*4 IRcy Revenue recycled as income tax reduction
*  Carbon price coverage        As per main scenario
*  Carbon price rate            As per main scenario
*  Revenue recycling            HH transfers from main scenario plus remaining revenue generated to income tax reduction.
*  Exemptions/ subsidies        As per main scenario
  rtEmiSIM(em,aaemi,t,"FacTxRcyl")  = rtEmiSIM(em,aaemi,t,"MainTxRed");

  tEmiM1SIM(ema,t,"FacTxRcyl") = tEmiM1SIM(ema,t,"MainTxRed") ;

  tpitD0ContSIM(h,t,"FacTxRcyl") =  0;
  tPrdM1SIM(a,tt,"FacTxRcyl") = tprdM1SIM(a,tt,"MainTxRed") ;
  tpafM1SIM(i,tt,"FacTxRcyl") = tpafM1SIM(i,tt,"MainTxRed") ;


*6 High Higher carbon price
*  Carbon price coverage        As per main scenario
*  Carbon price rate            Forecast EU ETS price from 2024
*  Revenue recycling            As per main scenario
*  Exemptions/ subsidies        As per main scenario

    rtEmiSIM(em,aaemi,t,"HighCarTx")$(years(t)>2023)  = 5.5 * 1e-3 * (10 + (years(t)-2023)*100/17);
*    rtEmiSIM(em,aaemi,t,"HighCarTx")$(years(t)>2030)  =   rtEmiSIM(em,aaemi,"2030","HighCarTx") +  5.5 * 1e-3 * (years(t)-2030)*18/10 ;

  tEmiM1SIM(ema,t,"HighCarTx") = tEmiM1SIM(ema,t,"MainTxRed") ;

  tpitD0ContSIM(h,t,"HighCarTx") =  tpitD0ContSIM(h,t,"MainTxRed") ;
  tPrdM1SIM(a,tt,"HighCarTx") = tprdM1SIM(a,tt,"MainTxRed") ;
  tpafM1SIM(i,tt,"HighCarTx") = tpafM1SIM(i,tt,"MainTxRed") ;


*7 NNrg Stationary energy excluded from coverage
*  Carbon price coverage        Industry, Wastewater, Transport
*  Carbon price rate            As per main scenario
*  Revenue recycling            As per main scenario
*  Exemptions/ subsidies        As per main scenario

  rtEmiSIM(em,aaemi,t,"NrgExclud")  = rtEmiSIM(em,aaemi,t,"MainTxRed");

  rtEmiSIM(em,aelec,t,"NrgExclud") = 0;

  tEmiM1SIM(ema,t,"NrgExclud") = tEmiM1SIM(ema,t,"MainTxRed") ;

  tpitD0ContSIM(h,t,"NrgExclud") =  tpitD0ContSIM(h,t,"MainTxRed") ;
  tPrdM1SIM(a,tt,"NrgExclud") = tprdM1SIM(a,tt,"MainTxRed") ;
  tpafM1SIM(i,tt,"NrgExclud") = tpafM1SIM(i,tt,"MainTxRed") ;


*8 NSub No subsidy reform
*  Carbon price coverage        As per main scenario
*  Carbon price rate            As per main scenario
*  Revenue recycling            As per main scenario
*  Exemptions/ subsidies        No subsidy reform

*  tEmiD2SIM(aaemi,t,"scn8")$(years(t)>2023)  = tEmiD2SIM(aaemi,t,"MainTxRed") ;*

*  tEmiM1SIM(ema,t,"scn8") = tEmiM1SIM(ema,t,"MainTxRed") ;
*  tpitD0ContSIM(h,t,"scn8") =  tpitD0ContSIM(h,t,"MainTxRed") ;

*-productivity shock
tfpSIM(t,"TotFacPro") =  tfpSIM(t,"bau") *0.99 ;
lambdakSIM(a,v,t,"CapitlPro") = lambdakSIM(a,v,t,"BaU") *0.99 ;

kstocksim(t,"CapStoDes") = kstocksim(t,"CapitlPro")*0.99 ;
