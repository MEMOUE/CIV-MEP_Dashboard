SET
var
/
SAVF
Land
co2    "Carbon emissions"
n2o    "N2O emissions"
ch4    "Methane emissions"
fgas    "Emissions of fluoridated gases"
EmiTot
EmiGHG
EmiXp
EmBySec
EmiTax
EmiSecA
delst
entrtax
er
exRates
fexp
fimp
gexp
GHG
hpop
htax
inc
inv
kaps
kapy
kd
kstock
laby
lambdak
lambdal
lambdan
lambdav
ld
lst
NIPA
nshrGDP
pa
paf
pd
pda
pe
pf
pk
pk_pt
pkf
pland
pland_pt
pma
pnum
Pop
pp
ps
ptland
pwe
pwm
rinv
rrat
rsg
rshrGDP
sav
pswage
swage
tland
toTR
transf
trb
uh
wage
xa
xat
xaV
xd
xe
xf
xkf
xkfshr
xm
xp
xpv
xs
xfd
yg
ygov
yh
gini
GFDebt
GDDebt
PFDeb
RGFDebt
RGDDebt
gl
AvgGL
fshr
qdel
ldel
aps
epshea
epsedu
unemp
brate
brateU
drate
popAge
deprate
flfp
flfptot
aep
af
aio
lambdaep
amarg
elecmix
   debtStkD         "Domestic Debt stock"
   debtStkF         "Foreign Debt stock"
   debtStkT         "Total Debt stock"
   debtGDP          "Debt to GDP"
   debtPay          "Debt payment"
   debtNew          "Debt New"
   rDebtStkD         repayment ratio for domestic debt
   rDebtStkF         repayment ratio for foreign debt
   rDebtStk          repayment ratio for domestic and foreign debt

   dmgTfpAct         CC damage to sector TFP
   dmgLambdaL_HH     CC damage to human health
   dmgLambdaL        CC damage to labor productivity
   dmgAtLand         CC damage to land supply
   dmgLambdaEh       CC damage to household energy demand
   dmgChie           CC damage to household energy demand
   dmgDepr           CC damage to household energy demand

   dmgShftTFP
   dmgShftLambdaL_HH
   dmgShftLambdaL
   dmgShftLand
   dmgShftLambdaEh
   dmgShftChie
   dmgShftDepr

   tfac
   tpsb
   tprd
   tvat
   tpaf
   tcit
   tpit
   texp
   timp
   temi
   tfacRev
   tpsbRev
   tprdRev
   tvatRev
   tpafRev
   tcitRev
   tpitRev
   texpRev
   timpRev
   temiRev
 tfpAct
 savh
 savEntr
 ev  
  /


rdim1
/
*"(blank)"
set.is
delst
co2
n2o
ch4
fgas
TotEm
set.cohorts
set.n
set.isrep
Total
*psb    "Production subsidies"
*ptx    "Production taxes"
*otx    "Other taxes"
*mtx    "Import taxes"
*etx    "Export taxes"
*dtx    "Direct taxes"
*atx    "Commodity taxes"
*ctx    "Emmisson taxes"
*ftx
/


rdim2
/
*"(blank)"
set.is
set.n
set.isrep
ppp
USD
EUR
Old
New
tot
cons
govt
invt
ginvt
delst
rtdelst
rtotexp
rtotimp
gl
ggdppc
rgdpmp
rgdppc
rgdpfc
ptdelst
ptotexp
ptotimp
pgdpmp
pgdpfc
trent
tdelst
totexp
totimp
gdpmp
gdpfc
food
Manu
Ener
Serv
Tran
Heal
PLT15
P1564
P65UP
PTOTL
k
land
Total
/
;


Parameter resCon(sim,var,rdim1,rdim2,t);
