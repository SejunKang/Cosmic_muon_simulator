#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

class EventAction : public G4UserEventAction
{
	public:
 		EventAction();
 		virtual ~EventAction();
 		virtual void BeginOfEventAction(const G4Event *event) override;
 		virtual void EndOfEventAction(const G4Event *event) override;

	private:
		//Number of modules in each direction
        	const G4int nx = 10;
        	const G4int ny = 8;
        	const G4int nz = 2;
};

#endif
