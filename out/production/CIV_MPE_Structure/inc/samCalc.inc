if(ifSAM,

   samT(i,a,tt) = 0 ;

   samT(i,a,tt)   = xa.l(i,a,tt)*chiPA(i)*pa.l(i,tt)*(1+tpaf.l(i,a,tt)) ;
   samT(lnd,a,tt) = pland.l(a,lnd,tt)*xf.l(a,lnd,tt) ;
   samT(l,a,tt)   = xf.l(a,l,tt)*swage.l(a,l,tt) ;
   samT(cap,a,tt) = sum(v, kd.l(a,v,tt)*pk.l(a,v,tt)) ;
   samT(ptx,a,tt) = tprd.l(a,tt)*px.l(a,tt)*xp.l(a,tt) ;
   samT(psb,a,tt) = tpsb.l(a,tt)*px.l(a,tt)*xp.l(a,tt) ;
*   samT(stx,a,tt) = sum(i, tpaf.l(i,a,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,a,tt)) ;
   samT(ftx,a,tt) = sum(lnd$mapftax(lnd,ftx),tFac.l(a,lnd,tt) * pland.l(a,lnd,tt)*xf.l(a,lnd,tt))
                  + sum(l$mapftax(l,ftx),tFac.l(a,l,tt) * swage.l(a,l,tt)*xf.l(a,l,tt))
                  + sum((v,cap)$mapftax(cap,ftx),tFac.l(a,cap,tt) * pk.l(a,v,tt)*kd.l(a,v,tt)) ;
   samT(a,i,tt)   = chiP(a,i)*p.l(a,i,tt)*x.l(a,i,tt) ;

   samT(i,j,tt)   = chiPA(i)*pa.l(i,tt)*xa.l(i,j,tt) ;

   samT(otx,i,tt) = (chiPD(i)*pd.l(i,tt) + pmarg.l(i,tt)*tmg.l(i,"d",tt))*tvat.l(i,"d",tt)*xd.l(i,tt)
                 + (er.l(tt)*pwm.l(i,tt)*(1+timp.l(i,tt)) + pmarg.l(i,tt)*tmg.l(i,"m",tt))*tvat.l(i,"m",tt)*xm.l(i,tt) ;

   samT(mtx,i,tt) = (xm.l(i,tt) + mdelst.l(i,tt))*pwm.l(i,tt)*er.l(tt)*timp.l(i,tt) ;
   samT(etx,i,tt) =  xe.l(i,tt)*chiPE(i)*pe.l(i,tt)*texp.l(i,tt) ;
   samT(stx,i,tt) =   sum((ax), tpaf.l(i,ax,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,ax,tt))
                    + sum((j), tpaf.l(i,j,tt)*chiPA(i)*pa.l(i,tt)*xa.l(i,j,tt));
   samT(row,i,tt) = (xm.l(i,tt) + mdelst.l(i,tt))*pwm.l(i,tt)*er.l(tt) ;

   samT(h,lnd,tt)    = chit(h,lnd,tt)*sum(a, pland.l(a,lnd,tt)*xf.l(a,lnd,tt)) ;
   samT(entr,lnd,tt) = chitentr(entr,lnd,tt)*sum(a, pland.l(a,lnd,tt)*xf.l(a,lnd,tt)) ;
   samT(h,l,tt)      = chil(h,l,tt)*sum(a,xf.l(a,l,tt)*swage.l(a,l,tt)) ;
   samT(h,cap,tt)    = chikh(h,tt)*kapy.l(tt) ;
   samT(entr,cap,tt) = chikEntr(entr,tt)*kapy.l(tt) ;
*   samT(gov,entr,tt) = sum((inst,instd)$(mapinst(gov,inst) and mapinst(entr,instd)), transfers.l(inst,instd,tt)) ;
   samT(inv,entr,tt) = savEntr.l(entr,tt) ;
   samT(gov,cap,tt)  = kapy.l(tt)*(1 - sum(h, chikh(h,tt)) - sum(entr, chikEntr(entr,tt))) ;
   samT(gov,psb,tt)  = yg.l("psb",tt) ;
   samT(gov,ptx,tt)  = yg.l("ptx",tt);
   samT(gov,otx,tt)  = yg.l("otx",tt) ;
   samT(gov,mtx,tt)  = yg.l("mtx",tt);
   samT(gov,etx,tt)  = yg.l("etx",tt);
   samT(gov,ftx,tt)  =sum(a, sum(lnd$mapftax(lnd,ftx),tFac.l(a,lnd,tt) * pland.l(a,lnd,tt)*xf.l(a,lnd,tt))
                      + sum(l$mapftax(l,ftx),tFac.l(a,l,tt) * swage.l(a,l,tt)*xf.l(a,l,tt))
                      + sum((v,cap)$mapftax(cap,ftx),tFac.l(a,cap,tt) * pk.l(a,v,tt)*kd.l(a,v,tt))) ;

   samT(gov,stx,tt)  = yg.l("atx",tt) ;



   samT(dtx,h,tt)    = tpit.l(h,tt) * yh.l(h,tt);
   samT(dtx,entr,tt) = tcit.l(entr,tt) * entrY.l(entr,tt) ;
   samT(dtx,gov,tt)  = gTax.l(tt) ;
   samT(gov,dtx,tt)  = yg.l("dtx",tt) ;
   samT(inv,h,tt)    = savh.l(h,tt) ;
   samT(inv,entr,tt) = savEntr.l(entr,tt) ;
*   samT(inv,gov,tt)  = savg.l(tt) - sum(adpinv$map_adpinv(gov,adpinv),yf.l(adpinv,tt))  ;
   samT(inv,gov,tt)  = savg.l(tt) ;
   samT(inv,row,tt)  = er.l(tt)*savf.l(tt) ;
   samT(stb,inv,tt)  = sum(i, chiPS(i)*ps.l(i,tt)*delst.l(i,tt) + er.l(tt)*pwm.l(i,tt)*(1+timp.l(i,tt))*mdelst.l(i,tt)) ;

   samT(inst,instp,tt)$(chiTr(inst, instp) ne 0) = transfers.l(inst,instp,tt) ;
   samT(inst,dinst,tt) = chiTr(inst, dinst) * totTr.l(dinst,tt) ;
   samT(inst,row,tt) = er.l(tt)*rowtransfers.l(inst,tt);

   samT(i,fd,tt)     = chiPA(i)*pa.l(i,tt)*xa.l(i,fd,tt)*(1+tpaf.l(i,fd,tt)) ;
   samT(i,stb,tt)    = chiPS(i)*ps.l(i,tt)*delst.l(i,tt) + er.l(tt)*pwm.l(i,tt)*(1+timp.l(i,tt))*mdelst.l(i,tt) ;
   samT(i,row,tt)    = er.l(tt)*chiPWE(i)*pwe.l(i,tt)*xe.l(i,tt) ;
   SAMT(instfd,"i-debt",tt) =  rDebtStk.l(tt)*(chiDebtPayD(instfd) * (DebtStkD.l(tt) * rDebtStkD.l(tt) + DebtStkD.l(tt)*DebtIntD.l(tt)/100)
                                                   + chiDebtPayF(instfd) * (DebtStkF.l(tt) *  rDebtStkF.l(tt) + DebtStkF.l(tt)*DebtIntF.l(tt)/100))   ;
   SAMT("i-debt",instfd,tt) =  chiDebtNew(instfd,tt) * ygov.l(tt)  ;
   SAMT("i-debt",gov,tt) =  sum(instfd,debtPay.l(instfd,tt))  ;
   SAMT(gov,"i-debt",tt) =  sum(instfd,debtNew.l(instfd,tt))  ;
   samT(i,adpInv,tt) =  chiPA(i)*pa.l(i,tt)*xa.l(i,adpinv,tt)*(1+tpaf.l(i,adpinv,tt))  ;
   samT(i,gInv,tt) =  chiPA(i)*pa.l(i,tt)*xa.l(i,ginv,tt)*(1+tpaf.l(i,ginv,tt))  ;
   samT(ginv,gov,tt) =  yf.l(ginv,tt)  ;
   samT(adpinv,gov,tt)$map_adpInv(gov,adpinv) =  yf.l(adpinv,tt)  ;
   samT(inv,adpinv,tt)$map_adpInv(inv,adpinv) =  - yf.l(adpinv,tt)  ;
);


  samTBal(is,tt)= sum(js,samT(is,js,tt))-sum(js,samT(js,is,tt)) ;
  samTBal(is,tt)$(abs(samTBal(is,tt))<1E-6)= 0 ;

  samTDiff(is,js,tt)= samT(is,js,tt)- sam(is,js) ;
  samTDiff(is,js,tt)$(abs(  samTDiff(is,js,tt)) < 1E-8)= 0 ;
