# HGCALwhole-chain-mapping

## Setup
#### lxplus
    . hgcal.sh

#### >> hgcal.sh content: setup cmsenv
    cd /afs/cern.ch/user/j/jinglu/jlwang/HGCAL/WholeChainMappingForDQM/CMSSW_13_2_0_pre3/src
    cmsenv

#### folder location
    cd ../../srcMapping/


## Produce input rootfile for DQM
#### Run
    root -l eventdataTree.C

- Output rootfile: test.root
