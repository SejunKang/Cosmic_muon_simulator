#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
 
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    	DetectorConstruction();
    	virtual ~DetectorConstruction();
    	virtual G4VPhysicalVolume *Construct() override;

    	//Function for registering SensitiveDetector
    	virtual void ConstructSDandField() override;

private:
	//Must define the logical volume here to use for SD
	G4LogicalVolume *detLog;
};

#endif
