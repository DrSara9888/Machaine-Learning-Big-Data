#include <math.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <string.h>
TCanvas * tc;
TH2F * hao;
TProfile2D * haem;
TH1F * haebad;
TH2F * han;
TH2F * h_badbins_energy;
TH2F * h_goodbins_energy;
TH2F * h_badbins_occupancy;
TH2F * h_goodbins_occupancy;
TH2F * h_sigmaplot_good;
TH2F * h_rmsplot_good;
TH2F * h_sigmaplot_bad;
TH2F * h_rmsplot_bad;
TAxis * xax;
TAxis * yax;
TAxis * xax1;
TAxis * yax1;
TProfile * hr;
TH1 * hn;
TH2F * hod;

//const char layer[16] = "EMB2C";
const char run[16] = "91639";

BinsDiffByStripsForClusters12(){
  char name[128];
  char path[128];

  // ################### Variables declared ###############################
  TFile * f = new TFile("HIST.91639.RNDM_unmasked.root");

  // ################## Open file ########################################

  sprintf(path,"run_%s/CaloMonitoring/ClusterMon/CaloCalTopoClusterNoTrigSel/2d_Rates",run);
  //sprintf(path,"run_%s/CaloMonitoring/ClusterMon/EMTopoCluster430NoTrigSel/2d_Rates",run);  
  f->cd(path);
  sprintf(name,"m_EtavsPhi0");
  cout << "retrieving histogram " << name << " from " << path << endl;
  hao = (TH2F*) gDirectory->Get(name);
    
  sprintf(path,"run_%s/CaloMonitoring/ClusterMon/CaloCalTopoClusterNoTrigSel/2d_AvEnergy",run);
  //sprintf(path,"run_%s/CaloMonitoring/ClusterMon/EMTopoCluster430NoTrigSel/2d_AvEnergy",run);
  f->cd(path);
  sprintf(name,"etaphi_thresh_avgenergy_0");
  cout << "retrieving histogram " << name << " from " << path << endl;
  haem = (TProfile2D*) gDirectory->Get(name);
  
  sprintf(name,"etaphi_avgenergy_badchan");
  cout << "retrieving histogram " << name << " from " << path << endl;
  haebad = (TH1F*) gDirectory->Get(name);
  

  xax = hao->GetXaxis();
  yax = hao->GetYaxis();
  xax1 = haem->GetXaxis();
  yax1 = haem->GetYaxis();
  int nbinx = xax->GetNbins();
  int nbiny = yax->GetNbins();
  
  cout << "nbinx" << nbinx << endl;
  cout << "nbiny" << nbiny<< endl; 
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  // ######################## histograms read #####################################
  // ######################## axis parameters read #####################################

  hr = new TProfile("avgoverphi","Average Occupancy of Skimmed Clusters vs #eta",nbinx,xax->GetXmin(),xax->GetXmax());
  hr->SetXTitle("#eta");
  hr->SetYTitle("Average Occupancy");

  hn = new TH1F("nbadbins","Number of Problematic Bins Found in #eta Slice",nbinx,xax->GetXmin(),xax->GetXmax());
  hn->SetXTitle("#eta");
  hn->SetYTitle("Number of Bad Bins"); 

  h_badbins_energy = new TH2F("EnergyFromBadbins","Average Energy of Problematic Bins Found after skimming ",nbinx,xax1->GetXmin(),xax1->GetXmax(),nbiny,yax1->GetXmin(),yax1->GetXmax());
  h_badbins_energy->SetXTitle("eta");
  h_badbins_energy->SetYTitle("phi");
  
  h_goodbins_energy = new TH2F("EnergyFromGoodbins","Average Energy From Good Bins Found after skimming ",nbinx,xax1->GetXmin(),xax1->GetXmax(),nbiny,yax1->GetXmin(),yax1->GetXmax());
  h_goodbins_energy->SetXTitle("eta");
  h_goodbins_energy->SetYTitle("phi");

h_badbins_occupancy = new TH2F("OccupancyFromBadBins","Occupancy of Problematic Bins Found after skimming ",nbinx,xax->GetXmin(),xax->GetXmax(),nbiny,yax->GetXmin(),yax->GetXmax());
  h_badbins_occupancy->SetXTitle("eta");
  h_badbins_occupancy->SetYTitle("phi");

  h_goodbins_occupancy = new TH2F("OccupancyFromGoodBins","Occupancy of Good Bins Found after skimming ",nbinx,xax->GetXmin(),xax->GetXmax(),nbiny,yax->GetXmin(),yax->GetXmax());
  h_goodbins_occupancy->SetXTitle("eta");
  h_goodbins_occupancy->SetYTitle("phi");

  h_sigmaplot_good = new TH2F("OccupancyLessThanSigmaThresh","Occupancy of Bins Less Than Sigma Threshold",nbinx,xax->GetXmin(),xax->GetXmax(),nbiny,yax->GetXmin(),yax->GetXmax());
  h_sigmaplot_good->SetXTitle("eta");
  h_sigmaplot_good->SetYTitle("phi");

  h_rmsplot_good = new TH2F("OccupancyLessThanRMSThresh","Occupancy of Bins Less Than RMS Threshold",nbinx,xax->GetXmin(),xax->GetXmax(),nbiny,yax->GetXmin(),yax->GetXmax());
  h_rmsplot_good->SetXTitle("eta");
  h_rmsplot_good->SetYTitle("phi");

  h_sigmaplot_bad = new TH2F("OccupancyGreaterThanSigmaThresh","Occupancy of Greater Than Sigma Threshold",nbinx,xax->GetXmin(),xax->GetXmax(),nbiny,yax->GetXmin(),yax->GetXmax());
  h_sigmaplot_bad->SetXTitle("eta");
  h_sigmaplot_bad->SetYTitle("phi");

  h_rmsplot_bad = new TH2F("OccupancyGreaterThanRMSThresh","Occupancy of Bins Greater Than RMS Threshold",nbinx,xax->GetXmin(),xax->GetXmax(),nbiny,yax->GetXmin(),yax->GetXmax());
  h_rmsplot_bad->SetXTitle("eta");
  h_rmsplot_bad->SetYTitle("phi");
  
  // ############### new histograms booked ######################################
  
  double ignoreval = 0;
  int    nsigma    = 3;
  int    nrms      = 10;
  int    iterdiv   = 2;
  int    maxdiffrel   = 1;
  int    niter = 4;
  //int    minstat   = 0;
  int 	 nbadbins = 0;
  int    ngoodbins = 0;
  int 	 maxnrms  = 0;
  double maxocc = -999999.9;
  double minocc = 999999.9;
  double minavg = 9999999;
  

  // ############# variables used in this macro declared ######################
  
  for ( int k = 1 ; k < nbinx+1; k++ ){
    
    double avg = 0;
    double sigma = 0;
    double rms = 0;
    //double etaAvgEn = 0;
    double etaAvgEnOverThresh = 0;
    //double etaAvgNoise = 0;
    double sigmathresh = 9999999999;
    double rmsthresh   = 9999999999;
    int    binCount = 0;
    float  xbin = xax->GetBinCenter(k);
    int    i = 0;
    double prevavg = 0;
    
    //Iterate niter times, applying badBin cuts after first pass
    //for ( int i = 0; i<niter ; i++) {
    do { 
      prevavg=avg;
      //double sumAvgEn = 0;
      double sumEnOverThresh = 0;
      //double sumNoise = 0;
      double sum = 0;
      binCount = 0;
      
      for ( int l = 1 ; l < nbiny+1; l++ ) {
	//find average for this x-slice
	double inputcont = hao->GetBinContent(k,l);
	if ( (i == 0) || ((fabs(inputcont - avg) <= sigmathresh) || (fabs(inputcont - avg) <= rmsthresh/iterdiv)) ){
	  if ( (inputcont != ignoreval) ){
	    sum += inputcont;
	    binCount++;
	    //sumAvgEn = haen->GetBinContent(k,l);
	    sumEnOverThresh += haem->GetBinContent(k,l);
	    //sumNoise = han->GetBinContent(k,l);
	  }
	}
      } // finish for loop finding good bins and adding their content to calculate average for this slice

      if (binCount != 0){
	
        avg = sum / binCount;
	sigma = sqrt(avg);
	sigmathresh = sigma * nsigma * sqrt(1.*binCount);
	//etaAvgEn = sumAvgEn / binCount;
	etaAvgEnOverThresh = sumEnOverThresh / binCount;
	//etaAvgNoise = sumNoise / binCount;
	if(avg < minavg) minavg = avg;
      }
      else {
	avg = 0;
	sigma = 0;
      } // new average and sigma calculated based on the presence of good bins

      double sumsq = 0;
      binCount = 0;
      int nbadbins1 = 0;
      for ( int l = 1 ; l < nbiny+1; l++ ) {

        float ybin = yax->GetBinCenter(l);
	double inputcont = hao->GetBinContent(k,l);	
	if ( (i == 0) || ((fabs(inputcont - avg) <= sigmathresh) || (fabs(inputcont - avg) <= rmsthresh/iterdiv)) ){ 
          sumsq += pow( (inputcont - avg) , 2);
          binCount++;
          nbadbins1++;


        }
        //else {
          

        //} 
      } // finish for loop finding sum of squares of deviation from mean for this slice

      if (binCount != 0){
	rms = sqrt( sumsq/binCount);
	rmsthresh = rms * nrms /* sqrt(1. *binCount);*/;
      }
      else {
	rms = 0;
      } // new rms calculated and set

      i = i + 1;
      if (i >= 100) prevavg=avg; 
    } while ( (avg != prevavg) && (i <= 100) );  
    //End of iterative sigma/rms/avg finder for this eta slice using DO WHILE statements
    
    if (binCount != 0) {
      for ( int l = 0 ; l < nbiny+1; l++ ) {
        float ybin = yax->GetBinCenter(l);
        double inputcont = hao->GetBinContent(k,l);
        if (inputcont != 0) {
          if(inputcont > maxocc) maxocc = inputcont;
          if(inputcont < minocc) minocc = inputcont; 
          if ( (inputcont > ( sigmathresh + avg )) && (inputcont >  ( rmsthresh + avg )) ) {
	    nbadbins++;
	    hn->Fill(xbin);
            if (inputcont > ( sigmathresh + avg )) h_sigmaplot_bad->Fill(xbin,ybin,haem->GetBinContent(k,l));
            if (inputcont > ( rmsthresh + avg )) h_rmsplot_bad->Fill(xbin,ybin,haem->GetBinContent(k,l));
            h_badbins_energy->Fill(xbin,ybin,haem->GetBinContent(k,l));  
            h_badbins_occupancy->Fill(xbin,ybin,hao->GetBinContent(k,l));
            cout << "eta = " << xbin << " phi = " << ybin << " occupancy = " << inputcont << " energy = " << haem->GetBinContent(k,l) << endl;
            if( ((inputcont - avg)/rms) > maxnrms ) {
	      maxnrms = (inputcont - avg)/rms;
	    }
          }       
          else {
            if (inputcont > ( sigmathresh + avg )) h_sigmaplot_good->Fill(xbin,ybin,haem->GetBinContent(k,l));
            if (inputcont > ( rmsthresh + avg )) h_rmsplot_good->Fill(xbin,ybin,haem->GetBinContent(k,l));
            h_goodbins_energy->Fill(xbin,ybin,haem->GetBinContent(k,l));
            h_goodbins_occupancy->Fill(xbin,ybin,hao->GetBinContent(k,l));
            ngoodbins++;
          }
        }
      }//double avEnMedEth = haem->GetBinContent(k,l);
    } // bad bins filled

    hr->Fill(xbin,avg);
    //cout<<"filled"<<endl;
  } // finish for loop for all slices in eta

  cout <<"complete"<<endl;


  //Do binned occupancy histograms:

  //Inch out minocc and maxocc so as not to miss anything:
  minocc -= 0.01*fabs(minocc);
  maxocc += 0.01*fabs(maxocc);
  
  //Automatically generate logarithmic bin array:
  double occbins[31];
  double deltaOcc = pow(maxocc/minocc,1/30.0);
  occbins[0] = minocc;
  for(int itr = 1; itr < 31; itr++) {
    occbins[itr] = occbins[itr-1] * deltaOcc;
  }
  
  hod = new TH2F("occvseta","Cluster Occupancy vs #eta",nbinx,xax->GetXmin(),xax->GetXmax(),30,occbins);
  hod->SetXTitle("#eta");
  hod->SetYTitle("Cluster Occupancy");
  
  ho = new TH1F("1DOccupancy","Cluster Occupancy Distribution, all #eta and #phi",30,occbins);
  ho->SetYTitle("Cluster Occupancy");
  
  for ( int k = 1 ; k < nbinx+1; k++ ){
    for ( int l = 0 ; l < nbiny; l++ ) {
      double inputcont = hao->GetBinContent(k,l);
      hod->Fill(xax->GetBinCenter(k),inputcont);
      ho->Fill(inputcont);
      
    }
  }

  double avg_occu = 0;
  double sum_occu = 0;
  double rms_occu = 0;
  int bincount_occu = 0;
  double sumsq_occu = 0;
  double avg_eng = 0;
  double sum_eng = 0;
  double rms_eng = 0;
  int bincount_eng = 0;
  double sumsq_eng = 0;
  for ( int k = 1 ; k < nbinx+1; k++ ){
    for ( int l = 0 ; l < nbiny; l++ ) {
      double inputcont = hao->GetBinContent(k,l);
      sum_occu += inputcont;
      bincount_occu++;
      double inputcont = haem->GetBinContent(k,l);  
      sum_eng += inputcont;
      bincount_eng++;
    }
  }
  avg_occu = sum_occu/bincount_occu;
  avg_eng = sum_eng/bincount_eng;
  bincount_occu = 0;
  bincount_eng = 0;
  for ( int k = 1 ; k < nbinx+1; k++ ){
    for ( int l = 0 ; l < nbiny; l++ ) {
      double inputcont = hao->GetBinContent(k,l);
      sumsq_occu += pow( (inputcont - avg_occu) , 2);
      bincount_occu++;
      double inputcont = haem->GetBinContent(k,l);  
      sumsq_eng += pow( (inputcont - avg_eng) , 2);
      bincount_eng++;
    }
  }
  rms_occu = sqrt(sumsq_occu/bincount_occu);
  rms_eng = sqrt (sumsq_eng/bincount_eng);
  
  // ##### fill histograms needed after skimming for good cells to find average #####

  cout << " Total number of bad bins = " << nbadbins << "   " << ngoodbins << "  " << endl;
  cout << " Maximum (occupancy - average)/rms = " << maxnrms << endl;
  cout << " avg occupancy = " << avg_occu << endl;
  cout << " avg energy = " << avg_eng << endl;
  cout << " rms in occupancy = " << rms_occu << endl;
  
  tc0 = new TCanvas("tc","High Occupancy Channels 91890",1024,750);
  tc0->Divide(2,2);
  tc0->cd(1);
  hao->SetStats(kFALSE);
  hao->SetMinimum(minocc);
  hao->SetMaximum(maxocc);
  hao->SetContour(100);
  hao->Draw("COLZ");
  gPad->SetLogz(1);
  minavg -= 0.05 * fabs(minavg);

  tc0->cd(2);
  hr->SetStats(kFALSE);
  hr->SetMinimum(minavg);
  hr->Draw();
  
  tc0->cd(3);
  ho->Draw();
  gPad->SetLogy(1);
  gPad->SetLogx(1);

  tc0->cd(4);
  hod->SetContour(100);
  hod->SetMinimum(1);
  hod->SetStats(kFALSE);
  hod->Draw("COLZ");
  tc0->cd(4)->SetLogy(1);
  tc0->cd(4)->SetLogz(1);
  
  // ############# Tcanvas 1 plots printed  ###############################

  tc1 = new TCanvas("tc11","additional plots for occupancy",1000,750);
  tc1->Divide(2,2);
  tc1->cd(1);
  hn->Draw();
  
  
  tc1->cd(2);
  h_badbins_occupancy->SetStats(kFALSE);
  h_badbins_occupancy->SetMinimum(minocc);
  h_badbins_occupancy->SetMaximum(maxocc);
  h_badbins_occupancy->SetContour(100);
  h_badbins_occupancy->Draw("COLZ");
  gPad->SetLogz(1);
  minavg -= 0.05 * fabs(minavg);

  tc1->cd(3);
  h_goodbins_occupancy->SetStats(kFALSE);
  h_goodbins_occupancy->SetMinimum(minocc);
  h_goodbins_occupancy->SetMaximum(maxocc);
  h_goodbins_occupancy->SetContour(100);
  h_goodbins_occupancy->Draw("COLZ");
  gPad->SetLogz(1);
  minavg -= 0.05 * fabs(minavg);

  tc1->cd(4);
  hao->SetStats(kFALSE);
  hao->SetMinimum(minocc);
  hao->SetMaximum(maxocc);
  hao->SetContour(100);
  hao->Draw("COLZ");
  gPad->SetLogz(1);
  minavg -= 0.05 * fabs(minavg);
  
  // ############# Tcanvas 2 plots printed  ###############################

  tc2 = new TCanvas("tc2","additional plots for energy of clusters",1000,750);
  tc2->Divide(2,2);
  tc2->cd(1);
  //haem->SetContour(100);
  //haem->SetMinimum(1);
  haem->SetStats(kFALSE);
  haem->Draw("lego");
  
  tc2->cd(2);
  h_badbins_energy->Draw("lego");

  tc2->cd(3);
  h_goodbins_energy->Draw("Lego");

  // ############# Tcanvas 3 plots printed  ###############################

  tc3 = new TCanvas("tc3","additional plots on Threshold selection",1000,750);
  tc3->Divide(2,2);
  tc3->cd(1);
  h_sigmaplot_good->Draw("lego");
  
  tc3->cd(2);
  h_sigmaplot_bad->Draw("lego");
  
  tc3->cd(3);
  h_rmsplot_good->Draw("lego");
 
  tc3->cd(4);
  h_rmsplot_bad->Draw("lego");


  // ############# Tcanvas 4 plots printed  ###############################

  tc4 = new TCanvas("tc3","additional plots on Threshold selection",1500,4000);
  tc4->Divide(4,2);
    
  tc4->cd(1);
  hao->SetStats(kFALSE);
  hao->Draw("COLZ");
  gPad->SetLogz(1);
  
  tc4->cd(2);
  haem->SetStats(kFALSE);
  haem->Draw("COLZ");
  gPad->SetLogz(1);

  tc4->cd(3);
  hao->SetStats(kFALSE);
  hao->Draw("COLZ");
  gPad->SetLogz(1);  
  
  tc4->cd(4);
  haem->SetStats(kFALSE);
  haem->Draw("COLZ");
  gPad->SetLogz(1);
  
  tc4->cd(5);
  hao->SetStats(kFALSE);
  hao->Draw("COLZ");
  gPad->SetLogz(1);
  
  tc4->cd(6);
  haem->SetStats(kFALSE);
  haem->Draw("COLZ");
  gPad->SetLogz(1);

  tc4->cd(7);
  hao->SetStats(kFALSE);
  hao->Draw("COLZ");
  gPad->SetLogz(1);
  
  tc4->cd(8);
  haem->SetStats(kFALSE);
  haem->Draw("COLZ");
  gPad->SetLogz(1);
  

}

