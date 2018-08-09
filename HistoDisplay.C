#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
//Global variables
TCanvas *histodisplay;

void CreateHistoDisplay(TFile*);

int main(int argc, char** argv){
  TFile* f = new TFile("133Ba_CenterOfArray.root");
  TApplication theApp("App",&argc, argv);
  CreateHistoDisplay(f);
  theApp.Run();


}
void CreateHistoDisplay(TFile *myFile){
  histodisplay = new TCanvas("histDisplay","Histogram Display",0,0,1200,800);
  TH1* myHist;
  myFile->GetObject("hESpecFhgBhg10",myHist);
  histodisplay->cd();
  myHist->Draw("hist");
  histodisplay->Draw();
}
