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
    uint32_t bxcounter    = 0;
    uint32_t eventcounter = 1;
    uint32_t event        = 1;
    uint32_t orbitcounter = 0;
    uint32_t trigtime     = 0;
    uint32_t trigwidth    = 0;

    // creating branches in eventdata tree
    T->Branch("chip",         &chip,                   "chip/i");
    T->Branch("half",         &half,                   "half/i");
    T->Branch("daqdata",      "std::vector<uint32_t>", &channelData);
    T->Branch("bxcounter",    &bxcounter,              "bxcounter/i");
    T->Branch("eventcounter", &eventcounter,           "eventcounter/i");
    T->Branch("event",        &event,                  "event/i");
    T->Branch("orbitcounter", &orbitcounter,           "orbitcounter/i");
    T->Branch("trigtime",     &trigtime,               "trigtime/i");
    T->Branch("trigwidth",    &trigwidth,              "trigwidth/i");

    // filling the eventdata tree
    for(uint32_t erx = 0; erx < 6; erx++)  {

        for(uint32_t ich = 0; ich < 37; ich++) {
            channelData[ich] = erx*37 + ich;
        }

        chip = erx / 2;
        half = erx % 2;

        // fill the tree
        T->Fill();
    }

    T->Write();
}
