$setGlobal oDir     ".\res"
$setGlobal inBaUGDX  "%odir%\BaU.gdx"


SET
sim
/
BaU
carbtax
/

restype
/
Level     level
PerBs     percentage deviation from baseline
DifBs     deviation in level from baseline
YoYGr     year on year growth rate
CumGr     cumulative growth
/

em
var
rdim1
rdim2
t
t0(t)
simRep(sim) reported sims
tRep(t)     reported years
;

Parameter
rescon(sim,var,rdim1,rdim2,t)
rescon0(sim,var,rdim1,rdim2,t)
rescon1(sim,var,rdim1,rdim2,t)
rescon2(sim,var,rdim1,rdim2,t)
rescon3(sim,var,rdim1,rdim2,t)
rescon4(sim,var,rdim1,rdim2,t)

result(resType,sim,var,rdim1,rdim2,t)
years(t)
;



$gdxin  %inBaUGDX%
*$load var rdim1 rdim2 em t t0 years rescon0=rescon
$load var rdim1 rdim2 em t t0 years

simRep(sim) = YES;
*simRep("BaU") = NO;

*tRep(t)$(mod(ord(t)+1,5)=0) = YES;
*tRep(t)$(years(t)>2040) = NO;

 tRep(t) = NO;
 tRep(t) = YES;
* tRep(t)$(years(t)<2036 and years(t)>2020) = YES;
$ontext
 tRep("2022") = YES;
 tRep("2025") = YES;
 tRep("2030") = YES;
* tRep("2035") = YES;
$offtext
* tRep("2040") = YES;
* tRep("2045") = YES;
* tRep("2050") = YES;


loop(sim,

   put_utility 'gdxin' / "%odir%\"sim.tl ;
*   execute_loadpoint ;
   execute_load rescon ;

result("Level",sim,var,rdim1,rdim2,tRep) = rescon(sim,var,rdim1,rdim2,tRep) ;

);


result("PerBs",simRep,var,rdim1,rdim2,tRep)$result("Level","BaU",var,rdim1,rdim2,tRep)
                                        = result("Level",simRep,var,rdim1,rdim2,tRep)
                                        / result("Level","BaU",var,rdim1,rdim2,tRep)*100-100;


*result("PerBs",sim,var,rdim1,rdim2,tRep)$(abs(result("PerBs",sim,var,rdim1,rdim2,tRep)) LT 1E-5) = 0;


result("DifBs",simRep,var,rdim1,rdim2,tRep)
                                        = result("Level",simrep,var,rdim1,rdim2,tRep)
                                        - result("Level","BaU",var,rdim1,rdim2,tRep);
result("DifBs",simRep,var,rdim1,rdim2,tRep)$(abs(result("DifBs",simRep,var,rdim1,rdim2,tRep))<1E-3) = 0 ;




result("YoYGr",simRep,var,rdim1,rdim2,t)$result("Level",simRep,var,rdim1,rdim2,t-1)
                                        = result("Level",simRep,var,rdim1,rdim2,t)
                                        / result("Level",simRep,var,rdim1,rdim2,t-1)*100-100;

result("YoYGr",simRep,var,rdim1,rdim2,t)$(NOT trep(t)) =0;


Loop(t0,
result("CumGr",simRep,var,rdim1,rdim2,tRep)$result("Level",simRep,var,rdim1,rdim2,t0)
                                        = result("Level",simRep,var,rdim1,rdim2,tRep)
                                        / result("Level",simRep,var,rdim1,rdim2,t0)*100-100;

);
$ontext
$offtext
*result(resType,"BaU",var,rdim1,rdim2,t) = 0 ;
*result(resType,sim,var,rdim1,rdim2,t)$(abs(result(resType,sim,var,rdim1,rdim2,t)) < 1E-6) = 0 ;


$macro getRes(var)    Parameter var&_r(restype,sim,rdim1,rdim2,t) ; \
                      var&_r(restype,sim,rdim1,rdim2,t) = result(restype,sim,'&var&',rdim1,rdim2,t)    ; \
*                      var&_r("YoYGr",sim,rdim1,rdim2,t)$result("Level",sim,'&var&',rdim1,rdim2,t-1) = result("Level",sim,'&var&',rdim1,rdim2,t)/result("Level",sim,'&var&',rdim1,rdim2,t-1)*100-100;

getres(sav)
getRes(savh)
getRes(saventr)
getRes(savf)
getRes(rsg)
getRes(inv)
getRes(rinv)
getRes(rshrGDP)
getRes(nshrGDP)
getRes(er)
getRes(fimp)
getRes(fexp)
getRes(inc)
getRes(ygov)
getRes(yg)
getRes(entrtax)
getRes(htax)
getRes(gexp)
getRes(yh)
getRes(gini)
getRes(laby)
getRes(uh)
getRes(kapy)
getRes(transf)
getRes(xp)
getRes(toTR)
getRes(Pop)
getRes(hPop)
getRes(exRates)
getRes(lst)
getRes(wage)
getRes(pf)
getRes(xfd)
getRes(xf)
getRes(kstock)
getRes(pnum)
getRes(kd)
getRes(xpv)
getRes(pk)
getRes(ld)
getRes(swage)
getRes(pswage)
getRes(tfac)
*getRes(chfwtx)
getRes(rrat)
getRes(pp)
getRes(land)
getRes(pland)
getRes(xs)
getRes(xd)
getRes(delst)
getRes(xm)
getRes(xe)
getRes(xat)
getRes(xa)
getRes(xaV)
getRes(paf)
getRes(ps)
getRes(pa)
getRes(pda)
getRes(pma)
getRes(pd)
getRes(pe)
getRes(pwe)
getRes(pwm)
getRes(pkf)
getRes(xkf)
getRes(xkfshr)
*getRes(em)
getRes(GHG)
getRes(gl)
getRes(avgGL)
getRes(lambdal)
getRes(lambdan)
getRes(lambdav)
getRes(lambdak)
getRes(fshr)
getRes(qdel)
getRes(ldel)
getRes(ldel)
getRes(fshr)
getRes(qdel)
getRes(ldel)
*getRes(emi)
getRes(EmBySec)
getRes(EmiXP)
getRes(EmiTot)
getRes(EmiTax)
getRes(EmiGHG)
*getRes(tdelst)
*getRes(rtdelst)
*getRes(ptdelst)
*getRes(texp)
*getRes(rtexp)
*getRes(ptexp)
*getRes(timp)
*getRes(rtimp)
*getRes(ptimp)
*getRes(gdpmp)
*getRes(rgdpmp)
*getRes(pgdpmp)
*getRes(rgdppc)
*getRes(ggdppc)
*getRes(gdpfc)
*getRes(rgdpfc)
*getRes(pgdpfc)
*getRes(trent)
getRes(aps)
getRes(unemp)
getRes(popAge)
getRes(brate)
getRes(brateU)
*getRes(FLFPtot)
getRes(drate)
getRes(deprate)
getRes(flfp)
getres(aep)
getres(af)
getres(aio)
getres(lambdaep)
getres(amarg)
getres(elecmix)
getres(emisecA)
getres(debtStkD)
getres(debtStkF)
getres(debtStkT)
getres(debtGDP)
getres(rDebtStkD)
getres(rDebtStkF)
getres(rDebtStk)
getres(debtPay)
getres(debtNew)
getres(dmgTfpAct)
getres(dmgLambdaL_HH)
getres(dmgLambdaL)
getres(dmgAtLand)
getres(dmgLambdaEh)
getres(dmgChie)
getres(dmgDepr)
getres(dmgShftTFP)
getres(dmgShftLambdaL_HH)
getres(dmgShftLambdaL)
getres(dmgShftLand)
getres(dmgShftLambdaEh)
getres(dmgShftChie)
getres(dmgShftDepr)
getres(tfac)
getres(tpsb)
getres(tprd)
getres(tvat)
getres(tpaf)
getres(tcit)
getres(tpit)
getres(texp)
getres(timp)
getres(temi)
getres(tfacRev)
getres(tpsbRev)
getres(tprdRev)
getres(tvatRev)
getres(tpafRev)
getres(tcitRev)
getres(tpitRev)
getres(texpRev)
getres(timpRev)
getres(temiRev)
getres(nipa)
*getres(forest)
*getres(peat)
*getres(emilucf)
*getres(yf)
getres(tfpact)
getRes(ev)

Parameter emi_r(restype,sim,var,rdim1,rdim2,t);

Loop((em,var)$sameas(em,var),
emi_r(restype,sim,var,rdim1,rdim2,t)         = result(restype,sim,var,rdim1,rdim2,t)             ;
);

$ontext
Parameter
tdelst_r(restype,sim,t)
rtdelst_r(restype,sim,t)
ptdelst_r(restype,sim,t)
totexp_r(restype,sim,t)
rtotexp_r(restype,sim,t)
ptotexp_r(restype,sim,t)
totimp_r(restype,sim,t)
rtotimp_r(restype,sim,t)
ptotimp_r(restype,sim,t)
$offtext
Parameter
gdpmp_r(restype,sim,t)
rgdpmp_r(restype,sim,t)
pgdpmp_r(restype,sim,t)
rgdppc_r(restype,sim,t)
ggdppc_r(restype,sim,t)
gdpfc_r(restype,sim,t)
rgdpfc_r(restype,sim,t)
pgdpfc_r(restype,sim,t)
trent_r(restype,sim,t)
;
$ontext
tdelst_r(restype,sim,t)  = result(restype,sim,"NIPA","Val","tdelst",t)  ;
rtdelst_r(restype,sim,t) = result(restype,sim,"NIPA","Vol","rtdelst",t) ;
ptdelst_r(restype,sim,t) = result(restype,sim,"NIPA","PrD","ptdelst",t) ;
totexp_r(restype,sim,t)    = result(restype,sim,"NIPA","Val","totexp",t)    ;
rtotexp_r(restype,sim,t)   = result(restype,sim,"NIPA","Vol","rtotexp",t)   ;
ptotexp_r(restype,sim,t)   = result(restype,sim,"NIPA","PrD","ptotexp",t)   ;
totimp_r(restype,sim,t)    = result(restype,sim,"NIPA","Val","totimp",t)    ;
rtotimp_r(restype,sim,t)   = result(restype,sim,"NIPA","Vol","rtotimp",t)   ;
ptotimp_r(restype,sim,t)   = result(restype,sim,"NIPA","PrD","ptotimp",t)   ;
$offtext

gdpmp_r(restype,sim,t)   = result(restype,sim,"NIPA","Val","gdpmp",t)   ;
rgdpmp_r(restype,sim,t)  = result(restype,sim,"NIPA","Vol","rgdpmp",t)  ;
pgdpmp_r(restype,sim,t)  = result(restype,sim,"NIPA","PrD","pgdpmp",t)  ;
rgdppc_r(restype,sim,t)  = result(restype,sim,"NIPA","Vol","rgdppc",t)  ;
ggdppc_r(restype,sim,t)  = result(restype,sim,"NIPA","Pct","ggdppc",t)  ;
gdpfc_r(restype,sim,t)   = result(restype,sim,"NIPA","Val","gdpfc",t)   ;
rgdpfc_r(restype,sim,t)  = result(restype,sim,"NIPA","Vol","rgdpfc",t)  ;
pgdpfc_r(restype,sim,t)  = result(restype,sim,"NIPA","PrD","pgdpfc",t)  ;
trent_r(restype,sim,t)   = result(restype,sim,"NIPA","PrD","trent",t)   ;


*execute_unload "%odir%\ResultAll_sen.gdx"
execute_unload "%odir%\ResultEmi.gdx"
*execute_unload "%odir%\ResultAgr.gdx"
*execute_unload "%odir%\ResultDD.gdx"
*execute_unload "%odir%\ResultComb.gdx"
nipa_r    ,
sav_r    ,
savf_r   ,
rsg_r    ,
inv_r    ,
rinv_r   ,
rshrGDP_r,
nshrGDP_r,
er_r     ,
fimp_r   ,
fexp_r   ,
inc_r    ,
ygov_r   ,
yg_r     ,
entrtax_r,
htax_r   ,
gexp_r   ,
yh_r     ,
gini_r   ,
laby_r   ,
uh_r     ,
kapy_r   ,
transf_r ,
xp_r     ,
toTR_r   ,
Pop_r    ,
hpop_r   ,
exRates_r,
lst_r    ,
wage_r   ,
pf_r     ,
xfd_r     ,
kstock_r ,
pnum_r   ,
kd_r     ,
xpv_r    ,
pk_r     ,
ld_r     ,
swage_r  ,
rrat_r   ,
pp_r     ,
land_r   ,
pland_r  ,
xs_r     ,
xd_r     ,
delst_r  ,
xm_r     ,
xe_r     ,
xat_r    ,
xa_r     ,
xaV_r    ,
tpaf_r  ,
paf_r    ,
ps_r     ,
pa_r     ,
pda_r    ,
pma_r    ,
pd_r     ,
pe_r     ,
pwe_r    ,
pwm_r    ,
pkf_r    ,
xkf_r    ,
xkfshr_r ,
emi_r     ,
GHG_r    ,
gl_r     ,
avgGL_r  ,
lambdal_r,
lambdan_r,
lambdav_r,
lambdak_r,
fshr_r   ,
qdel_r   ,
ldel_r   ,
ldel_r   ,
fshr_r   ,
qdel_r   ,
ldel_r   ,
emi_r    ,
EmBySec_r,
EmiXP_r  ,
EmiTot_r ,
EmiTax_r ,
EmiGHG_r ,
$ontext
tdelst_r ,
rtdelst_r,
ptdelst_r,
totexp_r   ,
rtotexp_r  ,
ptotexp_r  ,
totimp_r   ,
rtotimp_r  ,
ptotimp_r  ,
$offtext
gdpmp_r  ,
rgdpmp_r ,
pgdpmp_r ,
rgdppc_r ,
ggdppc_r ,
gdpfc_r  ,
rgdpfc_r ,
pgdpfc_r ,
trent_r,

aps_r,
unemp_r,
brate_r,
brateU_r,
*flfptot_r,
drate_r,
deprate_r,
popAge_r,
flfp_r,
aep_r,
af_r,
aio_r,
lambdaep_r,
amarg_r,
elecmix_r,
emisecA_r,
pswage_r,
debtStkD_r,
debtStkF_r,
debtStkT_r,
debtGDP_r,
rDebtStkD_r,
rDebtStkF_r,
rDebtStk_r,
debtPay_r,
debtNew_r,
debtGDP_r,
dmgTfpAct_r,
dmgLambdaL_HH_r,
dmgLambdaL_r,
dmgAtLand_r,
dmgLambdaEh_r,
dmgChie_r,
dmgDepr_r,
   dmgShftTFP_r,
   dmgShftLambdaL_HH_r,
   dmgShftLambdaL_r,
   dmgShftLand_r,
   dmgShftLambdaEh_r,
   dmgShftChie_r,
   dmgShftDepr_r,
xf_r,
   tfac_r,
   tpsb_r,
   tprd_r,
   tvat_r,
   tpaf_r,
   tcit_r,
   tpit_r,
   texp_r,
   timp_r,
   temi_r,
   tfacRev_r,
   tpsbRev_r,
   tprdRev_r,
   tvatRev_r,
   tpafRev_r,
   tcitRev_r,
   tpitRev_r,
   texpRev_r,
   timpRev_r,
   temiRev_r
*   forest_r
*   peat_R
*   emilucf_r
*   yf_r
 tfpact_r
 savh_r
 saventr_r
ev_r
;
