#include "MyPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

MyPhysicsList::MyPhysicsList()
{
	//PhysicsLists to register
   	RegisterPhysics (new G4EmStandardPhysics());
   	RegisterPhysics (new G4OpticalPhysics());
   	RegisterPhysics (new G4DecayPhysics());
   	RegisterPhysics (new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{
}
