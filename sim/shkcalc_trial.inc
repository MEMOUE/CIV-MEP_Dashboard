
Parameter
    chiPASIM(i,t,sim)
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
   tPaf0SIM(i,aa,t,sim)          Agent specific commodity tax base level
   tPafD0SIM(t,sim)              Agent specific commodity tax additive adjuster for all dimensions
   tPafD1SIM(i,t,sim)            Agent specific commodity tax additive adjuster for commodity i
   tPafD2SIM(aa,t,sim)           Agent specific commodity tax additive adjuster for agent aa
   tPafM0SIM(t,sim)              Agent specific commodity tax multiplicative adjuster for all dimensions
   tPafM1SIM(i,t,sim)            Agent specific commodity tax multiplicative adjuster for commodity i
   tPafM2SIM(aa,t,sim)           Agent specific commodity tax multiplicative adjuster for agent aa

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
   tPaf0SIM(i,aa,t,sim)          = tPaf0.l(i,aa,t)          ;
   tPafD0SIM(t,sim)              = tPafD0.l(t)              ;
   tPafD1SIM(i,t,sim)            = tPafD1.l(i,t)            ;
   tPafD2SIM(aa,t,sim)           = tPafD2.l(aa,t)           ;
   tPafM0SIM(t,sim)              = tPafM0.l(t)              ;
   tPafM1SIM(i,t,sim)            = tPafM1.l(i,t)            ;
   tPafM2SIM(aa,t,sim)           = tPafM2.l(aa,t)           ;

   chiPASIM(i,t,sim)           = chiPA(i) ;


*    emisect(a) = YES ;

*lmb trial Closing the gender gap Benin
*-------------------------------------------------------------------------------
*- Agriculture -----------------------------------------------------------------
*-------------------------------------------------------------------------------
$ontext
1% increase in government investment in agriculture increases productivity by 0.11%
Then for 30% increase >  We need to increase government investment by => 30/0.11 =~= 272.
Since we are targeting the 53% of employed (i.e. female) we need 272*0.53 = 144.55 % increase   ;
According to Balcet the share of agriculture in budget in chad is 1.93% of GDP and 44% of this is investment for 2004-2012.
Assuming the same rate: 6034*0.0193*0.44 = 51. So 144% increase means 73.71. Total Government investment is 212.
Thus adding another 73.71 is a 34.7% increase in government investments.
In the same way

10 13.04347826
15 19.56521739
18 23.47826087
20 26.08695652
34 30

According to:
Balcet, Jean-Claude Leon; Cesar Baira, Dering; Zoua, Paulette C.E. Aida Thioune;
 Tayelim, Berte. 2014. Chad - Public expenditure review in the agricultural,
 rural development, and food security sector (English). Washington, D.C. :
 World Bank Group.

Female operated land is  (1 + (1.567/(1.567 + 2.865)) so we improve the productivity of land
by weighting with this share.

$offtext
*-----------------------------------------------------------------------------------------------------------------------------
set agrisim(sim)
/
Agri10
Agri20
/
;

tfpActSIM(agsima,t,"Agri10")$(tshock(t) AND years(t) < 2031) = tfpActSIM(agsima,t,"BaU")*[1 + 0.19/2*shra(agsima)]**[1/(2031-2022)];
tfpActSIM(agsima,t,"Agri20")$(tshock(t) AND years(t) < 2031) = tfpActSIM(agsima,t,"BaU")*[1 + 0.19 *shra(agsima)]**[1/(2031-2022)];

xfdsim(ginv,t,"Agri10")$(tshock(t) AND years(t) < 2031)  = xfdsim(ginv,t,"BaU")*(1+0.062/2)**[1/(2031-2022)];
xfdsim(ginv,t,"Agri20")$(tshock(t) AND years(t) < 2031)  = xfdsim(ginv,t,"BaU")*(1+0.062)  **[1/(2031-2022)];

tfpActSIM(agsima,t,agrisim)$(tshock(t) AND years(t)>2030) =  tfpActSIM(agsima,"2030",agrisim);
xfdsim(ginv,t,agrisim)$(tshock(t) AND years(t)>2030)      =  xfdsim(ginv,"2030",agrisim) ;
*_______________________________________________________________________________________________________________________________
*xfdsim(ginv,t,"Agri10")$(tshock(t) AND years(t) < 2031)  = xfdsim(ginv,t,"BaU")*(1+0.062/2*(years(t)-2022)/9);
*xfdsim(ginv,t,"Agri20")$(tshock(t) AND years(t) < 2031)  = xfdsim(ginv,t,"BaU")*(1+0.062*(years(t)-2022)/9);
*tfpActSIM(agsima,t,"Agri10")$(tshock(t) AND years(t) < 2031) = tfpActSIM(agsima,t,"BaU")*[1 + 0.19/2*shra(agsima)*(years(t)-2022)/9];
*tfpActSIM(agsima,t,"Agri20")$(tshock(t) AND years(t) < 2031) = tfpActSIM(agsima,t,"BaU")*[1 + 0.19  *shra(agsima)*(years(t)-2022)/9];

lambdalSIM(agsima,l,t,"Agri10")$(tshock(t) AND ord(l)<5 AND years(t) < 2031) = lambdalSIM(agsima,l,t,"BaU")*(1 + 0.3*10/20*(years(t)-2019)/11);
lambdalSIM(agsima,l,t,"Agri20")$(tshock(t) AND ord(l)<5 AND years(t) < 2031) = lambdalSIM(agsima,l,t,"BaU")*(1 + 0.3*20/20*(years(t)-2019)/11);

lambdatSIM(agsima,lnd,t,"Agri10")$(tshock(t) AND years(t) < 2031) = lambdatSIM(agsima,lnd,t,"BaU")*(1 + 0.3*10/20*(years(t)-2019)/11);
lambdatSIM(agsima,lnd,t,"Agri20")$(tshock(t) AND years(t) < 2031) = lambdatSIM(agsima,lnd,t,"BaU")*(1 + 0.3*20/20*(years(t)-2019)/11);

lambdalSIM(agsima,l,t,agrisim)$(tshock(t) AND years(t)>2030) = lambdalSIM(agsima,l,"2030",agrisim)   ;
lambdatSIM(agsima,lnd,t,agrisim)$(tshock(t) AND years(t)>2030) = lambdatSIM(agsima,lnd,"2030",agrisim)   ;

*-------------------------------------------------------------------------------
*- Demographic dividend  -------------------------------------------------------
*-------------------------------------------------------------------------------
set demsim(sim)
/
DemD10
DemD20
/
;

*-calculate birth rate

brateSIM(t,sim) = brateSIM(t,"BaU") ;
brateSIM(t,"DemD10")$tshock(t) = (brateSIM(t,"BaU")*(1-(0.1+0.0025*(years(t)-2022)))  + brateSIM(t,"BaU")*(0.1+0.0025*(years(t)-2022))*0.5);
brateSIM(t,"DemD20")$tshock(t) = (brateSIM(t,"BaU")*(1-(0.2+0.0025*(years(t)-2022)))  + brateSIM(t,"BaU")*(0.2+0.0025*(years(t)-2022))*0.5);

chiPASIM(ihea,t,demsim)$tshock(t)  = chiPASIM(ihea,t,"DemD10")*0.75 ;
chiPASIM(iedu,t,demsim)$tshock(t)  = chiPASIM(iedu,t,"DemD10")*0.75 ;

tPaf0SIM(ihea,h,t,demsim)$tshock(t)     = -0.05  ;
tPaf0SIM(ihea,gov,t,demsim)$tshock(t)   = -0.05  ;
tPaf0SIM(iedu,h,t,demsim)$tshock(t)     = -0.05  ;
tPaf0SIM(iedu,gov,t,demsim)$tshock(t)   = -0.05  ;

*-*-*-Conbined Shock

tfpActSIM(agsima,t,"Combine")$tshock(t)    = tfpActSIM(agsima,t,"Agri10") ;
xfdsim(ginv,t,"Combine")$tshock(t)         = xfdsim(ginv,t,"Agri10") ;
brateSIM(t,"Combine")$tshock(t)            = brateSIM(t,"DemD20") ;
chiPASIM(ihea,t,"Combine")$tshock(t)       = chiPASIM(ihea,t,"DemD20")   ;
chiPASIM(iedu,t,"Combine")$tshock(t)       = chiPASIM(iedu,t,"DemD20")   ;
tPafSIM(ihea,h,t,"Combine")$tshock(t)      = tPafSIM(ihea,h,t,"DemD20") ;

*-------------------------------------------------------------------------------

