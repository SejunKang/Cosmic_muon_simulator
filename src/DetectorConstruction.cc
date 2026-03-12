#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "MySensitiveDetector.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
     	//NIST manager -> Database for all material properties
	G4NistManager *nist = G4NistManager::Instance();
    	
	//Set the World material as air
     	G4Material *WorldMat = nist -> FindOrBuildMaterial("G4_AIR");

     	//World -> This must exist or it may cause segfault
     	G4Box *WorldSol = new G4Box("WorldSol", 5. *m, 5. *m, 5. *m);
     	G4LogicalVolume *WorldLog = new G4LogicalVolume(WorldSol, WorldMat, "WorldLog");
     	G4VPhysicalVolume *WorldPhy = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), WorldLog, "WorldPhy", 0, false, 0);

	//Dummy detectors to see if the code works well -> Change the geometries to what you want to build
	G4Material *detMat = nist -> FindOrBuildMaterial("G4_SILICON_DIOXIDE");
	G4Box *detSol = new G4Box("detSol", 2.5 *cm, 2.5 *cm, 75.0 *cm);
	detLog = new G4LogicalVolume(detSol, detMat, "detLog");		//The logical volume must be defined in the header as a private variable to use it as a SensitiveDetector
	
	//If you want to place identical shapes in multiple places, just change the Copynumber rather than defining each of their geometries
	G4VPhysicalVolume *detPhy0 = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), detLog, "detPhy0", WorldLog, false, 0);	 //Copynumber = 0 
	G4VPhysicalVolume *detPhy1 = new G4PVPlacement(0, G4ThreeVector(5. *cm, 0., 0.), detLog, "detPhy1", WorldLog, false, 1); //Copynumber = 1

	return WorldPhy;
}

//SensitiveDetector registeration
void DetectorConstruction::ConstructSDandField()
{
	//Bring SD Manager
	auto SDManager = G4SDManager::GetSDMpointer();
	
	//Create new SD object for detector
	auto detSD = new MySensitiveDetector("detSD");
	SDManager -> AddNewDetector(detSD);
	
	//Connect the SD to a LogicalVolume
	SetSensitiveDetector(detLog, detSD);
}
