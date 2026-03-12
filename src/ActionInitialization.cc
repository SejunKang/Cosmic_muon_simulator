#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
	//Register RunAction (For Multithreading mode)
	SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
	//Register PrimaryGeneratorAction
	SetUserAction(new PrimaryGeneratorAction());

	//Register RunAction
	SetUserAction(new RunAction());

	//Register EventAction
	EventAction* EA = new EventAction();
	SetUserAction(EA);

	//Register SteppingAction
   	SetUserAction(new SteppingAction(EA));
}
