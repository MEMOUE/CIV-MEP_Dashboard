scalars

    ifDmg  Set to 1 to activate damages
    / 0 /
    ifVint Set to 1 for capital vintages (Careful!!! No vintage is not tested!)
    / 1 /
    ifSAM  Calculates post-sim SAM if one
    / 1 /
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
 ;

*- if solution resumes from a point set to 1 (Experimental, be careful!!! )
$setglobal resume 0

*-used in emission calculations (country's code in GTAP - has to be within double quotes)
$setglobal RegGtapName VNM

SET
   tf              all time /2018*2100 /
   t(tf)           sim time / 2018*2040 /
*   t(tf)           sim time / 2018*2025 /
   t0(t)           Base year / 2018 /
;
* put simulation names here
SET sim
/
BaU
carbtax
/
