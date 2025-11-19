# HaaAnalysis-CROWN

A physics analysis framework for studying Higgs boson decays to two pseudoscalars (H→aa) using the CROWN (Configurable ROOT Objects With NanoAOD) framework.

## Overview

This project implements a comprehensive analysis pipeline for searching for Higgs boson decays to two pseudoscalars in high-energy physics data. The analysis is built on the CROWN framework, which provides a flexible and efficient way to process NanoAOD data using ROOT's RDataFrame.

## Features

- **Multi-era Support**: Analysis configuration for 2016preVFP, 2016postVFP, 2017, and 2018 data
- **Multiple Decay Channels**: Support for muon-muon (mm), electron-electron (ee), and electron-muon (em) final states
- **Comprehensive Sample Types**: 
  - Data
  - Background processes (ttbar, Drell-Yan, W+jets, diboson)
  - Signal samples (Haa)
- **Systematic Uncertainties**: Built-in support for systematic shifts and uncertainties
- **Object Selection**: Advanced selection algorithms for photons, leptons, jets, and particle flow candidates
- **Scale Factors**: Integrated scale factor corrections for data/MC agreement


## Analysis Components

### Physics Objects

- **Electrons**: Selection based on Cut-based ID, isolation, and kinematic requirements
- **Muons**: Selection using tight ID, isolation, and kinematic cuts
- **Photons**: Photon identification and isolation for pseudoscalar reconstruction
- **Jets**: Jet selection with pile-up ID and overlap removal
- **Particle Flow Candidates**: Used for pseudoscalar and Higgs reconstruction algorithms

### Higgs Reconstruction

The analysis implements several algorithms for Higgs candidate reconstruction:

- **ClosestToHiggsMassAlgo**: Selects particle combinations closest to the Higgs mass
- **FourHardestPFCands**: Uses the four highest-pT particle flow candidates
- **ChargePairs**: Considers charge requirements in particle pairing

## Configuration

The analysis is highly configurable through Python configuration files:

- `config.py`: Main analysis configuration
- `overlap_conf.py`: Alternative configuration for overlap studies

Key configuration parameters include:
- Pile-up reweighting files for different eras
- Scale factor corrections
- Object selection criteria
- Systematic uncertainty definitions

## License

[Add appropriate license information]

---

*This analysis is part of the CMS Collaboration's search for exotic Higgs boson decays to pseudoscalars.*
