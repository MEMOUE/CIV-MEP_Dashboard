oscale = 1/inscale ;

  put csv ;

loop((t,t0)$treport(t),
   loop(nipa,
      put sim.tl, "NIPA", "Val", nipa.tl, years(t):4:0, (oscale*sum(fd$mapn(fd,nipa), yf.l(fd,t))) / ;
      put sim.tl, "NIPA", "Vol", nipa.tl, years(t):4:0, (oscale*sum(fd$mapn(fd,nipa), xfd.l(fd,t))) / ;
    if(sum(fd$mapn(fd,nipa),1),
      put sim.tl, "NIPA", "PrD", nipa.tl, years(t):4:0, (100*sum(fd$mapn(fd,nipa), pf.l(fd,t)*xfd.l(fd,t0))
                                                          /  sum(fd$mapn(fd,nipa), pf.l(fd,t0)*xfd.l(fd,t0))) / ;
      );
   ) ;

   put sim.tl, "NIPA", "Val", "tdelst",  years(t):4:0, (oscale*tdelst.l(t)) / ;
   put sim.tl, "NIPA", "Vol", "rtdelst", years(t):4:0, (oscale*rtdelst.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "ptdelst", years(t):4:0, (100*pdelst.l(t)) / ;

   put sim.tl, "NIPA", "Val", "texp",  years(t):4:0, (oscale*totexp.l(t)) / ;
   put sim.tl, "NIPA", "Vol", "rtexp", years(t):4:0, (oscale*rtotexp.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "ptexp", years(t):4:0, (100*pexp.l(t)) / ;

   put sim.tl, "NIPA", "Val", "timp",  years(t):4:0, (oscale*totimp.l(t)) / ;
   put sim.tl, "NIPA", "Vol", "rtimp", years(t):4:0, (oscale*rtotimp.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "ptimp", years(t):4:0, (100*pimp.l(t)) / ;

   put sim.tl, "NIPA", "Val", "gdpmp",  years(t):4:0, (oscale*gdpmp.l(t)) / ;
   put sim.tl, "NIPA", "Vol", "rgdpmp", years(t):4:0, (oscale*rgdpmp.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "pgdpmp", years(t):4:0, (100*pgdpmp.l(t)) / ;



   put sim.tl, "NIPA", "Vol", "rgdppc", years(t):4:0, (oscale*rgdppc.l(t)) / ;
   put sim.tl, "NIPA", "Pct", "ggdppc", years(t):4:0, (100*ggdppc.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "gl",     years(t):4:0, (100*gl.l(t)) / ;

   put sim.tl, "NIPA", "Val", "gdpfc",  years(t):4:0, (oscale*gdpfc.l(t)) / ;
   put sim.tl, "NIPA", "Vol", "rgdpfc", years(t):4:0, (oscale*rgdpfc.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "pgdpfc", years(t):4:0, (100*pgdpfc.l(t)) / ;
   put sim.tl, "NIPA", "PrD", "trent",  years(t):4:0, (trent.l(t)) / ;

   loop(gov,
      put sim.tl, "sav", gov.tl, "(blank)", years(t):4:0, (oscale*savg.l(t)) / ;
   ) ;

   put sim.tl, "sav", "hhtot", "(blank)", years(t):4:0, (oscale*sum(h, savh.l(h,t))) / ;

   loop(h,
      put sim.tl, "sav", h.tl, "(blank)", years(t):4:0, (oscale*savh.l(h,t)) / ;
   ) ;
   loop(entr,
      put sim.tl, "sav", entr.tl, "(blank)", years(t):4:0, (oscale*savEntr.l(entr,t)) / ;
   ) ;

   loop(row,
      put sim.tl, "sav", row.tl, "(blank)", years(t):4:0, (oscale*er.l(t)*savf.l(t)) / ;
   ) ;
      put sim.tl, "savf", "(blank)", "(blank)", years(t):4:0, (oscale*savf.l(t)) / ;

   put sim.tl, "rsg", "(blank)", "(blank)", years(t):4:0, (oscale*rsg.l(t)) / ;
   loop(inv,
      put sim.tl, "inv",  inv.tl, "(blank)", years(t):4:0, (oscale*yf.l(inv,t)) / ;
      put sim.tl, "rinv", inv.tl, "(blank)", years(t):4:0, (oscale*xfd.l(inv,t)) / ;
   ) ;
   loop(stb,
      put sim.tl, "inv", stb.tl, "(blank)", years(t):4:0, (oscale*sum(i, chiPS(i)*ps.l(i,t)*delst.l(i,t) + er.l(t)*pwm.l(i,t)*(1+timp.l(i,t))*mdelst.l(i,t))) / ;
   ) ;

   loop(f,
      put sim.tl, "rshrGDP", "(blank)", f.tl, years(t):4:0, (rshrGDP.l(f,t)) / ;
      put sim.tl, "nshrGDP", "(blank)", f.tl, years(t):4:0, (nshrGDP.l(f,t)) / ;
        ) ;


*current account balance variables
      put sim.tl, "er","(blank)", "(blank)", years(t):4:0, (er.l(t)) / ;

   work = sum(i, chiPWE(i)*pwe.l(i,t)*xe.l(i,t)- pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t))) ;
      put sim.tl, "trb","(blank)", "(blank)", years(t):4:0, (oscale*work) / ;

   work = sum(i, chiPWE(i)*pwe.l(i,t)*xe.l(i,t));
      put sim.tl, "fexp","(blank)", "(blank)", years(t):4:0, (oscale*work) / ;

   work = sum(i, pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t))) ;
      put sim.tl, "fimp","(blank)", "(blank)", years(t):4:0, (oscale*work) / ;

   loop(i,
      put sim.tl, "fexp", i.tl, "(blank)", years(t):4:0, (chiPWE(i)*pwe.l(i,t)*xe.l(i,t)*oscale) / ;
      put sim.tl, "fimp", i.tl, "(blank)", years(t):4:0, (oscale*pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t))) / ;
        ) ;

$ontext
   work = sum(i$mapRep(i,isrep), chiPWE(i)*pwe.l(i,t)*xe.l(i,t));
      put sim.tl, "fexp",isrep.tl, "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(i$iagr(i), chiPWE(i)*pwe.l(i,t)*xe.l(i,t));
      put sim.tl, "fexp","c-agr", "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(i$iman(i), chiPWE(i)*pwe.l(i,t)*xe.l(i,t));
      put sim.tl, "fexp","c-man", "(blank)", years(t):4:0, (oscale*work) / ;

   work = sum(i$isrv(i), pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t)));
      put sim.tl, "fimp","c-srv", "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(i$iagr(i), pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t)));
      put sim.tl, "fimp","c-agr", "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(i$iman(i), pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t)));
      put sim.tl, "fimp","c-man", "(blank)", years(t):4:0, (oscale*work) / ;
$offtext


   Loop(isrep,
   work = sum(i$mapRep(i,isrep), chiPWE(i)*pwe.l(i,t)*xe.l(i,t));
      put sim.tl, "fexp",isrep.tl, "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(i$mapRep(i,isrep), pwm.l(i,t)*(xm.l(i,t)+mdelst.l(i,t)));
      put sim.tl, "fimp",isrep.tl, "(blank)", years(t):4:0, (oscale*work) / ;
   );


   work = 0;

loop((inst,instp)$(row(inst)),
     work = work + transfers.l(instp,inst,t)
     );
     put sim.tl, "inc","(blank)", "(blank)", years(t):4:0, (oscale*work) / ;


* Government budget variables
      put sim.tl, "ygov","(blank)", "(blank)", years(t):4:0, (oscale*ygov.l(t)) / ;

   loop(g,
      put sim.tl, "yg", g.tl, "(blank)", years(t):4:0, (oscale*yg.l(g,t)) / ;
       ) ;

   loop(entr,
      put sim.tl, "citRev", entr.tl, "(blank)", years(t):4:0, (oscale*tCit.l(entr,t) * entrY.l(entr,t)) / ;
       ) ;

      put sim.tl, "citRev", "Total", "(blank)", years(t):4:0, (oscale*sum(entr,tCit.l(entr,t) * entrY.l(entr,t))) / ;

*Calvin modif

*      work=sum(h,zkt.l(h,t));
*      put sim.tl, "zkt","(blank)", "(blank)", years(t):4:0, (oscale*work) / ;

   loop(h,
      put sim.tl, "pitRev",h.tl, "(blank)", years(t):4:0, (oscale*tPit.l(h,t) * yh.l(h,t)) / ;
      );

      work=sum(h, tPit.l(h,t) * yh.l(h,t));
      put sim.tl, "pitRev","Total", "(blank)", years(t):4:0, (oscale*work) / ;

      work= SUM(inst$SUM(gov,mapInst(gov,inst)),totTr.l(inst,t))+sum(gov,yf.l(gov,t));
      put sim.tl, "gexp","(blank)", "(blank)", years(t):4:0, (oscale*work) / ;



*incomes
   loop(h,
      put sim.tl, "yh", h.tl, "(blank)", years(t):4:0, (oscale*yh.l(h,t)) / ;
    hwork(h) = sum(l, chil(h,l,t)*sum(a$aact(a),swage.l(a,l,t)*xf.l(a,l,t)))
      put sim.tl, "laby",h.tl, "(blank)", years(t):4:0, (oscale*hwork(h)) / ;
      put sim.tl, "uh",h.tl, "(blank)", years(t):4:0, (oscale*uh.l(h,t)) / ;
      put sim.tl, "yfh",h.tl, "", years(t):4:0, (oscale*yf.l(h,t)) / ;
      put sim.tl, "xfh",h.tl, "", years(t):4:0, (oscale*xfd.l(h,t)) / ;
    hwork(h) = chikh(h,t)*kapy.l(t)
      put sim.tl, "capy",h.tl, "", years(t):4:0, (oscale*hwork(h)) / ;
   hwork(h) = sum((lnd,a), chit(h,lnd,t)*pland.l(a,lnd,t)*xf.l(a,lnd,t))
      put sim.tl, "landy",h.tl, "", years(t):4:0, (oscale*work) / ;

       ) ;

   work= sum(h, yf.l(h,t))/sum(h, xfd.l(h,t)) ;
   put sim.tl, "CPI","", "", years(t):4:0, (work) / ;

  put sim.tl, "kapy", "(blank)", "(blank)", years(t):4:0, (oscale*kapy.l(t)) / ;
  put sim.tl, "brateU", "(blank)", "(blank)", years(t):4:0, (brateu.l(t)) / ;
  put sim.tl, "flfptot", "(blank)", "(blank)", years(t):4:0, (flfptot.l(t)) / ;

   work = sum((lnd,a,h), chit(h,lnd,t)*pland.l(a,lnd,t)*xf.l(a,lnd,t))
      put sim.tl, "landy","", "", years(t):4:0, (oscale*work) / ;


  loop((instp,iinst),
     put sim.tl, "transf",instp.tl,iinst.tl, years(t):4:0, (oscale*transfers.l(instp,iinst,t))/ ;
        );

*aggregated industry variables
$ontext
   work = sum(a$srv(a),xp.l(a,t))
      put sim.tl, "xp","a-srv", "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(a$agr(a),xp.l(a,t))
      put sim.tl, "xp","a-agr", "(blank)", years(t):4:0, (oscale*work) / ;
   work = sum(a$man(a),xp.l(a,t))
      put sim.tl, "xp","a-man", "(blank)", years(t):4:0, (oscale*work) / ;
$offtext

Loop(isrep,
      work = sum(a$mapRep(a,isrep),xp.l(a,t))
      put sim.tl, "xp",isrep.tl, "(blank)", years(t):4:0, (oscale*work) / ;
      )

Loop(emiaa,
      work = sum(a$mapemi(emiaa,a),xp.l(a,t))
      put sim.tl, "xp",emiaa.tl, "(blank)", years(t):4:0, (oscale*work) / ;
      )


   loop(inst,
      put sim.tl, "toTR", inst.tl, "(blank)", years(t):4:0, (oscale*totTr.l(inst,t)) / ;
       ) ;

   loop(cohorts,
      put sim.tl, "Pop",  "(blank)", cohorts.tl, years(t):4:0, (pop.l(cohorts,t)/pscale) / ;
    ) ;

   loop(exr,
      put sim.tl, "exRates",  "(blank)", exr.tl, years(t):4:0, (exRates0(exr)) / ;
   ) ;

   work = sum(l,lsT.l(l,t))
      put sim.tl, "lst","tot", "(blank)", years(t):4:0, (oscale*work) / ;
loop(l,
      put sim.tl, "lst",l.tl, "(blank)", years(t):4:0, (oscale*lsT.l(l,t)) / ;
      );

*   loop(l,
*      put sim.tl, "wage",  "(blank)", l.tl,  years(t):4:0, (wage.l(l,t)) / ;
*      put sim.tl, "lsT",   "(blank)", l.tl,  years(t):4:0, (oscale*lsT.l(l,t)) / ;
*   ) ;

   loop(isrep,
   work$SUM(l$maprep(l,isrep),wage.l(l,t0)*lsT.l(l,t)) = SUM(l$maprep(l,isrep),wage.l(l,t)*lsT.l(l,t))/SUM(l$maprep(l,isrep),wage.l(l,t0)*lsT.l(l,t)) ;
   if(work>0,   put sim.tl, "wage",  "(blank)", isrep.tl,  years(t):4:0, (work) / ;);
   work= SUM(l$maprep(l,isrep),lsT.l(l,t)) ;
   if(work>0,   put sim.tl, "lsT",   "(blank)", isrep.tl,  years(t):4:0, (oscale*work) / ;);
   ) ;

   Loop(l,
   put sim.tl, "wage",   "(blank)", l.tl,  years(t):4:0, (wage.l(l,t)) / ;
   );

   work$SUM(l,wage.l(l,t0)*lsT.l(l,t)) = SUM(l,wage.l(l,t)*lsT.l(l,t))/SUM(l,wage.l(l,t0)*lsT.l(l,t)) ;
   if(work>0,   put sim.tl, "wage",  "(blank)", "Total",  years(t):4:0, (work) / ;);

*   loop(l, work = flfp.l(l,t) ;
*   if(work>0,   put sim.tl, "wage",  "(blank)", "Total",  years(t):4:0, (work) / ;);
*   );

   loop(oa,
      put sim.tl, "pf",  oa.tl, "(blank)",  years(t):4:0, (pf.l(oa,t)) / ;
   ) ;

   put sim.tl, "kstock",  "(blank)", "(blank)",  years(t):4:0, (kstock.l(t)) / ;

   put sim.tl, "pnum",  "(blank)", "(blank)",  years(t):4:0, (pnum.l(t)) / ;
  loop(lnd,
   put sim.tl, "ptland",  "(blank)", "(blank)",  years(t):4:0, (ptland.l(lnd,t)) / ;
   put sim.tl, "tland",   "(blank)", "(blank)",  years(t):4:0, (oscale*tland.l(lnd,t)) / ;
   );
   loop((a,v),
      put sim.tl, "kd",  a.tl, v.tl, years(t):4:0, (oscale*kd.l(a,v,t)) / ;
      put sim.tl, "xpv", a.tl, v.tl, years(t):4:0, (oscale*xpv.l(a,v,t)) / ;
      put sim.tl, "pk",  a.tl, v.tl, years(t):4:0, (pk.l(a,v,t)) / ;
   ) ;

   loop((a,l),
      put sim.tl, "xf",    a.tl, l.tl, years(t):4:0, (oscale*xf.l(a,l,t)) / ;
      put sim.tl, "swage", a.tl, l.tl, years(t):4:0, (swage.l(a,l,t)) / ;
   ) ;

   loop(a,
      put sim.tl, "xf",    a.tl, "tot", years(t):4:0, (oscale*sum(l,xf.l(a,l,t))) / ;
   ) ;

   loop(isrep,
   loop(l,
$ontext
      lwork(l) = sum(a$srv(a),xf.l(a,l,t))
      put sim.tl, "xf","a-srv",l.tl, years(t):4:0, (oscale*lwork(l)) / ;
      lwork(l) = sum(a$agr(a),xf.l(a,l,t))
      put sim.tl, "xf","a-agr",l.tl, years(t):4:0, (oscale*lwork(l)) / ;
      lwork(l) = sum(a$man(a),xf.l(a,l,t))
      put sim.tl, "xf","a-man", l.tl, years(t):4:0, (oscale*lwork(l)) / ;
$offtext
      lwork(l) = sum(a$mapRep(a,isrep),xf.l(a,l,t))
      if(lwork(l)>0,
      put sim.tl, "xf",isrep.tl, l.tl, years(t):4:0, (oscale*lwork(l)) / ;
      ); );
      work = sum(l,sum(a$maprep(a,isrep),xf.l(a,l,t)))
      if(work>0,
      put sim.tl, "xf",isrep.tl,"tot", years(t):4:0, (oscale*work) / ;
      ); );

   loop(a,
      put sim.tl, "rrat",  a.tl, "(blank)", years(t):4:0, (rrat.l(a,t)) / ;
      put sim.tl, "xp",    a.tl, "(blank)", years(t):4:0, (oscale*xp.l(a,t)) / ;
      put sim.tl, "pp",    a.tl, "(blank)", years(t):4:0, (pp.l(a,t)) / ;
      put sim.tl, "ldT",   a.tl, "", years(t):4:0, (oscale*sum(l,xf.l(a,l,t))) / ;
      put sim.tl, "ldT_un", a.tl, "", years(t):4:0, (oscale*sum(ul,xf.l(a,ul,t))) / ;

   loop(lnd,
      put sim.tl, "land",  a.tl, "(blank)", years(t):4:0, (oscale*xf.l(a,lnd,t)) / ;
      put sim.tl, "pland", a.tl, "(blank)", years(t):4:0, (pland.l(a,lnd,t)) / ;
      );
   ) ;


   loop(isrep,
      put sim.tl, "xs",    isrep.tl, "(blank)", years(t):4:0, (oscale*SUM(i$mapRep(i,isrep),xs.l(i,t))) / ;
      put sim.tl, "xd",    isrep.tl, "(blank)", years(t):4:0, (oscale*SUM(i$mapRep(i,isrep),xd.l(i,t))) / ;
      put sim.tl, "delst", isrep.tl, "(blank)", years(t):4:0, (oscale*SUM(i$mapRep(i,isrep),delst.l(i,t))) / ;
      put sim.tl, "xm",    isrep.tl, "(blank)", years(t):4:0, (oscale*SUM(i$mapRep(i,isrep),xm.l(i,t))) / ;
      put sim.tl, "xe",    isrep.tl, "(blank)", years(t):4:0, (oscale*SUM(i$mapRep(i,isrep),xe.l(i,t))) / ;
      put sim.tl, "xat",   isrep.tl, "(blank)", years(t):4:0, (oscale*SUM(i$mapRep(i,isrep),xat.l(i,t))) / ;
      loop(i,
         put sim.tl, "xa",    i.tl, isrep.tl, years(t):4:0, SUM(aa$maprep(aa,isrep),(oscale*xa.l(i,aa,t))) / ;
         put sim.tl, "xaV",   i.tl, isrep.tl, years(t):4:0, SUM(aa$maprep(aa,isrep),(oscale*chiPA(i)*pa.l(i,t)*(1+tpaf.l(i,aa,t))*xa.l(i,aa,t))) / ;
         put sim.tl, "tpaf", i.tl, isrep.tl, years(t):4:0, SUM(aa$maprep(aa,isrep),(100*tpaf.l(i,aa,t))) / ;
         put sim.tl, "paf",   i.tl, isrep.tl, years(t):4:0, SUM(aa$maprep(aa,isrep),(chiPA(i)*paf.l(i,aa,t))) / ;

   ) ;
  ) ;
   loop(isrep,
      put sim.tl, "xa",   isrep.tl, "hhtot", years(t):4:0, sum(i$maprep(i,isrep),(oscale*sum(h, xa.l(i,h,t)))) / ;
      put sim.tl, "xaV",  isrep.tl, "hhtot", years(t):4:0, sum(i$maprep(i,isrep),(oscale*sum(h, chiPA(i)*pa.l(i,t)*(1+tpaf.l(i,h,t))*xa.l(i,h,t)))) / ;
   );
   Loop(i,
      put sim.tl, "ps",   i.tl, "(blank)", years(t):4:0, (chiPS(i)*ps.l(i,t)) / ;
      put sim.tl, "pa",   i.tl, "(blank)", years(t):4:0, (chiPA(i)*pa.l(i,t)) / ;
      put sim.tl, "pda",  i.tl, "(blank)", years(t):4:0, (chiPDa(i)*pda.l(i,t)) / ;
      put sim.tl, "pma",  i.tl, "(blank)", years(t):4:0, (chiPMa(i)*pma.l(i,t)) / ;
      put sim.tl, "pd",   i.tl, "(blank)", years(t):4:0, (chiPD(i)*pd.l(i,t)) / ;
      put sim.tl, "pe",   i.tl, "(blank)", years(t):4:0, (chiPE(i)*pe.l(i,t)) / ;
      put sim.tl, "pwe",  i.tl, "(blank)", years(t):4:0, (chiPWE(i)*pwe.l(i,t)) / ;
      put sim.tl, "pwm",  i.tl, "(blank)", years(t):4:0, (pwm.l(i,t)) / ;
   );

   loop((h,k),
      put sim.tl, "pkf",    h.tl, k.tl, years(t):4:0, (pkf.l(h,k,t)) / ;
      put sim.tl, "xkf",    h.tl, k.tl, years(t):4:0, (oscale*xkf.l(h,k,t)) / ;
      put sim.tl, "xkfshr", h.tl, k.tl, years(t):4:0, (100*xkfshr.l(h,k,t)) / ;
   ) ;

*  Emissions

   loop((em,emSrc,aa)$(rhoEmi(em,emSrc,aa) ne 0),
      put sim.tl, em.tl, emSrc.tl, aa.tl, years(t):4:0, (emiComm.l(em,emSrc,aa,t)/escale) / ;
   ) ;
   loop((em,fp,a)$(rhoEmiFac(em,fp,a) ne 0),
      put sim.tl, em.tl, fp.tl, a.tl, years(t):4:0, (emiFact.l(em,fp,a,t)/escale) / ;
   ) ;

   loop((em,a)$(rhoEmiXP(em,a) ne 0),
      put sim.tl, em.tl, "XP", a.tl, years(t):4:0, (emiXP.l(em,a,t)/escale) / ;
   ) ;

   loop((em,aa),
   put sim.tl, "EmibySec", em.tl, aa.tl, years(t):4:0, (emiSecA.l(em,aa,t)/escale) / ;
   );

   loop(em,
      put sim.tl, "EmiTotbyEm", em.tl, "(blank)", years(t):4:0, (emiTot.l(em,t)/escale) / ;
*     Note input emissions are in 1000 tons CO2, rescale emitax and multiply by 1000 to get tax in Dh/tonCO2
      Loop(aa,
           put sim.tl, "EmiTax", em.tl, aa.tl, years(t):4:0, (1000*temi.l(em,aa,t)*escale*oscale) / ;
      );
   ) ;

   put sim.tl, "EmiGHG", "(blank)", "(blank)", years(t):4:0, (emiGHG.l(t)/escale) / ;

   Loop((a,i)$ElecMix.l(a,i,t),
   put sim.tl, "EneryMix", a.tl, i.tl, years(t):4:0, (ElecMix.l(a,i,t)) / ;
   );

   if(not ifComp,
      put sim.tl, "gl",     "(blank)", "(blank)", years(t):4:0, (100*gl.l(t)) / ;
      put sim.tl, "kaps",   "(blank)", "(blank)", years(t):4:0, (oscale*kaps.l(t)) / ;
      put sim.tl, "kstock", "(blank)", "(blank)", years(t):4:0, (oscale*kstock.l(t)) / ;
      if(not t0(t),
            work = sum((a,l), swage.l(a,l,t)*xf.l(a,l,t)*((lambdal.l(a,l,t)/lambdal.l(a,l,t-1))**(1/gap(t))-1))/sum((a,l), swage.l(a,l,t)*xf.l(a,l,t)) ;
            put sim.tl, "avgGL",  "(blank)", "(blank)", years(t):4:0, (100*work) / ;
      ) ;

      loop((a,l),
         put sim.tl, "lambdal", a.tl, l.tl, years(t):4:0, (lambdal.l(a,l,t)) / ;
      ) ;

      loop((a,v),
         put sim.tl, "lambdan", a.tl, v.tl, years(t):4:0, (lambdan.l(a,v,t)) / ;
         put sim.tl, "lambdav", a.tl, v.tl, years(t):4:0, (lambdav.l(a,v,t)) / ;
         put sim.tl, "lambdak", a.tl, v.tl, years(t):4:0, (lambdak.l(a,v,t)) / ;
      ) ;

     if (ord(t) ne ord(t0),

*        Growth decomposition

         fshr(l,a,t) = swage.l(a,l,t)*xf.l(a,l,t) ;
         qdel(l,a,t) = xf.l(a,l,t) ;
         ldel(l,a,t) = lambdal.l(a,l,t) ;

         fshr(cap,a,t) = sum(v, pk.l(a,v,t)*kd.l(a,v,t)) ;
         qdel(cap,a,t) = sum(v, kd.l(a,v,t)) ;
         ldel(cap,a,t)$qdel(cap,a,t) = sum(v, lambdak.l(a,v,t)*kd.l(a,v,t))/qdel(cap,a,t) ;

         fshr(lnd,a,t) = pland.l(a,lnd,t)*xf.l(a,lnd,t) ;
         qdel(lnd,a,t) = xf.l(a,lnd,t) ;
         ldel(lnd,a,t) = lambdat.l(a,lnd,t) ;

         fshr(fp,a,t) = fshr(fp,a,t) / gdpfc.l(t) ;
*Calvin modification for checking
$ontext
         if(years(t) gt years(t0),
            loop((fp,a)$qdel(fp,a,t-1),
               put sim.tl, "qdel",  a.tl, fp.tl, years(t):4:0, (100*0.5*(fshr(fp,a,t-1)+fshr(fp,a,t))*((qdel(fp,a,t)/qdel(fp,a,t-1))**(1/gap(t))-1)) / ;
            ) ;
            loop((fp,a)$ldel(fp,a,t-1),
                put sim.tl, "ldel",  a.tl, fp.tl, years(t):4:0, (100*0.5*(fshr(fp,a,t-1)+fshr(fp,a,t))*((ldel(fp,a,t)/ldel(fp,a,t-1))**(1/gap(t))-1)) / ;
            ) ;
            put sim.tl, "yfcdel", "(blank)", "(blank)", years(t):4:0, (100*((rgdpfc.l(t)/rgdpfc.l(t-1))**(1/gap(t))-1)) / ;
            put sim.tl, "ympdel", "(blank)", "(blank)", years(t):4:0, (100*((rgdpmp.l(t)/rgdpmp.l(t-1))**(1/gap(t))-1)) / ;
         ) ;
$offtext
$ontext
         work = sum((a,l)$(xf.l(a,l,t-1) ne 0), (swage.l(a,l,t0)*lambdal.l(a,l,t)*xf.l(a,l,t)/rgdpmp.l(t))*(xf.l(a,l,t)/xf.l(a,l,t-1)-1)) ;
         put sim.tl, "gDecomp", "tLab", "(blank)", years(t):4:0,
            sum((a,l)$(xf.l(a,l,t-1) ne 0), (swage.l(a,l,t0)*lambdal.l(a,l,t)*xf.l(a,l,t)/rgdpmp.l(t))*(xf.l(a,l,t)/xf.l(a,l,t-1)-1)) / ;

         work = work + sum((a,l)$(xf.l(a,l,t-1) ne 0), (swage.l(a,l,t0)*lambdal.l(a,l,t)*xf.l(a,l,t)/rgdpmp.l(t))*(lambdal.l(a,l,t)/lambdal.l(a,l,t-1)-1)) ;
         put sim.tl, "gDecomp", "tLabProd", "(blank)", years(t):4:0,
            sum((a,l)$(xf.l(a,l,t-1) ne 0), (swage.l(a,l,t0)*lambdal.l(a,l,t)*xf.l(a,l,t)/rgdpmp.l(t))*(lambdal.l(a,l,t)/lambdal.l(a,l,t-1)-1)) / ;

         work = work + sum((a,Old)$(sum(v,kd.l(a,v,t-1)) ne 0), (pk.l(a,Old,t0)*sum(v,lambdak.l(a,v,t)*kd.l(a,v,t))/rgdpmp.l(t))
                     *     (sum(v,kd.l(a,v,t))/sum(v,kd.l(a,v,t-1))-1)) ;
         put sim.tl, "gDecomp", "tKap", "(blank)", years(t):4:0,
            sum((a,Old)$(sum(v,kd.l(a,v,t-1)) ne 0), (pk.l(a,Old,t0)*sum(v,lambdak.l(a,v,t)*kd.l(a,v,t))/rgdpmp.l(t))
                     *     (sum(v,kd.l(a,v,t))/sum(v,kd.l(a,v,t-1))-1)) / ;

         put sim.tl, "gDecomp", "tGDP",   "(blank)", years(t):4:0,(rgdpmp.l(t)/rgdpmp.l(t-1)-1) / ;
         put sim.tl, "gDecomp", "tGDPFC", "(blank)", years(t):4:0,(rgdpfc.l(t)/rgdpfc.l(t-1)-1) / ;
         put sim.tl, "gDecomp", "tRES",   "(blank)", years(t):4:0,((rgdpmp.l(t)/rgdpmp.l(t-1)-1) - work) / ;
$offtext
      ) ;
   ) ;
) ;
