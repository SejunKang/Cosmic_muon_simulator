#include "PrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleMomentum.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
	fPrimary = new G4ParticleGun();

	//Set the sky plane that cosmic muons falls off
	fMuonGen.SetUseSky();
	fMuonGen.SetSkySize({4. *m, 4. *m});
	fMuonGen.SetSkyCenterPosition({0., 0., 6. *m});

	MuonPlus = G4ParticleTable::GetParticleTable() -> FindParticle("mu+");
	MuonMinus = G4ParticleTable::GetParticleTable() -> FindParticle("mu-");
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
	//Adapt the EcoMug cosmic muon physical informations
	fMuonGen.Generate();
	std::array<double, 3> muonPos = fMuonGen.GetGenerationPosition();
	double muonTotMom = fMuonGen.GetGenerationMomentum();
	double muonTheta = fMuonGen.GetGenerationTheta();
	double muonPhi = fMuonGen.GetGenerationPhi();

	G4ThreeVector muonPosVec = G4ThreeVector(muonPos[0] *mm, muonPos[2] *mm, muonPos[1] *mm);
	G4ParticleMomentum muonMomVec = G4ParticleMomentum(muonTotMom*sin(muonTheta)*cos(muonPhi) *GeV, muonTotMom*cos(muonTheta) *GeV, muonTotMom*sin(muonTheta)*sin(muonPhi) *GeV);

	//Adjust the physical values for cosmic muons (Rotation applied for y-axis muon shower)
	if (fMuonGen.GetCharge() < 0) fPrimary -> SetParticleDefinition(MuonMinus);
        else fPrimary -> SetParticleDefinition(MuonPlus);
	
	fPrimary -> SetParticlePosition(muonPosVec);
        fPrimary -> SetParticleMomentum(muonMomVec);
        fPrimary -> GeneratePrimaryVertex(event);
}                                                                                                       
