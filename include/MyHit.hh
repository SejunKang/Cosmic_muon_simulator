#ifndef MYHIT_HH
#define MYHIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"

class MyHit : public G4VHit
{
	public:
		MyHit();
		virtual ~MyHit();

		//Overload new and delete operators to use for memory allocation
		inline void* operator new(size_t);
		inline void operator delete(void*);

		//Functions for data accumulation
		//Energy
		void SetEdep(G4double E) {fEdep = E;}
		G4double GetEdep() const {return fEdep;}

		//Position
		void SetPos(G4ThreeVector pos) {fPos = pos;}
		G4ThreeVector GetPos() const {return fPos;}

		//Detector ID
		void SetdetID(G4int detid) {fdetID = detid;}
		G4int GetdetID() const {return fdetID;}

		//Particle name
		void SetName(G4String name) {fName = name;}
		G4String GetName() const {return fName;}

		//TrackID
		void SetTrackID(G4int trackID) {fTrackID = trackID;}
		G4int GetTrackID() const {return fTrackID;}

		private:
		G4double fEdep;
		G4ThreeVector fPos;
		G4int fdetID;
		G4String fName;
		G4int fTrackID;
};

//Definitions of HitsCollection & HitsAllocator
typedef G4THitsCollection<MyHit> MyHitsCollection;
extern G4ThreadLocal G4Allocator<MyHit>* MyHitAllocator;

//Incarnation of the inline operators
inline void* MyHit::operator new(size_t) {
	if (!MyHitAllocator) MyHitAllocator = new G4Allocator<MyHit>;
	return (void*) MyHitAllocator -> MallocSingle();
}

inline void MyHit::operator delete(void* aHit) {
	MyHitAllocator -> FreeSingle((MyHit*) aHit);
}

#endif
