#include "MySensitiveDetector.hh"
#include "G4SDManager.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name), fHitsCollection(nullptr)
{
	//The collection name for the SensitiveDetector to use
        collectionName.insert("MyHitsCollection");
}

MySensitiveDetector::~MySensitiveDetector()
{
}

void MySensitiveDetector::Initialize(G4HCofThisEvent *HCE)
{
	//Create new HitsCollection
	fHitsCollection = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);

	//Register the HitsCollection to HCE
	static G4int hcID = -1;
	if (hcID < 0) hcID = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
	HCE -> AddHitsCollection(hcID, fHitsCollection);
}

G4bool MySensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *ToHist)
{	
	G4double Edep = step -> GetPreStepPoint() -> GetKineticEnergy();
	if (Edep <= 0.0) return false;

	if (step -> IsFirstStepInVolume()) {
		//New Hit object for data recording
        	MyHit *hit = new MyHit();

		//Types of data to accumulate in the Hit object
		hit -> SetdetID(step -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber());
		hit -> SetEdep(Edep);
		hit -> SetPos(step -> GetPreStepPoint() -> GetPosition());
		hit -> SetName(step -> GetTrack() -> GetDefinition() -> GetParticleName());
		hit -> SetTrackID(step -> GetTrack() -> GetTrackID());

		fHitsCollection -> insert(hit);

		return true;
	}

	return false;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent *HCE)
{
}
