#----------------------------------------------------------------------------
#Setup the project (Executable file name = cosmu)
#----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(cosmu)

#----------------------------------------------------------------------------
#Find Geant4 package, with all available UI and Vis drivers activated
#----------------------------------------------------------------------------

find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
#Setup include directories for this project
#----------------------------------------------------------------------------

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
#Locate sources and headers for this project
#----------------------------------------------------------------------------

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
#Add the executable, and link it to the Geant4 libraries
#----------------------------------------------------------------------------

add_executable(cosmu main.cc ${sources} ${headers})
target_link_libraries(cosmu ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
#Copy all macro files to the build directory
#so that we can run the executable directly
#----------------------------------------------------------------------------

set(SCRIPTS
  run.mac
  vis.mac
  )

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
