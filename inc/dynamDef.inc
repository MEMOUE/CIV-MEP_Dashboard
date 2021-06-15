$include '%incF%\Base.inc'
$include '%incF%\decl.inc'
$include '%incF%\model.inc'
$include '%incF%\inical.inc'

if(ifCal eq 0,

*   $$if exist "%inBaUGDX%" execute_loadpoint "%inBaUGDX%" ;
   execute_loadpoint "%inBaUGDX%" ;

   xfT(oa,t) = xfd.l(oa,t) ;
   brateScale(t)= brateU.l(t);
   ifLoad = 1 ;

) ;

if(ifcal=0,
   rshrGDPT(f,t) = rshrGDP.l(f,t);
);
