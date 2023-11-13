#include "../lib.h"

// ----------------------- Modification Zone - begin -----------------------
// choose wafer
int wafer = 1;// 1: LD | 2: LD3 | 3: LD4 | 4: HD

// default wafer (LD)
TString WAFER = "LD";
TString TAG   = "LD_0";

// general hex plot names without tags
TString HEX_adc_avg   = "hex_adc_avg_zside0_plane1_u1_v1_";
TString HEX_channelId = "hex_channelId_zside0_plane1_u1_v1_";

// folder
TString folderName = "DQMData/Run 14140848/HGCAL/Run summary/Summary";
// ----------------------- Modification Zone - end -----------------------

void checkHex() {
    // choose wafer
    switch (wafer) {
        case 1:
            WAFER = "LD";
            TAG   = "LD_0";
            break;
        case 2:
            WAFER = "LD3";
            TAG   = "LD_3";
            break;
        case 3:
            WAFER = "LD4";
            TAG   = "LD_4";
            break;
        case 4:
            WAFER = "HD";
            TAG   = "HD_0";
            break;
    }

    TString inputfile  = "../DQMplots/" + WAFER + "/DQM_V0001_HGCAL_R014140848.root";

    TFile *input = new TFile( inputfile );
    TDirectory *folder = (TDirectory*) input->Get( folderName );

    // hex 1: adc_avg with wafer tag
    TH2Poly *hexADC = (TH2Poly*) folder->Get( HEX_adc_avg + TAG );
    hexADC->SetDirectory(0);

    // hex 2: channelId with wafer tag
    TH2Poly *hexChannelId = (TH2Poly*) folder->Get( HEX_channelId + TAG );
    hexChannelId->SetDirectory(0);

    for (int i = 0; i < 200; i++) {
        float xADC       = hexADC->GetBinContent(i);
        float xChannelId = hexChannelId->GetBinContent(i);
        float diff       = xADC - xChannelId;

        std::cout << "bin=" << i << ",\t    adc_avg=" << xADC << ",\t    channelId=" << xChannelId << ",\t    adc_avg-channelId=" << diff << std::endl;

    }
}
