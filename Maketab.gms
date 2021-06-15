$setGlobal oDir     ".\res"
$setGlobal incF     ".\inc"
$setGlobal datF     ".\dat"
$setGlobal savF     ".\sav"
$setGlobal datFile  "BaU_data_in"
$setGlobal inBaUGDX  "%odir%\BaU.gdx"

*lmb removed set sim as already declared in opt.inc and it was creating errors
*$ontext
*lmb added  $onmulti to avoid compilation error
$onmulti
set sim Simulations to compare /
BaU
*Agri10
Agri20
*DemD10
DemD20
*combine
/ ;
*$offtext
*  Set ifCal to 1 for BaU scenarios

$setglobal BridgeFile BaseBridge_v1.xlsx

*$include "%incF%\dynamDef.inc"
$include '%incF%\opt.inc'

Parameter simrep(sim) simulations that are reported;
simrep(sim) = NO;
simrep("BaU") = YES;
*-change to report specific simulations
*lmb disactivated
*simrep(sim) = YES;
*lmb activated
simrep('Agri20') = YES;
simrep('DemD20') = YES;

*- set 1 to avoid solving demand calibration model
ifMakeTab = 1 ;

$include '%incF%\Base.inc'
$include '%incF%\decl.inc'
$include '%incF%\model.inc'
$include '%incF%\inical.inc'




set treport(t) /2018*2050/

set asim(sim) ; asim(sim) = no ;

file csv / %odir%\results.csv / ;
put csv ;
put "Simulation,Variable,Sector,Qualifier,Year,Value" / ;
csv.pc=5 ;
csv.nd=9 ;

file samcsv / %odir\samRes.csv / ;
scalar ifSamCsv / 0 / ;
if(ifSamCsv,
   put samcsv ;
   put "Simulation,rLab,cLab,Year,Value" / ;
   samcsv.pc=5 ;
   samcsv.nd=9 ;
) ;




loop(sim,

   put screen ;
   put // "Processing data for simulation ", sim.tl // ;
   putclose;
   put_utility 'gdxin' / "%odir%\"sim.tl ;
   execute_loadpoint ;

$include '%incF%\postsim.inc'
) ;
