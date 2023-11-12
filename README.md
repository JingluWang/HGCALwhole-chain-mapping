# HGCALwhole-chain-mapping

## Setup @lxplus
#### at home directory
    . hgcal.sh

#### >> hgcal.sh content: setup cmsenv
    cd /afs/cern.ch/user/j/jinglu/jlwang/HGCAL/WholeChainMappingForDQM/CMSSW_13_2_0_pre3/src
    cmsenv

#### folder location
    cd ../../srcMapping/


## STEP 1: Produce input rootfile for DQM
#### Run
    root -l eventdataTree.C

- Output rootfile: test.root


## STEP 2: Generate DQM plots (Example: LD -- MLFL00041ped)
#### go to cmsenv
    . runDir.sh
#### Reco command
    cmsRun -j FrameworkJobReport_pedestal_run0_roc2root_RECO.xml EventFilter/HGCalRawToDigi/test/tb_raw2reco.py mode=hgcmodule fedId=0 slinkBOE=0x2a cbHeaderMarker=0x0 econdHeaderMarker=0x154 ECONDsInPassthrough=0 activeECONDs=0 ECONDsInCharacterisation=0 inputFiles=../../srcMapping/test.root fedId=0 output=test_RECO conditions=MLFL00041ped dqmOnly=False runNumber=14140848 maxEvents=1000000000
#### DQM command
    cmsRun -j FrameworkJobReport_pedestal_run0_roc2root_DQM.xml DPGAnalysis/HGCalNanoAOD/test/tb_dqm.py tbEra=MLFL00041ped inputFiles=file:test_RECO_numEvent1000000000.root

### Output DQM rootfile (copied to this folder)
<img width="602" alt="DQMroot" src="https://github.com/JingluWang/HGCALwhole-chain-mapping/assets/107279970/b62b45f5-1b36-48f9-8554-5118cf9fa402">

#### copy to and back to this folder
    cp DQM_V0001_HGCAL_R014140848.root ../../srcMapping/DQMplots/LD
    . toRootfile.sh
    
#### plot location
    cd DQMplots/LD

- **Plots (LD: MLFL00041ped)**
  - adc_avg
    ![hex_adc_avg](https://github.com/JingluWang/HGCALwhole-chain-mapping/assets/107279970/421890f9-5785-427c-b5c3-ddbabc122c41)

  - channelId
    ![channelId](https://github.com/JingluWang/HGCALwhole-chain-mapping/assets/107279970/6f761574-ee18-4fe4-b66c-503db3bb3e91)


- Reference plots :
  #### location
      cd ref/
      root -l DQM_V0001_HGCAL_R014140848.root

## STEP 3: Check the difference between ADC_AVG and channelId
#### run (no cmsenv needed)
    cd src/
    root -l checkHEX.C
