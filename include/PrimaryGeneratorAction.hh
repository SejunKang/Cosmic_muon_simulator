#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "/home/sejunkang/EcoMug/EcoMug.h"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event *event);

private:
    G4ParticleGun *fPrimary;

    //EcoMug variables
    EcoMug fMuonGen;
    G4ParticleDefinition *MuonPlus;
    G4ParticleDefinition *MuonMinus; 
};

#endif
