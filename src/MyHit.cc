#include "MyHit.hh"

//Set initial memory allocation as zero
G4ThreadLocal G4Allocator<MyHit>* MyHitAllocator = 0;

MyHit::MyHit() : G4VHit()
{
	//Initialization
	fEdep = 0.0;
	fPos = G4ThreeVector();
	fMomentum = G4ThreeVector();
	fdetID = -1;
	fName = "";
	fTrackID = -1;
}

MyHit::~MyHit()
{
}
