#ifndef MYSENSITIVEDETECTOR_HH
#define MYSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "MyHit.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
	public:
		MySensitiveDetector(G4String name);
		virtual ~MySensitiveDetector();
		virtual void Initialize(G4HCofThisEvent *HCE) override;
		virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory* ToHist) override;
		virtual void EndOfEvent(G4HCofThisEvent *HCE) override;

	private:
		MyHitsCollection *fHitsCollection;
};

#endif
