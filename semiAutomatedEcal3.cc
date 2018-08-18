#include <TH1D.h>
#include <string>
#include <TApplication.h>
#include <TRint.h>
//#include <TROOT.h>
#include <TPad.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <iostream>
#include <TFile.h>
#include <sstream>
#include <TF1.h>
#include <fstream>
// Global
TH1D* h2;
TH1D* h1;
TH1D* myHist;
TH1D* myHist1;
TH1D* myHist2;

void UpdateDisplay(TFile*, int);
TF1* FitPeak1(TFile*, int, int, int);
TF1* FitPeak2(TFile*, int, int, int);
TF1* FitPeak3(TFile*, int, int, int);
Double_t lorentzianPeak(Double_t*, Double_t*);
  
int main(int argc, char *argv[])
{
  // Open File
  //  TFile* myFile = new TFile("133Ba_CenterOfArray.root");
  //TFile* myFile = new TFile("outfile22NaCenterCollimated.root");
  //  TFile* myFile = new TFile("outfile4938.root");
  TFile* myFile = new TFile("myBaHist.root");
  //TFile* myFile = new TFile("22Na_test.root");
  //  TFile* myFile = new TFile("outfile4940.root");
  //TFile* myFile = new TFile("outfile5004.root");
  //  TFile* myFile = new TFile("outfile4992.root");
  //  TFile* myFile = new TFile("22Na_CenterOfArray_Update_15.root");
  //    TFile* myFile = new TFile("133Ba_CenterOfArray_Update_60.root");
  //  TFile* myFile = new TFile("137Cs_CenterOfArray_Update.root");
  
  TApplication *myapp=new TApplication("myapp",0,0);
  h1 = new TH1D("h1","Test",100,0,10);
  h2 = new TH1D("h2","Test2",100,0,10);
  TCanvas *c = new TCanvas("c", "Energy Calibrations", 600, 500);
  h1->FillRandom("gaus",100000);
  h2->FillRandom("gaus",100000);

  c->Modified();
  c->Update();
  char termin;
  int histN=0;
  char tryagain='n';
  char dumbass='n';

  std::ofstream outfile;
  outfile.open ("example.txt");
  
  do{

  gSystem->ProcessEvents();
  histN++;
  //  std::cout << histN << std::endl;
  //  if ( histN!=8){
    termin = std::cin.get();

    if((termin == 'b' || termin == 'B') && histN > 1) {
      termin = std::cin.get();
      histN -= 2;
      UpdateDisplay(myFile,histN);
      c->Modified();
      c->Update();

    }
    else if((termin == 'f' || termin == 'F' || tryagain == 'y' ) && histN > 1){
      // Do fit
      TF1* myFit;
      int minBin;
      int maxBin;
      char whichHist;
      if ( dumbass == 'n' ){
	std::cout << "Which histogram do you want to fit?" << std::endl;
	std::cout << "Teal is z0; Orange is z10p; Violet is z10n." << std::endl;
	std::cin >> whichHist;	

	if ( whichHist == '0'){

	  std::cout << "Enter the minimum bin value and press enter" << std::endl;
	  std::cin >> minBin;
	  std::cout << "Enter the maximum bin value and press enter" << std::endl;
	  std::cin >> maxBin;
	  termin = std::cin.get();
	  histN -= 1;
		  
	  std::cout << "Here" << std::endl;
	  UpdateDisplay(myFile,histN);
	  myFit = FitPeak1(myFile,histN, minBin, maxBin);
	  termin = std::cin.get();
	  c->Modified();
	  c->Update();
	  gSystem->ProcessEvents();
	  char goodFit;
	  std::cout << "Is this a good fit? [y/n]" << std::endl;
	  gSystem->ProcessEvents();
	  //    std::cin >> goodFit;
	  termin = std::cin.get();
	  
	  if ( termin == 'y' ){
	    std::cout << "OK. Writing fit parameters to file. Hit enter to proceed to next bar." << std::endl;
	    std::cout << "Fit params: " << myFit->GetParameter(0) << std::endl;
	    outfile << histN << " " << minBin << " " << maxBin << " " << myFit->GetParameter(0) << " " << myFit->GetParameter(1) << " " << myFit->GetParameter(2) << std::endl;
	    std::stringstream mystring;
	    mystring << "bar" << histN << ".png";
	    c->SaveAs(mystring.str().c_str(),"PNG");
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'n';
	    dumbass = 'n';
	  }
	  else if ( termin =='n' ){
	    std::cout << "Hit enter to try new bounds." << std::endl;
	    c->Modified();
	    c->Update();
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'y';
	    dumbass = 'n';
	    
	  }
	  else{
	    std::cout << "Not a valid response. Hit enter to try again." << std::endl;
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'y';
	    dumbass = 'y';
	  }
	  
	}
	
	else if ( whichHist == 'p'){
	  std::cout << "Enter the minimum bin value and press enter" << std::endl;
	  std::cin >> minBin;
	  std::cout << "Enter the maximum bin value and press enter" << std::endl;
	  std::cin >> maxBin;
	  termin = std::cin.get();
	  histN -= 1;
	
	  
	  std::cout << "Next" << std::endl;
	  UpdateDisplay(myFile,histN);
	  myFit = FitPeak3(myFile,histN, minBin, maxBin);
	  termin = std::cin.get();
	  c->Modified();
	  c->Update();
	  gSystem->ProcessEvents();


	  char goodFit;
	  std::cout << "Is this a good fit? [y/n]" << std::endl;
	  gSystem->ProcessEvents();
	  //    std::cin >> goodFit;
	  termin = std::cin.get();
	  
	  if ( termin == 'y' ){
	    std::cout << "OK. Writing fit parameters to file. Hit enter to proceed to next bar." << std::endl;
	    std::cout << "Fit params: " << myFit->GetParameter(0) << std::endl;
	    outfile << histN << " " << minBin << " " << maxBin << " " << myFit->GetParameter(0) << " " << myFit->GetParameter(1) << " " << myFit->GetParameter(2) << std::endl;
	    std::stringstream mystring;
	    mystring << "bar" << histN << ".png";
	    c->SaveAs(mystring.str().c_str(),"PNG");
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'n';
	    dumbass = 'n';
	  }
	  else if ( termin =='n' ){
	    std::cout << "Hit enter to try new bounds." << std::endl;
	    c->Modified();
	    c->Update();
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'y';
	    dumbass = 'n';
	    
	  }
	  else{
	    std::cout << "Not a valid response. Hit enter to try again." << std::endl;
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'y';
	    dumbass = 'y';
	  }	  
	}
	
	else if ( whichHist == 'n'){

	  std::cout << "Enter the minimum bin value and press enter" << std::endl;
	  std::cin >> minBin;
	  std::cout << "Enter the maximum bin value and press enter" << std::endl;
	  std::cin >> maxBin;
	  termin = std::cin.get();
	  histN -= 1;

	  std::cout << "What" << std::endl;
	  UpdateDisplay(myFile,histN);
	  myFit = FitPeak2(myFile,histN, minBin, maxBin);
	  termin = std::cin.get();
	  c->Modified();
	  c->Update();
	  gSystem->ProcessEvents();

	  char goodFit;
	  std::cout << "Is this a good fit? [y/n]" << std::endl;
	  gSystem->ProcessEvents();
	  //    std::cin >> goodFit;
	  termin = std::cin.get();
	  
	  if ( termin == 'y' ){
	    std::cout << "OK. Writing fit parameters to file. Hit enter to proceed to next bar." << std::endl;
	    std::cout << "Fit params: " << myFit->GetParameter(0) << std::endl;
	    outfile << histN << " " << minBin << " " << maxBin << " " << myFit->GetParameter(0) << " " << myFit->GetParameter(1) << " " << myFit->GetParameter(2) << std::endl;
	    std::stringstream mystring;
	    mystring << "bar" << histN << ".png";
	    c->SaveAs(mystring.str().c_str(),"PNG");
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'n';
	    dumbass = 'n';
	  }
	  else if ( termin =='n' ){
	    std::cout << "Hit enter to try new bounds." << std::endl;
	    c->Modified();
	    c->Update();
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'y';
	    dumbass = 'n';
	    
	  }
	  else{
	    std::cout << "Not a valid response. Hit enter to try again." << std::endl;
	    gSystem->ProcessEvents();
	    termin = std::cin.get();
	    tryagain = 'y';
	    dumbass = 'y';
	  }
	  
	}
	else{
	  std::cout << "Not a valid answer. Hit enter to try again" << std::endl;
	  gSystem->ProcessEvents();
	  termin = std::cin.get();
	  tryagain = 'y';
	  dumbass = 'y';
	  
	}

      }
      
    }
    /*    if ( termin == 'q' ){
      exit(0);
      }*/
    else{
      termin = std::cin.get();
      UpdateDisplay(myFile,histN);
      c->Modified();
      c->Update();
      std::cout << "Hit enter to proceed, 'b' for back, or 'f' to fit" << std::endl;
    }
    

  }while(true);

  outfile.close();
  return 0;
}


void UpdateDisplay(TFile* myFile, int histN){
  std::stringstream histNameStream;
  histNameStream << "hESpecFhgBlg" << histN << "_z0";
  //  histNameStream << "hZPosFhgBlg" << histN;
  myFile->GetObject(histNameStream.str().c_str(),myHist);
  myHist->SetLineColor(kTeal-6);
  myHist->SetLineWidth(2);
  myHist->Draw("hist");

  std::stringstream histNameStream1;
  histNameStream1 << "hESpecFhgBlg" << histN << "_z10n";  
  myFile->GetObject(histNameStream1.str().c_str(),myHist1);
  myHist1->SetLineColor(kViolet+3);
  myHist1->SetLineWidth(2);
  myHist1->Draw("same");
  std::stringstream histNameStream2;
  histNameStream2 << "hESpecFhgBlg" << histN << "_z10p";    
  myFile->GetObject(histNameStream2.str().c_str(),myHist2);
  myHist2->SetLineColor(kOrange+9);
  myHist2->SetLineWidth(2);
  myHist2->Draw("same");

}
TF1* FitPeak1(TFile* myFile, int histN, int minBin, int maxBin){

  std::stringstream histNameStream;
  histNameStream << "hESpecFhgBlg" << histN << "_z0";
  //  histNameStream << "hZPosFhgBlg" << histN;
  myFile->GetObject(histNameStream.str().c_str(),myHist);
  TF1 *fa1 = new TF1("fa1","gaus",minBin,maxBin);
  //TF1 *fitFcn = new TF1("fitFcn",lorentzianPeak,minBin,maxBin,3);
  //  fitFcn->SetParameter(1,40); // width
  //  fitFcn->SetParameter(2,9000);   // peak

  myHist->Fit("fa1","","",minBin,maxBin);
  fa1->Draw("same");
  //  return fa1;
  //  fitFcn->Draw("same");
  return fa1;
}
TF1* FitPeak2(TFile* myFile, int histN, int minBin, int maxBin){

  std::stringstream histNameStream;
  histNameStream << "hESpecFhgBlg" << histN << "_z10n";
  //  histNameStream << "hZPosFhgBlg" << histN;
  myFile->GetObject(histNameStream.str().c_str(),myHist);
  TF1 *fa1 = new TF1("fa1","gaus",minBin,maxBin);
  //TF1 *fitFcn = new TF1("fitFcn",lorentzianPeak,minBin,maxBin,3);
  //  fitFcn->SetParameter(1,40); // width
  //  fitFcn->SetParameter(2,9000);   // peak

  myHist->Fit("fa1","","",minBin,maxBin);
  fa1->Draw("same");
  //  return fa1;
  //fitFcn->Draw("same");
  return fa1;
}
TF1* FitPeak3(TFile* myFile, int histN, int minBin, int maxBin){

  std::stringstream histNameStream;
  histNameStream << "hESpecFhgBlg" << histN << "_z10p";
  //  histNameStream << "hZPosFhgBlg" << histN;
  myFile->GetObject(histNameStream.str().c_str(),myHist);
  TF1 *fa1 = new TF1("fa1","gaus",minBin,maxBin);
  //TF1 *fitFcn = new TF1("fitFcn",lorentzianPeak,minBin,maxBin,3);
  //  fitFcn->SetParameter(1,40); // width
  //  fitFcn->SetParameter(2,9000);   // peak

  myHist->Fit("fa1","","",minBin,maxBin);
  fa1->Draw("same");
  //  return fa1;
  //fitFcn->Draw("same");
  return fa1;
}
// Lorenzian Peak function
Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[1]/TMath::Pi()) /
    TMath::Max( 1.e-10,(x[0]-par[2])*(x[0]-par[2])
		+ .25*par[1]*par[1]);
}

