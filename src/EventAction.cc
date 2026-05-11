#include "G4RunManager.hh"
#include "EventAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"
#include "MyHit.hh"
#include "G4SDManager.hh"

EventAction::EventAction() : G4UserEventAction()
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *event)
{
	//Print out the current evenrID with the total number of events
   	G4int eventID = event -> GetEventID();
   	G4int TotalEvents = RunAction::fTotalEvents;
	std::cerr << std::fixed << std::setprecision(2) << "\rProgress: " << eventID + 1 << " Completed out of " << TotalEvents << " Events" << std::flush;
}

void EventAction::EndOfEventAction(const G4Event *event)
{    
	//Bring Hit Collection
	auto HCE = event -> GetHCofThisEvent();
	if (!HCE) return;

	static G4int hcID = -1;
	if (hcID < 0) hcID = G4SDManager::GetSDMpointer() -> GetCollectionID("detSD/MyHitsCollection");	//"SD name/Hit collection" name format
	
	//Bring Hit Collection pointer
	auto hcPointer = static_cast<MyHitsCollection*>(HCE -> GetHC(hcID));
	
	if (hcPointer) {
		G4AnalysisManager *AM = G4AnalysisManager::Instance();
		G4int numHits = hcPointer -> entries();
		
		//Record Hit informations
		for (G4int n = 0; n < numHits; n++) {
		MyHit *hit = (*hcPointer)[n];
		
		//Extract i, j, & k from the copynumber
		auto copyNum = hit -> GetdetID();
		G4int i = copyNum % (nx*ny) % nx;
        	G4int j = copyNum % (nx*ny) / nx;
        	G4int k = copyNum / (nx*ny);
		
		AM -> FillNtupleIColumn(0, event -> GetEventID());	//Current EventID
		AM -> FillNtupleIColumn(1, hit -> GetTrackID());	//TrackID of the detected particle
		AM -> FillNtupleIColumn(2, hit -> GetStepNumber());	//Step number of the detected particle
		AM -> FillNtupleIColumn(3, i);				//x row ID of the detector
		AM -> FillNtupleIColumn(4, j);				//y row ID of the detector
		AM -> FillNtupleIColumn(5, k);				//z row ID of the detector
		AM -> FillNtupleSColumn(6, hit -> GetName());		//Name of the detected particle
		AM -> FillNtupleDColumn(7, hit -> GetTime()/ns);	//Time when the particle detected
		
		//Get muon energy when reaching the detector (Currently not in use)
		//AM -> FillNtupleDColumn(8, hit -> GetEdep()/MeV);
									
		//Get muon position when reaching the detector (Currently not in use)
		//auto position = hit -> GetPos();
		//AM -> FillNtupleDColumn(9, position.getX()/m);
		//AM -> FillNtupleDColumn(10, position.getY()/m);
		//AM -> FillNtupleDColumn(11, position.getZ()/m);
		
		//Get muon momentum when reaching the detector (Currently not in use)
		//auto momentum = hit -> GetMomentum();
                //AM -> FillNtupleDColumn(12, momentum.getX()/MeV);
                //AM -> FillNtupleDColumn(13, momentum.getY()/MeV);
                //AM -> FillNtupleDColumn(14, momentum.getZ()/MeV);
	
		AM -> AddNtupleRow();
		}
	}
}
