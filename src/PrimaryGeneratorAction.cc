#include "G4MuonMinus.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomTools.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    fPrimary -> SetParticleDefinition(G4MuonMinus::Definition());

    //Adjust physical values for cosmic muons
    fPrimary -> SetParticleEnergy(4. *GeV);
    fPrimary -> SetParticleCharge(-1. *eplus);
    fPrimary -> SetParticlePosition(G4ThreeVector(0., 3. *m, 0.));
    fPrimary -> SetParticleMomentumDirection(G4ThreeVector(0., -1., 0.));

    //If you want to simulate with random cosmic muon directions, use this instead
    //Format: G4RandomDirection(cos theta);
    /*
    G4ThreeVector dir = G4RandomDirection(0.99);
    dir.rotateX(90. *deg);	//The default beam direction is along z axis
    fPrimary -> SetParticleMomentumDirection(dir);
    */
    fPrimary -> GeneratePrimaryVertex(event);
}                                                                                                       
