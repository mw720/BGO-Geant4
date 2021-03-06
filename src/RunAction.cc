#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "TH1.h"
#include "CascadeGenerator.hh"
#include <vector>

namespace {

ofstream ifs("output.dat");

}

RunAction::RunAction(CascadeGenerator* aCasGen, DAQManager* aDAQMgr) {

  CasGen = aCasGen;
  DAQMgr = aDAQMgr;

}

RunAction::~RunAction() {

}

void RunAction::BeginOfRunAction(const G4Run* aRun) {

  DAQMgr->StartOfRun();

//  G4cout << "\n--------------------Run " << aRun->GetRunID() << " start.------------------------------\n" << G4endl;

//  CasGen->SetRun(aRun->GetRunID());//starts at 0
  CasGen->SetCascade();
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
    
}

void RunAction::EndOfRunAction(const G4Run* aRun) {

  CasGen->EndOfRun();
  DAQMgr->EndOfRun();

  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;
  
//  ETotLikelihood();
//  E01Likelihood();
//  MultLikelihood();

//  G4cout << NbOfEvents <<" Events this run" << G4endl;
//  G4cout << "\n--------------------End of Run------------------------------\n" << G4endl;

}

//-------------------------------------------------------------------------------------
//lilelihood functions
//-------------------------------------------------------------------------------------

/*
void RunAction::ETotLikelihood() {

  double norm = h_bgoE2->Integral()/h_bgoE->Integral();
  double hit = h_bgoE->Integral();

  for (int i=1; i<=h_bgoE->GetNbinsX(); i++) {
    h_bgoE->SetBinContent(i,h_bgoE->GetBinContent(i)*norm);
  }

  double lnL = 0;

  for (int i=1; i<=h_bgoE->GetNbinsX(); i++) {

    double Xi = h_bgoE2->GetBinContent(i);//exp data
    double Ni = h_bgoE->GetBinContent(i);//sim data

    double lnL_temp = log( pow(Ni,Xi) * pow(2.71828,Ni*(-1.)) / factorial(int(Xi)) );

    if (Xi==0) lnL_temp = 0;

    lnL += lnL_temp;

//    G4cout << i << "\t" << Ni << "\t" << Xi << "\t" << lnL_temp << G4endl;

    h_bgoE->SetBinContent(i,0);   

  }

//  G4cout << cascade[0] << "\t" << cascade[1] << "\t" << cascade[2] << "\t" << cascade[3] << "\t" << cascade[4] << "\t" << hit/double(NbOfEvents)*100. << "\t" << (-2)*lnL << G4endl; 

//  ifs << cascade[0] << "\t" << cascade[1] << "\t" << cascade[2] << "\t" << cascade[3] << "\t" << cascade[4] << "\t" << hit/double(NbOfEvents)*100. << "\t" << (-2)*lnL << G4endl; 

}

void RunAction::E01Likelihood() {

  double exp_tot = 0;
  double sim_tot = 0;

  double hit = h_bgoE->Integral();

  for (int i=0; i<4; i++) {
    exp_tot+=E01_exp[i];
    sim_tot+=E01[i];
  }

  double norm = exp_tot/sim_tot;

  double lnL = 0;

  for (int i=0; i<4; i++) {

    double Xi = E01_exp[i];//exp data
    double Ni = E01[i]*norm;//sim data

    double lnL_temp = log( pow(Ni,Xi) * pow(2.71828,Ni*(-1.)) / factorial(int(Xi)) );

    if (Xi==0) lnL_temp = 0;

    lnL += lnL_temp;

//    G4cout << i << "\t" <<  E01[i] << "\t" << Ni << "\t" << Xi << "\t" << lnL_temp << G4endl;

  }

//  G4cout << cascade[0] << "\t" << cascade[1] << "\t" << cascade[2] << "\t" << cascade[3] << "\t" << cascade[4] << "\t" << hit/double(g_count)*100. << "\t" << (-2)*lnL << G4endl; 

//  ifs << cascade[0] << "\t" << cascade[1] << "\t" << cascade[2] << "\t" << cascade[3] << "\t" << cascade[4] << "\t" <<hit/double(g_count)*100. << "\t" << (-2)*lnL << G4endl; 

  E01[0]=0;
  E01[1]=0;
  E01[2]=0;
  E01[3]=0;

}

void RunAction::MultLikelihood() {

  double exp_tot = 0;
  double sim_tot = 0;

  for (int i=1; i<=h_bgomult->GetNbinsX(); i++) {
    exp_tot+=h_bgomult2->GetBinContent(i);
    sim_tot+=h_bgomult->GetBinContent(i);
  }

  double norm = exp_tot/sim_tot;

  double lnL = 0;

  for (int i=1; i<=h_bgomult->GetNbinsX(); i++) {

    double Xi = h_bgomult2->GetBinContent(i);//exp data
    double Ni = h_bgomult->GetBinContent(i)*norm;//sim data

    double lnL_temp = log( pow(Ni,Xi) * pow(2.71828,Ni*(-1.)) / factorial(int(Xi)) );

    if (Xi==0) lnL_temp = 0;

    lnL += lnL_temp;

//    G4cout << i << "\t" <<  E01[i] << "\t" << Ni << "\t" << Xi << "\t" << lnL_temp << G4endl;

  }

}*/

