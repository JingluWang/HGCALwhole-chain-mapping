#include "lib.h"

// -------------------- Modification Zone - begin ----------------------
// choose wafer
int wafer = 4;// 1: LD | 2: LD3 | 3: LD4 | 4: HD

// default wafer info: test
TString outputFile = "test.root";
int Nerx = 6;

// Number of events
unsigned int Nevent = 100;
// -------------------- Modification Zone - end ----------------------

void eventdataTree(){
    // choose wafer
    switch (wafer) {
        case 1: 
            outputFile = "LD.root";
            Nerx = 6;
            break;
        case 2: 
            outputFile = "LD3.root";
            Nerx = 3;
            break;
        case 3:
            outputFile = "LD4.root";
            Nerx = 3;
            break;
        case 4:
            outputFile = "HD.root";
            Nerx = 12; 
            break; 
    }

    // ROOT init
    TFile *output = new TFile(outputFile, "RECREATE");
    TDirectory *dir = output->mkdir("hgcroc_rawdata");
    dir->cd();

    // creating the tree
    TTree *T = new TTree("eventdata", "eventdata");

    // defining variables
    std::vector<unsigned int> channelData(41, 0);
    unsigned int chip  = 0;
    unsigned int event = 1;
    int eventcounter   = 1;
    int half           = 0;
    int bxcounter      = 0;
    int orbitcounter   = 0;
    int trigtime       = 0;
    int trigwidth      = 0;

    // creating branches in eventdata tree
    T->Branch("daqdata",      "std::vector<uint32_t>", &channelData);
    T->Branch("chip",         &chip,                   "chip/i");
    T->Branch("event",        &event,                  "event/i");
    T->Branch("eventcounter", &eventcounter,           "eventcounter/I");
    T->Branch("half",         &half,                   "half/I");
    T->Branch("bxcounter",    &bxcounter,              "bxcounter/I");
    T->Branch("orbitcounter", &orbitcounter,           "orbitcounter/I");
    T->Branch("trigtime",     &trigtime,               "trigtime/I");
    T->Branch("trigwidth",    &trigwidth,              "trigwidth/I");

    // filling the eventdata tree
    for (unsigned int i = 0; i < Nevent; i++) {
        event        = i;
        eventcounter = i;    

        for (unsigned int erx = 0; erx < Nerx; erx++)  {
            for (unsigned int ich = 0; ich < 41; ich++) { 
                unsigned int val = (erx*41 + ich) & 0x3ff;
                channelData[ich+2] = val | (val<<10) | (val<<20); 
            }

            chip = erx / 2;
            half = erx % 2;

            // fill the tree 
            T->Fill();
        }
    }

    T->Write();
}
