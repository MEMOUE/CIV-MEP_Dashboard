scalars

    ifDmg  Set to 1 to activate damages
    / 0 /
    ifDmg1  Set to 1 to activate damages
    / 0 /
    ifVint Set to 1 for capital vintages (Careful!!! No vintage is not tested!)
    / 1 /
    ifSAM  Calculates post-sim SAM if one
    / 0 /
    calibCDE set to 1 to calibrate CDE functions
    / 1 /
    ifCreateBB creates the gdx from basebridge if set to 1
    / 1 /
    ifComp Set to 1 for comparative static simulations
    / 0 /
    ifCDE Set to 1 for using the CDE utility function
    / 1 /
    ifLoad "Flag to indicate whether a baseline has been loaded or not"
    / 0 /
    ifMakeTab  Set to 1 to run maketab.gms
    /1/

*change closure for foreign capital by setting 1 for one of the flags:
*capRFix for fixed capital account relative to GDP
*capFix for fixed capital account in levels
*capFlexGTAP for flexible capital account closure following GTAP
*capFlexUSAGE for flexible capital account closure following USAGE
scalar ifCapfix       / 0 /
scalar ifCapRfix      / 1 /
scalar ifCapFlexGTAP  / 0 /
scalar ifCapFlexUSAGE / 0 /
scalar ifCapFlexA1    / 0 /
scalar ifCapFlexA3    / 0 /
;

*- if solution resumes from a point set to 1 
$setglobal resume 0


$setglobal BridgeFile Database_CIV.xlsx

*-used in emission calculations (country's code in GTAP - has to be within double quotes)
$setglobal RegGtapName CIV

SET
   tf              all time /2019*2100 /
   t(tf)           sim time / 2021*2030/
   t0(t)           Base year / 2021 /
;
* put simulation names here
SET sim
/
BaU              Business as Usual

/
