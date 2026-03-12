//There is an alternative method for detecting hits using the SteppingAction
//But we will use SensitiveDetector instead because it is easier to change the code
//when the number of detectors increases

#include "SteppingAction.hh"
#include "G4Step.hh"

SteppingAction::SteppingAction(EventAction *EA) : G4UserSteppingAction(), m_EA(EA)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
}
