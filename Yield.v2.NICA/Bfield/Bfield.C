Int_t nbin = 10;// #events
Int_t xmin = 0;// #events
Double_t xmax = 1;// #events
Float_t norm = nbin/(TMath::Abs(xmin)+TMath::Abs(xmax));
TH1F *eBH = new TH1F("eBH","", nbin,xmin,xmax);
TH1F *VH = new TH1F("VH","", nbin,xmin,xmax);

Double_t eB,V;
Double_t rA = 6.38;//fm
Double_t nucleons = 79;//Au

const Int_t entriesT = 10000000;
Int_t nT;
Double_t eBT[entriesT];
Double_t VT[entriesT];
Double_t timeT[entriesT];
TTree* BfieldT = new  TTree("BfieldT","B field tree ");

void Bfield(){
  for(int k=10; k<11; k++){
  gROOT->Reset();
  TChain mychain("T");
  mychain.Add(TString::Format("prueba%d.root",k));
  struct particula_t 
  {
    Float_t time,X,Y,Z,E,Px,Py,Pz,Pt,P,m,id,isoespin,charge,lastcoll,numbercoll,history,frezetime,frezeX,frezeY,frezeZ,frezeE,frezePx,frezePy,frezePz,b,nspec,R,PXR,eBx,eBy,eBz,eByWave,eByPoint,dCb;
  } PARTICLE;
  particula_t  particle;
  mychain.SetBranchAddress("particle",&particle);

  BfieldT->Branch("nT",&nT,"nT/I");
  BfieldT->Branch("eBT",eBT,"eBT[nT]/D");
  BfieldT->Branch("VT",VT,"VT[nT]/D");
  BfieldT->Branch("timeT",timeT,"timeT[nT]/D");


  Int_t nevent = mychain.GetEntries();
  cout << nevent << endl;
  for(Int_t j=0; j<nevent; j++){
    mychain.GetEvent(j);
    if(TMath::Finite(particle.eBx) && TMath::Finite(particle.eBy) && TMath::Finite(particle.eBz) 
      && particle.lastcoll==0) {
    eBT[nT] = TMath::Sqrt((particle.eBx*particle.eBx)+(particle.eBy*particle.eBy)+(particle.eBz*particle.eBz));
    VT[nT] = 2*TMath::Pi()*rA*rA*particle.time*TMath::Power((1/2*nucleons),2/3);
    timeT[nT] = particle.time;
    nT++;
    eBH->Fill(particle.time,eBT[nT]);
    VH->Fill(particle.time,VT[nT]);
    }
  }
  
  BfieldT->Fill();
  char name[60];
  sprintf(name,"Bfield.root");
  cout << " Writtiing file ->" << name << endl;
  TFile fOut(name, "recreate");
  fOut.cd();
  BfieldT->Write();
  }

  
 
  TCanvas* c1 = new TCanvas("c1","UrQMD test example",800,800);
  //gStyle->SetOptStat(false);
  c1->SetRightMargin(0.0465116);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);
  c1->SetLogy();
  eBH->Draw("hist p");
  eBH->SetMarkerColor(1);
  eBH->SetMarkerStyle(20);
  eBH->SetXTitle("t [fm]");
  eBH->GetXaxis()->CenterTitle(true);
  eBH->GetXaxis()->SetTitleSize(0.04);
  eBH->GetXaxis()->SetLabelSize(0.03);
  eBH->GetXaxis()->SetTitleOffset(1.2);
  eBH->SetYTitle("e|B|/m_{#pi}^{2}");
  eBH->GetYaxis()->CenterTitle(true);
  eBH->GetYaxis()->SetTitleSize(0.04);
  eBH->GetYaxis()->SetLabelSize(0.03);
  eBH->GetYaxis()->SetTitleOffset(1.2);
    
TCanvas* c2 = new TCanvas("c2","UrQMD test example",800,800);
  gStyle->SetOptStat(false);
  c2->SetRightMargin(0.0465116);
  c2->SetTopMargin(0.1);
  c2->SetFillColor(0);
  VH->Draw("hist p");
  VH->SetMarkerColor(1);
  VH->SetMarkerStyle(20);
  VH->SetXTitle("t [fm]");
  VH->GetXaxis()->CenterTitle(true);
  VH->GetXaxis()->SetTitleSize(0.04);
  VH->GetXaxis()->SetLabelSize(0.03);
  VH->GetXaxis()->SetTitleOffset(1.2);
  VH->SetYTitle("V ");
  VH->GetYaxis()->CenterTitle(true);
  VH->GetYaxis()->SetTitleSize(0.04);
  VH->GetYaxis()->SetLabelSize(0.03);
  VH->GetYaxis()->SetTitleOffset(1.2);
 
}