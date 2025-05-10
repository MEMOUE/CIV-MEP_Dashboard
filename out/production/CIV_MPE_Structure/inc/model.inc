*
* ----------------------------------------------------------------------------
*
*  Production equations
*
* ----------------------------------------------------------------------------

*  P-1 -- Demand for aggregate non-energy intermediate demand bundle

ndeq(a,t)$(ts(t) and aacti(a))..
   nd(a,t) =e= sum(v, and(a,v,t)*(xpv(a,v,t)/lambdaxfac("nd",a,v,t))
            * (lambdaxfac("nd",a,v,t)*pxv(a,v,t)/pnd(a,t))**sigmap(a,v)) ;
            

            

*  P-2 -- Demand for value added plus energy bundle



vaveq(a,v,t)$(ts(t) and aact(a))..
    tfp(t)*(dmgTfpAct(a,t) * tfpAct(a,t))*lambdaxfac("va",a,v,t)*vav(a,v,t) =e= ava(a,v,t)*xpv(a,v,t)
                              * (tfp(t)*(dmgTfpAct(a,t) * tfpAct(a,t))*lambdaxfac("va",a,v,t)*pxv(a,v,t)/pva(a,v,t))**sigmap(a,v) ;

*  P-3 -- Unit cost of production by vintage

pxveq(a,v,t)$(ts(t) and aact(a) )..
   pxv(a,v,t)**(1-sigmap(a,v))
      =e= and(a,v,t)*(pnd(a,t)/lambdaxfac("nd",a,v,t))**(1-sigmap(a,v))
       +  ava(a,v,t)*(pva(a,v,t)/(tfp(t)*(dmgTfpAct(a,t) * tfpAct(a,t))*lambdaxfac("va",a,v,t)))**(1-sigmap(a,v)) ;


*  P-4 -- Aggregate unit cost of production

pxeq(a,t)$(ts(t) and aact(a)  )..
   px(a,t)*xp(a,t) =e= sum(v, pxv(a,v,t)*xpv(a,v,t)) ;

*  P-5 -- Output price

ppeq(a,t)$(ts(t) and aact(a))..
   pp(a,t) =e= px(a,t)*(1 + tPrd(a,t) + tpsb(a,t)) ;

*  P-6 -- Demand for land bundle

pland_ptEQ(a,lnd,t)$(ts(t) and aland(a,lnd,t) ne 0)..
           pland_pt(a,lnd,t) =e=  pland(a,lnd,t) * (1+ tfac(a,lnd,t))
                                 + Sum(em,tEmiFac(em,lnd,a,t)*emical(t)*chiEmiFac(em,lnd,a,t)*rhoEmiFac(em,lnd,a))
;

landdeq(a,lnd,t)$(ts(t) and aland(a,lnd,t) ne 0)..
   xf(a,lnd,t) =e= sum(v, aland(a,lnd,t)*vav(a,v,t)*(lambdat(a,lnd,t)**(sigmav(a,v)-1))
             *         (pva(a,v,t)/pland_pt(a,lnd,t))**sigmav(a,v)) ;

xf.fx(a,lnd,t)$(NOT sam(lnd,a)) = 0;
*  P-7 -- Demand for aggregate labor bundle

lab1eq(a,v,t)$(ts(t) and aact(a))..
   lab1(a,v,t)*plab1(a,v,t)**sigmav(a,v) =e=
      alab1(a,v,t)*vav(a,v,t)*pva(a,v,t)**sigmav(a,v) ;
      



*  P-8 -- Demand for capital+energy bundle

kseeq(a,v,t)$(ts(t) and aact(a))..
   kse(a,v,t) =e= akse(a,v,t)*vav(a,v,t)*(pva(a,v,t)/pkse(a,v,t))**sigmav(a,v) ;

*  P-9 -- Price of value added plus energy bundle by vintage

pvaeq(a,v,t)$(ts(t) and aact(a))..
   pva(a,v,t)**(1-sigmav(a,v)) =e= sum(lnd,aland(a,lnd,t)*(pland_pt(a,lnd,t)/lambdat(a,lnd,t))**(1-sigmav(a,v)) )
                                +  alab1(a,v,t)*plab1(a,v,t)**(1-sigmav(a,v))
                                +  akse(a,v,t)*pkse(a,v,t)**(1-sigmav(a,v)) ;

* pva.lo(a,v,t) = 0.01 ;

*  P-10 -- Sector and vintage specific demand for capital

kskeq(a,v,t)$(ts(t) and aact(a))..
   ksk(a,v,t) =e= aksk(a,v,t)*kse(a,v,t)*(pkse(a,v,t)/pksk(a,v,t))**sigmak(a,v) ;

*  P-11 -- Sector and vintage specific demand for energy bundle

xnrgpeq(a,v,t)$(ts(t) and aact(a))..
   xnrgp(a,v,t) =e= ae(a,v,t)*kse(a,v,t)*(pkse(a,v,t)/pnrgp(a,v,t))**sigmak(a,v) ;

*  P-12 -- Price of capital+energy bundle

pkseeq(a,v,t)$(ts(t) and aact(a))..
   pkse(a,v,t)**(1-sigmak(a,v)) =e= aksk(a,v,t)*pksk(a,v,t)**(1-sigmak(a,v))
                                 +  ae(a,v,t)*pnrgp(a,v,t)**(1-sigmak(a,v)) ;

* pke.lo(a,v,t) = 0.01 ;

*  P-13 -- Sector and vintage specific demand for capital

pk_ptEQ(a,v,t)$ts(t)..
        pk_pt(a,v,t) =e= pk(a,v,t) * (1 + sum(cap,tfac(a,cap,t)))
                                 + Sum((em,cap),tEmiFac(em,cap,a,t)*emical(t)*chiEmiFac(em,cap,a,t)*rhoEmiFac(em,cap,a))
                                                       ;

kdeq(a,v,t)$(ts(t) and aact(a))..
   lambdaxfac("ksk",a,v,t)*kd(a,v,t) =e=
      ak(a,v,t)*ksk(a,v,t)*(lambdaxfac("ksk",a,v,t)*pksk(a,v,t)/pk_pt(a,v,t))**sigmaks(a,v) ;

*-This needs to be modified if there are more than one capital type
kdToteq(a,cap,t)$(ts(t) and aact(a)).. xf(a,cap,t) =e= sum(v, kd(a,v,t)) ;

*  P-14 -- Sector and vintage specific demand for skilled labor bundle

lab2eq(a,v,t)$(ts(t) and aact(a))..
   lab2(a,v,t) =e= alab2(a,v,t)*ksk(a,v,t)*(pksk(a,v,t)/plab2(a,v,t))**sigmaks(a,v) ;

*  P-15 -- Price of capital+skill bundle

pkskeq(a,v,t)$(ts(t) and aact(a))..
   pksk(a,v,t)**(1-sigmaks(a,v)) =e= ak(a,v,t)*(pk_pt(a,v,t)/lambdaxfac("ksk",a,v,t))**(1-sigmaks(a,v))
                                  +  alab2(a,v,t)*plab2(a,v,t)**(1-sigmaks(a,v)) ;

* pksk.lo(a,v,t) = 0.01 ;

*  P-16 -- Sector and skill specific demand for labor

ldeq(a,l,t)$(ts(t) and ldFlag(a,l))..
   (dmgLambdaL_HH(a,l,t) * dmgLambdaL(a,l,t) * lambdal(a,l,t))*xf(a,l,t) =e= (sum(v, ald(a,l,v,t)*lab1(a,v,t)
                             *     ((dmgLambdaL_HH(a,l,t) * dmgLambdaL(a,l,t) *lambdal(a,l,t))*plab1(a,v,t)/pswage(a,l,t))**sigmaul(a,v)))$ul(l)
                             +  (sum(v, ald(a,l,v,t)*lab2(a,v,t)
                             *     ((dmgLambdaL_HH(a,l,t) * dmgLambdaL(a,l,t) * lambdal(a,l,t))*plab2(a,v,t)/pswage(a,l,t))**sigmasl(a,v)))$sl(l)
                             ;

*  P-17 -- Price of aggregate unskilled labor bundle

plab1eq(a,v,t)$(ts(t) and alab1(a,v,t))..
   plab1(a,v,t)**(1-sigmaul(a,v))
      =e= sum(l$ul(l), ald(a,l,v,t)*(pswage(a,l,t)/(dmgLambdaL_HH(a,l,t) * dmgLambdaL(a,l,t) * lambdal(a,l,t)))**(1-sigmaul(a,v))) ;

*  P-18 -- Price of aggregate skilled labor bundle

plab2eq(a,v,t)$(ts(t) and alab2(a,v,t))..
   plab2(a,v,t)**(1-sigmasl(a,v))
      =e= sum(l$sl(l), ald(a,l,v,t)*(pswage(a,l,t)/(dmgLambdaL_HH(a,l,t) * dmgLambdaL(a,l,t) * lambdal(a,l,t)))**(1-sigmasl(a,v))) ;
      


lambdaxfaceq(fpnest,a,v,t)$(ts(t) and aact(a))..
lambdaxfac(fpnest,a,v,t) =e=
            chixFacF(fpNest,t)
            *chixFacA(a,t)
            * chixFacV(v,t)
            * sum(mapAagr(aagr,a),chixFacAgr(aagr,t)) ;

* --- Total used to calculate VA sector shares

sectTotEq(t)$(ts(t)) ..
sectTot(t) =e= sum((a,v),sum(lnd,xf(a,lnd,t)*pland_pt(a,lnd,t))
                + sum(l,swage(a,l,t)*xf(a,l,t))
                +sum(cap,pk_pt(a,v,t)*xf(a,cap,t))
                    )
            +sum((ptx,a),sam(ptx,a))
                
;
*
*   ---Sector share in calculated total above

sectShrEq(aagr,t) $(ts(t) and sum(mapAagr(aagr,a),1)) ..
   SectShr(aagr,t)=e=
   (sum((a,v) $ mapaagr(aagr,a) ,sum(lnd,xf(a,lnd,t)*pland_pt(a,lnd,t))
                + sum(l,swage(a,l,t)*xf(a,l,t))
                +sum(cap,pk(a,v,t)*xf(a,cap,t))
                    )
                +sum((ptx,a)$mapaagr(aagr,a),sam(ptx,a))
                )             
/sectTot(t);
*


*  P-15 -- Demand for non-energy intermediate inputs

xap1eq(in,a,t)$(ts(t) and aio(in,a,t) ne 0)..
   xa(in,a,t) =e= aio(in,a,t)*nd(a,t)*(pnd(a,t)/(chiPA(in)*paf(in,a,t)))**sigman(a) ;

*  P-19 -- Price of aggregate non-energy intermediate demand bundle

pndeq(a,t)$(ts(t) and aacti(a))..
   pnd(a,t)$(aacti(a))**(1-sigman(a)) =e= sum(in, aio(in,a,t)
                            *    (chiPA(in)*paf(in,a,t))**(1-sigman(a))) ;

*  P-20 -- Demand for energy intermediate inputs

xap2eq(e,a,t)$(ts(t) and aep(e,a,'Old',t) ne 0)..
   xa(e,a,t) =e= sum(v,  aep(e,a,v,t)*xnrgp(a,v,t)
              *         (lambdaep(a,e,v,t)**(sigmae(a,v) - 1))
              *         (pnrgp(a,v,t)/paf(e,a,t))**sigmae(a,v)) ;

*  P-21 -- Price of energy bundle

pnrgpeq(a,v,t)$(ts(t) and ae(a,v,t) ne 0)..
    pnrgp(a,v,t)**(1-sigmae(a,v)) =e=
         sum(e, aep(e,a,v,t)*chiPA(e)*((paf(e,a,t)/lambdaep(a,e,v,t))**(1-sigmae(a,v)))) ;

*  P-22 -- Joint-production equation
*  !!!! Need to fix for infinite elasticity since pp is initialized at 1!

xeq(a,i,t)$(ts(t) and ap(a,i,t) ne 0)..
   0 =e= (x(a,i,t)*pp(a,t)**omegap(a) - ap(a,i,t)*(chiP(a,i)**omegap(a))*xp(a,t)*p(a,i,t)**omegap(a))$(omegap(a) ne inf)
      +  (chiP(a,i)*p(a,i,t) - pp(a,t))$(omegap(a) eq inf) ;

*  P-23 -- Supply equilibrium condition

xpeq(a,t)$(ts(t) and aact(a) )..
   pp(a,t)*xp(a,t) =e= sum(i,chiP(a,i)*p(a,i,t)*x(a,i,t)) ;

*  P-24 -- Aggregation of multiple actitivies

peq(a,i,t)$(ts(t) and as(a,i,t) ne 0)..
   0 =e= (x(a,i,t)*p(a,i,t)**sigmas(i) - as(a,i,t)*xs(i,t)*gammap(a,i,t)**sigmas(i)*ps(i,t)**sigmas(i))$(sigmas(i) ne inf)
      +  (p(a,i,t) - gammap(a,i,t)*ps(i,t))$(sigmas(i) eq inf) ;

*  P-25 -- Supply price of commodity i

xseq(i,t)$(ts(t) and iact(i))..
   0 =e= (ps(i,t)**(1-sigmas(i)) - sum(a, as(a,i,t)*(gammap(a,i,t)**(sigmas(i)-1))*p(a,i,t)**(1-sigmas(i))))$(sigmas(i) ne inf)
      +  (xs(i,t) - sum(a, x(a,i,t)))$(sigmas(i) eq inf) ;


* Power mix targeting
ElecMixEq(aElec,iElec,t)$(ts(t))..
  ElecMix(Aelec,iElec,t) =e= x(aelec,iElec,t)/sum(aelecp,x(aelecp,iElec,t));

* ----------------------------------------------------------------------------
*
*  Income distribution equations
*
* ----------------------------------------------------------------------------

*  Y-1 -- Gross capital income

kapyeq(t)$ts(t)..
   kapy(t) =e= sum((a,v)$aact(a), pk(a,v,t)*kd(a,v,t)) ;

*  Y-2 -- Gross household income
yheq(h,t)$ts(t)..
   yh(h,t) =e= sum((lnd,a), chit(h,lnd,t)*pland(a,lnd,t)*xf(a,lnd,t))
            +  sum(l, chil(h,l,t)*sum(a$aact(a),swage(a,l,t)*xf(a,l,t)))
            +  chikh(h,t)*kapy(t)
            +  sum((inst,instp)$mapinst(h,instp), transfers(instp, inst, t))
            +  SUM(inst$mapinst(h,inst),debtPay(inst,t))
                 ;

ginieq(t)$ts(t)..
  gini(t)  =e= 2 * sum(h,ord(h) * yh(h,t))/(card(h)*sum(h,yh(h,t))) - (card(h)+1)/card(h) ;

*- T-4a -- Dependency ration
deprateEq(cohorts,t)$ts(t).. deprate(cohorts,t) =e= pop(cohorts,t)/pop("P1564",t) ;

*  Y-4 -- Average propensity to save
$ontext
Cruz, Marcio; Ahmed, S. Amer. 2016.�
Based on the GMM method with several co-variates, it is estimated that an increase of 1 percentage point in the share of working-age population
is associated with an increase of 0.78 percentage point in domestic savings as a share of the gross national income (GNI).
Ahmed, S. Amer; Cruz, Marcio; Go, Delfin S.; Maliszewska, Maryla; Osorio-Rodarte, Israel. 2014.�
Parameters for Savings as a Share of GDP Function in LINKAGE:
                            High income country   LIC
Youth dependency ratio     -0.068                  -0.279
Elderly dependency ratio   -0.218                  -1.37
$offtext
apseq(h,t)$ts(t)..
   aps(h,t) =e= chims(t)*aps0(h)
*             + sign(aps(h,t-1))*aps(h,t-1)*((deprate("P65UP",t)/deprate("P65UP",t-1))**(-7.8)
*               *(deprate("PLT15",t)/deprate("PLT15",t-1))**(-7.8)-1)

               ;

*  Y-5 -- Total household transfers

hhtreq(h,inst,t)$(ts(t) and mapinst(h,inst))..
   totTr(inst,t) =e= chiTotTr(inst)*yh(h,t) ;

*  Y-6 -- Household expenditures on goods and services

yfheq(h,t)$ts(t)..
   yf(h,t) =e= (1-aps(h,t))*(yh(h,t) - sum(inst$mapinst(h,inst), totTr(inst,t))
            - tPit(h,t) * yh(h,t))
            +  TRgvthhd(h,t)
                  ;

*  Y-7 -- Household savings

savheq(h,t)$ts(t)..
   savh(h,t) =e= aps(h,t)*(yh(h,t) - sum(inst$mapinst(h,inst), totTr(inst,t))
              -  tPit(h,t) * yh(h,t)) - sum(inst$mapinst(h,inst), debtNew(inst,t)) ;

*  Y-8 -- Revenues generated by production subsidies

*DP modif for factor taxes
ygftxeq(t)$ts(t)..
   yg("ftx",t) =e=sum(a, sum(lnd,tFac(a,lnd,t) * pland(a,lnd,t)*xf(a,lnd,t))
                       + sum(l,tFac(a,l,t) * swage(a,l,t)*xf(a,l,t))
                       + sum((v,cap),tFac(a,cap,t) * pk(a,v,t)*kd(a,v,t)))   ;

ygpsbeq(t)$ts(t)..
   yg("psb",t) =e= sum(a$aact(a),tpsb(a,t)*px(a,t)*xp(a,t)) ;

ygetxeq(t)$ts(t)..
   yg("etx",t) =e= sum(i,xe(i,t)*chiPE(i)*pe(i,t)*tExp(i,t));

*  Y-9 -- Revenues generated by production taxes

ygptxeq(t)$ts(t)..
   yg("ptx",t) =e= sum(a$aact(a),tPrd(a,t)*px(a,t)*xp(a,t)) ;

*  Y-10 -- Revenues generated by sales taxes

ygotxeq(t)$ts(t)..
   yg("otx",t)
      =e= sum(i$iarm(i), (chiPD(i)*pd(i,t) + pmarg(i,t)*tmg(i,"d",t))*tVat(i,"d",t)*xd(i,t)
       +  (er(t)*pwm(i,t)*(1+tImp(i,t)) + pmarg(i,t)*tmg(i,"m",t))*tVat(i,"m",t)*xm(i,t)) ;

*  Y-11 -- Revenues generated by import tariffs

ygmtxeq(t)$ts(t)..
   yg("mtx",t) =e= sum(i, (xm(i,t) + mdelst(i,t))*pwm(i,t)*er(t)*tImp(i,t)) ;

*  Y-12 -- Revenues generated by commodity taxes

ygatxeq(t)$ts(t)..
   yg("atx",t) =e= sum((i,aa), tPaf(i,aa,t)*chiPA(i)*pa(i,t)*xa(i,aa,t)) ;

*  Y-13 -- Revenues generated by emission taxes
* !!!! For the moment, only applied on Armington demand

ygctxeq(t)$ts(t)..
   yg("ctx",t) =e= sum((em,emSrc,aa), tEmi(em,aa,t)*emical(t)*chiEmi(em,emSrc,aa,t)*rhoEmi(em,emSrc,aa)
*                                                         *phiEmi(em,emSrc,aa)*sum(i$emsrc(i),xa(i,aa,t))) ;
                                                         *phiEmi(em,emSrc,aa)*xa(emSrc,aa,t))
                                +Sum((em,fp,a),tEmiFac(em,fp,a,t)*emical(t)*chiEmiFac(em,fp,a,t)*rhoEmiFac(em,fp,a)*xf(a,fp,t))
                                                 ;

*  Y-14 -- Revenues generated by direct household taxation

yghtxeq(t)$ts(t)..
   yg("dtx",t) =e= sum(h, tPit(h,t) * yh(h,t)) + sum(entr, tCit(entr,t) * entrY(entr,t)) + gtax(t) ;

*  Y-15 -- Government revenues

ygoveq(gov, t)$ts(t)..
   ygov(t) =e= sum(g, yg(g,t))
            + sum((instp,inst)$mapinst(gov,instp), transfers(instp, inst, t))
            + chikGov(gov,t)*kapy(t)
            + sum((lnd,a), chiTGov(gov,lnd,t)*pland_pt(a,lnd,t)*xf(a,lnd,t))
            + SUM(inst,debtNew(inst,t))
            ;


*  Y-16 -- Government direct taxes

gtaxeq(t)$ts(t)..
   gtax(t) =e= dgovTax(t)*ygov(t) ;

*  Y-17 -- Government transfers

govtreq(gov,inst,t)$(ts(t) and mapinst(gov,inst))..
   totTr(inst,t) =e= chiTotTr(inst)*ygov(t) ;

*  Y-18 -- Nominal government savings

savgeq(gov,t)$ts(t)..
*-HD: Generalize to avoid hardcoding
   savg(t) =e= ygov(t) - gtax(t)
            - sum(inst$mapinst(gov,inst), totTr(inst,t)) - yf(gov,t)- SUM(ginv,yf(ginv,t))
            - sum(inst,debtPay(inst,t))
            - sum(adpinv$map_adpInv(gov,adpinv),yf(adpinv,t))
            - sum(h,TRgvthhd(h,t))
                                 ;


debtInterestEQ(t)$ts(t)..
    debtInterest(t)  =e=   (DebtStkD(t)-sum(instd,debtNew(instd,t)))*DebtIntD(t)/100 + (DebtStkF(t)-sum(instf,debtNew(instf,t)))*DebtIntF(t)/100 ; 



fiscalBalanceEQ(t)$ts(t)..
         fiscalbalance(t) =e=
 ygov(t) - gtax(t)
            - sum((inst,gov,instp)$mapinst(gov,instp), transfers(inst, instp, t)) - sum(gov, yf(gov,t))
              - sum(ginv, yf(ginv,t))
            - debtinterest(t)
            - sum(inst,debtNew(inst,t))
            ;


            

fiscalBalanceGDPeq(t)$ts(t)..
         fiscalBalanceGDP(t) =e= fiscalBalance(t)/ gdpmp(t);

*Government overall balance
Obaleq(t)$ts(t)..
         Obal(t) =e= fiscalbalance(t) -
         sum(inst,debtPay(inst,t))
         ;


ObalGDPeq(t)$ts(t)..
         ObalGDP(t) =e= Obal(t)/gdpmp(t);

ygGDPeq(t)$ts(t)..
         ygGDP(t) =e= sum(g, yg(g,t)) /gdpmp(t);

ygTGDPeq(t)$ts(t)..
         ygTGDP(t) =e= [ygov(t)- sum(inst,debtNew(inst,t))] /gdpmp(t);

ExpGDPeq(t)$ts(t).. ExpGDP(t) =e=  [gtax(t)+ sum(inst$mapinst('g-govt',inst), totTr(inst,t)) + yf('g-govt',t)+ SUM(ginv,yf(ginv,t))
                                   + sum(inst,debtPay(inst,t)) + sum(adpinv$map_adpInv('g-govt',adpinv),yf(adpinv,t))] /gdpmp(t);
                                   




*  Y-19 -- Real government savings

rsgeq(t)$ts(t)..
   rsg(t)*pnum(t) =e= savg(t) ;

*  Y-20 -- Enterprise income

entrYeq(entr,t)$ts(t)..
   entrY(entr, t) =e= sum((lnd,a), chitentr(entr,lnd,t)*xf(a,lnd,t)*pland_pt(a,lnd,t))
            +  chikEntr(entr,t)*kapY(t)
            +  sum((instp,inst)$mapinst(entr,instp), transfers(instp, inst, t))
            +  SUM(inst$mapinst(entr,inst),debtPay(inst,t));

*  Y-22 -- Enterprise saving

savEntreq(entr,t)$ts(t)..
   savEntr(entr, t) =e= apsEntr(entr,t)*entrY(entr,t)* (1 - tCit(entr,t)) - SUM(inst$mapinst(entr,inst),debtNew(inst,t));

*  Y-23 -- Enterprise transfers

entrtreq(entr,inst,t)$(ts(t) and mapinst(entr,inst))..
*   totTr(inst,t) =e= entrY(entr,t) * (1- tCit(entr, t)) - savEntr(entr, t) - debtNew(inst,t);
   totTr(inst,t) =e= entrY(entr,t) * (1- tCit(entr, t)) - savEntr(entr, t) - debtNew(inst,t);

*  Y-24 -- Allocation of domestic transfers

dtransferseq(inst,dinst,t)$(ts(t) and chiTr(inst,dinst) ne 0)..
   transfers(inst,dinst,t) =e= chiTr(inst, dinst) * totTr(dinst,t) ;

*  Y-25 -- ROW transfers

rowtransferseq(inst,row,instp,t)$(ts(t) and
   mapinst(row,instp) and chiTr(inst,instp) ne 0)..
      transfers(inst,instp,t) =e= er(t)*rowtransfers(inst,t) ;

*  Y-27 -- Debt Equations

DebtStkDEq(t)$ts(t).. DebtStkD(t)   =e= DebtStkD(t-1) + SUM(instd,debtNew(instd,t) - debtPay(instd,t) ) ;
DebtStkFEq(t)$ts(t).. DebtStkF(t)   =e= DebtStkF(t-1) + SUM(instf,debtNew(instf,t) - debtPay(instf,t) ) ;
DebtStkTEq(t)$ts(t).. DebtStkT(t)   =e= DebtStkD(t) + DebtStkF(t)  ;

debtGDPEQ(t)$ts(t).. DebtGDP(t)     =e= DebtStkT(t) / gdpmp(t) ;

debtPayEq(instfd,t)$ts(t)..   debtPay(instfd,t)  =e= rDebtStk(t)*(chiDebtPayD(instfd) * (DebtStkD(t) * rDebtStkD(t) + DebtStkD(t)*DebtIntD(t)/100)
                                                               + chiDebtPayF(instfd) * (DebtStkF(t) *  rDebtStkF(t) + DebtStkF(t)*DebtIntF(t)/100))  ;

debtNewEq(inst,t)$( chiDebtNew(inst,t) and ts(t)).. debtNew(inst,t)    =E= chiDebtShf(t)*chiDebtNew(inst,t) * (-obal(t))  ;

debtNewTEq(t)$ts(t).. debtNewT(t)   =E= sum(instfd,debtNew(instfd,t)) ;

 DebtIntFEQ(t,t0)$(ts(t)).. DebtIntF(t) =e= DebtIntF(t0) +  0.3 * (DebtGDP(t)-DebtGDP(t0)) ;
 DebtIntDEQ(t,t0)$(ts(t)).. DebtIntD(t) =e= DebtIntD(t0) + 1.5 * (DebtGDP(t)-DebtGDP(t0)) ;


*  Y-26 -- Investment savings balance

inveq(inv,t)$ts(t)..
   yf(inv,t) =e= sum(h, savh(h,t)) + savg(t) + sum(entr, savEntr(entr,t))
              +  er(t)*savf(t) - sum(i, chiPS(i)*ps(i,t)*delst(i,t)
              +  er(t)*pwm(i,t)*(1+tImp(i,t))*mdelst(i,t))
              -  sum(adpinv$map_adpInv(inv,adpinv),yf(adpinv,t))
;

* ----------------------------------------------------------------------------
*
*  Demographic equations
*
* ----------------------------------------------------------------------------

BirthEq(t)$ts(t)..
                popAge("age000",t) =e=  brateU(t) * pop("P1564",t-1);

popAgeEq(age,t)$(ts(t) AND ord(age)>1 AND ord(t)>1)..
                popAge(age,t) =e= popAge(age-1,t-1)*drate(age,t);


popEq(cohorts,t)$ts(t).. pop(cohorts,t) =e= sum(age$mapage(age,cohorts),popAge(age,t));

*-HH population

hpopeq(h,t)$ts(t)..

    hpop(h,t) =e=  hpop0(h)/pop0("ptotl")*pop("ptotl",t) ;

* ----------------------------------------------------------------------------
*
*  Household demand equations
*
* ----------------------------------------------------------------------------

*  CDE utility function

*  Factor needed for household consumption function

consScaleeq(h,t)$(ts(t) and ifCDE)..
   consScale(h,t) =e= sum(k$akfact(h,k), akf(h,k,t)*bh(h,k,t)
                             * (uh(h,t)**(eh(h,k,t)*bh(h,k,t)))
                             * (pkf(h,k,t)**(bh(h,k,t)))
                             * ((yf(h,t)/hpop(h,t))**(-bh(h,k,t)))) ;

*  D-1 -- Household demand


xkfeq(h,k,t)$(ts(t) and akfact(h,k) and ifCDE)..
  xkf(h,k,t)*consScale(h,t) =e= hpop(h,t)*akf(h,k,t)*bh(h,k,t)
                                * (uh(h,t)**(eh(h,k,t)*bh(h,k,t)))
                                * (pkf(h,k,t)**(bh(h,k,t)-1))
                                * ((yf(h,t)/hpop(h,t))**(1-bh(h,k,t))) ;

*  D-2 -- Household utility

uheq(h,t)$(ts(t) and ifCDE)..
   1 =e= sum(k$akfact(h,k), akf(h,k,t)
      *  (uh(h,t)**(eh(h,k,t)*bh(h,k,t)))
      *  (pkf(h,k,t)**(bh(h,k,t)))
      *  ((yf(h,t)/hpop(h,t))**(-bh(h,k,t)))) ;

*  D-3 -- Household budget budget shares

xkfshreq(h,k,t)$(ts(t) and akfact(h,k))..
   xkfshr(h,k,t)*yf(h,t) =e= pkf(h,k,t)*xkf(h,k,t) ;

*  D-4 -- Consumer price index

pfheq(h,t)$ts(t)..
   pf(h,t) =e= sum(k, xkfshr(h,k,t)*pkf(h,k,t)) ;

*  Uncompensated household elasticity of demand

uedeq(h,k,kp,t)$(ts(t) and akfact(h,k) and akfact(h,kp) and ifCDE)..
   ued(h,k,kp,t) =e= (1-bh(h,k,t))*(xkfshr(h,kp,t)-kron(k,kp))
                  -   xkfshr(h,kp,t)*(bh(h,kp,t) + incElas(h,k,t)
                  -   sum(kk, xkfshr(h,kk,t)*bh(h,kk,t))) ;

*  Income elasticity

incelaseq(h,k,t)$(ts(t) and akfact(h,k) and ifCDE)..
   incelas(h,k,t) =e= (eh(h,k,t)*bh(h,k,t)-sum(kk, xkfshr(h,kk,t)*eh(h,kk,t)*bh(h,kk,t)))
                   /  sum(kk, xkfshr(h,kk,t)*eh(h,kk,t))
                   -  (bh(h,k,t) - 1) + sum(kk, xkfshr(h,kk,t)*bh(h,kk,t)) ;

*  Compensated demand elasticity

cedeq(h,k,kp,t)$(ts(t) and akfact(h,k) and akfact(h,kp) and ifCDE)..
   ced(h,k,kp,t) =e= (1-bh(h,k,t))*(xkfshr(h,kp,t)-kron(k,kp))
                  -  xkfshr(h,kp,t)*(bh(h,kp,t) - sum(kk, xkfshr(h,kk,t)*bh(h,kk,t))) ;

*  Allen partial elasticity of demand

apeeq(h,k,kp,t)$(ts(t) and akfact(h,k) and akfact(h,kp) and ifCDE)..
   ape(h,k,kp,t) =e= (1-bh(h,k,t))*(1-kron(k,kp)/xkfshr(h,kp,t)) - bh(h,kp,t)
                  +  sum(kk, xkfshr(h,kk,t)*bh(h,kk,t)) ;

* ----------------------------------------------------------------------------
*
*  Transformation of household demand for good k into demand for produced goods
*
* ----------------------------------------------------------------------------

*  Energy/non-energy bundles

*  D-5 -- Aggregate demand for non energy goods

xkfnnrgeq(h,k,t)$(ts(t) and aknnrg(h,k) ne 0)..
   xkfnnrg(h,k,t) =e= aknnrg(h,k)*xkf(h,k,t)*(pkf(h,k,t)/pkfnnrg(h,k,t))**sigmac(h,k) ;

*  D-6 -- Aggregate energy demand

xkfnrgeq(h,k,t)$(ts(t) and aknrg(h,k) ne 0)..
   xkfnrg(h,k,t) =e= aknrg(h,k)*xkf(h,k,t)*(pkf(h,k,t)/pkfnrg(h,k,t))**sigmac(h,k) ;

*  D-7 -- Aggregate price of good k

pkfeq(h,k,t)$(ts(t) and akfact(h,k))..
   pkf(h,k,t)**(1-sigmac(h,k)) =e= aknnrg(h,k)*pkfnnrg(h,k,t)**(1-sigmac(h,k))
                                + aknrg(h,k)*pkfnrg(h,k,t)**(1-sigmac(h,k)) ;

*  Decomposition of non-energy bundles

*  D-8 -- Armington final demand for non energy goods

xakfnnrgeq(h,in,t)$(ts(t) and xaact(in, h))..
   xa(in,h,t) =e= sum(k, af(h,in,k,t)*xkfnnrg(h,k,t)
               * (pkfnnrg(h,k,t)/(chiPA(in)*paf(in,h,t)))**sigmacaa(h,k)) ;

*  Decomposition of energy bundles

*  D-9 -- Armington final demand for energy goods

xakfnrgeq(h,e,t)$(ts(t) and xaact(e, h))..
   xa(e,h,t) =e= sum(k, af(h,e,k,t)*(xkfnrg(h,k,t)/(dmgLambdaEh(h,e,k,t) * lambdaeh(h,e,k,t)))
              *     (dmgLambdaEh(h,e,k,t) * lambdaeh(h,e,k,t)
              *      pkfnrg(h,k,t)/(chiPA(e)*paf(e,h,t)))**sigmacae(h,k)) ;

*  D-10 -- Price of non energy bundle

pkfnnrgeq(h,k,t)$(ts(t) and aknnrg(h,k) ne 0)..
   pkfnnrg(h,k,t)**(1-sigmacaa(h,k)) =e= sum(in$(af(h,in,k,t) ne 0),
      af(h,in,k,t)*(chiPA(in)*paf(in,h,t))**(1-sigmacaa(h,k))) ;

*  D-11 -- Price of energy bundle

pkfnrgeq(h,k,t)$(ts(t) and aknrg(h,k) ne 0)..
   pkfnrg(h,k,t)**(1-sigmacae(h,k)) =e= sum(e$(af(h,e,k,t) ne 0),
      af(h,e,k,t)*(chiPA(e)*paf(e,h,t)/(dmgLambdaEh(h,e,k,t) * lambdaeh(h,e,k,t)))**(1-sigmacae(h,k))) ;

* ----------------------------------------------------------------------------
*
*  Other demand equations
*
* ----------------------------------------------------------------------------

*  D-12 -- Aggregate demand for non energy goods

xfnnrgeq(f,t)$(ts(t) and afnnrg(f,t) ne 0)..
   xfnnrg(f,t) =e= afnnrg(f,t)*xfd(f,t)*(pf(f,t)/pfnnrg(f,t))**sigmaf(f) ;

*  D-13 -- Aggregate energy demand

xfnrgeq(f,t)$(ts(t) and afnrg(f,t) ne 0)..
   xfnrg(f,t) =e= afnrg(f,t)*xfd(f,t)*(pf(f,t)/pfnrg(f,t))**sigmaf(f) ;

*  D-14 -- Aggregate price deflator for agent f

pfeq(f,t)$(yf0(f,t) AND ts(t))..
   pf(f,t)**(1-sigmaf(f)) =e=
      afnnrg(f,t)*pfnnrg(f,t)**(1-sigmaf(f)) + afnrg(f,t)*pfnrg(f,t)**(1-sigmaf(f)) ;

*  Decomposition of non-energy bundles

*  D-15 -- Armington final demand for non energy goods
*lmb____________________________________________________________________________
 xafnnrgeq(f,in,t)$(ts(t) and xaact(in, f))..
   xa(in,f,t) =e= aff(f,in,t)*xfnnrg(f,t)
               * (pfnnrg(f,t)/(chiPA(in)*paf(in,f,t)))**sigmafaa(f) ;
* changing public consumption of in products here if f1 is active
* allows to fix xa(in,f,t) to use as policy variable for targeted current expenditure
* activate equation if you want to use it
xfnnrgeq1(f,t)$(ts(t) and afnnrg(f,t) ne 0 and f1(f))..
   xfnnrg(f,t) =e= sum(in,xa(in,f,t)*(chiPA(in)*paf(in,f,t)))/ pfnnrg(f,t);
*_______________________________________________________________________________
*  Decomposition of energy bundles

*  D-16 -- Armington final demand for energy goods

xafnrgeq(f,e,t)$(ts(t) and xaact(e,f))..
   xa(e,f,t) =e= aff(f,e,t)*(xfnrg(f,t)/lambdaef(f,e,t))
              *  (lambdaef(f,e,t)*pfnrg(f,t)/(chiPA(e)*paf(e,f,t)))**sigmafae(f) ;

*  D-17 -- Price of non energy bundle

pfnnrgeq(f,t)$(ts(t) and afnnrg(f,t) ne 0)..
   pfnnrg(f,t)**(1-sigmafaa(f)) =e= sum(in$(aff(f,in,t) ne 0),
      aff(f,in,t)*(chiPA(in)*paf(in,f,t))**(1-sigmafaa(f))) ;

*  D-18 -- Price of energy bundle

pfnrgeq(f,t)$(ts(t) and afnrg(f,t) ne 0)..
   pfnrg(f,t)**(1-sigmafae(f)) =e= sum(e$(aff(f,e,t) ne 0),
      aff(f,e,t)*(chiPA(e)*paf(e,f,t)/lambdaef(f,e,t))**(1-sigmafae(f))) ;

* ----------------------------------------------------------------------------
*
*  Miscellaneous demand equations
*
* ----------------------------------------------------------------------------

*  D-19 -- Aggregate margins to deliver good i to each of the three nodes

xmargeq(j,t)$(ts(t) and mgencl(j))..
   xmarg(j,t) =e= tmg(j,"d",t)*xd(j,t) + tmg(j,"m",t)*xm(j,t) + tmg(j,"x",t)*xe(j,t) ;

*  D-20 -- Demand for margin commodities

*  !!!! Margins pay neither sales tax nor emissions tax

xamrgeq(i,j,t)$(ts(t) and amarg(i,j) ne 0)..
   xa(i,j,t) =e= amarg(i,j)*xmarg(j,t)*(pmarg(j,t)/(chiPA(i)*pa(i,t)))**sigmamg(j) ;

*  D-21 -- Price of delivering good i

pmargeq(j,t)$(ts(t) and mgencl(j))..
   pmarg(j,t)**(1-sigmamg(j)) =e= sum(i, amarg(i,j)*(chiPA(i)*pa(i,t))**(1-sigmamg(j))) ;

*  D-22 -- Volume or value definition

yfeq(oa,t)$ts(t)..
   yf(oa,t) =e= pf(oa,t)*xfd(oa,t) ;

* ----------------------------------------------------------------------------
*
*  Trade equations
*
* ----------------------------------------------------------------------------


*  T-3 -- Agents' price of imports

pmaeq(i,t)$(ts(t) and iimp(i))..
   chiPMa(i)*pma(i,t) =e= (er(t)*pwm(i,t)*(1+tImp(i,t)) + pmarg(i,t)*tmg(i,"m",t))
                       *  (1+tVat(i,"m",t)) ;

*  T-4 -- Agents' price of domestically produced goods

pdaeq(i,t)$(ts(t) and idom(i))..
   chiPDa(i)*pda(i,t) =e= (chiPD(i)*pd(i,t) + pmarg(i,t)*tmg(i,"d",t))
                       *  (1+tVat(i,"d",t)) ;

*  T-5 -- Aggregate Armington demand

xateq(i,t)$(ts(t) and iarm(i))..
   xat(i,t) =e= sum(aa, xa(i,aa,t)) ;

*  T-6 -- Domestic demand for domestic goods

xddeq(i,t)$(ts(t) and idom(i))..
   xd(i,t) =e= ad(i,t)*(gammamd(i,t)**sigmam(i))
            *  xat(i,t)*(pa(i,t)/pda(i,t))**sigmam(i) ;

*  T-7 -- Domestic demand for imported goods

xmeq(i,t)$(ts(t) and iimp(i))..
   xm(i,t) =e= am(i,t)*(gammamm(i,t)**sigmam(i))
            *  xat(i,t)*(pa(i,t)/pma(i,t))**sigmam(i) ;

*  T-8 -- Basic Armington price

paeq(i,t)$(ts(t) and iarm(i))..
   pa(i,t)**(1-sigmam(i)) =e=
         ad(i,t)*(gammamd(i,t)**(sigmam(i)-1))*pda(i,t)**(1-sigmam(i))
       + am(i,t)*(gammamm(i,t)**(sigmam(i)-1))*pma(i,t)**(1-sigmam(i)) ;

*  Tax definitions

tFacEq(a,fp,t)$(ts(t) AND SAM(fp,a))..
   tFac(a,fp,t)=e= (tFac0(a,fp,t) + (tFacD0(t) + tFacD1(a,t) + tFacD2(fp,t)))
                     * tFacM0(t) * tFacM1(a,t) * tFacM2(fp,t)
                     * (tfacMLab(t)$l(fp)
                     + tfacMCap(t)$cap(fp)
                     + tfacMlnd(t)$lnd(fp)) * tMall(t)
                     ;

tpsbEq(a,t)$ts(t)..
   tpsb(a,t)=e= (tpsb0(a,t) + (tpsbD0(t) + tpsbD1(a,t)))
                     * tpsbM0(t) * tpsbM1(a,t) ;

tPrdEq(a,t)$ts(t)..
   tPrd(a,t)=e= (tPrd0(a,t) + (tPrdD0(t) + tPrdD1(a,t)))
                     * tPrdM0(t) * tPrdM1(a,t) ;

tExpEq(i,t)$ts(t)..
   tExp(i,t)=e= (tExp0(i,t) + (tExpD0(t) + tExpD1(i,t)))
                     * tExpM0(t) * tExpM1(i,t)  ;

tImpEq(i,t)$ts(t)..
   tImp(i,t)=e= (tImp0(i,t) + (tImpD0(t) + tImpD1(i,t)))
                     * tImpM0(t) * tImpM1(i,t)  ;

tEmiEq(em,aa,t)$ts(t)..
   tEmi(em,aa,t)=e= (tEmi0(em,aa,t) + (tEmiD0(t) + tEmiD1(em,t) + tEmiD2(aa,t)))
                     * tEmiM0(t) * tEmiM1(em,t) * tEmiM2(aa,t) ;

tPitEq(h,t)$ts(t)..
   tPit(h,t)=e= (tPit0(h,t) + (tPitD0(t) + tPitD1(h,t)))
                    * tDr(t) * tPitM0(t) * tPitM1(h,t)* tMall(t);

tCitEq(entr,t)$ts(t)..
   tCit(entr,t)=e= (tCit0(entr,t) + (tCitD0(t) + tCitD1(entr,t)))
                    * tDr(t) * tCitM0(t) * tCitM1(entr,t) * tMall(t);

tVatEq(i,n,t)$ts(t)..
   tVat(i,n,t)=e= (tVat0(i,n,t) + (tVatD0(t) + tVatD1(i,t) + tVatD2(n,t)))
                     * tVatM0(t) * tVatM1(i,t) * tVatM2(n,t) * tMall(t) ;

tPafEq(i,aa,t)$ts(t)..
   tPaf(i,aa,t) =e= (tPaf0(i,aa,t) + (tPafD0(t) + tPafD1(i,t) + tPafD2(aa,t)))
                     * tPafM0(t) * tPafM1(i,t) * tPafM2(aa,t)  ;


*  T-9 -- End-user Armington price

pafeq(i,aa,t)$(ts(t) and iarm(i) and not emsrc(i))..
   paf(i,aa,t) =e= (1 + tPaf(i,aa,t)) * pa(i,t) ;

paf1eq(emSrc,aa,t)$(ts(t))..
   paf(emSrc,aa,t) =e= (1 + tPaf(emSrc,aa,t)) * pa(emSrc,t)
                +   sum(em, tEmi(em,aa,t) * emical(t)* chiEmi(em,emSrc,aa,t)
                * rhoEmi(em,emSrc,aa) * phiEmi(em,emSrc,aa)) / chiPA(emSrc) ;

*  T-10 -- Domestic supply of domestic goods

xdseq(i,t)$(ts(t) and idom(i))..
   0 =e= (xd(i,t)*ps(i,t)**sigmax(i) - gd(i,t)*(xs(i,t) - delst(i,t))*(gammaxd(i,t)**sigmax(i))*(pd(i,t)**sigmax(i)))$(sigmax(i) ne inf)
      +  (gammaxd(i,t)*pd(i,t) - ps(i,t))$(sigmax(i) eq inf) ;

*  T-11 -- Supply of export goods

edseq(i,t)$(ts(t) and iexp(i))..
   0 =e= (xe(i,t)*ps(i,t)**sigmax(i) - ge(i,t)*(xs(i,t) - delst(i,t))*(gammaxe(i,t)**sigmax(i))*(pe(i,t)**sigmax(i)))$(sigmax(i) ne inf)
      +  (gammaxe(i,t)*pe(i,t) - ps(i,t))$(sigmax(i) eq inf) ;

*  T-12 -- Revenue equation

pseq(i,t)$(ts(t) and iact(i))..
   0 =e= (ps(i,t)**(1+sigmax(i)) - (gd(i,t)*(gammaxd(i,t)**(1+sigmax(i)))*pd(i,t)**(1+sigmax(i))
      +                             ge(i,t)*(gammaxe(i,t)**(1+sigmax(i)))*pe(i,t)**(1+sigmax(i))))$(sigmax(i) ne inf)
      +  (xs(i,t) - (xd(i,t) + xe(i,t) + delst(i,t)))$(sigmax(i) eq inf) ;

*  T-13 -- Domestic price of exports

peeq(i,t)$(ts(t) and iexp(i))..
   chiPE(i)*pe(i,t)*(1 + tExp(i,t)) + pmarg(i,t)*tmg(i,"x",t) =e= er(t)*chiPWE(i)*pwe(i,t) ;

*  T-14 -- World price of exports

pweeq(i,t)$(ts(t) and iexp(i))..
    0 =e= (pwe(i,t) - gammaPWE(i,t)*pwerow(i,t))$(etae(i) eq inf)
       +  (xe(i,t)*pwe(i,t)**etae(i) - chie(i,t)*(gammaPWE(i,t)**etae(i))*pwerow(i,t)**etae(i))$(etae(i) ne inf) ;

*  T-15 -- World price of imports

pwmeq(i,t)$(ts(t) and iimp(i))..
   0 =e= (pwm(i,t) - pwmrow(i,t))$(omegam(i) eq inf)
      +  ((xm(i,t) +mdelst(i,t))*pwmROW(i,t)**omegam(i) - chim(i,t)*pwm(i,t)**omegam(i))$(omegam(i) ne inf) ;

* ----------------------------------------------------------------------------
*
*  Labor market equilibrium
*
* ----------------------------------------------------------------------------

*  L-1 -- Aggregate labor supply for skill level l

lsTeq(l,t)$ts(t)..
   0 =e= (lsT(l,t) - chiLs(l,t)*v_chiLs(l,t)*(wage(l,t)/pnum(t))**epsL(l))$(epsL(l) ne inf)
      +  (wage(l,t) - pnum(t))$(epsL(l) eq inf) ;



*  Gender differential in labor supply
FLFPeq(fl,t)$ts(t)..  FLFP(fl,t) =e= lsT(fl,t)/pop("p1564",t)*3 ;

FLFPTotEq(t)$ts(t)..  FLFPTot(t) =e= SUM(l$(not ml(l)),lsT(l,t))/pop("p1564",t)*3.1;

MLFPTotEq(t)$ts(t)..  MLFPTot(t) =e= SUM(l$(ml(l)),lsT(l,t))/pop("p1564",t)*1.15;
*_______________________________________________________________________________
chiLseq(l,t)$ts(t) ..
v_chiLs(l,t) =e=  1
*                 *(culIndex(l,t)/culIndex(l,t-1))**epsCul(l,t)
*                 *((SUM((aasoc,ihea),xa(ihea,aasoc,t))
*                   /SUM((aasoc,ihea),xa(ihea,aasoc,t-1)))**epsHea(l,t))
*                  *(1$(ord(t)<11) +((SUM((aasoc,iedu),xa(iedu,aasoc,t-9))
*                   /SUM((aasoc,iedu),xa(iedu,aasoc,t-10)))**epsEdu(l,t))$(ord(t)>10))
                  * (v_chiLs(l,t-1)*pop("p1564",t)/pop("p1564",t-1));

*  L-2 -- Sectoral labor supply

lseq(a,l,t)$(ts(t) and gammal(a,l,t) ne 0)..
   0 =e= (ls(a,l,t)*phiw(a,l,t)*(phiw(a,l,t)*wage(l,t))**omegal(l) -
            gammal(a,l,t)*lsT(l,t)*swage(a,l,t)**omegal(l))$(omegal(l) ne inf)
      +  (swage(a,l,t) - phiw(a,l,t)*wage(l,t))$(omegal(l) eq inf) ;

*  L-3 -- Definition of aggregate wage

wageeq(l,t)$ts(t)..
*   wage(l,t)*lsT(l,t) =e= sum(a, swage(a,l,t)*ls(a,l,t)) ;
*respect additivity
  lsT(l,t) =e= sum(a, ls(a,l,t)) ;

*DP modif for factor tax
pswageeq(a,l,t)$(ts(t) and gammal(a,l,t) ne 0)..
   pswage(a,l,t) =e= swage(a,l,t) * (1 + tFac(a,l,t));

*-HD: Introduce real factor tax

rtFacEQ(a,l,t)$(ts(t) AND sum(is$mapftax(l,is),sam(is,a)))..
  rtFac(a,l,t)*pgdpmp(t) =e= tFac(a,l,t) ;

*  L-4 -- Labor market equilibrium condition

swageeq(a,l,t)$(ts(t) and gammal(a,l,t) ne 0)..
   ls(a,l,t) =e= xf(a,l,t) ;

* ----------------------------------------------------------------------------
*
*  Land market equilibrium
*
* ----------------------------------------------------------------------------

*  A-1 -- Total land supply

tlandeq(lnd,t)$(ts(t) and ifLand)..
   0 =e= (tland(lnd,t) - (dmgAtLand(lnd,t) * atland(lnd,t))*(ptland(lnd,t)/pnum(t))**omegatl(lnd))$(omegatl(lnd) ne inf)
      +  (ptland(lnd,t) - pnum(t))$(omegatl(lnd) eq inf) ;

*  A-2 -- Sectoral price of land

plandeq(a,lnd,t)$(ts(t) and alands(a,lnd,t) ne 0)..
   0 =e= (xf(a,lnd,t)  - alands(a,lnd,t)*tland(lnd,t)*(pland_pt(a,lnd,t)/ptland(lnd,t))**omegat(lnd))$(omegat(lnd) ne inf)
      +  (pland_pt(a,lnd,t) - ptland(lnd,t))$(omegat(lnd) eq inf) ;

*  A-3 -- Average price of land

ptlandeq(lnd,t)$(ts(t) and ifLand)..
    tland(lnd,t) =e= sum(a, xf(a,lnd,t)) ;

* ----------------------------------------------------------------------------
*
*  Capital market equilibrium in comparative static
*
* ----------------------------------------------------------------------------

*  K-1 -- Aggregate capital supply in non-vintage version of the model

kapsCSeq(t)$(ts(t) and ifComp and epsK ne inf)..
   0 =e= (kaps(t) - chiKs(t)*(trent(t)/pnum(t))**epsK)$(epsK ne inf)
      +  (trent(t) - pnum(t))$(epsK eq inf) ;

*  K-2 -- Sectoral allocation of capital in the comp. stat. version of the model

ksCSeq(a,v,t)$(ts(t) and not ifVint and gammak(a,t) ne 0)..
   0 =e= (kd(a,v,t)*trent(t)**omegak - gammak(a,t)*Kaps(t)*pk(a,v,t)**omegak)$(omegak ne inf)
      +  (pk(a,v,t) - trent(t))$(omegak eq inf);

*  K-3 -- Aggregate return to capital in the comp. stat. version of the model

trentCSeq(v,t)$(ts(t) and not ifVint)..
   trent(t)*kaps(t) =e= sum(a, pk(a,v,t)*kd(a,v,t)) ;

* ----------------------------------------------------------------------------
*
*     Capital market equilibrium in dynamics
*
* ----------------------------------------------------------------------------

*  K-5 -- Calculate the capital output ratio for old capital

kxrateq(a,v,t)$(ts(t) and ifVint and vOld(v) and ak(a,v,t) ne 0)..
   kxrat(a,t)*xpv(a,v,t) =e= kd(a,v,t) ;

*  K-6 -- Determine the equilbrium rate of return on old capital
*         in declining sectors, it cannot exceed 1.

rrateq(a,t)$(ts(t) and ifVint and ak(a,"Old",t) ne 0)..
   rrat(a,t) =l= (kxrat(a,t)*xp(a,t)
              /  (sum(v, kd(a,v,t-1))*power(1-depr(t), gap(t))))**(1/InvElas(a)) ;
              
*rrateq(a,t)$(ts(t) and ifVint and ak(a,"Old",t) ne 0)..
*   rrat(a,t) =l= (kxrat(a,t)*xp(a,t))
*              / oldShr(a)  ;

*  K-7 -- Aggregate capital market equilibrium
*            --> essentially determines 'new' rent, or trent

trenteq(t)$(ts(t) and ifVint)..
   kaps(t) =e= sum((a,v), kd(a,v,t))  ;

*  K-8 -- Set the vintage rental rates

pkeq(a,v,t)$(ts(t) and ifVint and ak(a,"Old",t))..
   pk(a,v,t) =e= trent(t)*rrat(a,t) ;

*  K-9 -- Old output cannot exceed total output
*           --> essentially determines old output

xpOldeq(a,v,t)$(ts(t) and vOld(v) and ifVint and aact(a))..
   xpv(a,v,t)*kxrat(a,t) =e= (sum(vp, kd(a,vp,t-1))*power(1-depr(t), gap(t)))
                          *  rrat(a,t)**InvElas(a) ;

display  gap;
*  K-10 -- Output aggregation

*  In comparative static mode, the following equation sets old output to total output
*  In dynamic mode, this essentially determines the new vintage output

xpNeweq(a,t)$(ts(t) and aact(a))..
   xp(a,t) =e= sum(v, xpv(a,v,t)) ;


* ----------------------------------------------------------------------------
*
*     Flexible capital account
*
* ----------------------------------------------------------------------------
*   kstockeeq(t)   Anticipated end-of-period capital stock
*   roreq(t)       Net aggregate rate of return to capital
*   rorceq(t)      Cost adjusted rate of return to capital
*   roreeq(t)      Expected rate of return to capital
*   devROReq(t)    Change in rate of return
*   grKeq(t)       Anticipated growth of the capital stock
*   savfeq(t)      Capital account closure
*$ontext
*Anticipated end-of-period capital stock
kstockeeq(t)$(ts(t))..
   kstocke(t) =e= (1-depr(t))*kstock(t) + sum(inv, xfd(inv,t)) ;
*   kstocke(t) =e= (1-depr(t))*kstock(t) + sum(inv, xfd(inv,t))  + sum(ginv, xfd(ginv,t));

*Net aggregate rate of return to capital
roreq(t)$(ts(t))..
   ror(t) =e= kapY(t) / kstock(t) ;
*   ror(t) =e= sum(entr,chikEntr(entr,t))*kapY(t) / kstock(t) ;

*Cost adjusted rate of return to capital
rorceq(t)$(ts(t))..
*   rorc(t) =e= ror(t) - depr(t) ;
   rorc(t) =e= ror(t)/sum(inv, pf(inv,t)) - depr(t) ;

*Expected rate of return to capital
roreeq(t)$(ts(t))..
   rore(t) =e=(rorc(t)*(kstocke(t)/kstock(t))**(-epsRor(t)))
*   rore(t) =e= (rorc(t))
                    $(ifcapFlexGTAP or ifcapFix or ifcapRFix or ifcapFlexA1 or ifcapFlexA3)
                       +  ((ror(t)/sum(inv,pf(inv,t))+(1-depr(t)))/(1+DebtIntD(t)/100) - 1)$(ifcapFlexUSAGE)
                       ;
* Change in rate of return
devRoReq(t)$(ts(t) and ifcapFlexUSAGE)..
   devRoR(t) =e= rore(t) - rord(t) - rorg(t) ;

*Anticipated growth of the capital stock
grKeq(t)$(ts(t))..
*   sum(inv, xfd(inv,t)) =e= kstock(t)*(grK(t) + depr(t)) ;
   sum(inv, xfd(inv,t))+ sum(ginv, xfd(ginv,t)) =e= kstock(t)*(grK(t) + depr(t)) ;

phisfeq(t)$ts(t) ..
*   phisf(t) =e= gammasf(t) * [((1+trent(t))/(1+retrow(t))) ** eta1(t)] * [((1+ggdppc(t))/(1+ggdppcrow(t))) ** eta2(t)] ;
   phisf(t) =e= gammasf(t) * [((1+trent(t))/(1+retrow(t))) ** eta1(t)] * [((1+ggdppc(t))/(1+ggdppcrow(t))) ** eta2(t)] ;
**   phisf(t) =e= gammasf(t) * [((1+trent(t))/(1+retrow(t))) * ((1+ggdppc(t))/(1+ggdppcrow(t)))] ** eta1(t) ;

*Capital account closure
$macro logasc(t) ((grKMax(t) - grKTrend(t))/(grkTrend(t) - grKMin(t)))
savfeq(t)$(ts(t))..
   0 =e= (savf(t) - savfBar(t))$(ifcapFix)
      +  (savf(t) - savfRat(t)*gdpmp(t)/er(t))$(ifcapRFix)
      +  (savf(t) - phisf(t)*savftilde(t))$(ifcapFlexA1)
      +  (savf(t) - phisf(t)*savftilde1(t))$(ifcapFlexA3)
*      +  (riskPrem(t)*rore(t) - rorg(t))$(ifcapFlexGTAP)
      +  (savf(t)- riskPrem(t)*(rore(t)/rorg(t))**epssavf(t))$(ifcapFlexGTAP)
      +  (grk(t) - (grKMax(t)*exp(chigrK(t)*devRoR(t)) + grKMin(t)*logasc(t))
                   /  (exp(chigrK(t)*devRoR(t)) + logasc(t)))$(ifcapFlexUSAGE)
      ;
*add yf(ginv)?
 savftildeeq(t)$(ts(t) and ifcapFlexA3) ..
*    savftilde(t) =e= invtilde(t) ;
    savftilde1(t) =e= {[invtilde(t) -  sum(h, savh(h,t)) - savg(t) - sum(entr, savEntr(entr,t))
                    + sum(i, chiPS(i)*ps(i,t)*delst(i,t) - er(t)*pwm(i,t)*(1+tImp(i,t))*mdelst(i,t))
                    + sum(adpinv$map_adpInv('i-invt',adpinv),yf(adpinv,t))]/er(t)};

invtildeeq(t)$ts(t) ..
    invtilde(t) =e= [(ror(t)/rorg(t)) ** (1/vareps(t)) + depr(t) - 1] * kstock(t) ;

savfGDPeq(t)$ts(t)..
   savfGDP(t)    =e= (savf(t)*er(t) )/gdpmp(t); 

* ----------------------------------------------------------------------------
*
*  Macro identities
*
* ----------------------------------------------------------------------------

*  M-1 -- Nominal aggregate stock building

tdelsteq(t)$(ts(t) and ifDelSt)..
   tdelst(t) =e= sum(i, chiPS(i)*ps(i,t)*delst(i,t) + er(t)*pwm(i,t)*(1+tImp(i,t))*mdelst(i,t)) ;

*  M-2 -- Real aggregate stock building

rtdelsteq(t,t0)$(ts(t) and ifDelSt)..
   rtdelst(t) =e= sum(i, chiPS(i)*ps(i,t0)*delst(i,t)
               + er(t0)*pwm(i,t0)*(1+tImp(i,t0))*mdelst(i,t)) ;

*  M-3 -- Stock building aggregate price index

pdelsteq(t)$(ts(t) and ifDelSt)..
   pdelst(t)*rtdelst(t) =e= tdelst(t) ;

*  M-4 -- Nominal aggregate exports

totexpeq(t)$ts(t)..
   totexp(t) =e= er(t) * sum(i, chiPWE(i)*pwe(i,t) * xe(i,t)) ;

*  M-5 -- Real aggregate exports

rtotexpeq(t,t0)$ts(t)..
   rtotexp(t) =e= er(t0) * sum(i, chiPWE(i)*pwe(i,t0) * xe(i,t)) ;

*  M-6 -- Aggregate export price index

pexpeq(t)$ts(t)..
   rtotexp(t)*pexp(t) =e= totexp(t) ;

*  M-7 -- Nominal aggregate imports

totimpeq(t)$ts(t)..
   totimp(t) =e= er(t) * sum(i, pwm(i,t) * (xm(i,t) + mdelst(i,t))) ;

*  M-8 -- Real aggregate imports

rtotimpeq(t,t0)$ts(t)..
   rtotimp(t) =e= er(t0) * sum(i, pwm(i,t0) * (xm(i,t) + mdelst(i,t))) ;

*  M-9 -- Aggregate import price index

pimpeq(t)$ts(t)..
   rtotimp(t)*pimp(t) =e= totimp(t) ;

*  M-10 -- Nominal GDP at market price

gdpmpeq(t)$ts(t)..
   gdpmp(t) =e= sum(fd, yf(fd,t)) + tdelst(t) + totexp(t) - totimp(t) ;

*  M-11 -- Real GDP at market price

rgdpmpeq(t)$ts(t)..
   rgdpmp(t) =e= sum(fd, xfd(fd,t)) + rtdelst(t) + rtotexp(t) - rtotimp(t) ;

*  M-12 -- GDP at market price deflator

pgdpmpeq(t)$ts(t)..
   rgdpmp(t)*pgdpmp(t) =e= gdpmp(t) ;

*  M-13 -- Real per capita GDP

rgdppceq(t)$ts(t)..
   rgdppc(t)*pop("ptotl",t) =e= rgdpmp(t) ;

*  M-14 -- Growth in real per capita GDP

ggdppceq(t)$ts(t)..
   rgdppc(t) =e= rgdppc(t-1)*power(1 + ggdppc(t), gap(t)) ;

*  M-15 -- Nominal GDP at factor cost

gdpfceq(t)$ts(t)..
   gdpfc(t) =e= sum((a,lnd), pland_pt(a,lnd,t)*xf(a,lnd,t))
             +  sum((a,l), pswage(a,l,t)*xf(a,l,t))
             +  sum((a,v), pk_pt(a,v,t)*kd(a,v,t)) ;

*  M-16 -- Real GDP at factor cost

rgdpfceq(t,t0)$ts(t)..
   rgdpfc(t) =e= sum((a,lnd), pland_pt(a,lnd,t0)*lambdat(a,lnd,t)*xf(a,lnd,t))
              +  sum((a,l), pswage(a,l,t0)*(dmgLambdaL_HH(a,l,t) * dmgLambdaL(a,l,t) * lambdal(a,l,t))*xf(a,l,t))
              +  sum((a,v), pk_pt(a,v,t0)*lambdaxfac("ksk",a,v,t)*kd(a,v,t)) ;

*  M-17 -- GDP at factor cost deflator

pgdpfceq(t)$ts(t)..
   pgdpfc(t)*rgdpfc(t) =e= gdpfc(t) ;

*  M-18 -- Real GDP shares (gov and inv)

rshrGDPeq(f,t)$ts(t)..
   rshrGDP(f,t)*rgdpmp(t) =e= xfd(f,t) ;

*  M-19 -- Nominal GDP shares (gov and inv)

nshrGDPeq(f,t)$ts(t)..
   nshrGDP(f,t)*gdpmp(t) =e= yf(f,t) ;

*  M-20 -- Choice of domestic numeraire

pnumeq(t)$ts(t)..
   pnum(t) =e= pgdpmp(t) ;

*  M-21 -- Walras law

walraseq(t)$ts(t)..
   walras - savf(t) =e= sum(i, chiPWE(i)*pwe(i,t)*xe(i,t) - pwm(i,t)*(xm(i,t) +mdelst(i,t)))
           + sum((inst,row,instp)$mapinst(row,instp),
                   transfers(inst,instp,t)- transfers(instp,inst,t))/er(t)
           +  SUM(instf, debtNew(instf,t) - debtPay(instf,t))/er(t)
          ;

* ----------------------------------------------------------------------------
*
*  Emissions module
*
* ----------------------------------------------------------------------------

*  E-1 -- Emissions linked to the use of commodities

emiCommeq(em,emSrc,aa,t)$(ts(t) and rhoEmi(em,emSrc,aa) ne 0)..
   emiComm(em,emSrc,aa,t) =e= emical(t)*chiEmi(em,emSrc,aa,t)*rhoEmi(em,emSrc,aa)*xa(emSrc,aa,t) ;

*  E-2 -- Emisssions linked to the use of factors of production (land, capital, etc.)
*  !!!! will have to be modified if we include land

emiFacteq(em,fp,a,t)$(ts(t) and rhoEmiFac(em,fp,a) ne 0)..
   emiFact(em,fp,a,t) =e= emical(t)*chiEmiFac(em,fp,a,t)*rhoEmiFac(em,fp,a)*xf(a,fp,t) ;

*  E-2a -- Emisssions linked to land use change

emiLUCFeq(em,a,t)$(ts(t) AND sum(lnd,rhoEmiLnd(em,lnd,a)))..
   emiLUCF(em,a,t) =e= sum(lnd,-rhoEmiLnd(em,lnd,a)*(xf(a,lnd,t)-xf(a,lnd,t-1)));

*  E-3 -- Emissions linked to the volume of production (e.g. municipal waste)

emiProdeq(em,a,t)$(ts(t) and rhoEmiXP(em,a) ne 0)..
   emiXP(em,a,t) =e= emical(t)*chiEmiXP(em,a,t)*rhoEmiXP(em,a)*xp(a,t) ;


emiSecAeq(em,aa,t)$ts(t)..
   emiSecA(em,aa,t) =e= sum(emSrc, emiComm(em,emSrc,aa,t))
                     +  sum((fp,a)$sameas(aa,a), emiFact(em,fp,a,t))
                     +  sum(a$sameas(aa,a),emiXP(em,a,t))
                     +  sum(a$sameas(aa,a),emiLUCF(em,a,t))
                 ;


rtEmiEQ(em,aa,t)$ts(t)..
    rtEmi(em,aa,t) *pgdpmp(t)  =e= tEmi(em,aa,t);

Parameter emSwitch /1/;


emRevDef(em,aa,t)$ts(t)..
      emSwitch*emRev(em,aa,t) =E= -emBuy(em,aa,t)*tEmi(em,aa,t)*emSwitch;

emConstn(em,aa,t)$ts(t)..
      emSwitch*emiSecA(em,aa,t) =E= (emPerm(em,aa,t) +emBuy(em,aa,t))*emSwitch ;

embuyConst(em,t)$ts(t)..
      emSwitch*SUM(aa,embuy(em,aa,t)) =E= emSupply(em,t)*emSwitch;

emTotDef(em,t)$ts(t)..
      emiTot(em,t) =E=  SUM(aa,emBuy(em,aa,t) +emPerm(em,aa,t)) ;

*  E-4 -- Total emissions
emiToteq(em,t)$ts(t)..
   emiTot(em,t) =e= sum(aa,emiSecA(em,aa,t)) ;

*  E-5 -- Total emissions of GHG in Ceq

emiGHGeq(t)$ts(t)..
   emiGHG(t) =e= sum(ghg, gwp(ghg)*emiTot(ghg,t)) ;


* ----------------------------------------------------------------------------
*
*  CC impact channels
*
* ----------------------------------------------------------------------------

*- TFP damages
dmgTfpActEq(a,t)$(ifDmg1  and ts(t))..
dmgTfpAct(a,t) =e=  { [1 - sum(mth, eta(a,mth,t)) ] * [1 + sum(mth, beta(a,mth)* precipD(mth,t))]}* dmgShftTFP(t) ;
*dmgTfpAct(a,t) =e=   [1 - sum(mth, eta(a,mth,t)) ] * [1 + sum(mth, beta(a,mth)* precipD(mth,t))];

*-human health : add to labor productivity effect!-------------------------------------------------------------------
dmgLambdaL_HHEq(a,l,t)$(ifDmg1  and ts(t))..
      dmgLambdaL_HH(a,l,t) =e= (1+dmgShftLambdaL_HH(t) * (tempD(t)*dmgLambdaL_HH1(a,l,t))) ;

*-labor productivity-------------------------------------------------------------------
dmgLambdaLEq(a,l,t)$(ifDmg1  and ts(t))..
      dmgLambdaL(a,l,t) =e= (1+(dmgLambdaL1(a,l)*tempD(t) + dmgLambdaL2(a,l)*tmaxD(t))) ;


*-SLR land supply changes with temperature-------------------------------------------------------------------
dmgAtLandEq(lnd,t)$(ifDmg1  and ts(t))..
      dmgAtLand(lnd,t) =e=  (1-dmgShftLand(t)*dmgShftLand1(t)*(  dmgAtLand0(lnd,t)$slrD(t)
                                               + dmgAtLand1(lnd,t)*slrD(t)
                                               + dmgAtLand2(lnd,t)*slrD(t)*slrD(t)
                                               + dmgAtLand3(lnd,t)*slrD(t)*slrD(t)*slrD(t) )) ;

*-Tourism Export Demand -----------------------------------------------------------------

dmgChieEq(i,t)$(ifDmg1  and ts(t))..
dmgChie(i,t) =e=  (1+ dmgShftChie(t)*(dmgChie1(i,t) * tempD(t)
                    + dmgChie2(i,t) * tempD(t) * tempD(t))) ;

*- Capital Stock------------------------------------------------------------------
dmgDeprEq(t)$(ifDmg1  and ts(t))..
        dmgDepr(t) =e= 1 - dmgShftDepr(t)*
                 ( dmgdepr0(t)$slrD(t)
                 + dmgdepr1(t)*slrD(t)
                 + dmgdepr2(t)*slrD(t)*slrD(t)
                 + dmgdepr3(t)*slrD(t)*slrD(t)*slrD(t) ) ;
*-Energy demand-------------------------------------------------------------------
*-demand shift!
dmgLambdaEhEq(h,i,k,t)$(ifDmg  and ts(t))..
dmgLambdaEh(h,i,k,t)  =e= (1 + dmgShftLambdaEh(t)*( dmgLambdaEh1(h,i,k,t) * tempD(t) + dmgLambdaEh0(h,i,k,t) ));

*-adaptation capital damage shifter

Equation
xfdInvEq(adpinv,t)
;

xfd.l(adpinv,t) = 0 ;

xfdInvEq(adpinv,t)$ts(t)..

 xfd(adpinv,t) =e= adpInvShr(adpinv,t) * sum(f$map_adpInv(f,adpinv),xfd(f,t)) ;


dmgShftTFPEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftTFP(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftTFP(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t)  ;

*lmb when you activate, it creates an imbalance of 1
dmgShftLambdaL_HHEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftLambdaL_HH(t0)*sum((ihea,aa),xa(ihea,aa,t0))**rhodmg(t) =e= dmgShftLambdaL_HH(t) * sum((ihea,aa),xa(ihea,aa,t))**rhodmg(t)  ;
*    dmgShftLambdaL_HH(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftLambdaL_HH(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t)  ;

dmgShftLambdaLEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftLambdaL(t0)*sum((iedu,aa),xa(iedu,aa,t0))**rhodmg(t) =e= dmgShftLambdaL(t) * sum((iedu,aa),xa(iedu,aa,t))**rhodmg(t);
*    dmgShftLambdaL(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftLambdaL(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t);

dmgShftLandEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftLand(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftLand(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t)  ;

dmgShftChieEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftChie(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftChie(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t)  ;


dmgShftLambdaEhEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftLambdaEh(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftLambdaEh(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t)  ;

dmgShftDeprEq(t,t0)$(ifDmg  and ts(t))..
    dmgShftDepr(t0)*sum(adpinv,xfd(adpinv,t0))**rhodmg(t) =e= dmgShftDepr(t) * sum(adpinv,xfd(adpinv,t))**rhodmg(t)  ;

* ----------------------------------------------------------------------------
*
*  Dynamics
*
* ----------------------------------------------------------------------------

*  Capital accumulation in dynamic scenarios when gap(t) > 1
*  First equation essentially determines the endogenous growth of investment
*  Second equation determines the actual capital stock

*  G-1 -- Investment growth factor

*invGFacteq(inv,t)$(ts(t) and gap(t) gt 1)..
invGFacteq(t)$(ts(t) and gap(t) gt 1)..
   invGFact(t)*(([sum(inv,xfd(inv,t))+ sum(ginv,xfd(ginv,t))]/[sum(inv,xfd(inv,t-1))+ sum(ginv,xfd(ginv,t-1))])**(1/gap(t)) - 1 + depr(t)) =e= 1 ;

*  G-2 -- Capital accumulation

kstockeq(t)$(ts(t) and gap(t) gt 1)..
   kstock(t) =e= dmgDepr(t) * (kstock(t-1) - invGFact(t)*[sum(inv,xfd(inv,t-1))+ sum(ginv,xfd(ginv,t-1))])*power(1-depr(t), gap(t))
              +   invGFact(t)*[sum(inv,xfd(inv,t-1))+ sum(ginv,xfd(ginv,t-1))] ;


*  G-3 -- Capital normalization equation

kapseq(t,t0)$(ts(t) and not ifComp)..
   kaps(t)/kstock(t) =e= kaps(t0)/kstock(t0) ;

*  G-4 -- Productivity factor in sectors with calibrated productivity

lambdaleq(a,l,t,t0)$(ts(t))..
   lambdal(a,l,t) =e= (chiLambdaLA(a,l,t)*chiLambdaL(l,t)) * [lambdal(a,l,t0)
*                  * ((SUM((aasoc,ihea),xa(ihea,aasoc,t))
*                  / SUM((aasoc,ihea),xa(ihea,aasoc,t0)))**epsHea(l,t))
*                  * (1$(ord(t)<11) +((SUM((aasoc,iedu),xa(iedu,aasoc,t-9))
*                  / SUM((aasoc,iedu),xa(iedu,aasoc,t-10)))**epsEdu(l,t))$(ord(t)>10))
                  ] ;

awageEq(t)$ts(t)..
    awage(t)*sum(l,lsT(l,t)) =e= sum(l,wage(l,t)*lsT(l,t)) ;


unempeq(t)$ts(t)..
    unemp(t)  =l= pop("P1564",t) - sum(l,lsT(l,t)) ;


display acal;


model cge /
   unempeq.awage, awageeq.unemp,
   ndeq, vaveq, pxveq.pxv, pxeq, ppeq,
   landdeq, lab1eq, kseeq, pvaeq.pva,
   kskeq, xnrgpeq, pkseeq.pkse, kdeq, kdToteq, lab2eq, pkskeq.pksk, pk_ptEQ.pk_pt,
   ldeq, plab1eq.plab1, plab2eq.plab2
   xap1eq, pndeq.pnd, xap2eq, pnrgpeq.pnrgp,
   xeq, xpeq, peq, xseq, ElecMixEq,

   kapyeq, yheq, ginieq, apseq, deprateEq, hhTreq, yfheq, savheq,
   tFacEq, rtFacEq, tpsbEq, tPrdEq, tExpEq, tImpEq, tEmiEq, rtEmiEQ, tPITEq,
   tCITEq, tVatEq, tPafEq,
   ygftxeq, ygpsbeq, ygetxeq, ygptxeq,ygmtxeq, yghtxeq, ygatxeq, ygctxeq,
ygotxeq,
   ygoveq, gtaxeq, govTreq,
   savgeq,
   rsgeq,
Obaleq, ObalGDPeq,
ygGDPeq, ygTGDPeq,ExpGDPeq,

*ygEmieq,
   entrYeq, savEntreq, entrTreq,

   dtransferseq, rowtransferseq, inveq,
   popAgeEq, BirthEq, popEq ,
*   brateEq,
   hpopeq, consScaleeq, xkfeq, uheq, xkfshreq, pfheq,
   xkfnnrgeq, xkfnrgeq, pkfeq, xakfnnrgeq, xakfnrgeq, pkfnnrgeq, pkfnrgeq,

   xfnnrgeq, xfnrgeq, pfeq, xafnnrgeq,xafnrgeq, pfnnrgeq, pfnrgeq,
*   xfnnrgeq1,

   xmargeq, xamrgeq, pmargeq, yfeq,

   pmaeq, pdaeq, xateq, xddeq, xmeq, paeq.pa, pafeq,paf1eq,
   pseq, xdseq, edseq, peeq,
   pweeq, pwmeq,

   lsTeq, lseq, wageeq, pswageeq, swageeq, chiLseq,  FLFPeq , FLFPTotEq ,MLFPTotEq ,
   tlandeq,

plandeq, pland_ptEQ, ptlandeq,

   kapsCSeq, ksCSeq, trentCSeq,

   kxrateq, rrateq.rrat, trenteq, pkeq, xpOldeq, xpNeweq,
   kstockeeq, roreq, rorceq, roreeq, devRoReq, grKeq, savfeq,savfGDPeq,
   phisfeq,savftildeeq,invtildeeq
   tdelsteq, rtdelsteq, pdelsteq, totexpeq, rtotexpeq, pexpeq, totimpeq, rtotimpeq, pimpeq,
   gdpmpeq, rgdpmpeq, pgdpmpeq, rgdppceq, ggdppceq, gdpfceq, rgdpfceq, pgdpfceq,
   rshrGDPeq, nshrGDPeq, pnumeq,

   invGFacteq, kstockeq, kapseq,lambdaleq,

   emiCommeq, emiFacteq, emiProdeq, emiToteq,emiGHGeq,

   emiSecAeq,

   emRevDef,    emConstn,    emBuyConst,
*   emTotDef,
   DebtStkDEq, DebtStkFEq, debtPayEq, debtNewEq,debtNewTEq, DebtIntFEQ, DebtIntDEQ,
   DebtStkTEq, debtGDPEQ,

   dmgTfpActEq,
   dmgLambdaL_HHEq,
   dmgLambdaLEq,
   dmgAtLandEq,
   dmgChieEq,
   dmgLambdaEhEq,
   dmgdeprEq,

   xfdInvEq,

   dmgShftTFPEq,
   dmgShftLambdaL_HHEq,
   dmgShftLambdaLEq,
   dmgShftLandEq,
   dmgShftChieEq,
   dmgShftLambdaEhEq,
   dmgShftdeprEq,

   walraseq,
   
   sectTotEq
   sectShrEq
   
*lambdaveq
*lambdaneq
lambdaxfaceq
debtinterestEQ
fiscalbalanceEQ
fiscalbalanceGDPEQ

/ ;

cge.holdfixed = 1 ;
cge.tolinfrep = 1e-5 ;


uedLosseq..
   uedLoss =e= sum((k,h,t)$(ts(t) and hs(h)),
                     xkfshr(h,k,t)*(ued(h,k,k,t) - prcElas0(h,k))*(ued(h,k,k,t) - prcElas0(h,k))) ;

model bhcal /
   uedLosseq, uedeq
/ ;
bhcal.holdfixed = 1 ;

model bhcal2 / uedeq / ;
bhcal2.holdfixed = 1 ;

incelasLosseq..
   incElasLoss =e= sum((k,h,t)$(ts(t) and hs(h)),
                     xkfshr(h,k,t)*(incElas(h,k,t) - incElas0(h,k))*(incElas(h,k,t) - incElas0(h,k))) ;

incElasC1eq..
   1 =e= sum((k,h,t)$(ts(t) and hs(h)), xkfshr(h,k,t)*incElas(h,k,t)) ;

incElasC2eq(h,k,t)$(ts(t) and hs(h) and akfact(h,k))..
   (incElas(h,k,t)-1)*(incElas0(h,k)-1) =g= 0 ;

model ehcal /
   incelasLosseq, incElasC1eq, incElasC2eq, incelaseq
/ ;


ehcal.holdfixed = 1 ;

model ehcal2 /
   incelaseq
/ ;

ehcal2.holdfixed = 1 ;
