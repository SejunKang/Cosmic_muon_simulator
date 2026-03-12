# How to use

**1. Download (You must install git first)**
  ```
  git clone git@github.com:SejunKang/Cosmic_muon_simulator.git
  ```

**2. Operate `CMAKE` to create the executable file**
```
cd cosmu
mkdir build
cd build
cmake ..
make
```

**3. Run the simulation**

a. Run in UI mode
```
./cosmu
```
Push the start button on the top of the GUI screen to shoot one muon beam. If you want to shoot multiple beams, type `/run/beamOn <number>` in the UI window.

b. Run in batch mode
```
./cosmu run.mac
```
This will automatically run the simulation without any graphic visualization. To change the number of beams, open `run.mac` and change the number in the line `/run/beamOn <number>`. You must do `make` in the `/build` directory after changing everything. 

**4. Other important factors**
- If you modify anything of the code, you must do `make` in the `/build` directory.
- If you make a new `.cc` or `.hh` file in the simulation set, or delete the existing file, you must do `cmake ..` before `make`.
- If there are any problems while running the `cmake`, type `ccmake ..` in the `/build` directory and check if all the environment variables are correctly registered.
- **Please call me if any other problems happen.** 
