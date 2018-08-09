#include <TH1D.h>
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
TH1* myHist;

void UpdateDisplay(TFile*, int);
TF1* FitPeak(TFile*, int, int, int);

int main(int argc, char *argv[])
{
  // Open File
  TFile* myFile = new TFile("133Ba_CenterOfArray.root");
  
  TApplication *myapp=new TApplication("myapp",0,0);
  h1 = new TH1D("h1","Test",100,0,10);
  h2 = new TH1D("h2","Test2",100,0,10);
  TCanvas *c = new TCanvas("c", "Energy Calibrations", 400, 400);
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
  termin = std::cin.get();

  if((termin == 'b' || termin == 'B') && histN > 1) {
    termin = std::cin.get();
    histN -= 1;
  }  
  if((termin == 'f' || termin == 'F' || tryagain == 'y' ) && histN > 1){
    // Do fit
    TF1* myFit;
    if ( dumbass == 'n' ){
    std::cout << "Enter the minimum bin value and press enter" << std::endl;
    int minBin;
    std::cin >> minBin;
    std::cout << "Enter the maximum bin value and press enter" << std::endl;
    int maxBin;//
    std::cin >> maxBin;
    termin = std::cin.get();
    histN -= 1;

      UpdateDisplay(myFile,histN);
      myFit = FitPeak(myFile,histN, minBin, maxBin);
      termin = std::cin.get();
      c->Modified();
      c->Update();
    }

    char goodFit;
    std::cout << "Is this a good fit? [y/n]" << std::endl;
    gSystem->ProcessEvents();
    //    std::cin >> goodFit;
    termin = std::cin.get();
    
    if ( termin == 'y' ){
      std::cout << "OK. Writing fit parameters to file. Hit enter to proceed to next bar." << std::endl;
      std::cout << "Fit params: " << myFit->GetParameter(0) << std::endl;
      outfile << histN << " " << myFit->GetParameter(0) << " " << myFit->GetParameter(1) << " " << myFit->GetParameter(2) << std::endl;
      gSystem->ProcessEvents();
      termin = std::cin.get();
      tryagain = 'n';
      dumbass = 'n';
    }
    else if ( termin =='n' ){
      std::cout << "Hit enter to try new bounds." << std::endl;
      gSystem->ProcessEvents();
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
  if ( termin == 'q' ){
    exit(0);
  }
  else{
    //    termin = std::cin.get();
    UpdateDisplay(myFile,histN);
    c->Modified();
    c->Update();
    std::cout << "Hit enter to proceed, or 'f' to fit" << std::endl;
  }


  }while(true);

  outfile.close();
  return 0;
}


void UpdateDisplay(TFile* myFile, int histN){
  std::stringstream histNameStream;
  histNameStream << "hESpecFhgBhg" << histN;
  myFile->GetObject(histNameStream.str().c_str(),myHist);
  //  if (histN==2){
  myHist->Draw("hist");
    //  }
    //  else{
    //    h1->Draw("hist");
    //  }
}
TF1* FitPeak(TFile* myFile, int histN, int minBin, int maxBin){

  std::stringstream histNameStream;
  histNameStream << "hESpecFhgBhg" << histN;
  myFile->GetObject(histNameStream.str().c_str(),myHist);
  TF1 *fa1 = new TF1("fa1","gaus",minBin,maxBin);
  myHist->Fit("fa1","","",minBin,maxBin);
  fa1->Draw("same");
  return fa1;
}
