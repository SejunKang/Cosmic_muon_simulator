#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include <ctime>

//User-Defined Classes
#include "DetectorConstruction.hh"
#include "MyPhysicsList.hh"  
#include "ActionInitialization.hh"

int main(int argc, char **argv)
{
    //Decide UI session (GUI or Batch)
    G4UIExecutive *ui = nullptr;
    if (argc == 1) ui = new G4UIExecutive(argc, argv);

    //Set random seed number
    G4Random::setTheSeed(time(nullptr));

    //Construct RunManager
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

    //Set user-defined initialization classes
    runManager -> SetUserInitialization(new DetectorConstruction());
    runManager -> SetUserInitialization(new MyPhysicsList());
    runManager -> SetUserInitialization(new ActionInitialization());

    //Initialize Geant4 kernel
    runManager -> Initialize();

    //Initialize visualization manager
    auto visManager = new G4VisExecutive;
    visManager -> Initialize();

    //Get the pointer to UImanager
    auto UImanager = G4UImanager::GetUIpointer();
		 
	//GUI or Batch mode depending on the value of ui
    if (ui)
    {
        //GUI mode (Ex: ./cosmu)
        UImanager -> ApplyCommand("/control/execute vis.mac");
        ui -> SessionStart();
        delete ui;
	delete visManager;
    }

    else
    {
        //Batch mode (Ex: ./cosmu run.mac)
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager -> ApplyCommand(command + filename);
    }

    //Delete general process
    delete runManager;

    return 0;
}
