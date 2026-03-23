#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "MySensitiveDetector.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"

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
     	G4Material *WorldMat = nist -> FindOrBuildMaterial("G4_AIR");
	G4Material *detMat = nist -> FindOrBuildMaterial("G4_Galactic");
	//The material of the detectors is set to near vacuum (G4_Galactic) to prevent any particle formation inside.

     	//World -> This must exist or it may cause segfault
     	G4Box *WorldSol = new G4Box("WorldSol", 10. *m, 10. *m, 10. *m);
     	G4LogicalVolume *WorldLog = new G4LogicalVolume(WorldSol, WorldMat, "WorldLog");
     	G4VPhysicalVolume *WorldPhy = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), WorldLog, "WorldPhy", 0, false, 0);

	//Building SUBMET detector modules
	//Detector SolidVolume
    	const G4double cellSize = 5 *cm;
    	G4Box *detSol = new G4Box("detSol", cellSize/2, cellSize/2, 0.75 *m);

	//Detector LogicalVolume (Definition in DetectorConstruction.hh)
    	detLog = new G4LogicalVolume(detSol, detMat, "detLog");
	G4double tiltAngle = -1.023 *deg;	//Detectors are tilted for arctan(5/280) = 1.023 deg
	G4double roughness = 0.0 *deg;     	//+0.5 : less tilted floor (pointing downwards) / -0.5 : more tilted floor (pointing upwards)
    	G4RotationMatrix *rot = new G4RotationMatrix();
        	rot -> rotateX(tiltAngle + roughness);
        	rot -> rotateY(0 *deg);
        	rot -> rotateZ(0 *deg);
    	detLog -> SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

	//Detector PhysicalVolume
	//Number of modules in each direction
        const G4int nx = 10;
        const G4int ny = 8;
        const G4int nz = 2;

	//Parameters to adjust the detector center position
	const G4double x0 = 0.0;
	const G4double y0 = 0.0;
	const G4double z0 = 0.0;
        
	//Placing each modules
        for (G4int i = 0; i < nx; i++)
        {
                for (G4int j = 0; j < ny; j++)
                {
                        for (G4int k = 0; k < nz; k++)
                        {
                                G4double x = (-(nx - 1)/2.0 + i)*(cellSize + 1 *cm);
                                G4double y;
				G4double z;

                                if (k == 0) {
					y = (-(ny - 1)/2.0 + j)*(cellSize + 1 *cm);
					z = -125 *cm;
				}

                                else if (k == 1) {
					//Allignment to the front layer (Consider both tiltAngle & roughness)
					y = (-(ny - 1)/2.0 + j)*(cellSize + 1 *cm) - (5.0/280.0)*2.5 *m + 2.5*std::tan(roughness) *m;
					z = 125 *cm;
				}
	
				//Set the name of each module (e.g. Module_0_0_0)
                                std::stringstream ss;
                                ss << "Module_" << i << "_" << j << "_" << k;
                                G4String name = ss.str();

				//Change x0, y0, and z0 to move the detector position (Currently centered at (0, 0, 0))
                                auto detPos = G4ThreeVector(x + x0, y + y0, z + z0);
                                auto detPhy = new G4PVPlacement(rot, detPos, detLog, name, WorldLog, false, i + j*nx + k*nx*ny);
                        }
                }
        }

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
