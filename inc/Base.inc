
SET

tlast(t)        Last year of simulations
ts(t)           Simulation period
tsim(t)
is0             SAM accounts
a0(is0)         Initial activities
i0(is0)         Initial commodities

macEl           Elements of Macro data
cohorts(macEl)  Population cohorts
age             Ages /age000*age100/
ch(cohorts)     age cohorts except total
exr(macEl)      Exchange rates
is              SAM accounts
mapis(is0,is)   Mapping from base SAM to aggregate SAM
aa(is)          Armington agents
aasoc(aa)  Armington demand agents for social spendings

a(aa)           Activities
aElec(a)        Electricity activities
agr(a)          Agricultural activities
man(a)          Manufacturing activities
srv(a)          Services
anrg(a)         Energy activities
acal(a)         Activities with endogenous productivity growth
oa(aa)          Other Armington agents
fd(oa)          Final demand accounts
h(oa)           Households
hs(h)           Households with CDE calibration
f(oa)           Other final demand accounts
oax(oa)         Other Armington agents excluding households
i(aa)           Commodities
iagr(i)         Agricultural commodities
iman(i)         Manufacturing commodities
isrv(i)         Services commodities
iElec(i)        Electricity commodities
iedu(i)         Education commodities
ihea(i)         Health commodities
atour(a)        Tourism sectors
ctour(i)        Tourism sectors
e(i)            Energy commodities
in(i)           Non energy commodities
k               Final demand commodities
nrg(k)          Energy bundle
mapk(k,i)       Mapping between consumed and produced goods
fp(is)          Factors of production
l(fp)           Labor
ul(l)           Unskilled labor
sl(l)           Skilled labor
fl(l)           Female labor
ml(l)           Male labor
inst(is)        Institutions
instd(inst)        Domestic creditors
instf(inst)        Foreign creditors
instfd(inst)        Foreign + domestic creditors
mapInst(is,inst) Mapping for institutions from is to inst
entr(is)        Enterprises
cap(fp)         Capital
lnd(fp)         Land
gov(f)          Government
inv(f)          investment
ginv(f)         Government Investment
stb(is)         Stock Changes
row(is)         Rest of the world
dtx(is)         Direct taxes
ptx(is)         production taxes
stx(is)         Sales Taxes
mtx(is)         Tariffs
otx(is)         Other taxes
atx(is)         Activity taxes
ctx(is)         Carbon taxis
psb(is)         Production subsidies
etx(is)         Export taxes
ssb(is)         Subsidies
ftx(is)         Factor taxes
mapftax(fp,is)   Mapping between factors and factor taxes

vint            Capital Vintages / Old, New /
   v            Vintages          / Old, New /
   v0(v)        Initialization    / Old /
   vc(v)        Calibration       / New /
   vOld(v)      Old vintage       / Old /
   Old(v)       Old index         / Old /
   New(v)       New index         / New /

emiAa           Sectors in emission reporting
mapemi(emiAa,aa)  Mapping between Sectors in emission reporting  and SAM accounts
isRep            Aggregations for reporting
mapRep(is,isRep)    Mapping for report Aggregations
adpinv(oa)         Adaptation investments
emSrc(i)       Emission source commodities
;

*-LOAD SETS
if(ifCreateBB,
$CALL "GDXXRW i=%datF%\%BridgeFile% o=%savF%\%datFile%.gdx index=Layout!A4 MaxDupeErrors = 100"
);
$gdxin %savF%\%datFile%.gdx
$loaddc is0 a0 i0
$loaddc macEl cohorts exr
$loaddc is mapis
$loaddc aa a agr man srv anrg acal aElec
$loaddc oa fd h f
$loaddc i iagr iman isrv e iElec iedu ihea
$loaddc k nrg mapk
$loaddc fp l ul
$loaddc inst mapInst entr cap lnd
$loaddc gov inv ginv adpinv stb row
$loaddc dtx ptx stx mtx otx atx ctx psb etx ssb ftx mapftax
$loaddc emiAa mapemi isrep mapRep emSrc atour ctour ml fl

$gdxin

aasoc(h) = YES ;
aasoc(gov) = YES ;

SET
mapage(age,cohorts) mapping from ages to cohorts
/
age000*age014.PLT15
age015*age064.P1564
age065*age100.P65UP
age000*age100.PTOTL
/;

set mapv(v, vint) /
   Old.Old
   New.New
/ ;



set
   diag Diagnostic indicators about model solve
   /modStatus
   solStatus
   Walras
   /
*lmb
$ontext
   fl(l)      female labor
/
f-F_skl
f-F_nsk
/
$offtext
;

fl(l)     = YES;

Alias
(is0,js0), (is, js), (i, j), (inst, instp), (l,lp,lpp), (h,hp,hpp), (e,ep),
(aelec,aelecp), (lnd,lndp), (t,tt)
;

*- Dynamic set assignments
ch(cohorts) = yes ; ch('ptotl') = no ;
oax(oa)$(not h(oa)) = yes ;
in(i) = not e(i) ;
sl(l) = not ul(l) ;
tlast(t)$(ord(t)=card(t)) = YES ;
*fl(l) = not ml(l) ;
Parameter
    SAM0(is0,js0)       "PRP 2018, million"
    nrgPriceBase(i0)     Base Energy Prices
    macroData(macel)     Macro Data
    pop0(cohorts)        Base year population
    popAge0(tf,age)      Base year population
    hpop0(h)             Base year population by HHs
    exRates0(exr)        Base year exchange rates in Dirham per foreign units
    sam(is,js)           Final SAM
    transMat(i,k,h)      Transformation matrix
    ProdElas0(is,*)      Produuction Elasticities no vintage
    ProdElas1(is,*,vint) Produuction Elasticities for vintage
    CommElas(is,*)       Commodity elasticites
    FDElas(*)            Various other elasticites
    hhElas(k,*,h)        HH elasticities
    ActProd(is,*)        Activity elasticities
    oldShr(a)            old capital share
    sigman0(a)
    omegap0(a)
    invElas0(a)
    sigmap0(a,vint)
    sigmav0(a,vint)
    sigmaul0(a,vint)
    sigmasl0(a,vint)
    sigmak0(a,vint)
    sigmaks0(a,vint)
    sigmae0(a,vint)
    sigmas0(i)
    sigmam0(i)
    sigmax0(i)
    sigmamg0(i)
    omegam0(i)
    etae0(i)
    sigmac0(h,k)
    sigmacaa0(h,k)
    sigmacae0(h,k)
    sigmaf0(f)
    sigmafaa0(f)
    sigmafae0(f)
    epsL0(l)
    omegaL0(l)
    epsK0(vint)
    omegaK0(vint)
    omegatl0
    omegat0
    incElas0(h,k)        Income Elasticity
    prcElas0(h,k)        Price Elasticity
    popT(cohorts,t)      Population by cohorts
    ggdppcT(t)           Per capita growth assumptions
*    depr(t)              Depreciation rate
    prodTab0(a, *)       Sectoral productivity assumptions
    exProd(a,v,t)        Exogenous productivity shifter
    alphaL(a,l,t)        Additive sectoral wedge for labor productivity
    betaL(a,l,t)         Multiplicative sectoral factor for labor productivity
    yexo(a,t)            Exogenous yield shifter
    kprod(a,t)           Exogenous capital productivity shifter
    geP(e,a,v,t)         Energy efficiency growth in production
    geC(h,e,k,t)         Energy efficiency growth in consumption
    geF(f,e,t)           Energy efficiency growth in other final demand
    Labor(fp,a)          Labor quantities
    rshrGDPT(f,t)
    DebtStkF0            Foreign debt stock
    DebtStkD0            Domestic debt stock
    chiDebtPayD(inst)    share of creditor inst in total domestic debt payments
    chiDebtPayF(inst)    share of creditor inst in total debt payments
    chiDebtNew(inst)     share of creditor inst in total new domestic debt
    DebtIntF0            Interest on foreign debt
    DebtIntD0            Interest on domestic debt
    rhodmg(t)            damage shifter elasticity;
;

scalar
    RoR0            Average rate of return on capital
    KSAMA0          SAMA net foreign assets
    inscale         Scale factor for SAM
    pscale          Scale factor for population
    escale          Scale factor for emissions

;


$gdxin %savF%\%datFile%.gdx
$loaddc SAM0 NrgPriceBase macroData
$loaddc ProdElas0 ProdElas1 CommElas FDElas hhElas prodTab0 popAge0

*  The initial capital stock will be guess-stimated based
*  on an assumption of the initial rate of return of the
*  capital stock. It could also be calibrated to some notion
*  of the capital output ratio. And finally, one could have
*  a separate estimate of the capital stock.


exRates0(exr) = macroData(exr);

KSAMA0   = macroData("KSAMA0");
RoR0     = macroData("RoR0");
inscale  = macroData("inscale");
pscale   = macroData("pscale");
escale   = macroData("escale");

DebtStkF0  = macroData("DebtStkF0")*inscale;
DebtStkD0  = macroData("DebtStkD0")*inscale;
DebtIntF0  = macroData("DebtIntF0");
DebtIntD0  = macroData("DebtIntD0");


popAge0(t,age) = popAge0(t,age)*pscale ;

Loop(t0,
pop0(cohorts) = SUM(age$mapage(age,cohorts),popAge0(t0,age)) ;
);


sam(is,js) = inscale*sum((is0,js0)$(mapis(is0,is) and mapis(js0,js)), sam0(is0,js0)) ;

parameter sambal(is);
sambal(is) = sum(js,sam(is,js)) - sum(js,sam(js,is));
sambal(is)$(abs(sambal(is)<1E-7)) = 0;

*- assign creditors
instd(inst)$(SAM("i-debt",inst) AND NOT (sum(gov,mapinst(gov,inst) OR sum(row,mapinst(row,inst)))))  = YES;
instf(inst)$(sum((row)$mapinst(row,inst),SAM("i-debt",row)) AND NOT sum(gov,mapinst(gov,inst)))  = YES;
instfd(inst)  = instd(inst) + instf(inst);

ALIAS (instd,instdp),(instf,instfp);

loop(is,
ABORT$(sambal(is) > 1E-7) 'SAM Not Balanced. Check ', is ;
);

loop((i,k,h)$mapk(k,i),
   transmat(i, k, h) = SAM(i, h) ;
) ;


oldShr(a)         = ProdElas0(a,"oldShr")       ;
sigman0(a)        = ProdElas0(a,"sigman0")       ;
omegap0(a)        = ProdElas0(a,"omegap0")       ;
invElas0(a)       = ProdElas0(a,"invElas0")       ;
sigmap0(a,vint)   = ProdElas1(a,"sigmap0",vint) ;
sigmav0(a,vint)   = ProdElas1(a,"sigmav0",vint) ;
sigmaul0(a,vint)  = ProdElas1(a,"sigmaul0",vint) ;
sigmasl0(a,vint)  = ProdElas1(a,"sigmasl0",vint) ;
sigmak0(a,vint)   = ProdElas1(a,"sigmak0",vint) ;
sigmaks0(a,vint)  = ProdElas1(a,"sigmaks0",vint) ;
sigmae0(a,vint)   = ProdElas1(a,"sigmae0",vint) ;

sigmas0(i)        = commElas(i,"sigmas0") ;
sigmam0(i)        = commElas(i,"sigmam0") ;
sigmax0(i)        = commElas(i,"sigmax0") ;
sigmamg0(i)       = commElas(i,"sigmamg0") ;
omegam0(i)        = commElas(i,"omegam0") ;
etae0(i)          = commElas(i,"etae0") ;

sigmac0(h,k)   = FDElas("sigmac0")  ;

sigmacaa0(h,k) = FDElas("sigmacaa0");

*sigmacaa0(h,"heal") = 0;


sigmacae0(h,k) = FDElas("sigmacae0");
sigmaf0(f)     = FDElas("sigmaf0");
sigmafaa0(f)   = FDElas("sigmafaa0");
sigmafae0(f)   = FDElas("sigmafae0");
epsL0(l)       = FDElas("epsL0");
omegaL0(l)     = FDElas("omegaL0");
epsK0(vint)    = FDElas("epsK0");
omegaK0(vint)  = FDElas("omegaK0");
omegatl0       = FDElas("omegatl0");
omegat0        = FDElas("omegat0");

*- income elasticities
incElas0(h,k) = hhElas(k,"Incelas0",h) ;

*- price elasticites
prcElas0(h,k) = hhElas(k,"prcElas0",h) ;

*-*-*-*-*- VNMScen.dat
parameter dyntab(*,tf) Dynamic trends;

$gdxin %savF%\%datFile%
$load  dyntab
$gdxin


*-load GTAP emissions data
SET
em         GTAP emission types
aGTAP     GTAP activities with ely aggregated
cGTAP      GTAP Commodities
regGTAP    GTAP regions
endwGTAP   Endowment Commodities
;

$gdxin %datF%\gtapData.gdx
*$gdxin gsddat.gdx
$loaddc regGTAP aGTAP cGTAP endwGTAP
$gdxin

set em "Emission types" /
   co2               "Carbon emissions"
   n2o               "N2O emissions"
   ch4               "Methane emissions"
   fgas              "Emissions of fluoridated gases"
/ ;

set ema(em) "air pollution" /
   n2o               "N2O emissions"
   ch4               "Methane emissions"
   fgas              "Emissions of fluoridated gases"
/ ;

*-add CO2

set ghg(em) Greenhouse gas emissions
;

ghg(em) = YES;

Parameter gwp(em)
;

gwp(ghg) = 1;


Parameter

MDF(cGTAP,aGTAP,regGTAP)                  emissions from firms (intermediate) consumption of domestic products MTCO2e
MDG(cGTAP,regGTAP)                        emissions from government consumption of domestic products MTCO2e
MDP(cGTAP,regGTAP)                        emissions from private consumption of domestic products MTCO2e
MIF(cGTAP,aGTAP,regGTAP)                  emissions from firms (intermediate) consumption of import products MTCO2e
MIG(cGTAP,regGTAP)                        emissions from government consumption of import products MTCO2e
MIP(cGTAP,regGTAP)                        emissions from private consumption of import products MTCO2e
NC_ENDW_CEQ(em,endwGTAP,aGTAP,regGTAP)    Non-co2 emissions from endowment use
NC_HH_CEQ(em,cGTAP,regGTAP)               Non-co2 emissions from private consumption
NC_QO_CEQ(em,aGTAP,regGTAP)               Non-co2 emissions from production
NC_TRAD_CEQ(em,cGTAP,aGTAP,regGTAP)       Non-co2 emissions from input use

VDFM(cGTAP,aGTAP,regGTAP)                 Firms (intermediate) consumption of domestic products
VDGM(cGTAP,regGTAP)                       firms (intermediate) consumption of domestic products MTCO2e
VDPM(cGTAP,regGTAP)                       government consumption of domestic products MTCO2e
VIFM(cGTAP,aGTAP,regGTAP)                 private consumption of domestic products MTCO2e
VIGM(cGTAP,regGTAP)                       firms (intermediate) consumption of import products MTCO2e
VIPM(cGTAP,regGTAP)                       government consumption of import products MTCO2e
VFM(endwGTAP,aGTAP,regGTAP)            private consumption of import products MTCO2e
TVOM(aGTAP,regGTAP)                       Domestic sales

emiGTAP(em,is0,js0)                   MtCo2e per Million USD
emiXPGTAP(em,is0)
emiGTAPCoeff(em,*,*)                   MtCo2e per Million USD
unitSAM                              coefficient to translate 1 GTAP unit to 1 SAM unit
;


$gdxin %datF%\gtapData.gdx
*$gdxin gsdnco2.gdx
$loaddc NC_ENDW_CEQ NC_HH_CEQ
*no domain control since ELY is single sector for fgas
$load NC_QO_CEQ NC_TRAD_CEQ
$loaddc MDF MDG MDP MIF MIG MIP
$loaddc VDFM VDGM VDPM VIFM VIGM VIPM VFM TVOM
$gdxin

*-load mapping between gtap sets and model sets
Set
mapaGtap(aGtap,is0)
mapcGtap(cGtap,i0)
;

$gdxin %savF%\%datFile%.gdx
$loaddc mapaGtap mapcGtap
$gdxin

SET
a0(is0)
i0(is0)
h0(is0)
gov0(is0)
lnd0(is0)
cap0(is0)
fp0(is0)
;

a0(is0)$SUM(a,mapis(is0,a))    = YES;
h0(is0)$SUM(h,mapis(is0,h))    = YES;
gov0(is0)$SUM(gov,mapis(is0,gov))= YES;
lnd0(is0)$SUM(lnd,mapis(is0,lnd))= YES;
cap0(is0)$SUM(cap,mapis(is0,cap))= YES;
fp0(is0)$SUM(fp,mapis(is0,fp))= YES;

ALIAS (is0,is0p),(h0,h0p),(lnd0,lnd0p),(cap0,cap0p), (gov0,gov0p), (I0,I0P),(A0,A0P) ;

*- for household, government and sectors that match more than one GTAP sector, use aggregated emissions and sam values

SET
mapaGtap1n(aGtap,is0) mapping between one gtap activity and multiple SAM activities
mapaGtapn1(aGtap,is0) mapping between multiple gtap activities and one SAM activity
mapcGtap1n(cGtap,is0) mapping between one gtap commodity and multiple SAM commodities
mapcGtapn1(cGtap,is0) mapping between multiple gtap commodities and one SAM commodity
;
ALIAS (agtap,agtapp), (cgtap,cgtapp) ;
mapaGtap1n(aGtap,is0)$(mapaGtap(aGtap,is0) AND SUM(aGtapp$mapaGtap(aGtapp,is0),1) eq 1)= YES;
mapaGtapn1(aGtap,is0)$(mapaGtap(aGtap,is0) AND SUM(aGtapp$mapaGtap(aGtapp,is0),1) gt 1)= YES;
mapcGtap1n(cGtap,i0)$(mapcGtap(cGtap,i0)  AND SUM(cGtapp$mapcGtap(cGtapp,i0),1) eq 1)= YES;
mapcGtapn1(cGtap,i0)$(mapcGtap(cGtap,i0)  AND SUM(cGtapp$mapcGtap(cGtapp,i0),1) gt 1)= YES;

*- calculate emission factors from GTAP
emiGTAPCoeff(em,cGTAP,aGTAP)
        = NC_TRAD_CEQ(em,cGTAP,aGTAP,"%RegGtapName%");

emiGTAPCoeff(em,cGTAP,"h0")
        = NC_HH_CEQ(em,cGTAP,"%RegGtapName%");

emiGTAPCoeff(em,"emixp",aGTAP)
        = NC_QO_CEQ(em,aGTAP,"%RegGtapName%");

emiGTAPCoeff(em,"lnd0",aGTAP)
        = NC_ENDW_CEQ(em,"Land",aGTAP,"%RegGtapName%");

emiGTAPCoeff(em,"cap0",aGTAP)
        = NC_ENDW_CEQ(em,"Capital",aGTAP,"%RegGtapName%");

emiGTAPCoeff("co2",cGTAP,aGTAP)
        = (MDF(cGTAP,aGTAP,"%RegGtapName%") + MIF(cGTAP,aGTAP,"%RegGtapName%"))
               ;

emiGTAPCoeff("co2",cGTAP,"h0")
        = (MDP(cGTAP,"%RegGtapName%") + MIP(cGTAP,"%RegGtapName%"))
                ;

emiGTAPCoeff("co2",cGTAP,"gov0")
        = (MDG(cGTAP,"%RegGtapName%") + MIG(cGTAP,"%RegGtapName%"));


*-calculate the weights
Parameter emiWeight(is0,js0) ;
Parameter emiWeightXP(is0) ;

emiWeight(i0,a0)= sum((aGtap,cGtap)$(mapaGtap(aGtap,a0) AND mapcGtap(cGtap,i0)), sum((i0p,a0p)$(mapaGtap(aGtap,a0p) AND mapcGtap(cGtap,i0p)),sam0(i0p,a0p)));

emiWeight(i0,h0)  = sum(cGtap$mapcGtap(cGtap,i0), sum((i0p,h0p)$mapcGtap(cGtap,i0p),sam0(i0p,h0p)));
emiWeight(i0,gov0)= sum(cGtap$mapcGtap(cGtap,i0), sum((i0p,gov0p)$mapcGtap(cGtap,i0p),sam0(i0p,gov0p)));

emiWeight(lnd0,a0)= sum(aGtap$mapaGtap(aGtap,a0), sum((lnd0p,a0p)$mapaGtap(aGtap,a0p),sam0(lnd0p,a0p)));
emiWeight(cap0,a0)= sum(aGtap$mapaGtap(aGtap,a0), sum((cap0p,a0p)$mapaGtap(aGtap,a0p),sam0(cap0p,a0p)));

emiWeightXP(a0) = sum(aGtap$mapaGtap(aGtap,a0), sum((is0p,a0p)$mapaGtap(aGtap,a0p),sam0(is0p,a0p)));

*- aggregate over GTAP mapping and distribute with SAM wights if multiple sam element mapped to one GTAP element
emiGTAP(em,i0,a0)$emiWeight(i0,a0) = sum((cGTAP,aGtap)$(mapaGtap(aGtap,a0) AND mapcGtap(cGtap,i0)),emiGTAPCoeff(em,cGTAP,aGtap))
                                        * SAM0(i0,a0) / emiWeight(i0,a0);


emiGTAP(em,i0,h0)$(NOT emiGTAP(em,i0,h0) AND emiWeight(i0,h0)) =       sum(cGTAP$mapcGtap(cGtap,i0),emiGTAPCoeff(em,cGTAP,"h0")) * SAM0(i0,h0) / emiWeight(i0,h0) ;
emiGTAP(em,i0,gov0)$(NOT emiGTAP(em,i0,gov0) AND emiWeight(i0,gov0)) =   sum(cGTAP$mapcGtap(cGtap,i0),emiGTAPCoeff(em,cGtap,"gov0")) * SAM0(i0,gov0) / emiWeight(i0,gov0) ;

emiGTAP(em,lnd0,a0)$(NOT emiGTAP(em,lnd0,a0) AND emiWeight(lnd0,a0)) =   sum(aGtap$mapaGtap(aGtap,a0),emiGTAPCoeff(em,"lnd0",aGtap)) * SAM0(lnd0,a0) / emiWeight(lnd0,a0) ;
emiGTAP(em,cap0,a0)$(NOT emiGTAP(em,cap0,a0) AND emiWeight(cap0,a0)) =   sum(aGtap$mapaGtap(aGtap,a0),emiGTAPCoeff(em,"cap0",aGtap)) * SAM0(cap0,a0) / emiWeight(cap0,a0);


emiXPGTAP(em,a0)$emiWeightXP(a0)= sum(aGtap$mapaGtap(aGtap,a0),emiGTAPCoeff(em,"emixp",aGTAP)) * SUM(is0,SAM0(is0,a0))/emiWeightXP(a0);

$ontext
emiGTAPCoeff(em,cGTAP,aGTAP)$(VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%"))
                     =  NC_TRAD_CEQ(em,cGTAP,aGTAP,"%RegGtapName%")
                                   /(VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%")) ;

emiGTAPCoeff(em,cGTAP,"h0")$(VDPM(cGTAP,"%RegGtapName%") + VIPM(cGTAP,"%RegGtapName%"))
        = NC_HH_CEQ(em,cGTAP,"%RegGtapName%")/(VDPM(cGTAP,"%RegGtapName%") + VIPM(cGTAP,"%RegGtapName%"));

emiGTAPCoeff(em,"emixp",aGTAP)$TVOM(aGTAP,"%RegGtapName%")
        = NC_QO_CEQ(em,aGTAP,"%RegGtapName%")/TVOM(aGTAP,"%RegGtapName%");

emiGTAPCoeff(em,"lnd0",aGTAP)$VFM("Land",aGTAP,"%RegGtapName%")
        = NC_ENDW_CEQ(em,"Land",aGTAP,"%RegGtapName%")/VFM("Land",aGTAP,"%RegGtapName%");

emiGTAPCoeff(em,"cap0",aGTAP)$VFM("Capital",aGTAP,"%RegGtapName%")
        = NC_ENDW_CEQ(em,"Capital",aGTAP,"%RegGtapName%")/VFM("Capital",aGTAP,"%RegGtapName%");

emiGTAPCoeff(em,cGTAP,aGTAP)$(VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%"))
        = (MDF(cGTAP,aGTAP,"%RegGtapName%") + MIF(cGTAP,aGTAP,"%RegGtapName%"))
               /(VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%")) ;

emiGTAPCoeff(em,cGTAP,aGTAP)$(VDPM(cGTAP,"%RegGtapName%")+VIPM(cGTAP,"%RegGtapName%"))
        =  (MDP(cGTAP,"%RegGtapName%") + MIP(cGTAP,"%RegGtapName%"))
                /(VDPM(cGTAP,"%RegGtapName%")+VIPM(cGTAP,"%RegGtapName%"));

emiGTAPCoeff(em,cGTAP,aGTAP)$(VDGM(cGTAP,"%RegGtapName%")+VIGM(cGTAP,"%RegGtapName%"))
        =  (MDG(cGTAP,"%RegGtapName%") + MIG(cGTAP,"%RegGtapName%"))
                /(VDGM(cGTAP,"%RegGtapName%")+VIGM(cGTAP,"%RegGtapName%"));

$offtext


$ontext
emiGTAP(em,i0,is0)$SUM((cGTAP,aGTAP)$(mapaGtap(aGtap,is0) AND mapcGtap(cGtap,i0)),VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%"))
        = SUM((cGTAP,aGTAP)$(mapaGtap(aGtap,is0) AND mapcGtap(cGtap,i0)),NC_TRAD_CEQ(em,cGTAP,aGTAP,"%RegGtapName%"))
                  /SUM((cGTAP,aGTAP)$(mapaGtap(aGtap,is0) AND mapcGtap(cGtap,i0)),(VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%"))) ;

emiGTAP(em,i0,h0)$SUM(cGTAP$mapcGtap(cGtap,i0),VDPM(cGTAP,"%RegGtapName%") + VIPM(cGTAP,"%RegGtapName%"))
        = SUM(cGTAP$mapcGtap(cGtap,i0),NC_HH_CEQ(em,cGTAP,"%RegGtapName%"))/SUM(cGTAP$mapcGtap(cGtap,i0),(VDPM(cGTAP,"%RegGtapName%") + VIPM(cGTAP,"%RegGtapName%")));

emiGTAP(em,is0,i0)$SUM(aGTAP$mapaGtap(aGtap,is0),TVOM(aGTAP,"%RegGtapName%"))
        = SUM(aGTAP$mapaGtap(aGtap,is0),NC_QO_CEQ(em,aGTAP,"%RegGtapName%"))/SUM(aGTAP$mapaGtap(aGtap,is0),TVOM(aGTAP,"%RegGtapName%"));

emiGTAP(em,lnd0,is0)$SUM(aGTAP$mapaGtap(aGtap,is0),VFM("Land",aGTAP,"%RegGtapName%"))
        = SUM(aGTAP$mapaGtap(aGtap,is0),NC_ENDW_CEQ(em,"Land",aGTAP,"%RegGtapName%"))/SUM(aGTAP$mapaGtap(aGtap,is0),VFM("Land",aGTAP,"%RegGtapName%"));

emiGTAP(em,cap0,is0)$SUM(aGTAP$mapaGtap(aGtap,is0),VFM("Capital",aGTAP,"%RegGtapName%"))
        = SUM(aGTAP$mapaGtap(aGtap,is0),NC_ENDW_CEQ(em,"Capital",aGTAP,"%RegGtapName%"))/SUM(aGTAP$mapaGtap(aGtap,is0),VFM("Capital",aGTAP,"%RegGtapName%"));


emiGTAP("co2",i0,is0)$SUM((cGTAP,aGTAP)$(mapaGtap(aGtap,is0) AND mapcGtap(cGtap,i0)),VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%"))
        = SUM((cGTAP,aGTAP)$(mapaGtap(aGtap,is0) AND mapcGtap(cGtap,i0)),(MDF(cGTAP,aGTAP,"%RegGtapName%") + MIF(cGTAP,aGTAP,"%RegGtapName%")))
               /SUM((cGTAP,aGTAP)$(mapaGtap(aGtap,is0) AND mapcGtap(cGtap,i0)),(VDFM(cGTAP,aGTAP,"%RegGtapName%") + VIFM(cGTAP,aGTAP,"%RegGtapName%"))) ;

emiGTAP("co2",i0,h0)$SUM(cGTAP$mapcGtap(cGtap,i0),VDPM(cGTAP,"%RegGtapName%")+VIPM(cGTAP,"%RegGtapName%"))
        =  SUM(cGTAP$mapcGtap(cGtap,i0),(MDP(cGTAP,"%RegGtapName%") + MIP(cGTAP,"%RegGtapName%")))
                /SUM(cGTAP$mapcGtap(cGtap,i0),(VDPM(cGTAP,"%RegGtapName%")+VIPM(cGTAP,"%RegGtapName%")));

emiGTAP("co2",i0,gov0)$SUM(cGTAP$mapcGtap(cGtap,i0),VDGM(cGTAP,"%RegGtapName%")+VIGM(cGTAP,"%RegGtapName%"))
        =  SUM(cGTAP$mapcGtap(cGtap,i0),(MDG(cGTAP,"%RegGtapName%") + MIG(cGTAP,"%RegGtapName%")))
                /SUM(cGTAP$mapcGtap(cGtap,i0),(VDGM(cGTAP,"%RegGtapName%")+VIGM(cGTAP,"%RegGtapName%")));



$offtext

Parameter emi0;
Parameter emiXP0;
Parameter emiCommFlag;

emi0(em,is0,js0) = emiGTAP(em,is0,js0) ;
emiXP0(em,is0) = emiXPGTAP(em,is0) ;
emiCommFlag(em,emSrc,aa,t)$sum((js0,is0)$(mapis(js0,emSrc) and mapis(is0,aa)), emi0(em,js0,is0))  = 1;

ALIAS (is0,is0p,js0p);


Parameter scaleEm(em) Emission scale factor;

*scaleEm(em) = 1 ;
*- calibrated according to https://www.sciencedirect.com/science/article/pii/S1364032117305257
scaleEm('co2')  = 7.76/(sum(is0,emiXP0('co2',is0)) + SUM((is0p,js0p), emi0('co2',is0p,js0p))) ;
scaleEm('ch4')  = 6.79/(sum(is0,emiXP0('ch4',is0)) + SUM((is0p,js0p), emi0('ch4',is0p,js0p))) ;
scaleEm('n2o')  = 2.99/(sum(is0,emiXP0('n2o',is0)) + SUM((is0p,js0p), emi0('n2o',is0p,js0p))) ;
*scaleEm('fgas') = 5/SUM((is0p,js0p), emi0('fgas',is0p,js0p)) ;

emi0(em,is0,js0) = scaleEm(em)* emi0(em,is0,js0);
emiXP0(em,is0) = scaleEm(em)* emiXP0(em,is0);

*emiProd0(em, a0)= SUM(js0,emi0(em,a0,js0)) ;

Parameter GDPProj(tf) GDP from Macrostructural Model;
GDPProj(tf) = dyntab("GDP",tf);

Parameter
GDPpcProj(tf) GDP per capita growth
GDPpc(tf) GDP per capita
GDP(tf)   GDP;

Loop(t0,
GDP(t0) =  SUM((i,fd),sam(i,fd)) - SUM((i,fd),SAM(fd,i))
            + SUM((i,stb),SAM(i,stb))
            + SUM((i,row),SAM(i,row))
            - SUM((i,row),SAM(row,i)) ;
);

Loop(t$(NOT t0(t)),
GDP(t) = (1+dyntab("GDP",t)/100)*GDP(t-1) ;
);


GDPpc(t) = GDP(t) / SUM(age,popAge0(t,age)) ;
GDPpcProj(t)$(not t0(t)) = GDPpc(t)/GDPpc(t-1)*100-100 ;

$ontext
*  Productivity assumptions

parameter prodTab0(a, *) Sectoral productivity assumptions ;


prodTab0(a, 'exprod')=0;
prodTab0(a, 'alphaL')=1;
prodTab0(a, 'betaL') =1;
prodTab0(a, 'energyEff')=1;
prodTab0(a, 'yexo') =0;
prodTab0(a, 'kprod')=0;

exProd(a,v,t) = 0.01*prodTab0(a, 'exprod') ;
alphaL(a,l,t) = 0.01*prodTab0(a, 'alphaL') ;
betaL(a,l,t)  = prodTab0(a, 'betaL') ;

Yexo(a,t)     = 0.01*prodTab0(a, 'yexo') ;
KProd(a,t)    = 0.01*prodTab0(a, 'kprod') ;

*  Energy efficiency assumptions

geP(e,a,v,t) = 0.01*prodTab0(a, 'energyEff') ;
geC(h,e,k,t) = 0 ;
geF(f,e,t)   = 0 ;

$offtext



parameter
   years(tf)
   gap(t)
;

years(tf) = 2017 + ord(tf) ;

gap(t)$(not t0(t)) = years(t) - years(t-1) ;

*  Initialize population scenario

   popT(cohorts,t) = SUM(age$mapage(age,cohorts),popAge0(t,age)) ; ;

*  Per capita growth rates

loop((t)$(not t0(t)),
   ggdppcT(t) = GDPpcProj(t) ;
) ;
display ggdppct ;

ggdppcT(t) = 0.01*ggdppcT(t) ;

*  Productivity assumptions

exProd(a,v,t) = 0.01*prodTab0(a, 'exprod') ;
alphaL(a,l,t) = 0.01*prodTab0(a, 'alphaL') ;
betaL(a,l,t)  = prodTab0(a, 'betaL') ;

Yexo(a,t)     = 0.01*prodTab0(a, 'yexo') ;
KProd(a,t)    = 0.01*prodTab0(a, 'kprod') ;

*  Energy efficiency assumptions

geP(e,a,v,t) = 0.01*prodTab0(a, 'energyEff') ;
geC(h,e,k,t) = 0 ;
geF(f,e,t)   = 0 ;


$gdxin %savF%\%datFile%.gdx
$loaddc labor

alias (a,app);

labor(l,a) = pop0("P1564")*0.775 *  labor(l,a)/SUM((lp,app),labor(lp,app))  ;

labor(l,a)$(NOT labor(l,a)) = SAM(l,a)/SUM((lp,app),SAM(lp,app))*pop0("P1564")  ;

$gdxin

*- this is to define console as a file for put statements
file screen / con / ;
put screen ;
