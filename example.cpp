#include <TFile.h>
#include <TTree.h>
#include <TString.h>



void example(){

	// open the file
	TFile *f = TFile::Open("/mnt/hadoop/scratch/dmytro/NanoAOD/505/Charmonium+Run2016D-17Jul2018-v1+MINIAOD/B000929A-C68A-E811-AF3D-0CC47A7C3408.root");
	// get the tree from the file
	TTree *t = (TTree*)f->Get("Events");

	// define a cut
	string cut = "abs(bkmm_jpsimc_mass-5.4)<0.5&&mm_kin_sl3d>%f";

	// let's run this cut from 0 to 5 in steps of 0.5
	int i = 0;
	for (float cut_value=2; cut_value<5; cut_value+=0.5){

		TH1F h ("histo", "my histogram", 100, 4.9,5.6);//histogram with 100 bins between 4.9 and 5.6
		auto this_cut = Form(cut.c_str(),cut_value);
		cout<< "Drawing with cut: "<<this_cut<<endl;
		//create a canvas
		TCanvas c; //
		// draw something, using this cut
		t->Draw("bkmm_jpsimc_mass>>histo", this_cut);
		cout<< "This histogram contains "<<h.GetEntries()<<" events."<<endl;
		//save the plot as a png image
		c.SaveAs(Form("mass_%d.png",i));
		h.Reset(); //empty the histogram
		i++;
	}
}