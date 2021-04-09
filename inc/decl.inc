set g Government accounts /
   psb               Production subsidies
   ptx               Production taxes
   otx               Other taxes
   mtx               Import taxes
   etx               Export taxes
   dtx               Direct taxes
   atx               Commodity taxes
   ctx               Emmisson taxes
   ftx               Factor taxes
/ ;

set n Transport nodes /
   d  Domestic
   x  Export
   m  Import
/ ;

set nipa GDP components /
   cons
   govt
   invt
   ginvt
/

;

set map_adpInv(f,adpinv)
*/
*i-CGDS.i-adpPri
*g-govt.i-adpPub
*/
;

map_adpInv(f,adpinv) = NO ;

set mapn(oa,nipa) ;

mapn(h,   "cons") = yes ;
mapn(gov, "govt") = yes ;
mapn(inv, "invt") = yes ;
mapn(ginv, "ginvt") = yes ;
set acal(a) ;

set dinst(inst) Subset of domestic institutions ;
loop(row,
   dinst(inst)$(not mapinst(row,inst)) = yes ;
) ;

set agsima(a)
/
a-agr
a-frs
/
;

alias(k,kp) ; alias(k,kk) ; alias(instp,iinst);

scalar ifDelSt / 1 / ;
scalar ifLand  / 1 / ;

parameter    walrasT(t);

variables

*  Production variables

   nd(a,t)              "Non energy aggregate intermediate demand"
   vav(a,v,t)           "Value added plus energy bundle"
   pxv(a,v,t)           "Unit cost by vintage"
   px(a,t)              "Average unit cost"
   pp(a,t)              "Producer price"
   xf(a,fp,t)         "Demand for factor f"
   lab1(a,v,t)          "Demand for aggregate unskilled labor by vintage"
   kse(a,v,t)           "Demand for KSE bundle by vintage"
   pva(a,v,t)           "Value added price by vintage"
   ksk(a,v,t)           "Demand for KSK bundle by vintage"
   xnrgp(a,v,t)         "Demand for energy bundle by vintage"
   pkse(a,v,t)          "Price of KSE bundle by vintage"
   kd(a,v,t)            "Demand for capital by vintage"
   lab2(a,v,t)          "Demand for aggregate skilled labor by vintage"
   pksk(a,v,t)          "Price of KSK bundle by vintage"
   ld(a,l,t)            "Demand for labor by skill"
   plab1(a,v,t)         "Price of aggregate unskilled labor by vintage"
   plab2(a,v,t)         "Price of aggregate killed labor by vintage"

   pswage(a,l,t)         "Sectoral wage by skill including tax"
   swage(a,l,t)         "Sectoral wage by skill"

   pk(a,v,t)            "Sectoral price of capital by vintage"
   pk_pt(a,v,t)         "Tax inclusive Sectoral price of capital by vintage"
   pnrgp(a,v,t)         "Sectoral price of energy bundle by vintage"
   pnd(a,t)             "Price of non energy aggregate intermediate demand"
   xpv(a,v,t)           "Output by vintage"
   pva(a,v,t)           "Price of value added plus energy bundle"
   xp(a,t)              "Gross output"

   x(a,i,t)             "Domestic production of good i produced by activity a"
   p(a,i,t)             "Price of good i produced by activity a"
   xs(i,t)              "Supply of good i produced domestically"
   ps(i,t)              "Supply price of good i"
   delst(i,t)           "Stock changes assumed from domestic production"
   mdelst(i,t)          "Imported stocks"
   ElecMix(a,i,t)       "Electricity mix"
*  Income variables

   kapy(t)              "Gross profits"
   yh(h,t)              "Total household income"
   gini(t)              "Gini coefficient"
*   ye(entr,t)           "Total enterprise income"
   aps(h,t)             "Average propensity to save"
   chims(t)             "Shifter on marginal propensity to save"
   savh(h,t)            "Nominal household saving"
   totTr(inst,t)        "Total value of transfers per institution"
   debtStkD(t)          "domestic Debt stock"
   debtStkF(t)          "foreign Debt stock"
   debtStkT(t)          "total Debt stock"
   debtGDP(t)           "debt to GDP ratio"
   debtPay(inst,t)      "Debt payment"
   debtNew(inst,t)      "Debt New"
   debtNewT(t)          "Total Debt New"
   rDebtStkD(t)         repayment ratio for domestic debt
   rDebtStkF(t)         repayment ratio for foreign debt
   rDebtStk(t)          repayment ratio for domestic and foreign debt
   DebtIntF(t)          Interest on foreign debt
   DebtIntD(t)          Interest on domestic debt

   yg(g,t)              "Vector of government revenues"
   ygov(t)              "Total government revenues"
   gtax(t)              "Government direct taxes"
   dgovtax(t)           "Direct tax rate on government"
   savg(t)              "Nominal government savings"
   rsg(t)               "Real government savings"

   entrY(entr,t)        "Enterprise income"
   entrTax(entr,t)      "Enterprise direct taxes"
   dentrTax(entr,t)     "Direct tax rate on enterprises"
   savEntr(entr,t)      "Enterprise savings"
   apsEntr(entr,t)      "Enterprise savings rate"

   savf(t)              "Foreign investment in foreign currency terms"

   transfers(inst,instp,t) "Transfers across institutions"
   rowtransfers(inst,t)    "Exogenous transfers from ROW in foreign currency units"

*  Aggregate expenditure variables

   yf(oa,t)             "Aggregate nominal expenditures on goods and services"
   xfd(oa,t)             "Aggregate real expenditurs on goods and services"
   pf(oa,t)             "Aggregate expenditure price index"

*  CDE variables

   consScale(h,t)       "Scaling factor in household demand equation"
   xkf(h,k,t)           "Demand for bundled commodities"
   uh(h,t)              "Household utility function"
   hpop(h,t)            "Household population"

   eh(h,k,t)            "CDE expansion parameters"
   bh(h,k,t)            "CDE substitution parameters"

   incelas(h,k,t)       "Income elasticity"
   ued(h,k,kp,t)        "Uncompensated demand elasticity"
   ced(h,k,kp,t)        "Compensated demand elasticity"
   ape(h,k,kp,t)        "Allen partial elasticity"
   uedLoss
   incElasLoss


*  Household demand variables

   pkf(h,k,t)           Price of bundled commodities
   xkfnnrg(h,k,t)       Aggregate non energy demand
   xkfnrg(h,k,t)        Aggregate energy demand
   pkfnnrg(h,k,t)       Price of aggregate non energy demand
   pkfnrg(h,k,t)        Price of aggregate energy demand
   xkfshr(h,k,t)        Budget shares

*  Other demand variables

   xfnnrg(f,t)          Other final demand demand for non energy aggregate
   xfnrg(f,t)           Other final demand demand for energy aggregate
   pfnnrg(f,t)          Other final demand price of non energy aggregate
   pfnrg(f,t)           Other final demand price of energy aggregate

   xmarg(j,t)           Demand for margin good j
   pmarg(j,t)           Price of margin good j

*  Trade variables

   xa(i,aa,t)           Armington demand
   xat(i,t)             Aggregate Armington demand
   pa(i,t)              Armington price
   paf(i,aa,t)          Tax inclusive Armington price

   xd(i,t)              Domestic supply of domestically produced goods
   pd(i,t)              Producer price of domestic supply
   pda(i,t)             Agents price of domestic supply
   xe(i,t)              Domestic supply of exported goods
   pe(i,t)              Producer price of exported goods
   pwe(i,t)             World price of domestic exports

   xm(i,t)              Imports
   pwm(i,t)             World price of domestic imports
   pma(i,t)             Agents price of imports

*  Factor supplies

   lsT(l,t)             Aggregate labor supply
   wage(l,t)            Aggregate wage
   ls(a,l,t)            Sectoral labor supply

   tland(lnd,t)             Total land supply
   ptland(lnd,t)            Average price of land
   pland(a,lnd,t)           Price of land by sector
   pland_pt(a,lnd,t)        Tax inclusive Price of land by sector
   kxrat(a,t)           Capital output ratio for old vintages
   rrat(a,t)            Rate of return of old capital relative to new capital
   trent(t)             Economy wide rate of return to new capital

   kaps(t)              Aggregate capital stock normalized
   kstock(t)            Aggregate capital stock in level
   invGFact(t)          Investment growth factor for multiple time steps
   depr(t)              Depreciation rate

   v_chiLs(l,t)         labor supply shifter variable
   FLFP(l,t)            female labor force participation rate
   FLFPTot(t)           total female labor

*-Demographics
   pop(cohorts,t)       Population

   unemp(t)             Unemployed population
   awage                Average wage (mcp with unemployed population)
   deprate(cohorts,t)   Dependency ratio by age cohort
   popAge(age,t)        poplulation at each age
*   brate(l,t)           birth rate
   brateU(t)            birth rate
   drate(age,t) death rate

*  Emission variables

   emiComm(em,emSrc,aa,t)      Emissions for each cell of the SAM
   emiFact(em,fp,a,t)      Emissions for each cell of the SAM
   emiXP(em, a, t)      Emissions for overall activity levels
   emiLUCF(em,a,t)         Emissions from land use change
   emiTot(em,t)         Total emissions
   emiOth(em,t)         Exogenous other emissions
   emiGHG(t)            Greenhouse gas emissions
   emical(t)            Emission Calibration factor
   emiSecA(em,aa,t)     Emissions by Sector

   emPerm(em,aa,t)     Emission permissions
   emBuy(em,aa,t)      Bought amount of emission permission
   emRev(em,aa,t)      Revenue from emission permission
   emSupply(em,t)      Emission permission sold
   emTot(em,t)         Total amount of emissions

*  Macro variables

   tdelst(t)            Aggregate nominal change in stocks
   rtdelst(t)           Aggregate real change in stocks
   pdelst(t)            Aggregate change in stocks price deflator

   totExp(t)              Aggregate nominal exports
   rTotExp(t)             Aggregate real exports
   pexp(t)              Aggregate export price deflator
   totimp(t)              Aggregate nominal imports
   rtotimp(t)             Aggregate real imports
   pimp(t)              Aggregate import price deflator

   pgdpmp(t)            GDP at market price deflator
   gdpmp(t)             Nominal GDP at market price
   rgdpmp(t)            Real GDP at market price

   rgdppc(t)            Real GDP per capita
   ggdppc(t)            Per capita GDP growth

   pgdpfc(t)            GDP at factor cost excl indirect taxes deflator
   gdpfc(t)             GDP at factor cost excl indirect taxes
   rgdpfc(t)            Real GDP at factor cost excl indirect taxes

   rshrGDP(f,t)         Real share of GDP
   nshrGDP(f,t)         Nominal share of GDP

   pnum(t)              Choice of domestic deflator

   walras               Walras law

*  Productivity variables

   gl(t)                Uniform labor productivity shifter
   lambdan(a,v,t)       Productivity of intermediate inputs
   lambdav(a,v,t)       Productivity of value added bundle
   lambdat(a,lnd,t)         Land productivity
   lambdal(a,l,t)       Labor producitivity
   lambdak(a,v,t)       Capital productivity
   lambdaep(a,e,v,t)    Energy efficiency in production
   lambdaeh(h,e,k,t)    Energy efficiency in household demand
   lambdaef(f,e,t)      Energy efficiency in other final demand
   tfp(t)               VA productivity shifter
   tfpAct(a,t)          Activity tfp shifter

*  Policy variables



   tFac(a,fp,t)           Factor tax
   rtFac(a,fp,t)          Real Factor tax
   tFac0(a,fp,t)          Factor tax base level
   tFacD0(t)              Factor tax additive adjuster for all dimensions
   tFacD1(a,t)            Factor tax additive adjuster for activity a
   tFacD2(fp,t)           Factor tax additive adjuster for factor fp
   tFacM0(t)              Factor tax multiplicative adjuster for all dimensions
   tFacM1(a,t)            Factor tax multiplicative adjuster for activity a
   tFacM2(fp,t)           Factor tax multiplicative adjuster for factor fp
   tfacMLab(t)            Factor tax multiplicative adjuster for labor
   tfacMCap(t)            Factor tax multiplicative adjuster for capital
   tfacMlnd(t)            Factor tax multiplicative adjuster for land


   tpsb(a,t)              Production Subsidy
   tpsb0(a,t)             Production Subsidy base level
   tpsbD0(t)              Production Subsidy additive adjuster for all dimensions
   tpsbD1(a,t)            Production Subsidy additive adjuster for activity a
   tpsbM0(t)              Production Subsidy multiplicative adjuster for all dimensions
   tpsbM1(a,t)            Production Subsidy multiplicative adjuster for activity a

   tPrd(a,t)              Production Tax
   tPrd0(a,t)             Production Tax base level
   tPrdD0(t)              Production Tax additive adjuster for all dimensions
   tPrdD1(a,t)            Production Tax additive adjuster for activity a
   tPrdM0(t)              Production Tax multiplicative adjuster for all dimensions
   tPrdM1(a,t)            Production Tax multiplicative adjuster for activity a

   tExp(i,t)              Export tax
   tExp0(i,t)             Export tax base level
   tExpD0(t)              Export tax additive adjuster for all dimensions
   tExpD1(i,t)            Export tax additive adjuster for activity a
   TExpM0(t)              Export tax multiplicative adjuster for all dimensions
   tExpM1(i,t)            Export tax multiplicative adjuster for commodity i

   tVat(i,n,t)            Value added tax
   tVat0(i,n,t)           Value added tax base level
   tVatD0(t)              Value added tax additive adjuster for all dimensionsnsion
   tVatD1(i,t)            Value added tax additive adjuster for commodity i
   tVatD2(n,t)            Value added tax additive adjuster for source n
   tVatM0(t)              Value added tax multiplicative adjuster for all dim
   tVatM1(i,t)            Value added tax multiplicative adjuster for commodity i
   tVatM2(n,t)            Value added tax multiplicative adjuster for source n

   tImp(i,t)              Import tax
   tImp0(i,t)             Import tax base level
   tImpD0(t)              Import tax additive adjuster for all dimensions
   tImpD1(i,t)            Import tax additive adjuster for commodity i
   tImpM0(t)              Import tax multiplicative adjuster for all dimensions
   tImpM1(i,t)            Import tax multiplicative adjuster for commodity i

   tEmi(em,aa,t)          Agent specific emission tax
   rtEmi(em,aa,t)         Agent specific emission tax
   tEmi0(em,aa,t)         Agent specific emission tax base level
   tEmiD0(t)              Agent specific emission tax additive adjuster for all dimensionsnsion
   tEmiD1(em,t)           Agent specific emission tax additive adjuster for emission em
   tEmiD2(aa,t)            Agent specific emission tax additive adjuster for agent aa
   tEmiM0(t)              Agent specific emission tax multiplicative adjuster for all dim
   tEmiM1(em,t)           Agent specific emission tax multiplicative adjuster for emission em
   tEmiM2(aa,t)           Agent specific emission tax multiplicative adjuster for agent aa

   tPIT(h,t)              Personal income tax
   tPIT0(h,t)             Personal income tax base level
   tPITD0(t)              Personal income tax additive adjuster for all dimensions
   tPITD1(h,t)            Personal income tax additive adjuster for household h
   tPITM0(t)              Personal income tax multiplicative adjuster for all dimensions
   tPITM1(h,t)            Personal income tax multiplicative adjuster for household h

   tCIT(entr,t)           Corporate income tax
   tCIT0(entr,t)          Corporate income tax base level
   tCITD0(t)              Corporate income tax additive adjuster for all dimensions
   tCITD1(entr,t)         Corporate income tax additive adjuster for enterprise entr
   tCITM0(t)              Corporate income tax multiplicative adjuster for all dimensions
   tCITM1(entr,t)         Corporate income tax multiplicative adjuster for enterprise entr

   tDr(t )                Personal and Corporate income tax multiplicative adjuster

   tmAll(t)               Shifter for all taxes

   tPaf(i,aa,t)           Agent specific commodity tax
   tPaf0(i,aa,t)          Agent specific commodity tax base level
   tPafD0(t)              Agent specific commodity tax additive adjuster for all dimensions
   tPafD1(i,t)            Agent specific commodity tax additive adjuster for commodity i
   tPafD2(aa,t)           Agent specific commodity tax additive adjuster for agent aa
   tPafM0(t)              Agent specific commodity tax multiplicative adjuster for all dimensions
   tPafM1(i,t)            Agent specific commodity tax multiplicative adjuster for commodity i
   tPafM2(aa,t)           Agent specific commodity tax multiplicative adjuster for agent aa

*  Exogenous variables

   tmg(i,n,t)           Trade and transport margins
   pwmROW(i,t)          Global price of imports
   pweROW(i,t)          Global export price
   er(t)                Exchange rate

*-  CC damages
   dmgTfpAct(a,t)          CC damage to sector TFP
   dmgLambdaL_HH(a,l,t)    CC damage to human health
   dmgLambdaL(a,l,t)       CC damage to labor productivity
   dmgAtLand(lnd,t)        CC damage to land supply
   dmgChie(i,t)            CC damage to land supply
   dmgLambdaEh(h,i,k,t)    CC damage to household energy demand
   dmgDepr(t)              CC damage to capital stock
   dmgShftTFP(t)
   dmgShftLambdaL_HH(t)
   dmgShftLambdaL(t)
   dmgShftLand(t)
   dmgShftChie(t)
   dmgShftLambdaEh(t)
   dmgShftDepr(t)
   adpInvShr(oa,t)         Share of adaptation investment in public and private investment;
   ;

parameters
*Calvin add parameters for simulations
   prodeffct(a)   productivity effect related to public investment
   brateScale(t)  birth rate scaling parameter

*Production parameters

   and(a,v,t)           ND bundle CES share parameter
   ava(a,v,t)           VA+NRG bundle CES share parameter
   sigmap(a,v)          Substitution elasticity between ND and VA bundles

   aland(a,lnd,t)         Land share parameter in VA+NRG bundle
   alab1(a,v,t)         Unskiled labor bundle share parameter in VA+NRG bundle
   akse(a,v,t)          K+S+E share parameter in VA+NRG bundle
   sigmav(a,v)          Capital (+E) labor substitution elasticity

   aksk(a,v,t)          KS share parameter in KSE bundle
   ae(a,v,t)            Energy bundle share parameter in KSE bundle
   sigmak(a,v)          Capital energy substitution elasticity

   ak(a,v,t)            Capital share parameter in K+SK bundle
   alab2(a,v,t)         Skilled labor share parameter in K+SK bundle
   sigmaks(a,v)         Capital skilled labor substitution elasticity

   ald(a,l,v,t)         Labor by skill share parameters in AL bundle
   sigmaul(a,v)         Intra-unskilled substitution elasticity
   sigmasl(a,v)         Intra-skilled substitution elasticity

   aio(i, a, t)         IO coefficients in ND bundle
   sigman(a)            Intra-IO substitution elasticity

   aep(e, a, v, t)      Energy by carrier share parameter in NRG bundle
   sigmae(a, v)         Intra-fuel substitution elasticity

   ap(a,i,t)            CET share parameters for domestic make matrix
   omegap(a)            CET elasticity of domestic make matrix
   as(a,i,t)            CES share parameters for domestic use table
   sigmas(i)            CES elasticity for domestic use table

   chiP(a,i)            Supply by activity price normalizer
   gammaP(a,i,t)        Supply by activity price shifter

   TfpLoss(a)         tfp Loss in activities by the last year in the baseline

*  Income parameters

   chit(h,lnd,t)            Share of land income going to household h
chitentr(entr,lnd,t)            Share of land income going to enterprise entr
*Calvin addition to account for natural ressource spayment to government
   chiTGov(gov,lnd,t)       Share of land income going to government gov
   chil(h,l,t)          Share of labor income l going to household h
chikh(h,t)           Share of capital income going to household h

   chikGov(gov,t)       Share of capital income going to government
   chikEntr(entr,t)     Share of capital income going to enterprises
   chiTr(inst,instp)    Transfer shares
   chiTotTr(inst)       Total transfer share of incomes of domestic institutions

*  Demand parameters

*  Household demand

   kron(k,kp)           Kronecker factor

   akf(h,k,t)           Share parameter for top level household demand
   aknnrg(h,k)          CES non energy share parameter for top level final demand bundle
   aknrg(h,k)           CES energy share parameter for top level final demand bundle
   sigmac(h,k)          CES substitution elasticity between energy and non energy

   af(h,i,k,t)          CES share parameter for second level final demand bundles
   sigmacaa(h,k)        CES substitution elasticity across non energy goods
   sigmacae(h,k)        CES substitution elasticity across energy goods

   transmat(i, k, h)    Transition matrix in household consumption

*  Other demand

   sigmaf(f)            CES elasticity of substitution for top level final demand bundle
   afnnrg(f,t)          CES non energy share parameter in other final demand
   afnrg(f,t)           CES energy share parameter in other final demand

   aff(f,i,t)           CES Armington demand share parameters in other final demand
   sigmafaa(f)          CES substitution across non energy goods in other final demand
   sigmafae(f)          CES substitution across energy goods in other final demand

   amarg(i,j)           CES share parameters for margin demand
   sigmamg(j)           CES substitution for margin demand

*  Armington CES function

   ad(i,t)              Domestic demand share parameter
   am(i,t)              Import demand share parameter
   sigmam(i)            Armington CES elasticity

   chiPDa(i)            Domestic price normalization factor
   chiPMa(i)            Import price normalization factor
   chiPA(i)             Armington price normalization factor
   gammamd(i,t)         Domestic price shifter
   gammamm(i,t)         Import price shifter

*  Supply CET function

   gd(i,t)              Domestic supply share parameter
   ge(i,t)              Export supply share parameter
   sigmax(i)            CET elasticity

   chiPD(i)             Domestic price normalization factor
   chiPE(i)             Export price normalization factor
   chiPS(i)             Supply price normalization factor
   gammaxd(i,t)         Domestic price shifter
   gammaxe(i,t)         Export price shifter

*  Export demand function

   chie(i,t)            Export demand shifter
   etae(i)              Export demand elasticity

   chiPWE(i)            Export price normalizer
   gammaPWE(i,t)        Export price shifter

   chiPWEx(i)           World export price normalizer

*  Import supply function

   chim(i,t)            Import supply shifter
   omegam(i)            Import supply elasticity

*  Labor market parameters

   chiLs(l,t)           Labor supply shifter by skill
   epsL(l)              Labor supply elasticity by skill

   gammal(a,l,t)        CET sectoral labor supply share paramters
   phiw(a,l,t)          Wage distribution parameter
   omegal(l)            CET elasticity of transformation of labor across sectors

   epsEdu(l,t)          elasticity of labor supply shifter to education spending
   epsHea(l,t)          elasticity of labor supply shifter to health spending
   epsCul(l,t)          elasticity of labor supply shifter to culture index
   culIndex(l,t)        cultural effect index (higher = less women can work)
   chiLambdaL(l,t)      LAbor productivity shifter


*  Land market parameters
   philand(a,t)     Land technology parameter

   atland(lnd,t)        Aggregate land supply shift parameter
   omegatl(lnd)          Aggregate land supply elasticity

   alands(a,lnd,t)      Land transformation share parameter
   omegat(lnd)         Land transformation elasticity

*  Capital market parameters for comp static version of model

   chiKs(t)             Capital supply shifter
   epsK                 Capital supply elasticity

   gammak(a,t)          CET sectoral capital supply share paramters
   omegak               CET elasticity of transformation of capital across sectors

*  Capital market parameters for dynamic version of the model

   invElas(a)           Dis investment elasticity for declining sectors

*  Emission coefficients

   rhoEmi(em,emSrc,js)     Emissions per unit of demand
   rhoEmiFac(em,fp,js)     Emissions per unit of demand
   rhoEmiXP(em, a)      Emissions per unit of activity
   rhoEmiLnd(em,lnd,a)      Average carbon intensity by land use CO2 per hectare
   chiEmi(em,emSrc,aa,t)   Shifters on emissions per unit of demand
   chiEmiFac(em,fp,aa,t)   Shifters on emissions per unit of demand
   chiEmiXP(em,a,t)     Shifters on emissions per unit of activity
   phiEmi(em,emSrc,aa)      "Level of participation in emissions tax (0 = no, 1 = full)"

*  Dynamic parameters

*
   exprod(a,v,t)        Exogenous productivity assumptions
   alphal(a,l,t)        Labor productivity sector shifter
   betal(a,l,t)         Labor productivity sector multiplier

   yexo(a,t)            Autonomous yield improvement
   kprod(a,t)           Autonomous improvement in capital productivity

   geP(e,a,v,t)         Growth in energy efficiency in production
   geC(h,e,k,t)         Growth in energy efficiency in consumption
   geF(f,e,t)           Growth in energy efficiency in other final demand

   aps0(h)              Initial household saving rate

   xfT(oa,t)            Baseline volume of expenditures

   ldFlag(a,l)          Labor demand flag

*  Output parameters

   fshr(fp,a,t)      "Factor share in VA"
   qdel(fp,a,t)      "Growth in volume"
   ldel(fp,a,t)      "Growth in productivity"

   oscale
   samT(is,js,t)     Post-sim SAM
   samTDiff(is,js,t)     Post-sim SAM
   samTBal(is,t)     Post-sim SAM balance


   fshr(fp,a,t)      "Factor share in VA"
   qdel(fp,a,t)      "Growth in volume"
   ldel(fp,a,t)      "Growth in productivity"

   work

*- CC damage function parameters
   tempD(t)          Temperature change
   dmgTfpAct0(a,t)
   dmgTfpAct1(a,t)
   dmgTfpAct2(a,t)
   dmgTfpAct3(a,t)
   dmgTfpAct4(a,t)
   dmgTfpAct5(a,t)
   dmgTfpAct6(a,t)
   dmgLambdaL_HH1(a,l,t)
   dmgLambdaL0(a)
   dmgLambdaL1(a)
   dmgLambdaL2(a)
   dmgAtLand0(lnd,t)
   dmgAtLand1(lnd,t)
   dmgChie0(i,t)
   dmgChie1(i,t)
   dmgChie2(i,t)
   dmgLambdaEh0(h,i,k,t)
   dmgLambdaEh1(h,i,k,t)
   dmgdepr1(t)
   dmgdepr2(t)
   dmgdepr3(t)
   dmgdepr4(t)
   dmgdepr5(t)
   dmgdepr6(t)
   dmgdepr7(t)

   ;

parameter
   yf0
   diagnostics(diag, t)  diagnostic measures about model solve
   emiGHGTarg(t)         emission target
;;


alias(v,vp) ;

equations
   ndeq(a,t)                     Demand for ND bundle
   vaveq(a,v,t)                  Demand for VA+NRG bundle
   pxveq(a,v,t)                  Unit cost by vintage
   pxeq(a,t)                     Average unit cost
   ppeq(a,t)                     Output price

   landdeq(a,lnd,t)              Demand for land
   lab1eq(a,v,t)                 Demand for unskilled labor bundle
   kseeq(a,v,t)                  Demand for K+S+E bundle
   pvaeq(a,v,t)                  Price of VA+E bundle

   kskeq(a,v,t)                  Demand for KSK bundle by vintage
   xnrgpeq(a,v,t)                Demand for NRG bundle by vintage
   pkseeq(a,v,t)                 Price of K+S+E bundle

   kdeq(a,v,t)                   Demand for capital by vintage
   kdToteq(a,fp,t)               Total Demand for capital
   lab2eq(a,v,t)                 Demand for aggregate skilled labor by vintage
   pkskeq(a,v,t)                 Price of KSK bundle by vintage
   pk_ptEQ(a,v,t)                Tax inclusive price of capital by vintage

   ldeq(a,l,t)                   Labor demand by skill
   plab1eq(a,v,t)                Price of aggregate unskilled labor bundle
   plab2eq(a,v,t)                Price of aggregate skilled labor bundle

   xap1eq(i,a,t)                 Demand for non energy intermediate inputs
   pndeq(a,t)                    Price of ND bundle
   xap2eq(e,a,t)                 Demand for energy intermediate inputs
   pnrgpeq(a,v,t)                Price of NRG bundle

   xeq(a,i,t)                    Supply of i from activity a
   xpeq(a,t)                     CET revenue function

   peq(a,i,t)                    Demand for i from activity a
   xseq(i,t)                     CES revenue function

   kapyeq(t)                     Gross profits
   yheq(h,t)                     Gross household income
   ginieq(t)                     Gini coefficient
   deprateEq (cohorts,t)         Dependency ratio definition
   apseq(h,t)                    Household saving rate
   hhtreq(h,inst,t)              Total household transfers
   yfheq(h,t)                    Household expenditures on goods and services
   savheq(h,t)                   Household savings

   tPiteq(h,t)                   Household direct taxes
   tFacEq(a,fp,t)                Factor tax definition
   rtFacEq(a,fp,t)                Factor tax definition
   tpsbEq(a,t)                   Production subsidy definition
   tPrdEq(a,t)                   Production tax definition
   tExpEq(i,t)                   Export tax definition
   tImpEq(i,t)                   Import tax definition
   tEmiEq(em,aa,t)               Agent specific emission tax definition
   rtEmiEQ(em,aa,t)              Real emission Tax
   tPITEq(h,t)                   Personal income tax definition
   tCITEq(entr,t)                Corporate income tax definition
   tVatEq(i,n,t)                 VAT tax definition
   tPafEq(i,aa,t)                Agent specific commodity tax definition

   ygftxeq(t)                    Revenues from factor taxes
   ygpsbeq(t)                    Revenues from production subsidies
   ygptxeq(t)                    Revenues from production taxes
   ygetxeq(t)                    Revenues from export tax
   ygotxeq(t)                    Revenues from sales or value added taxes
   ygmtxeq(t)                    Revenues from trade taxes
   yghtxeq(t)                    Revenues from direct household taxes
   ygatxeq(t)                    Revenues from commodity taxes
   ygctxeq(t)                    Revenues from carbon taxes

   ygoveq(gov,t)                 Gross government revenues
   gtaxeq(t)                     Government taxes
   govTreq(gov,inst,t)           Total government transfers
   savgeq(f,t)                   Nominal government savings
   rsgeq(t)                      Real government savings

   entrYeq(entr,t)               Enterprise income
   tCiteq(entr,t)             Enterprise taxes
   savEntreq(entr,t)             Enterprise savings
   entrTreq(entr,inst,t)         Total enterprise transfers

   dtransferseq(inst,instp,t)    Allocation of total domestic transfers across destinations
   rowtransferseq(inst,row,instp,t)  Transfers from ROW

   inveq(f,t)                    Investment savings balance


   hpopeq(h,t)                   Household population (currently constant base shares)
   consScaleeq(h,t)              Scaling factor used in CDE demand system
   xkfeq(h,k,t)                  Household demand for goods and services
   uheq(h,t)                     CDE utility function
   pfheq(h,t)                    Household expenditure deflator

*  Used for calibrating CDE demand system

   incelaseq(h,k,t)        Definition of income elasticity
   uedeq(h,k,kp,t)         Uncompensated demand elasticity
   cedeq(h,k,kp,t)         Compensated demand elasticity
   apeeq(h,k,kp,t)         Allen partial elasticity
   uedLosseq
   incelasLosseq
   incElasC1eq
   incElasC2eq(h,k,t)

   xkfnnrgeq(h,k,t)        Aggregate non energy demand
   xkfnrgeq(h,k,t)         Aggregate energy demand
   pkfeq(h,k,t)            Price of final demand goods
   xakfnnrgeq(h,i,t)       Final demand for produced non energy goods
   xakfnrgeq(h,i,t)        Final demand for produced energy goods
   pkfnnrgeq(h,k,t)        Price of aggregate non energy bubdle
   pkfnrgeq(h,k,t)         Price of aggregate energy bundle
   xkfshreq(h,k,t)         Budget shares

   xfnnrgeq(f,t)           Other final demand demand for non energy bundle
   xfnrgeq(f,t)            Other final demand demand for energy bundle
   pfeq(f,t)               Other final demand expenditure deflator
   xafnnrgeq(f,i,t)        Other final demand demand for non energy Armington goods
   xafnrgeq(f,e,t)         Other final demand demand for energy Armington goods
   pfnnrgeq(f,t)           Other final demand price of non energy bundle
   pfnrgeq(f,t)            Other final deamdn price of energy bundle

   xmargeq(j,t)            Demand for margin good j
   xamrgeq(i,j,t)          Armington demand for good i to deliver good j
   pmargeq(j,t)            Price of margin good j

   yfeq(oa,t)              Volume and or price split for aggregate expenditures

   pmaeq(i,t)              Agents price of imports
   pdaeq(i,t)              Agents price of domestic goods

   xateq(i,t)              Aggregate Armington demand
   xddeq(i,t)              Demand for domestic production
   xmeq(i,t)               Demand for imports
   paeq(i,t)               Armington price
   pafeq(i,aa,t)           Armington price inclusive of all taxes

   xdseq(i,t)              Domestic supply of production
   edseq(i,t)              Export supply of production
   pseq(i,t)               Total production
   peeq(i,t)               Domestic price of exports

   pweeq(i,t)              Border price of exports

   pwmeq(i,t)              Border price of imports

*  Labor market equilibrium

   lsTeq(l,t)              Aggregate labor supply
   lseq(a,l,t)             Sectoral labor supply
   wageeq(l,t)             Aggregate wage by skill
   pswageeq(a,l,t)         Wage with tax definition
   swageeq(a,l,t)          Labor market equilibrium
   unempeq(t)              unemployed population equation
   awageEq(t)              average wage equation (mcp with unemp)

*  Gender
   chiLseq(l,t)            social spending effect on labor supply
   FLFPEq(l,t)             Female labor force participation rate by labot type
   FLFPTotEq(t)            Total female labor force participation rate

*  Land market equilibrium

   tlandeq(lnd,t)              Aggregate land supply
   plandeq(a,lnd,t)            Land price by sector
   pland_ptEQ(a,lnd,t)         Land price by sector with tax
   ptlandeq(lnd,t)             Aggregate land price

*  Capital market equations in comparative static

   kapsCSeq(t)             Aggregate capital supply
   ksCSeq(a,v,t)           Sectoral capital supply
   trentCSeq(v,t)          Aggregate rent

*  Capital market equations in dynamics

   kxrateq(a,v,t)          Capital output ratio for old vintages
   rrateq(a,t)             Rate of return to old capital relative to new capital
   trenteq(t)              Economywide rate of return to new capital
   pkeq(a,v,t)             Sectoral rate of return to capital by vintage
   xpOldeq(a,v,t)          Determination of output with installed capital

*  Vintage production constraint

   xpNeweq(a,t)            Vintage production constraint

*  Macro identities

   tdelsteq(t)             Aggregate nominal change in stocks
   rtdelsteq(t,t)          Aggregate real change in stocks
   pdelsteq(t)             Change in stock deflator
   totexpeq(t)               Aggregate nominal exports
   rtotexpeq(t,t)            Aggregate real exports
   pexpeq(t)               Aggregate export price deflator
   totimpeq(t)               Aggregate nominal imports
   rtotimpeq(t,t)            Aggregate real imports
   pimpeq(t)               Aggregate import price deflator

   gdpmpeq(t)              Nominal GDP at market price
   rgdpmpeq(t)             Real GDP at market price
   pgdpmpeq(t)             GDP at market price deflator

   rgdppceq(t)             Definition of real GDP per capita
   ggdppceq(t)             Growth of per capita GDP

   gdpfceq(t)              Nominal GDP at factor cost
   rgdpfceq(t,t)           Real GDP at factor cost
   pgdpfceq(t)             GDP at factor cost deflator

   rshrGDPeq(f,t)          Real share of GDP
   nshrGDPeq(f,t)          Nominal share of GDP

   pnumeq(t)               Choice of domestic price deflator

   walraseq(t)             Walras law

*  Emissions module
   ElecMixEq(a,i,t)        electricity output
   emiCommeq(em,emSrc,aa,t)    Emissions per unit of demand
   emiFacteq(em,fp,a,t)   Emissions per unit of factor use
   emiLUCFeq(em,a,t)          Emissions from land use change
   emiProdeq(em,a,t)       Emissions per unit of activity
   emiToteq(em,t)          Total emissions
   emiGHGeq(t)             Total emissions of GHG in carbon equivalent
   emiSecAeq(em,aa,t)      Emissions by sector

*- Emission trading
   emRevDef(em,aa,t)       Revenue from sales of emission permissions
   emConstn(em,aa,t)       Constraint on emissions
   emBuyConst(em,t)        Emission buying-selling constraint
   emTotDef(em,t)          Total emissions definition


*  Demographics
    popAgeEq(age,t)         Paopulation in each age group definition
    BirthEq(t)              Number of births
*    brateEq(t)              Birth rate equation
*    drateEq(t)              Death rate equation
    popEq(cohorts,t)        Population equation

*  Dynamic equations

   invGFacteq(f,t)         Investment growth with multi year gaps
   kstockeq(f,t)           Capital accumulation equation with multi year gaps
   kapseq(t,t)             Capital normalization equation
   lambdaleq(a,l,t,t0)        Labor productivity growth equation


*-debt equations
   DebtStkDEq(t)           Domestic debt stock
   DebtStkFEq(t)           Foreign debt stock
   DebtStkTEq(t)           Total debt stock
   debtGDPEQ(t)            Debt to GDP ratio
   debtPayEq(inst,t)       Debt payments
   debtNewEq(inst,t)      New domestic debt
   debtNewTEq(t)      New total debt
   DebtIntFEQ(t,t0)
   DebtIntDEQ(t,t0)

*- climate change damages

   dmgTfpActEq(a,t)            CC damage to sector TFP
   dmgLambdaL_HHEq(a,l,t)      CC damage to human health
   dmgLambdaLEq(a,l,t)         CC damage to labor productivity
   dmgAtLandEq(lnd,t)          CC damage to land supply
   dmgChieEq(i,t)              CC damage to export supply
   dmgLambdaEhEq(h,i,k,t)      CC damage to household energy demand
   dmgDeprEq(t)          CC damage to capital stock

   dmgShftTFPEq(t,t0)
   dmgShftLambdaL_HHEq(t,t0)
   dmgShftLambdaLEq(t,t0)
   dmgShftLandEq(t,t0)
   dmgShftChieEq(t,t0)
   dmgShftLambdaEhEq(t,t0)
   dmgShftDeprEq(t,t0)

   ;

sets
   aact(a)       Active activities
   iact(i)       Active domestic commodities
   iarm(i)       Active Armington commodities
   iimp(i)       Active imports
   idom(i)       Active domestic supply
   iexp(i)       Active export supply
   akfact(h,k)   Active final demand cells
   xaact(i,aa)   Active Armington demand
   mgEncl(j)     Commodities that require margins
;
