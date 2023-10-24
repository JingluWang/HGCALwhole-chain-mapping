#include "lib.h"

void eventdataTree(){
    // ROOT init
    TFile *output = new TFile("test.root", "RECREATE");
    TDirectory *dir = output->mkdir("hgcroc_rawdata");
    dir->cd();

    // creating the tree
    TTree *T = new TTree("eventdata", "eventdata");

    // defining variables
    uint32_t chip = 0;
    uint32_t half = 0;
    std::vector<uint32_t> channelData(37, 0);
    int bxcounter    = 0;
    int eventcounter = 0;
    int orbitcounter = 0;
    int trigtime     = 0;
    int trigwidth    = 0;

    // creating branches in eventdata tree
    T->Branch("chip",         &chip,                   "chip/I");
    T->Branch("half",         &half,                   "half/I");
    T->Branch("daqdata",      "std::vector<uint32_t>", &channelData);
    T->Branch("bxcounter",    &bxcounter,              "bxcounter/I");
    T->Branch("eventcounter", &eventcounter,           "eventcounter/I");
    T->Branch("orbitcounter", &orbitcounter,           "orbitcounter/I");
    T->Branch("trigtime",     &trigtime,               "trigtime/I");
    T->Branch("trigwidth",    &trigwidth,              "trigwidth/I");

    // filling the eventdata tree
    for(int erx = 0; erx < 6; erx++)  {

        for(int ich = 0; ich < 37; ich++) {
            channelData[ich] = erx*37 + ich;
        }

        chip = erx / 2;
        half = erx % 2;

        // fill the tree
        T->Fill();
    }

    T->Write();
}
