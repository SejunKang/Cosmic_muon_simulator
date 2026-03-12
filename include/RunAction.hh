#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

struct IDList {
	G4int pName;
	G4int cProc;
	G4int E;
	G4int px;
	G4int py;
	G4int pz;
	G4int eid;
	G4int pid;
};

extern IDList id;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction() override;
    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;
    static G4int fTotalEvents;
};

#endif
