#include "../lib.h"

// ----------------------- Modification Zone - begin -----------------------
TString inputfile  = "../DQMplots/DQM_V0001_HGCAL_R014140848.root";
TString folderName = "DQMData/Run 14140848/HGCAL/Run summary/Summary";

TString HEX_adc_avg   = "hex_adc_avg_zside0_plane1_u1_v1_LD_0";
TString HEX_channelId = "hex_channelId_zside0_plane1_u1_v1_LD_0";
// ----------------------- Modification Zone - end -----------------------

void checkHex() {
    TFile *input = new TFile( inputfile );
    TDirectory *folder = (TDirectory*) input->Get( folderName );

    TH2Poly *hexADC = (TH2Poly*) folder->Get( HEX_adc_avg );
    hexADC->SetDirectory(0);

    TH2Poly *hexChannelId = (TH2Poly*) folder->Get( HEX_channelId );
    hexChannelId->SetDirectory(0);

    for (int i = 0; i < 200; i++) {
        float xADC       = hexADC->GetBinContent(i);
        float xChannelId = hexChannelId->GetBinContent(i);
        float diff       = xADC - xChannelId;

        std::cout << diff << std::endl;
    }
}
