#include "lib.h"

void eventdataTree(){
    // ROOT init
    TFile *output = new TFile("test.root", "RECREATE");
    TDirectory *dir = output->mkdir("hgcroc_rawdata");
    dir->cd();

    // creating the tree
    TTree *T = new TTree("eventdata", "eventdata");

    // defining variables
    unsigned int chip  = 0;
    unsigned int event = 1;
    std::vector<unsigned int> channelData(41, 0);
    int half         = 0;
    int bxcounter    = 0;
    int eventcounter = 1;
    int orbitcounter = 0;
    int trigtime     = 0;
    int trigwidth    = 0;

    // creating branches in eventdata tree
    T->Branch("chip",         &chip,                   "chip/i");
    T->Branch("event",        &event,                  "event/i");
    T->Branch("daqdata",      "std::vector<uint32_t>", &channelData);
    T->Branch("half",         &half,                   "half/I");
    T->Branch("bxcounter",    &bxcounter,              "bxcounter/I");
    T->Branch("eventcounter", &eventcounter,           "eventcounter/I");
    T->Branch("orbitcounter", &orbitcounter,           "orbitcounter/I");
    T->Branch("trigtime",     &trigtime,               "trigtime/I");
    T->Branch("trigwidth",    &trigwidth,              "trigwidth/I");

    // filling the eventdata tree
    for(uint32_t erx = 0; erx < 6; erx++)  {

        for(uint32_t ich = 0; ich < 37; ich++) {
            channelData[ich+2] = erx*37 + ich;
        }

        chip = erx / 2;
        half = erx % 2;

        // fill the tree
        T->Fill();
    }

    T->Write();
}
