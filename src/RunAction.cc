#include "G4RunManager.hh"
#include "RunAction.hh"
#include "G4AnalysisManager.hh"

//Initialize the number of total runs
G4int RunAction::fTotalEvents = 0;

RunAction::RunAction() : G4UserRunAction()
{
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
	//Find the total number of events to be processed (Will be sent to EventAction)
  	fTotalEvents = run -> GetNumberOfEventToBeProcessed();

	//Create ntuple and output file
   	G4AnalysisManager *AM = G4AnalysisManager::Instance();

   	AM -> SetVerboseLevel(0);
   	AM -> OpenFile("output.root");
   	AM -> CreateNtuple("tree", "cosmic_muon_detection");
   	AM -> CreateNtupleIColumn("eid");
	AM -> CreateNtupleIColumn("tid");
   	AM -> CreateNtupleIColumn("detid");
	AM -> CreateNtupleSColumn("pname");
   	AM -> CreateNtupleDColumn("E");
   	AM -> CreateNtupleDColumn("px");
   	AM -> CreateNtupleDColumn("py");
   	AM -> CreateNtupleDColumn("pz");
   	AM -> FinishNtuple(0); 
}

void RunAction::EndOfRunAction(const G4Run *run)
{
   	G4AnalysisManager *AM = G4AnalysisManager::Instance();
   	AM -> Write();
   	AM -> CloseFile();
}
