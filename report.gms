*$onlisting

oscale = 1/inscale;

resCon("%SimName%","NIPA","Val",rdim2,tt)=(oscale*sum(fd$sum(nipa$sameas(nipa,rdim2),mapn(fd,nipa)),yf.l(fd,tt)));
resCon("%SimName%","NIPA","Vol",rdim2,tt)=(oscale*sum(fd$sum(nipa$sameas(nipa,rdim2),mapn(fd,nipa)),xfd.l(fd,tt)));

Loop(t0,
resCon("%SimName%","NIPA","PrD",rdim2,tt)$sum(fd$sum(nipa$sameas(nipa,rdim2),mapn(fd,nipa)),pf.l(fd,t0)*xfd.l(fd,t0))
                        =(100*sum(fd$sum(nipa$sameas(nipa,rdim2),mapn(fd,nipa)),pf.l(fd,tt)*xfd.l(fd,t0))
                                /sum(fd$sum(nipa$sameas(nipa,rdim2),mapn(fd,nipa)),pf.l(fd,t0)*xfd.l(fd,t0)));
);

resCon("%SimName%","NIPA","Val","tdelst",tt)=(oscale*tdelst.l(tt));
resCon("%SimName%","NIPA","Vol","rtdelst",tt)=(oscale*rtdelst.l(tt));
resCon("%SimName%","NIPA","PrD","ptdelst",tt)=(100*pdelst.l(tt));
resCon("%SimName%","NIPA","Val","texp",tt)=(oscale*texp.l(tt));
resCon("%SimName%","NIPA","Vol","rtexp",tt)=(oscale*rtexp.l(tt));
resCon("%SimName%","NIPA","PrD","ptexp",tt)=(100*pexp.l(tt));
resCon("%SimName%","NIPA","Val","timp",tt)=(oscale*timp.l(tt));
resCon("%SimName%","NIPA","Vol","rtimp",tt)=(oscale*rtimp.l(tt));
resCon("%SimName%","NIPA","PrD","ptimp",tt)=(100*pimp.l(tt));
resCon("%SimName%","NIPA","Val","gdpmp",tt)=(oscale*gdpmp.l(tt));
resCon("%SimName%","NIPA","Vol","rgdpmp",tt)=(oscale*rgdpmp.l(tt));
resCon("%SimName%","NIPA","PrD","pgdpmp",tt)=(100*pgdpmp.l(tt));
resCon("%SimName%","NIPA","Vol","rgdppc",tt)=(oscale*rgdppc.l(tt));
resCon("%SimName%","NIPA","Pct","ggdppc",tt)=(100*ggdppc.l(tt));
resCon("%SimName%","NIPA","PrD","gl",tt)=(100*gl.l(tt));
resCon("%SimName%","NIPA","Val","gdpfc",tt)=(oscale*gdpfc.l(tt));
resCon("%SimName%","NIPA","Vol","rgdpfc",tt)=(oscale*rgdpfc.l(tt));
resCon("%SimName%","NIPA","PrD","pgdpfc",tt)=(100*pgdpfc.l(tt));
resCon("%SimName%","NIPA","PrD","trent",tt)=(trent.l(tt));

resCon("%SimName%","sav","g-govt","(blank)",tt)=(oscale*savg.l(tt));
resCon("%SimName%","aps",rdim1,"(blank)",tt)=SUM(sameas(h,rdim1),aps.l(h,tt));

resCon("%SimName%","sav","hhtot","(blank)",tt)=(oscale*sum(h,savh.l(h,tt)));
resCon("%SimName%","sav",rdim1,"(blank)",tt)=SUM(sameas(h,rdim1),oscale*savh.l(h,tt));
resCon("%SimName%","sav",rdim1,"(blank)",tt)=SUM(sameas(entr,rdim1),oscale*savEntr.l(entr,tt));
resCon("%SimName%","sav",rdim1,"(blank)",tt)=SUM(sameas(row,rdim1),oscale*er.l(tt)*savf.l(tt));
resCon("%SimName%","savf","(blank)","(blank)",tt)=(oscale*savf.l(tt));
resCon("%SimName%","rsg","(blank)","(blank)",tt)=(oscale*rsg.l(tt));
resCon("%SimName%","inv",rdim1,"(blank)",tt)=SUM(sameas(inv,rdim1),oscale*yf.l(inv,tt));
resCon("%SimName%","rinv",rdim1,"(blank)",tt)=SUM(sameas(inv,rdim1),oscale*xfd.l(inv,tt));
resCon("%SimName%","inv","delst","(blank)",tt)=(oscale*sum(i,chiPS(i)*ps.l(i,tt)*delst.l(i,tt)+er.l(tt)*pwm.l(i,tt)*(1+tm.l(i,tt))*mdelst.l(i,tt)));
resCon("%SimName%","rshrGDP","(blank)",rdim2,tt)=SUM(sameas(f,rdim2),rshrGDP.l(f,tt));
resCon("%SimName%","nshrGDP","(blank)",rdim2,tt)=SUM(sameas(f,rdim2),nshrGDP.l(f,tt));
resCon("%SimName%","er","(blank)","(blank)",tt)=(er.l(tt));
resCon("%SimName%","trb","(blank)","(blank)",tt)=oscale*sum(i,chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)-pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt)));
resCon("%SimName%","fexp","(blank)","(blank)",tt)=(oscale*sum(i,chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fimp","(blank)","(blank)",tt)=(oscale*sum(i,pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
resCon("%SimName%","fexp",rdim1,"(blank)",tt)=SUM(sameas(i,rdim1),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)*oscale);
resCon("%SimName%","fimp",rdim1,"(blank)",tt)=SUM(sameas(i,rdim1),oscale*pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt)));
resCon("%SimName%","fexp","c-srv","(blank)",tt)=(oscale*sum(i$isrv(i),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fexp","c-agr","(blank)",tt)=(oscale*sum(i$iagr(i),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fexp","c-man","(blank)",tt)=(oscale*sum(i$iman(i),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fimp","c-srv","(blank)",tt)=(oscale*sum(i$isrv(i),pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
resCon("%SimName%","fimp","c-agr","(blank)",tt)=(oscale*sum(i$iagr(i),pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
resCon("%SimName%","fimp","c-man","(blank)",tt)=(oscale*sum(i$iman(i),pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
Loop(inst$row(inst),
resCon("%SimName%","inc","(blank)","(blank)",tt)=SUM((row,instp),oscale*transfers.l(instp,inst,tt));
);
resCon("%SimName%","ygov","(blank)","(blank)",tt)=(oscale*ygov.l(tt));

resCon("%SimName%","yg",rdim1,"(blank)",tt)=SUM(g$sameas(g,rdim1),oscale*yg.l(g,tt));


resCon("%SimName%","entrtax",rdim1,"(blank)",tt)=SUM(sameas(entr,rdim1),oscale*entrtax.l(entr,tt));
resCon("%SimName%","htax","(blank)","(blank)",tt)=(oscale*sum(h,htax.l(h,tt)));
resCon("%SimName%","gexp","(blank)","(blank)",tt)=(oscale*SUM(inst$SUM(gov,mapInst(gov,inst)),tottr.l(inst,tt))+sum(gov,yf.l(gov,tt)));

Loop((h,rdim1)$sameas(h,rdim1),
resCon("%SimName%","yh",rdim1,"(blank)",tt)=oscale*yh.l(h,tt);
resCon("%SimName%","laby",rdim1,"(blank)",tt)=oscale*sum(l,chil(h,l,tt)*sum(a$aact(a),swage.l(a,l,tt)*xf.l(a,l,tt)));
resCon("%SimName%","uh",rdim1,"(blank)",tt)=oscale*uh.l(h,tt);
);

resCon("%SimName%","kapy","(blank)","(blank)",tt)=(oscale*kapy.l(tt));

Loop((instp,rdim1)$sameas(instp,rdim1),
resCon("%SimName%","toTR",rdim1,"(blank)",tt)= oscale*tottr.l(instp,tt);

Loop((iinst,rdim2)$sameas(iinst,rdim2),
resCon("%SimName%","transf",rdim1,rdim2,tt)=oscale*transfers.l(instp,iinst,tt);
);
);

resCon("%SimName%","xp","a-srv","(blank)",tt)=(oscale*sum(a$srv(a),xp.l(a,tt)));
resCon("%SimName%","xp","a-agr","(blank)",tt)=(oscale*sum(a$agr(a),xp.l(a,tt)));
resCon("%SimName%","xp","a-man","(blank)",tt)=(oscale*sum(a$man(a),xp.l(a,tt)));

resCon("%SimName%","Pop","(blank)",rdim2,tt)=SUM(sameas(cohorts,rdim2),pop.l(cohorts,tt)/pscale);
resCon("%SimName%","hpop","(blank)",rdim2,tt)= SUM(sameas(h,rdim2),hpop.l(h,tt))/pscale;
resCon("%SimName%","exRates","(blank)",rdim2,tt)=SUM(sameas(exr,rdim2),exRates0(exr));
resCon("%SimName%","lst","(blank)","tot",tt)=(oscale*sum(l,lsT.l(l,tt)));

Loop((l,rdim2)$sameas(l,rdim2),
resCon("%SimName%","wage","(blank)",rdim2,tt)=SUM(sameas(l,rdim2),wage.l(l,tt));
resCon("%SimName%","lsT","(blank)",rdim2,tt)=SUM(sameas(l,rdim2),oscale*lsT.l(l,tt));
resCon("%SimName%","epshea","(blank)",rdim2,tt)=epshea(l,tt);
resCon("%SimName%","epsedu","(blank)",rdim2,tt)=epsedu(l,tt);
);

Loop((oa,rdim1)$sameas(oa,rdim1),
resCon("%SimName%","pf",rdim1,"(blank)",tt)= pf.l(oa,tt);
resCon("%SimName%","xfd",rdim1,"(blank)",tt)= xfd.l(oa,tt);
);

resCon("%SimName%","kstock","(blank)","(blank)",tt)=(oscale*kstock.l(tt));
resCon("%SimName%","pnum","(blank)","(blank)",tt)=(pnum.l(tt));
Loop((lnd,rdim1)$sameas(lnd,rdim1),
resCon("%SimName%","ptland",rdim1,"(blank)",tt)=(ptland.l(lnd,tt));
resCon("%SimName%","tland",rdim1,"(blank)",tt)=(oscale*tland.l(lnd,tt));
);

Loop((a,rdim1)$sameas(a,rdim1),
Loop((cap,rdim2)$sameas(cap,rdim2),
resCon("%SimName%","xf",rdim1,rdim2,tt) = oscale*xf.l(a,cap,tt);
));
Loop((a,rdim1)$sameas(a,rdim1),
Loop((v,rdim2)$sameas(v,rdim2),
resCon("%SimName%","kd",rdim1,rdim2,tt) = oscale*kd.l(a,v,tt);
resCon("%SimName%","xpv",rdim1,rdim2,tt)= oscale*xpv.l(a,v,tt);
resCon("%SimName%","pk",rdim1,rdim2,tt) = pk.l(a,v,tt);
));

Loop((l,rdim2)$sameas(l,rdim2),
Loop((a,rdim1)$sameas(a,rdim1),
resCon("%SimName%","swage",rdim1,rdim2,tt)= swage.l(a,l,tt);
resCon("%SimName%","pswage",rdim1,rdim2,tt)= pswage.l(a,l,tt);
resCon("%SimName%","fwtx",rdim1,rdim2,tt)= fwtx.l(a,l,tt);
resCon("%SimName%","xf",rdim1,rdim2,tt) = oscale*xf.l(a,l,tt);
);

resCon("%SimName%","xf","a-srv",rdim2,tt)= oscale*sum(a$srv(a),xf.l(a,l,tt));
resCon("%SimName%","xf","a-agr",rdim2,tt)= oscale*sum(a$agr(a),xf.l(a,l,tt));
resCon("%SimName%","xf","a-man",rdim2,tt)= oscale*sum(a$man(a),xf.l(a,l,tt));
);

resCon("%SimName%","chfwtx","(blank)","(blank)",tt)= chfwtx.l(tt);

resCon("%SimName%","xf","a-srv","tot",tt)=(oscale*sum(l,sum(a$srv(a),xf.l(a,l,tt))));
resCon("%SimName%","xf","a-agr","tot",tt)=(oscale*sum(l,sum(a$agr(a),xf.l(a,l,tt))));
resCon("%SimName%","xf","a-man","tot",tt)=(oscale*sum(l,sum(a$man(a),xf.l(a,l,tt))));



Loop((rdim1,a)$sameas(rdim1,a),
resCon("%SimName%","rrat",rdim1,"(blank)",tt) = rrat.l(a,tt);
resCon("%SimName%","xp",rdim1,"(blank)",tt)   = oscale*xp.l(a,tt);
resCon("%SimName%","pp",rdim1,"(blank)",tt)   = pp.l(a,tt);
Loop((rdim2,lnd)$sameas(rdim2,lnd),
resCon("%SimName%","xf",rdim1,rdim2,tt) = oscale*xf.l(a,lnd,tt);
resCon("%SimName%","pland",rdim1,rdim2,tt)= pland.l(a,lnd,tt);
));

Loop((rdim1,i)$sameas(rdim1,i),
resCon("%SimName%","xs",rdim1,"(blank)",tt)      = oscale*xs.l(i,tt);
resCon("%SimName%","xd",rdim1,"(blank)",tt)      = oscale*xd.l(i,tt);
resCon("%SimName%","delst",rdim1,"(blank)",tt)   = oscale*delst.l(i,tt);
resCon("%SimName%","xm",rdim1,"(blank)",tt)      = oscale*xm.l(i,tt);
resCon("%SimName%","xe",rdim1,"(blank)",tt)      = oscale*xe.l(i,tt);
resCon("%SimName%","xat",rdim1,"(blank)",tt)     = oscale*xat.l(i,tt);
resCon("%SimName%","ps",rdim1,"(blank)",tt)      = chiPS(i)*ps.l(i,tt);
resCon("%SimName%","pa",rdim1,"(blank)",tt)      = chiPA(i)*pa.l(i,tt);
resCon("%SimName%","pda",rdim1,"(blank)",tt)     = chiPDa(i)*pda.l(i,tt);
resCon("%SimName%","pma",rdim1,"(blank)",tt)     = chiPMa(i)*pma.l(i,tt);
resCon("%SimName%","pd",rdim1,"(blank)",tt)      = chiPD(i)*pd.l(i,tt);
resCon("%SimName%","pe",rdim1,"(blank)",tt)      = chiPE(i)*pe.l(i,tt);
resCon("%SimName%","pwe",rdim1,"(blank)",tt)     = chiPWE(i)*pwe.l(i,tt);
resCon("%SimName%","pwm",rdim1,"(blank)",tt)     = pwm.l(i,tt);

Loop((rdim2,aa)$sameas(rdim2,aa),
resCon("%SimName%","xa",rdim1,rdim2,tt)      =oscale*xa.l(i,aa,tt);
resCon("%SimName%","xaV",rdim1,rdim2,tt)     =oscale*chiPA(i)*pa.l(i,tt)*(1+patax.l(i,aa,tt))*xa.l(i,aa,tt);
resCon("%SimName%","patax",rdim1,rdim2,tt)   =100*patax.l(i,aa,tt);
resCon("%SimName%","paf",rdim1,rdim2,tt)     =chiPA(i)*paf.l(i,aa,tt);
);
);

Loop((rdim1,i)$sameas(rdim1,i),
resCon("%SimName%","xaV",rdim1,"hhtot",tt)=oscale*sum(h,chiPA(i)*pa.l(i,tt)*(1+patax.l(i,h,tt))*xa.l(i,h,tt));
resCon("%SimName%","xa",rdim1,"hhtot",tt)=SUM(sameas(i,rdim1),oscale*sum(h,xa.l(i,h,tt)));
);

Loop((h,rdim1)$sameas(h,rdim1),
Loop((k,rdim2)$sameas(k,rdim2),
resCon("%SimName%","pkf",rdim1,rdim2,tt)   = pkf.l(h,k,tt) ;
resCon("%SimName%","xkf",rdim1,rdim2,tt)   = oscale*xkf.l(h,k,tt) ;
resCon("%SimName%","xkfshr",rdim1,rdim2,tt)= 100*xkfshr.l(h,k,tt) ;
);
);

*Emissions

loop((em,var)$sameas(em,var),
loop((i,rdim1)$sameas(i,rdim1),
loop((aa,rdim2)$sameas(aa,rdim2),

*resCon("%SimName%",var,rdim1,rdim2,tt)$(SUM(is$sameas(is,rdim1),SUM(aa$sameas(aa,rdim2),SUM(em$sameas(em,var),rhoEmi(em,is,aa)))) ne 0)
resCon("%SimName%",var,rdim1,rdim2,tt)
             = emiComm.l(em,i,aa,tt)/escale;
);
);
);

loop((em,var)$sameas(em,var),
loop((fp,rdim1)$sameas(fp,rdim1),
loop((a,rdim2)$sameas(a,rdim2),

*resCon("%SimName%",var,rdim1,rdim2,tt)$(SUM(is$sameas(is,rdim1),SUM(aa$sameas(aa,rdim2),SUM(em$sameas(em,var),rhoEmi(em,is,aa)))) ne 0)
resCon("%SimName%",var,rdim1,rdim2,tt)
             = emiFact.l(em,fp,a,tt)/escale;
);
);
);


loop((em,rdim1)$sameas(em,rdim1),
loop((aa,rdim2)$sameas(aa,rdim2),
resCon("%SimName%","EmiSecA",rdim1,rdim2,tt) = SUM(is,emiSecA.l(em,aa,tt))/escale;

);
);


loop((a,rdim2)$sameas(a,rdim2),
loop((em,rdim1)$sameas(em,rdim1),
resCon("%SimName%","EmiXP",rdim1,rdim2,tt)
        =emiXP.l(em,a,tt)/escale;
);
resCon("%SimName%","EmiXP","TotEm",rdim2,tt)
        =SUM(em,emiXP.l(em,a,tt)/escale);
);

Loop((em,rdim1)$sameas(em,rdim1),
resCon("%SimName%","EmiTot",rdim1,"(blank)",tt)=emiTot.l(em,tt)/escale;
resCon("%SimName%","EmiTax",rdim1,"(blank)",tt)=emiTax.l(em,tt)*escale*oscale;
);

resCon("%SimName%","EmiGHG","(Blank)","(blank)",tt)=(emiGHG.l(tt)/escale);

if(not ifComp,
resCon("%SimName%","gl","(blank)","(blank)",tt)=(100*gl.l(tt));
resCon("%SimName%","kaps","(blank)","(blank)",tt)=(oscale*kaps.l(tt));
resCon("%SimName%","kstock","(blank)","(blank)",tt)=(oscale*kstock.l(tt));
);

resCon("%SimName%","avgGL","(blank)","(blank)",tt)$(not t0(tt))=(100*sum((a,l),pswage.l(a,l,tt)*xf.l(a,l,tt)*((lambdal.l(a,l,tt)/lambdal.l(a,l,tt-1))**(1/gap(tt))-1))/sum((a,l),pswage.l(a,l,tt)*xf.l(a,l,tt)));

Loop((a,rdim1)$sameas(a,rdim1),
Loop((l,rdim2)$sameas(l,rdim2),
resCon("%SimName%","lambdal",rdim1,rdim2,tt)= lambdal.l(a,l,tt);
);
Loop((v,rdim2)$sameas(v,rdim2),
resCon("%SimName%","lambdan",rdim1,rdim2,tt)= lambdan.l(a,v,tt);
resCon("%SimName%","lambdav",rdim1,rdim2,tt)= lambdav.l(a,v,tt);
resCon("%SimName%","lambdak",rdim1,rdim2,tt)= lambdak.l(a,v,tt);
);
);

*Growth decomposition
Loop((a,rdim1)$sameas(a,rdim1),
Loop((l,rdim2)$sameas(l,rdim2),
resCon("%SimName%","fshr",rdim1,rdim2,tt)$(ord(tt) ne 1)  = pswage.l(a,l,tt)*xf.l(a,l,tt);
resCon("%SimName%","qdel",rdim1,rdim2,tt)$(ord(tt) ne 1)  = xf.l(a,l,tt);
resCon("%SimName%","ldel",rdim1,rdim2,tt)$(ord(tt) ne 1)  = lambdal.l(a,l,tt);
);
Loop((cap,rdim2)$sameas(cap,rdim2),
resCon("%SimName%","fshr",rdim1,rdim2,tt)$(ord(tt) ne 1)    = sum(v,pk.l(a,v,tt)*kd.l(a,v,tt));
resCon("%SimName%","qdel",rdim1,rdim2,tt)$(ord(tt) ne 1)    = sum(v,kd.l(a,v,tt));
resCon("%SimName%","ldel",rdim1,rdim2,tt)$(resCon("%SimName%","qdel",rdim1,"k",tt))=sum(v,lambdak.l(a,v,tt)*kd.l(a,v,tt))/resCon("%SimName%","qdel",rdim1,"k",tt);
);
Loop((lnd,rdim2)$sameas(lnd,rdim2),
resCon("%SimName%","fshr",rdim1,rdim2,tt)$(ord(tt) ne 1) = pland.l(a,lnd,tt)*xf.l(a,lnd,tt);
resCon("%SimName%","qdel",rdim1,rdim2,tt)$(ord(tt) ne 1) = xf.l(a,lnd,tt);
resCon("%SimName%","ldel",rdim1,rdim2,tt)$(ord(tt) ne 1) = lambdat.l(a,lnd,tt);
);
);

resCon("%SimName%","fshr",rdim1,rdim2,tt)$(ord(tt) ne 1)=resCon("%SimName%","fshr",rdim1,rdim2,tt)/gdpfc.l(tt);
resCon("%SimName%","unemp","(blank)","(blank)",tt)$(ord(tt) ne 1)=unemp.l(tt);

Loop((rdim1,age)$sameas(age,rdim1),
resCon("%SimName%","drate",rdim1,"(blank)",tt)$(ord(tt) ne 1)=drate.l(age,tt);
resCon("%SimName%","popAge",rdim1,"(blank)",tt)$(ord(tt) ne 1)=popage.l(age,tt);
);



resCon("%SimName%","brateU","(blank)","(blank)",tt)$(ord(tt) ne 1)=brateU.l(tt);
resCon("%SimName%","flfptot","(blank)","(blank)",tt)$(ord(tt) ne 1)=FLFPTot.l(tt);

Loop((rdim1,cohorts)$sameas(rdim1,cohorts),
resCon("%SimName%","deprate",rdim1,"(blank)",tt)$(ord(tt) ne 1)=deprate.l(cohorts,tt);
);


Loop((rdim1,l)$sameas(rdim1,l),
resCon("%SimName%","flfp",rdim1,"(blank)",tt)$(ord(tt) ne 1)=flfp.l(l,tt);
);

Loop(v0,
Loop((e,rdim1)$sameas(e,rdim1),
Loop((a,rdim2)$sameas(a,rdim2),
rescon("%SimName%","aep",rdim1,rdim2,tt)= aep(e,a,v0,tt);
rescon("%SimName%","lambdaep",rdim1,rdim2,tt) =  lambdaep.l(a,e,v0,tt) ;
)));

Loop((h,rdim1)$sameas(h,rdim1),
Loop((i,rdim2)$sameas(i,rdim2),
rescon("%SimName%","af",rdim1,rdim2,tt) = af(h,i,"ener",tt);
));

Loop((i,rdim1)$sameas(i,rdim1),
Loop((a,rdim2)$sameas(a,rdim2),
rescon("%SimName%","aio",rdim1,rdim2,tt) = aio(i,a,tt) ;
));

Loop((i,rdim1)$sameas(i,rdim1),
Loop((j,rdim2)$sameas(j,rdim2),
rescon("%SimName%","amarg",rdim1,rdim2,tt) = amarg(i,j) ;
));

Loop((a,rdim1)$sameas(a,rdim1),
Loop((i,rdim2)$sameas(i,rdim2),
rescon("%SimName%","elecmix",rdim1,rdim2,tt) = elecmix.l(a,i,tt) ;
));


rescon("%SimName%","debtStkD","(blank)","(blank)",tt)  = debtStkD.l(tt) ;
rescon("%SimName%","debtStkF","(blank)","(blank)",tt)  = debtStkF.l(tt) ;
rescon("%SimName%","debtStkT","(blank)","(blank)",tt)  = debtStkT.l(tt) ;
rescon("%SimName%","debtGDP","(blank)","(blank)",tt)  = debtGDP.l(tt) ;
rescon("%SimName%","rDebtStkD","(blank)","(blank)",tt) = rDebtStkD.l(tt) ;
rescon("%SimName%","rDebtStkF","(blank)","(blank)",tt) = rDebtStkF.l(tt) ;
rescon("%SimName%","rDebtStk","(blank)","(blank)",tt)  = rDebtStk.l(tt) ;



Loop((rdim1,inst)$sameas(rdim1,inst),
rescon("%SimName%","debtPay",rdim1,"(blank)",tt)   = debtPay.l(inst,tt) ;
rescon("%SimName%","debtNew",rdim1,"(blank)",tt)   = debtNew.l(inst,tt) ;
);

Loop((rdim1,a)$sameas(rdim1,a),
rescon("%SimName%","dmgTfpAct    ",rdim1,"(blank)",tt) = dmgTfpAct.l(a,tt)       ;
Loop((rdim2,l)$sameas(rdim2,l),
rescon("%SimName%","dmgLambdaL_HH",rdim1,rdim2,tt) = dmgLambdaL_HH.l(a,l,tt) ;
rescon("%SimName%","dmgLambdaL   ",rdim1,rdim2,tt) = dmgLambdaL.l(a,l,tt)    ;
));

Loop((rdim1,lnd)$sameas(rdim1,lnd),
rescon("%SimName%","dmgAtLand    ",rdim1,"(blank)",tt) = dmgAtLand.l(lnd,tt)         ;
);

Loop((h,rdim1)$sameas(h,rdim1),
Loop((i,rdim2)$sameas(i,rdim2),
rescon("%SimName%","dmgLambdaEh  ",rdim1,rdim2,tt) = sum(k,dmgLambdaEh.l(h,i,k,tt)) ;
));

   rescon("%SimName%","dmgShftTFP","(blank)","(blank)",tt)        =  dmgShftTFP.l(t)         ;
   rescon("%SimName%","dmgShftLambdaL_HH","(blank)","(blank)",tt) =  dmgShftLambdaL_HH.l(t)  ;
   rescon("%SimName%","dmgShftLambdaL","(blank)","(blank)",tt)    =  dmgShftLambdaL.l(t)     ;
   rescon("%SimName%","dmgShftLand","(blank)","(blank)",tt)       =  dmgShftLand.l(t)        ;
   rescon("%SimName%","dmgShftLambdaEh","(blank)","(blank)",tt)   =  dmgShftLambdaEh.l(t)    ;



execute_unload "%odir%\%simName%.gdx" ;

