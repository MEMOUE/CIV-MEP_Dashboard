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
resCon("%SimName%","NIPA","Val","totexp",tt)=(oscale*totexp.l(tt));
resCon("%SimName%","NIPA","Vol","rtotexp",tt)=(oscale*rtotexp.l(tt));
resCon("%SimName%","NIPA","PrD","ptotexp",tt)=(100*pexp.l(tt));
resCon("%SimName%","NIPA","Val","totimp",tt)=(oscale*totimp.l(tt));
resCon("%SimName%","NIPA","Vol","rtotimp",tt)=(oscale*rtotimp.l(tt));
resCon("%SimName%","NIPA","PrD","ptotimp",tt)=(100*pimp.l(tt));
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

loop((rdim1,gov)$sameas(rdim1,gov),
resCon("%SimName%","sav",rdim1,"(blank)",tt)=(oscale*savg.l(tt));
);
resCon("%SimName%","aps",rdim1,"(blank)",tt)=SUM(sameas(h,rdim1),aps.l(h,tt));

resCon("%SimName%","sav","hhtot","(blank)",tt)=(oscale*sum(h,savh.l(h,tt)));
resCon("%SimName%","sav",rdim1,"(blank)",tt)=SUM(sameas(h,rdim1),oscale*savh.l(h,tt));
resCon("%SimName%","sav",rdim1,"(blank)",tt)=SUM(sameas(entr,rdim1),oscale*savEntr.l(entr,tt));
resCon("%SimName%","sav",rdim1,"(blank)",tt)=SUM(sameas(row,rdim1),oscale*er.l(tt)*savf.l(tt));
resCon("%SimName%","savf","(blank)","(blank)",tt)=(oscale*savf.l(tt));
resCon("%SimName%","rsg","(blank)","(blank)",tt)=(oscale*rsg.l(tt));
resCon("%SimName%","inv",rdim1,"(blank)",tt)=SUM(sameas(inv,rdim1),oscale*yf.l(inv,tt));
resCon("%SimName%","rinv",rdim1,"(blank)",tt)=SUM(sameas(inv,rdim1),oscale*xfd.l(inv,tt));
resCon("%SimName%","inv","delst","(blank)",tt)=(oscale*sum(i,chiPS(i)*ps.l(i,tt)*delst.l(i,tt)+er.l(tt)*pwm.l(i,tt)*(1+timp.l(i,tt))*mdelst.l(i,tt)));
resCon("%SimName%","rshrGDP","(blank)",rdim2,tt)=SUM(sameas(f,rdim2),rshrGDP.l(f,tt));
resCon("%SimName%","nshrGDP","(blank)",rdim2,tt)=SUM(sameas(f,rdim2),nshrGDP.l(f,tt));
resCon("%SimName%","er","(blank)","(blank)",tt)=(er.l(tt));
resCon("%SimName%","trb","(blank)","(blank)",tt)=oscale*sum(i,chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)-pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt)));
resCon("%SimName%","fexp","(blank)","(blank)",tt)=(oscale*sum(i,chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fimp","(blank)","(blank)",tt)=(oscale*sum(i,pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
resCon("%SimName%","fexp",rdim1,"(blank)",tt)=SUM(sameas(i,rdim1),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)*oscale);
resCon("%SimName%","fimp",rdim1,"(blank)",tt)=SUM(sameas(i,rdim1),oscale*pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt)));
resCon("%SimName%","fexp","cc-srv","(blank)",tt)=(oscale*sum(i$isrv(i),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fexp","cc-agr","(blank)",tt)=(oscale*sum(i$iagr(i),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fexp","cc-man","(blank)",tt)=(oscale*sum(i$iman(i),chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt)));
resCon("%SimName%","fimp","cc-srv","(blank)",tt)=(oscale*sum(i$isrv(i),pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
resCon("%SimName%","fimp","cc-agr","(blank)",tt)=(oscale*sum(i$iagr(i),pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
resCon("%SimName%","fimp","cc-man","(blank)",tt)=(oscale*sum(i$iman(i),pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt))));
Loop(inst$row(inst),
resCon("%SimName%","inc","(blank)","(blank)",tt)=SUM((row,instp),oscale*transfers.l(instp,inst,tt));
);
resCon("%SimName%","ygov","(blank)","(blank)",tt)=(oscale*ygov.l(tt));

resCon("%SimName%","yg",rdim1,"(blank)",tt)=SUM(g$sameas(g,rdim1),oscale*yg.l(g,tt));


resCon("%SimName%","gexp","(blank)","(blank)",tt)=(oscale*SUM(inst$SUM(gov,mapInst(gov,inst)),tottr.l(inst,tt))+sum(gov,yf.l(gov,tt)));

Loop((h,rdim1)$sameas(h,rdim1),
resCon("%SimName%","yh",rdim1,"(blank)",tt)=oscale*yh.l(h,tt);
resCon("%SimName%","laby",rdim1,"(blank)",tt)=oscale*sum(l,chil(h,l,tt)*sum(a$aact(a),swage.l(a,l,tt)*xf.l(a,l,tt)));
resCon("%SimName%","uh",rdim1,"(blank)",tt)=oscale*uh.l(h,tt);
);

resCon("%SimName%","gini","(blank)","(blank)",tt)=gini.l(tt)*100;

resCon("%SimName%","kapy","(blank)","(blank)",tt)=(oscale*kapy.l(tt));

Loop((instp,rdim1)$sameas(instp,rdim1),
resCon("%SimName%","toTR",rdim1,"(blank)",tt)= oscale*tottr.l(instp,tt);

Loop((iinst,rdim2)$sameas(iinst,rdim2),
resCon("%SimName%","transf",rdim1,rdim2,tt)=oscale*transfers.l(instp,iinst,tt);
);
);

resCon("%SimName%","xp","aa-srv","(blank)",tt)=(oscale*sum(a$srv(a),xp.l(a,tt)));
resCon("%SimName%","xp","aa-agr","(blank)",tt)=(oscale*sum(a$agr(a),xp.l(a,tt)));
resCon("%SimName%","xp","aa-man","(blank)",tt)=(oscale*sum(a$man(a),xp.l(a,tt)));

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
Loop((v,rdim2)$sameas(v,rdim2),
resCon("%SimName%","kd",rdim1,rdim2,tt) = oscale*kd.l(a,v,tt);
resCon("%SimName%","xpv",rdim1,rdim2,tt)= oscale*xpv.l(a,v,tt);
resCon("%SimName%","pk",rdim1,rdim2,tt) = pk.l(a,v,tt);
resCon("%SimName%","pk_pt",rdim1,rdim2,tt) = pk_pt.l(a,v,tt);
));

Loop((l,rdim2)$sameas(l,rdim2),
Loop((a,rdim1)$sameas(a,rdim1),
resCon("%SimName%","swage",rdim1,rdim2,tt)= swage.l(a,l,tt);
resCon("%SimName%","pswage",rdim1,rdim2,tt)= pswage.l(a,l,tt);
resCon("%SimName%","xf",rdim1,rdim2,tt) = oscale*xf.l(a,l,tt);
);
);

Loop((fp,rdim2)$sameas(fp,rdim2),
Loop((a,rdim1)$sameas(a,rdim1),
resCon("%SimName%","tfac",rdim1,rdim2,tt)= tfac.l(a,fp,tt);
);

resCon("%SimName%","xf","aa-srv",rdim2,tt)= oscale*sum(a$srv(a),xf.l(a,fp,tt));
resCon("%SimName%","xf","aa-agr",rdim2,tt)= oscale*sum(a$agr(a),xf.l(a,fp,tt));
resCon("%SimName%","xf","aa-man",rdim2,tt)= oscale*sum(a$man(a),xf.l(a,fp,tt));
);


resCon("%SimName%","xf","aa-srv","tot",tt)=(oscale*sum(fp,sum(a$srv(a),xf.l(a,fp,tt))));
resCon("%SimName%","xf","aa-agr","tot",tt)=(oscale*sum(fp,sum(a$agr(a),xf.l(a,fp,tt))));
resCon("%SimName%","xf","aa-man","tot",tt)=(oscale*sum(fp,sum(a$man(a),xf.l(a,fp,tt))));



Loop((rdim1,a)$sameas(rdim1,a),
resCon("%SimName%","rrat",rdim1,"(blank)",tt) = rrat.l(a,tt);
resCon("%SimName%","xp",rdim1,"(blank)",tt)   = oscale*xp.l(a,tt);
resCon("%SimName%","pp",rdim1,"(blank)",tt)   = pp.l(a,tt);
Loop((rdim2,lnd)$sameas(rdim2,lnd),
resCon("%SimName%","pland",rdim1,rdim2,tt)= pland.l(a,lnd,tt);
resCon("%SimName%","pland_pt",rdim1,rdim2,tt)= pland_pt.l(a,lnd,tt);
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
resCon("%SimName%","xaV",rdim1,rdim2,tt)     =oscale*chiPA(i)*pa.l(i,tt)*(1+tpaf.l(i,aa,tt))*xa.l(i,aa,tt);
*resCon("%SimName%","tpaf",rdim1,rdim2,tt)   =100*tpaf.l(i,aa,tt);
resCon("%SimName%","paf",rdim1,rdim2,tt)     =chiPA(i)*paf.l(i,aa,tt);
);
);

Loop((rdim1,i)$sameas(rdim1,i),
resCon("%SimName%","xaV",rdim1,"hhtot",tt)=oscale*sum(h,chiPA(i)*pa.l(i,tt)*(1+tpaf.l(i,h,tt))*xa.l(i,h,tt));
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
loop((emSrc,rdim1)$sameas(emSrc,rdim1),
loop((aa,rdim2)$sameas(aa,rdim2),

*resCon("%SimName%",var,rdim1,rdim2,tt)$(SUM(is$sameas(is,rdim1),SUM(aa$sameas(aa,rdim2),SUM(em$sameas(em,var),rhoEmi(em,is,aa)))) ne 0)
resCon("%SimName%",var,rdim1,rdim2,tt)
             = emiComm.l(em,emSrc,aa,tt)/escale;
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
Loop((aa,rdim2)$sameas(aa,rdim2),
resCon("%SimName%","EmiTot",rdim1,"(blank)",tt)=emiTot.l(em,tt)/escale;
resCon("%SimName%","EmiTax",rdim1,rdim2,tt)=temi.l(em,aa,tt)*escale*oscale;
);
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

*Loop((h,rdim1)$sameas(h,rdim1),
*Loop((i,rdim2)$sameas(i,rdim2),
*rescon("%SimName%","af",rdim1,rdim2,tt) = af(h,i,"ener",tt);
*));

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
Loop(k$mapk(k,i),
rescon("%SimName%","dmgLambdaEh  ",rdim1,rdim2,tt) = dmgLambdaEh.l(h,i,k,tt) ;
)));

Loop((i,rdim1)$sameas(i,rdim1),
rescon("%SimName%","dmgChie      ",rdim1,"(blank)",tt) = dmgChie.l(i,tt) ;
);

rescon("%SimName%","dmgDepr      ","(blank)","(blank)",tt) = dmgDepr.l(tt) ;



   rescon("%SimName%","dmgShftTFP","(blank)","(blank)",tt)        =  dmgShftTFP.l(tt)         ;
   rescon("%SimName%","dmgShftLambdaL_HH","(blank)","(blank)",tt) =  dmgShftLambdaL_HH.l(tt)  ;
   rescon("%SimName%","dmgShftLambdaL","(blank)","(blank)",tt)    =  dmgShftLambdaL.l(tt)     ;
   rescon("%SimName%","dmgShftLand","(blank)","(blank)",tt)       =  dmgShftLand.l(tt)        ;
   rescon("%SimName%","dmgShftLambdaEh","(blank)","(blank)",tt)   =  dmgShftLambdaEh.l(tt)    ;
   rescon("%SimName%","dmgShftChie","(blank)","(blank)",tt)       =  dmgShftChie.l(tt)        ;
   rescon("%SimName%","dmgShftDepr","(blank)","(blank)",tt)       =  dmgShftDepr.l(tt)        ;


*   walrasT(tt) = sum(i, chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt) - pwm.l(i,tt)*(xm.l(i,tt)+mdelst.l(i,tt)))
*       +   savf.l(tt) + sum((inst,row,instp)$mapinst(row,instp),
*               transfers.l(inst,instp,tt)- transfers.l(instp,inst,tt))/er.l(tt)
*       +  SUM(instf, debtNew.l(instf,tt) - debtPay.l(instf,tt))/er.l(tt)
*                   ;
     walrasT(tt) = walras.l  ;

Loop((a,rdim1)$sameas(a,rdim1),
      resCon("%SimName%","tfacRev",rdim1,"Total",tt)= sum(lnd,tFac.l(a,lnd,tt) * pland.l(a,lnd,tt)*xf.l(a,lnd,tt));
      resCon("%SimName%","tfacRev",rdim1,"Total",tt)= sum(l,tFac.l(a,l,tt) * swage.l(a,l,tt)*xf.l(a,l,tt));
      resCon("%SimName%","tfacRev",rdim1,"Total",tt)= sum(cap,sum(v,tFac.l(a,cap,tt) * pk.l(a,v,tt)*kd.l(a,v,tt)));

  Loop((lnd,rdim2)$sameas(lnd,rdim2),
           resCon("%SimName%","tfacRev",rdim1,rdim2,tt)= tFac.l(a,lnd,tt) * pland.l(a,lnd,tt)*xf.l(a,lnd,tt);
     );

  Loop((l,rdim2)$sameas(l,rdim2),
      resCon("%SimName%","tfacRev",rdim1,rdim2,tt)= tFac.l(a,l,tt) * swage.l(a,l,tt)*xf.l(a,l,tt);
    );

  Loop((cap,rdim2)$sameas(cap,rdim2),
      resCon("%SimName%","tfacRev",rdim1,rdim2,tt)= sum(v,tFac.l(a,cap,tt) * pk.l(a,v,tt)*kd.l(a,v,tt));
     );
);

  Loop((lnd,rdim2)$sameas(lnd,rdim2),
           resCon("%SimName%","tfacRev","Total",rdim2,tt)= sum(a,tFac.l(a,lnd,tt) * pland.l(a,lnd,tt)*xf.l(a,lnd,tt));
  );

  Loop((l,rdim2)$sameas(l,rdim2),
      resCon("%SimName%","tfacRev","Total",rdim2,tt)= sum(a,tFac.l(a,l,tt) * swage.l(a,l,tt)*xf.l(a,l,tt));
  );

  Loop((cap,rdim2)$sameas(cap,rdim2),
      resCon("%SimName%","tfacRev","Total",rdim2,tt)= sum(a,sum(v,tFac.l(a,cap,tt) * pk.l(a,v,tt)*kd.l(a,v,tt)));
  );

Loop((a,rdim1)$sameas(a,rdim1),
   rescon("%SimName%","tpsb",rdim1,"(blank)",tt)        =    100*tpsb.l(a,tt);
   rescon("%SimName%","tpsbRev",rdim1,"(blank)",tt)     =    oscale*tpsb.l(a,tt)*px.l(a,tt)*xp.l(a,tt);
   rescon("%SimName%","tPrd",rdim1,"(blank)",tt)        =    100*tPrd.l(a,tt);
   rescon("%SimName%","tPrdRev",rdim1,"(blank)",tt)     =    oscale*tPrd.l(a,tt)*px.l(a,tt)*xp.l(a,tt);
   );

   rescon("%SimName%","tpsbRev","Total","(blank)",tt)   =    oscale*sum(a,tpsb.l(a,tt)*px.l(a,tt)*xp.l(a,tt));
   rescon("%SimName%","tprdRev","Total","(blank)",tt)   =    oscale*sum(a,tprd.l(a,tt)*px.l(a,tt)*xp.l(a,tt));

Loop((i,rdim1)$sameas(i,rdim1),
   rescon("%SimName%","texp",rdim1,"(blank)",tt)        =    100*tExp.l(i,tt) ;
   rescon("%SimName%","texpRev",rdim1,"(blank)",tt)     =    oscale*xe.l(i,tt)*chiPE(i)*pe.l(i,tt)*texp.l(i,tt);
   rescon("%SimName%","timp",rdim1,"(blank)",tt)        =    100*timp.l(i,tt) ;
   rescon("%SimName%","timpRev",rdim1,"(blank)",tt)     =    oscale*(xm.l(i,tt) + mdelst.l(i,tt))*pwm.l(i,tt)*er.l(tt)*tImp.l(i,tt);
   rescon("%SimName%","tVat","d","(blank)",tt)        =    100*tVat.l(i,"d",tt) ;
   rescon("%SimName%","tVat","m","(blank)",tt)        =    100*tVat.l(i,"m",tt) ;
   rescon("%SimName%","tVatRev",rdim1,"(blank)",tt)     =    oscale*((chiPD(i)*pd.l(i,tt) + pmarg.l(i,tt)*tmg.l(i,"d",tt))*tVat.l(i,"d",tt)*xd.l(i,tt)
                                                                     + (er.l(tt)*pwm.l(i,tt)*(1+tImp.l(i,tt)) + pmarg.l(i,tt)*tmg.l(i,"m",tt))*tVat.l(i,"m",tt)*xm.l(i,tt));
   rescon("%SimName%","tpafRev",rdim1,"Total",tt)       =   oscale*sum(aa, tPaf.l(i,aa,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,aa,tt));

  Loop((rdim2,aa)$sameas(aa,rdim2),
   rescon("%SimName%","tpaf",rdim1,rdim2,tt)            =   100*tPaf.l(i,aa,tt);
   rescon("%SimName%","tpafRev",rdim1,rdim2,tt)         =   oscale*tPaf.l(i,aa,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,aa,tt);
   );
 );
   rescon("%SimName%","texpRev","Total","(blank)",tt)   =    oscale* sum(i,xe.l(i,tt)*chiPE(i)*pe.l(i,tt)*texp.l(i,tt));
   rescon("%SimName%","timpRev","Total","(blank)",tt)   =    oscale* sum(i,(xm.l(i,tt) + mdelst.l(i,tt))*pwm.l(i,tt)*er.l(tt)*tImp.l(i,tt));
   rescon("%SimName%","tVatRev","Total","(blank)",tt)   =    oscale*sum(i,(chiPD(i)*pd.l(i,tt) + pmarg.l(i,tt)*tmg.l(i,"d",tt))*tVat.l(i,"d",tt)*xd.l(i,tt)
                                                                     + (er.l(tt)*pwm.l(i,tt)*(1+tImp.l(i,tt)) + pmarg.l(i,tt)*tmg.l(i,"m",tt))*tVat.l(i,"m",tt)*xm.l(i,tt));
  Loop((rdim2,aa)$sameas(aa,rdim2),
   rescon("%SimName%","tpafRev","Total",rdim2,tt)       =   oscale*sum(i, tPaf.l(i,aa,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,aa,tt));
  );

   rescon("%SimName%","tpafRev","Total","Total",tt)     =   oscale*sum((aa,i), tPaf.l(i,aa,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,aa,tt));

 Loop((rdim1,em)$sameas(rdim1,em),
   rescon("%SimName%","temiRev",rdim1,"Total",tt)         =   oscale*sum((emSrc,aa), tEmi.l(em,aa,tt)*emical.l(tt)*chiEmi(em,emSrc,aa,tt)*rhoEmi(em,emSrc,aa)*phiEmi(em,emSrc,aa)*sum(i$emsrc(i),xa.l(i,aa,tt))) ;;
    Loop((rdim2,aa)$sameas(rdim2,aa),
      rescon("%SimName%","temi",rdim1,rdim2,tt)            =   100*tEmi.l(em,aa,tt);
      rescon("%SimName%","temiRev",rdim1,rdim2,tt)         =   oscale*sum(emSrc, tEmi.l(em,aa,tt)*emical.l(tt)*chiEmi(em,emSrc,aa,tt)*rhoEmi(em,emSrc,aa)*phiEmi(em,emSrc,aa)*sum(i$emsrc(i),xa.l(i,aa,tt))) ;;
      );
  );

 Loop((rdim2,aa)$sameas(rdim2,aa),
   rescon("%SimName%","temiRev","Total",rdim2,tt)         =   oscale*sum((emSrc,em), tEmi.l(em,aa,tt)*emical.l(tt)*chiEmi(em,emSrc,aa,tt)*rhoEmi(em,emSrc,aa)*phiEmi(em,emSrc,aa)*sum(i$emsrc(i),xa.l(i,aa,tt))) ;;
 );

Loop((h,rdim1)$sameas(rdim1,h),
  rescon("%SimName%","tpaf",rdim1,"(blank)",tt) =  100*tPit.l(h,tt) ;
  rescon("%SimName%","tpafRev",rdim1,"(blank)",tt) = oscale*tPit.l(h,tt) * yh.l(h,tt)  ;
   );
Loop((entr,rdim1)$sameas(rdim1,entr),
  rescon("%SimName%","tpaf",rdim1,"(blank)",tt) =  100*tCit.l(entr,tt) ;
  rescon("%SimName%","tpafRev",rdim1,"(blank)",tt) = oscale*tCit.l(entr,tt) * entrY.l(entr,tt) ;
   );

  rescon("%SimName%","tPitRev","Total","(blank)",tt)   =    oscale*sum(h,tPit.l(h,tt) * yh.l(h,tt));
  rescon("%SimName%","tCitRev","Total","(blank)",tt)   =    oscale*sum(entr,tCit.l(entr,tt) * entrY.l(entr,tt));

